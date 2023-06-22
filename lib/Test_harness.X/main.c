/*
 * File:   main.c
 * Author: Chiling Han
 * Brief:  Test harness for all peripherals of the OSAVC
 * Created on June 19, 2023 at 1:00pm
 */

/*******************************************************************************
 * #INCLUDES                                                                   *
 ******************************************************************************/
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include "xc.h"
#include "SerialM32.h"
#include "Board.h"
#include "System_timer.h"
#include "ICM_20948.h"
#include "RC_servo.h"
#include "NEO_M8N.h"
#include "common/mavlink.h"
#include "Radio_serial.h"
#include "RC_RX.h"

/*******************************************************************************
 * #DEFINES                                                                    *
 ******************************************************************************/
#define CONTROL_PERIOD 20 //Period for control loop in msec
#define BUFFER_SIZE 1024
#define UINT_16_MAX 0xffff
#define RAW 1
#define SCALED 2

#define GPS_PERIOD 100 //10 Hz update rate

#define HEARTBEAT_PERIOD 1000 //1 sec interval for hearbeat update

/*******************************************************************************
 * VARIABLES                                                                   *
 ******************************************************************************/
mavlink_system_t mavlink_system = {
    1, // System ID (1-255)
    MAV_COMP_ID_AUTOPILOT1 // Component ID (a MAV_COMPONENT value)
};

struct IMU_out IMU_raw = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; //container for raw IMU data
struct IMU_out IMU_scaled = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; //container for scaled IMU data

static struct GPS_data GPS_data;

static uint8_t IMU_test = FALSE;
static uint8_t GPS_test = TRUE;
static uint8_t Servo_test = FALSE;
static uint8_t Brushless_test = FALSE;
static uint8_t Radio_test = FALSE;
static uint8_t Heartbeat_test = FALSE;

/*******************************************************************************
 * TYPEDEFS                                                                    *
 ******************************************************************************/


/*******************************************************************************
 * FUNCTION PROTOTYPES                                                         *
 ******************************************************************************/
/**
 * @function check_IMU_events(void)
 * @param none
 * @brief detects when IMU SPI transaction completes and then publishes data over Mavlink
 * @author Aaron Hunter
 */
void check_IMU_events(void);

/**
 * @function publish_IMU_data()
 * @param data_type RAW or SCALED
 * @brief reads module level IMU data and publishes over radio serial in Mavlink
 * @author Aaron Hunter
 */
void publish_IMU_data(uint8_t data_type);

/**
 * @function check_GPS_events(void)
 * @param none
 * @brief checks for GPS messages, parses, and stores data in module gps variable
 * @author aaron hunter
 */
void check_GPS_events(void);

/**
 * @function publish_GPS(void)
 * @param none
 * @brief invokes mavlink helper function to generate GPS message and sends to
 * radio serial port
 * @author aaron hunter
 */
void publish_GPS(void);

/**
 * @function check_radio_events(void)
 * @param none
 * @brief looks for messages sent over the radio serial port to OSAVC, parses
 * them and provides responses, if needed
 * @note currently only pushing information to usb-serial port
 * @author Aaron Hunter
 */
void check_radio_events(void);

/**
 * @Function publish_heartbeat(void)
 * @param none
 * @brief invokes mavlink helper to generate heartbeat and sends out via the radio
 * @author aaron hunter
 */
void publish_heartbeat(void);

/**
 * @Function publish_parameter(uint8_t param_id[16])
 * @param parameter ID
 * @brief invokes mavlink helper to send out stored parameter 
 * @author aaron hunter
 */
void publish_parameter(uint8_t param_id[16]);
/*******************************************************************************
 * FUNCTIONS                                                                   *
 ******************************************************************************/

/**
 * @function check_IMU_events(void)
 * @param none
 * @brief detects when IMU SPI transaction completes and then publishes data over Mavlink
 * @author Aaron Hunter
 */
void check_IMU_events(void) {
    if (IMU_is_data_ready() == TRUE) {
        IMU_get_raw_data(&IMU_raw);
        //        publish_IMU_data(RAW);
        IMU_get_scaled_data(&IMU_scaled);
        //        if (pub_IMU == TRUE) {
        //            publish_IMU_data(RAW);
        //        }
    }
}

/**
 * @function publish_IMU_data()
 * @param none
 * @brief reads module level IMU data and publishes over radio serial in Mavlink
 * @author Aaron Hunter
 */
void publish_IMU_data(uint8_t data_type) {
    if (data_type == RAW) {
        printf("a: %d %d %d g: %d %d %d m: %d %d %d \r",
                IMU_raw.acc.x,
                IMU_raw.acc.y,
                IMU_raw.acc.z, 
                IMU_raw.gyro.x,
                IMU_raw.gyro.y,
                IMU_raw.gyro.z,
                IMU_raw.mag.x,
                IMU_raw.mag.x,
                IMU_raw.mag.z);
    } else if (data_type == SCALED) {
                printf("a: %d %d %d g: %d %d %d m: %d %d %d \r",
                IMU_scaled.acc.x,
                IMU_scaled.acc.y,
                IMU_scaled.acc.z, 
                IMU_scaled.gyro.x,
                IMU_scaled.gyro.y,
                IMU_scaled.gyro.z,
                IMU_scaled.mag.x,
                IMU_scaled.mag.x,
                IMU_scaled.mag.z);
    }
    
}

/**
 * @function check_GPS_events(void)
 * @param none
 * @brief checks for GPS messages, parses, and stores data in module gps variable
 * @author Aaron Hunter
 */
void check_GPS_events(void) {
    if (GPS_is_msg_avail() == TRUE) {
        GPS_parse_stream();
    }
    if (GPS_is_data_avail() == TRUE) {
        GPS_get_data(&GPS_data);
    }
}

/**
 * @function publish_GPS(void)
 * @param none
 * @brief invokes mavlink helper function to generate GPS message and sends to
 * radio serial port
 * @author Aaron Hunter
 */
void publish_GPS(void) {
    printf("Fix: %d Lat: %0.6f Lon: %0.6f Speed: %3.3f Heading: %0.6f\r", 
            (uint8_t) GPS_has_fix(),
            GPS_data.lat,
            GPS_data.lon,
            GPS_data.spd,
            GPS_data.cog);

}

/**
 * @function check_radio_events(void)
 * @param none
 * @brief looks for messages sent over the radio serial port to OSAVC, parses
 * them and provides responses, if needed
 * @note currently only pushing information to usb-serial port
 * @author Aaron Hunter
 */
void check_radio_events(void) {
    uint8_t channel = MAVLINK_COMM_0;
    uint8_t msg_byte;
    uint16_t msg_length;
    uint8_t msg_buffer[BUFFER_SIZE];
    mavlink_message_t msg_rx;
    mavlink_status_t msg_rx_status;

    //MAVLink command structs
    mavlink_heartbeat_t heartbeat;
    mavlink_command_long_t command_qgc;
    mavlink_param_request_read_t param_read;

    if (Radio_data_available()) {
        msg_byte = Radio_get_char();
        if (mavlink_parse_char(channel, msg_byte, &msg_rx, &msg_rx_status)) {
            switch (msg_rx.msgid) {
                case MAVLINK_MSG_ID_HEARTBEAT:
                    mavlink_msg_heartbeat_decode(&msg_rx, &heartbeat);
                    if (heartbeat.type)
                        printf("heartbeat received type(%d)\r\n", heartbeat.type);
                    break;
                case MAVLINK_MSG_ID_COMMAND_LONG:
                    mavlink_msg_command_long_decode(&msg_rx, &command_qgc);
                    printf("Command ID %d received from Ground Control\r\n", command_qgc.command);
                    break;
                case MAVLINK_MSG_ID_PARAM_REQUEST_READ:
                    mavlink_msg_param_request_read_decode(&msg_rx, &param_read);
                    printf("Parameter request ID %s received from Ground Control\r\n", param_read.param_id);
                    publish_parameter(param_read.param_id);
                    break;
                default:
                    printf("Received message with ID %d, sequence: %d from component %d of system %d\r\n",
                            msg_rx.msgid, msg_rx.seq, msg_rx.compid, msg_rx.sysid);
                    break;
            }
        }
    }
}

/**
 * @Function publish_heartbeat(void)
 * @param none
 * @brief invokes mavlink helper to generate heartbeat and sends out via the radio
 * @author aaron hunter
 */
void publish_heartbeat(void) {
    mavlink_message_t msg_tx;
    uint16_t msg_length;
    uint8_t msg_buffer[BUFFER_SIZE];
    uint16_t index = 0;
    uint8_t mode = MAV_MODE_FLAG_MANUAL_INPUT_ENABLED | MAV_MODE_FLAG_SAFETY_ARMED;
    uint32_t custom = 0;
    uint8_t state = MAV_STATE_STANDBY;
    mavlink_msg_heartbeat_pack(mavlink_system.sysid
            , mavlink_system.compid,
            &msg_tx,
            MAV_TYPE_GROUND_ROVER, MAV_AUTOPILOT_GENERIC,
            mode,
            custom,
            state);
    msg_length = mavlink_msg_to_send_buffer(msg_buffer, &msg_tx);
    for (index = 0; index < msg_length; index++) {
        Radio_put_char(msg_buffer[index]);
    }
}

/**
 * @Function publish_parameter(uint8_t param_id[16])
 * @param parameter ID
 * @brief invokes mavlink helper to send out stored parameter 
 * @author aaron hunter
 */
void publish_parameter(uint8_t param_id[16]) {
    mavlink_message_t msg_tx;
    uint16_t msg_length;
    uint8_t msg_buffer[BUFFER_SIZE];
    uint16_t index = 0;
    float param_value = 320.0; // value of the requested parameter
    uint8_t param_type = MAV_PARAM_TYPE_INT16; // onboard mavlink parameter type
    uint16_t param_count = 1; // total number of onboard parameters
    uint16_t param_index = 1; //index of this value
    mavlink_msg_param_value_pack(mavlink_system.sysid,
            mavlink_system.compid,
            &msg_tx,
            param_id,
            param_value,
            param_type,
            param_count,
            param_index
            );
    msg_length = mavlink_msg_to_send_buffer(msg_buffer, &msg_tx);
    for (index = 0; index < msg_length; index++) {
        Radio_put_char(msg_buffer[index]);
    }
}


int main(void) {
    uint32_t cur_time = 0;
    uint32_t warmup_time = 250; //time in ms to allow subsystems to stabilize (IMU))
    uint32_t control_start_time = 0;
    
    int8_t IMU_state = ERROR;
    int8_t IMU_retry = 5;
    uint32_t IMU_error = 0;
    uint8_t error_report = 50;
    
    uint32_t gps_start_time = 0;
    int i;
    
    uint16_t test_pulse = Brushless_test ? RC_SERVO_MIN_PULSE : RC_SERVO_CENTER_PULSE;
    uint16_t ESC_start_time;
    uint16_t ESC_cur_time;
    uint16_t ESC_time = 5000;
    uint16_t ESC_test_time = 250;
    int direction = 1;

    uint32_t heartbeat_start_time = 0;
    
    RCRX_channel_buffer servo_data[CHANNELS];

    //Initialization routines
    Board_init(); //board configuration
    Serial_init(); //start debug terminal (USB)
    Sys_timer_init(); //start the system timer
    
    /*small delay to get all the subsystems time to get online*/
    while (cur_time < warmup_time) {
        cur_time = Sys_timer_get_msec();
    }
    
    if (IMU_test == TRUE) {
        IMU_state = IMU_init(IMU_SPI_MODE);
        if (IMU_state == ERROR && IMU_retry > 0) {
            IMU_state = IMU_init(IMU_SPI_MODE);
            printf("IMU failed init, retrying %d \r\n", IMU_retry);
            IMU_retry--;
        }
    }

    if (GPS_test == TRUE) GPS_init();
    
    if (Servo_test == TRUE) {
        RC_servo_init(RC_SERVO_TYPE, SERVO_PWM_1);
        RC_servo_init(RC_SERVO_TYPE, SERVO_PWM_2);
        RC_servo_init(RC_SERVO_TYPE, SERVO_PWM_3);
        RC_servo_init(RC_SERVO_TYPE, SERVO_PWM_4);
    } // start the servo subsystem

    if (Brushless_test == TRUE) {
        RC_servo_init(ESC_UNIDIRECTIONAL_TYPE, SERVO_PWM_1);
        RC_servo_init(ESC_UNIDIRECTIONAL_TYPE, SERVO_PWM_2);
        RC_servo_init(ESC_UNIDIRECTIONAL_TYPE, SERVO_PWM_3);
        RC_servo_init(ESC_UNIDIRECTIONAL_TYPE, SERVO_PWM_4);
        ESC_start_time = Sys_timer_get_msec();
        ESC_cur_time = ESC_start_time;
        while ((ESC_cur_time - ESC_start_time) <= ESC_time) {
            ESC_cur_time = Sys_timer_get_msec();
        }
    }
    
    if (Radio_test == TRUE) RCRX_init();
    
    if (Heartbeat_test == TRUE) Radio_serial_init();
    
    printf("\r\nTest Harness %s, %s \r\n", __DATE__, __TIME__);

    while (1) {
        cur_time = Sys_timer_get_msec();
        //check for all events
        if (IMU_test == TRUE) check_IMU_events(); //check for IMU data ready and publish when available

        if (Radio_test == TRUE) check_radio_events();
        //publish control and sensor signals
        if (cur_time - control_start_time >= CONTROL_PERIOD) {
            control_start_time = cur_time; //reset control loop timer
            if (IMU_test == TRUE) {
                publish_IMU_data(RAW);
                
                /*start next data acquisition round*/
                IMU_state = IMU_start_data_acq(); //initiate IMU measurement with SPI
                if (IMU_state == ERROR) {
                    IMU_error++;
                    if (IMU_error % error_report == 0) {
                        printf("IMU error count %d\r\n", IMU_error);
                    }
                }
            }
            
            if (Servo_test == TRUE || Brushless_test == TRUE) {
                if (Servo_test == TRUE) {
                    if (direction == 1) {
                        RC_servo_set_pulse(test_pulse, SERVO_PWM_1);
                        RC_servo_set_pulse(test_pulse, SERVO_PWM_2);
                        RC_servo_set_pulse(test_pulse, SERVO_PWM_3);
                        RC_servo_set_pulse(test_pulse, SERVO_PWM_4);
                        test_pulse += 10;
                        if (test_pulse > RC_SERVO_MAX_PULSE) {
                            direction = -1;
                        }
                    }
                    if (direction == -1) {
                        RC_servo_set_pulse(test_pulse, SERVO_PWM_1);
                        RC_servo_set_pulse(test_pulse, SERVO_PWM_2);
                        RC_servo_set_pulse(test_pulse, SERVO_PWM_3);
                        RC_servo_set_pulse(test_pulse, SERVO_PWM_4);
                        test_pulse -= 10;
                        if (test_pulse < RC_SERVO_MIN_PULSE) {
                            direction = 1;
                        }
                    }
                }
                
                if (Brushless_test == TRUE) {
                    if (direction == 1) {
                        RC_servo_set_pulse(test_pulse, SERVO_PWM_1);
                        RC_servo_set_pulse(test_pulse, SERVO_PWM_2);
                        RC_servo_set_pulse(test_pulse, SERVO_PWM_3);
                        RC_servo_set_pulse(test_pulse, SERVO_PWM_4);
                        test_pulse += 50;
                        if (test_pulse > RC_SERVO_CENTER_PULSE) {
                            direction = -1;
                        }
                    }
                    if (direction == -1) {
                        RC_servo_set_pulse(test_pulse, SERVO_PWM_1);
                        RC_servo_set_pulse(test_pulse, SERVO_PWM_2);
                        RC_servo_set_pulse(test_pulse, SERVO_PWM_3);
                        RC_servo_set_pulse(test_pulse, SERVO_PWM_4);
                        test_pulse -= 50;
                        if (test_pulse < RC_SERVO_MIN_PULSE) {
                            direction = 1;
                        }
                    }
                    
                    
                
                }
                
                printf("SERVO_PWM_1: %d, current ticks: %d \r\n", RC_servo_get_pulse(SERVO_PWM_1), RC_servo_get_raw_ticks(SERVO_PWM_1));
                printf("SERVO_PWM_2: %d, current ticks: %d \r\n", RC_servo_get_pulse(SERVO_PWM_2), RC_servo_get_raw_ticks(SERVO_PWM_2));
                printf("SERVO_PWM_3: %d, current ticks: %d \r\n", RC_servo_get_pulse(SERVO_PWM_3), RC_servo_get_raw_ticks(SERVO_PWM_3));
                printf("SERVO_PWM_4: %d, current ticks: %d \r\n", RC_servo_get_pulse(SERVO_PWM_4), RC_servo_get_raw_ticks(SERVO_PWM_4));
                
                if (Brushless_test == TRUE) {
                    ESC_start_time = Sys_timer_get_msec();
                    ESC_cur_time = ESC_start_time;
                    while ((ESC_cur_time - ESC_start_time) <= ESC_test_time) {
                        ESC_cur_time = Sys_timer_get_msec();
                    }
                
                }
            }
     
        }
        
        if (Radio_test == TRUE) {
            if (RCRX_new_cmd_avail() == TRUE) {
                RCRX_get_cmd(servo_data);
                ///*Throttle is assigned to elevator channel to center at midpoint for ESCs unlike
                // how an airplane motor is configured.  We need reverse drive in other words.
                // Steering servo is assigned to rudder channel, may be easier to drive on aileron
                // Switch D is for passthrough mode and assigned to channel .  Low is passthrough, High is autonomous*/
                printf("%d, %d, %d, %d, %d, %d, %d, %d, %d \r",
                        servo_data[0], servo_data[1], servo_data[2], servo_data[3],
                        servo_data[4], servo_data[5], servo_data[6], servo_data[7],
                        servo_data[8]);
                // printf("T %d S %d M %d stat %x ERR %d \r", servo_data[2], servo_data[3], \
                // servo_data[7], RCRX_msgs.sbus_buffer[RCRX_msgs.read_index][23], parse_error_counter);
                // printf("stat %x ERR %d \r\n", RCRX_msgs.sbus_buffer[RCRX_msgs.read_index][23], parse_error_counter);
            }
        }
        
        if (GPS_test == TRUE) {
            check_GPS_events(); //check and process incoming GPS messages

            //publish GPS
            if (cur_time - gps_start_time > GPS_PERIOD) {
                gps_start_time = cur_time; //reset GPS timer
                publish_GPS();
            }
        }
        
        if (Heartbeat_test == TRUE) {
                //publish heartbeat
            if (cur_time - heartbeat_start_time >= HEARTBEAT_PERIOD) {
                heartbeat_start_time = cur_time; //reset the timer
                publish_heartbeat();
            }
        }


    }
    return 0;
}