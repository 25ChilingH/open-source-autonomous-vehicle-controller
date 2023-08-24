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
#include "RC_ESC.h"
#include "Garmin_v3hp.h"
#include "AS5047D.h"

/*******************************************************************************
 * #DEFINES                                                                    *
 ******************************************************************************/
#define CONTROL_PERIOD 20 //Period for control loop in msec
#define ENCODER_PERIOD 10 //re-initiate encoder at 100 Hz
#define BUFFER_SIZE 1024
#define UINT_16_MAX 0xffff
#define RAW 1
#define SCALED 2

#define GPS_PERIOD 100 //10 Hz update rate

#define HEARTBEAT_PERIOD 1000 //1 sec interval for hearbeat update

#define TEN_HZ 100000

/*******************************************************************************
 * VARIABLES                                                                   *
 ******************************************************************************/
struct IMU_out IMU_raw = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; //container for raw IMU data
struct IMU_out IMU_scaled = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; //container for scaled IMU data

static struct GPS_data GPS_data;

RCRX_channel_buffer RC_channels[CHANNELS];

static encoder_t encoder_data[NUM_ENCODERS];

static uint8_t IMU_test = FALSE;
static uint8_t GPS_test = FALSE;
static uint8_t Servo_test = FALSE;
static uint8_t Unidirectional_test = FALSE;
static uint8_t Bidirectional_test = FALSE;
static uint8_t Radio_test = FALSE;
static uint8_t Telemetry_test = FALSE;
static uint8_t Heartbeat_test = FALSE;
static uint8_t Lidar_test = FALSE;
static uint8_t Encoder_test = FALSE;

/*******************************************************************************
 * TYPEDEFS                                                                    *
 ******************************************************************************/
mavlink_system_t mavlink_system = {
    1, // System ID (1-255)
    MAV_COMP_ID_AUTOPILOT1 // Component ID (a MAV_COMPONENT value)
};

enum mav_output_type {
    USB,
    RADIO
};

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
 * @function check_GPS_events(void)
 * @param none
 * @brief checks for GPS messages, parses, and stores data in module gps variable
 * @author aaron hunter
 */
void check_GPS_events(void);

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
 * @function check_usb_events(void)
 * @param none
 * @brief looks for messages sent over the usb-c serial port to OSAVC, parses
 * them and provides responses, if needed
 * @author Aaron Hunter
 */
void check_usb_events(void);

/**
 * @function publish_IMU_data()
 * @param data_type RAW or SCALED
 * @brief reads module level IMU data and publishes over radio serial in Mavlink
 * @author Aaron Hunter
 */
void publish_IMU_data(uint8_t data_type);

/**
 * @function publish_GPS(void)
 * @param none
 * @brief invokes mavlink helper function to generate GPS message and sends to
 * radio serial port
 * @author aaron hunter
 */
void publish_GPS(void);

void publish_LIDAR(void);

void publish_RC_data(void);

int set_and_publish_pulse(uint8_t servo, uint8_t motor, uint16_t test_pulse, int direction, uint16_t max, uint16_t min);

void publish_encoder(void);

/**
 * @Function publish_heartbeat(uint8_t dest)
 * @param dest, either USB or RADIO
 * @brief publishes heartbeat message 
 * @return none
 * @author Aaron Hunter
 */
void publish_heartbeat(uint8_t dest);

/**
 * @Function publish_parameter(uint8_t param_id[16])
 * @param parameter ID
 * @brief invokes mavlink helper to send out stored parameter 
 * @author aaron hunter
 */
void publish_parameter(uint8_t param_id[16], uint8_t dest);

/**
 * @Function mavprint(char msg_buffer[], int8_t msg_length, int8_t output);
 * @param msg_buffer, string of bytes to send to receiver
 * @param msg_length, length of msg_buffer
 * @param output, either USB or RADIO, which peripheral to send the message from
 * @return SUCCESS or ERROR
 */
int8_t mavprint(uint8_t msg_buffer[], uint8_t msg_length, uint8_t output);
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
                    if (heartbeat.type) {
                        msg_length = sprintf(msg_buffer, "heartbeat received type(%d)\r\n", heartbeat.type);
                        mavprint(msg_buffer, msg_length, RADIO);
                    }
                    break;
                case MAVLINK_MSG_ID_COMMAND_LONG:
                    mavlink_msg_command_long_decode(&msg_rx, &command_qgc);
                    msg_length = sprintf(msg_buffer, "Command ID %d received from Ground Control\r\n", command_qgc.command);
                    mavprint(msg_buffer, msg_length, RADIO);
                    break;
                case MAVLINK_MSG_ID_PARAM_REQUEST_READ:
                    mavlink_msg_param_request_read_decode(&msg_rx, &param_read);
                    msg_length = sprintf(msg_buffer, "Parameter request ID %s received from Ground Control\r\n", param_read.param_id);
                    mavprint(msg_buffer, msg_length, RADIO);
                    publish_parameter(param_read.param_id, USB);
                    break;
                default:
                    msg_length = sprintf(msg_buffer, "Received message with ID %d, sequence: %d from component %d of system %d\r\n",
                            msg_rx.msgid, msg_rx.seq, msg_rx.compid, msg_rx.sysid);
                    mavprint(msg_buffer, msg_length, RADIO);
                    break;
            }
        }
    }
}

/**
 * @function check_usb_events(void)
 * @param none
 * @brief looks for messages sent over the usb-c serial port to OSAVC, parses
 * them and provides responses, if needed
 * @author Aaron Hunter
 */
void check_usb_events(void) {
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

    if (msg_byte = get_char()) {
        if (mavlink_parse_char(channel, msg_byte, &msg_rx, &msg_rx_status)) {
            switch (msg_rx.msgid) {
                case MAVLINK_MSG_ID_HEARTBEAT:
                    mavlink_msg_heartbeat_decode(&msg_rx, &heartbeat);
                    if (heartbeat.type) {
                        msg_length = sprintf(msg_buffer, "heartbeat received type(%d)\r\n", heartbeat.type);
                        mavprint(msg_buffer, msg_length, RADIO);
                    }
                    break;
                case MAVLINK_MSG_ID_COMMAND_LONG:
                    mavlink_msg_command_long_decode(&msg_rx, &command_qgc);
                    msg_length = sprintf(msg_buffer, "Command ID %d received from Ground Control\r\n", command_qgc.command);
                    mavprint(msg_buffer, msg_length, RADIO);
                    break;
                case MAVLINK_MSG_ID_PARAM_REQUEST_READ:
                    mavlink_msg_param_request_read_decode(&msg_rx, &param_read);
                    msg_length = sprintf(msg_buffer, "Parameter request ID %s received from Ground Control\r\n", param_read.param_id);
                    mavprint(msg_buffer, msg_length, RADIO);
                    publish_parameter(param_read.param_id, USB);
                    break;
                default:
                    msg_length = sprintf(msg_buffer, "Received message with ID %d, sequence: %d from component %d of system %d\r\n",
                            msg_rx.msgid, msg_rx.seq, msg_rx.compid, msg_rx.sysid);
                    mavprint(msg_buffer, msg_length, RADIO);
                    break;
            }
        }
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
        printf("a: %+0.1f %+0.1f %+0.1f g: %+0.1f %+0.1f %+0.1f m: %+0.1f %+0.1f %+0.1f \r",
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
        printf("a: %+0.3f %+0.3f %+0.3f g: %+0.3f %+0.3f %+0.3f m: %+0.3f %+0.3f %+0.3f \r",
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

void publish_LIDAR(void) {
    uint16_t range;
    range = Lidar_get_range();
    printf("Range: %d cm\r\n", range);
    if (Lidar_get_I2C_error() == TRUE) {
        printf("I2C Error \r\n");
    }
}

void publish_RC_data(void) {
    printf("%d, %d, %d, %d, %d, %d, %d, %d, %d \r",
            RC_channels[0], RC_channels[1], RC_channels[2], RC_channels[3],
            RC_channels[4], RC_channels[5], RC_channels[6], RC_channels[7],
            RC_channels[8]);
}

int set_and_publish_pulse(uint8_t servo, uint8_t motor, uint16_t test_pulse, int direction, uint16_t max, uint16_t min) {
    if (servo == TRUE) {
        RC_servo_set_pulse(test_pulse, motor);
        printf("SERVO_PWM_%d: %d, current ticks: %d \r\n", motor + 1, RC_servo_get_pulse(motor), RC_servo_get_raw_ticks(motor));
    } else {
        RC_ESC_set_pulse(test_pulse, motor);
        printf("ESC_PWM_%d: %d, current ticks: %d \r\n", motor + 1, RC_ESC_get_pulse(motor), RC_ESC_get_raw_ticks(motor));
    }

    if (direction == 1 && test_pulse > max) {
        direction = -1;
    } else if (direction == -1 && test_pulse < min) {
        direction = 1;
    }

    return direction;
}

void publish_encoder(void) {
    char name[] = "LRH";
    for (int i = 0; i < NUM_ENCODERS; i++) {
        printf("%c: %6d, %6d\r", name[i], Encoder_get_angle(i), Encoder_get_velocity(i));
    }
}

/**
 * @Function publish_heartbeat(mav_output_type dest)
 * @param dest, either USB or RADIO
 * @brief publishes heartbeat message 
 * @return none
 * @author Aaron Hunter
 */
void publish_heartbeat(uint8_t dest) {
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
    mavprint(msg_buffer, msg_length, dest);
}

/**
 * @Function publish_parameter(uint8_t param_id[16])
 * @param parameter ID
 * @brief invokes mavlink helper to send out stored parameter 
 * @author aaron hunter
 */
void publish_parameter(uint8_t param_id[16], uint8_t dest) {
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
    mavprint(msg_buffer, msg_length, dest);
}

/**
 * @Function mavprint(char msg_buffer[], int8_t msg_length, int8_t output);
 * @param msg_buffer, string of bytes to send to receiver
 * @param msg_length, length of msg_buffer
 * @param output, either USB or RADIO, which peripheral to send the message from
 * @return SUCCESS or ERROR
 */
int8_t mavprint(uint8_t msg_buffer[], uint8_t msg_length, uint8_t output) {
    uint8_t i;
    if (output == USB) {
        for (i = 0; i < msg_length; i++) {
            putchar(msg_buffer[i]);
        }
    } else if (output == RADIO) {
        for (i = 0; i < msg_length; i++) {
            Radio_put_char(msg_buffer[i]);
        }
    } else {
        return ERROR;
    }
    return SUCCESS;
}

int main(void) {
    uint32_t cur_time = 0;
    uint32_t warmup_time = 250; //time in ms to allow subsystems to stabilize (IMU))
    uint32_t control_start_time = 0;

    char c;

    //Initialization routines
    Board_init(); //board configuration
    Serial_init(); //start debug terminal (USB)
    Sys_timer_init(); //start the system timer

    /*small delay to get all the subsystems time to get online*/
    while (cur_time < warmup_time) {
        cur_time = Sys_timer_get_msec();
    }

    printf("\r\nChoose the peripherals that you would like to test: \r\n");
    printf("For IMU, type i \r\n");
    printf("For GPS, type g \r\n");
    printf("For DC brushless unidirectional motors, type u (PWM output channel 1) \r\n");
    printf("For DC brushless bidirectional motors, type b (PWM output channel 2) \r\n");
    printf("For servo motors, type s (PWM output channels 3 and 4) \r\n");
    printf("For radio controller, type c \r\n");
    printf("For telemetry radio, type t \r\n");
    printf("For heartbeat over USB, type h \r\n");
    printf("For LIDAR, type l \r\n");
    printf("For encoders, type e \r\n");
    printf("**********************************************\r\n");

    while (1) {
        if (c = get_char()) {
            put_char(c);
        }
        if (c == 'i' || c == 'I') {
            IMU_test = TRUE;
            break;
        }
        if (c == 'g' || c == 'G') {
            GPS_test = TRUE;
            break;
        }
        if (c == 'u' || c == 'U') {
            Unidirectional_test = TRUE;
            break;
        }
        if (c == 'b' || c == 'B') {
            Bidirectional_test = TRUE;
            break;
        }
        if (c == 's' || c == 'S') {
            Servo_test = TRUE;
            break;
        }
        if (c == 'c' || c == 'C') {
            Radio_test = TRUE;
            break;
        }
        if (c == 't' || c == 'T') {
            Telemetry_test = TRUE;
            break;
        }
        if (c == 'h' || c == 'H') {
            Heartbeat_test = TRUE;
            break;
        }
        if (c == 'l' || c == 'L') {
            Lidar_test = TRUE;
            break;
        }
        if (c == 'e' || c == 'E') {
            Encoder_test = TRUE;
            break;
        }
        if (c == '\r') break;
    }

    printf("\r\n");

    int8_t IMU_state = ERROR;
    int8_t IMU_retry = 5;
    uint32_t IMU_error = 0;
    uint8_t error_report = 50;

    uint32_t gps_start_time = 0;

    uint16_t uni_test_pulse;
    uint16_t bi_test_pulse;
    uint16_t servo_test_pulse;
    if (Unidirectional_test) uni_test_pulse = RC_ESC_MIN_PULSE;
    if (Bidirectional_test) bi_test_pulse = RC_ESC_CENTER_PULSE;
    if (Servo_test) servo_test_pulse = RC_SERVO_CENTER_PULSE;
    uint16_t motor_start_time;
    uint16_t motor_cur_time;
    uint16_t ESC_time = 5000;
    uint16_t motor_test_time = 250;
    int uni_direction = 1;
    int bi_direction = 1;
    int servo_direction = 1;

    uint32_t heartbeat_start_time = 0;

    int startTime;
    int loopTime = TEN_HZ;

    uint32_t encoder_start_time = 0;

    if (IMU_test == TRUE) {
        IMU_state = IMU_init(IMU_SPI_MODE);
        if (IMU_state == ERROR && IMU_retry > 0) {
            IMU_state = IMU_init(IMU_SPI_MODE);
            printf("IMU failed init, retrying %d \r\n", IMU_retry);
            IMU_retry--;
        }
    }

    if (GPS_test == TRUE) GPS_init();

    if (Unidirectional_test == TRUE || Bidirectional_test == TRUE) {
        if (Unidirectional_test) {
            RC_ESC_init(ESC_UNIDIRECTIONAL_TYPE, BRUSHLESS_PWM_1);
        }
        if (Bidirectional_test)
            RC_ESC_init(ESC_BIDIRECTIONAL_TYPE, BRUSHLESS_PWM_2);
        motor_start_time = Sys_timer_get_msec();
        motor_cur_time = motor_start_time;
        while ((motor_cur_time - motor_start_time) <= ESC_time) {
            motor_cur_time = Sys_timer_get_msec();
        }
    }

    if (Servo_test == TRUE) {
        RC_servo_init(SERVO_PWM_3);
        RC_servo_init(SERVO_PWM_4);
    } // start the servo subsystem


    if (Radio_test == TRUE) RCRX_init();

    if (Telemetry_test == TRUE) Radio_serial_init();

    if (Lidar_test == TRUE) {
        Lidar_Init();
        startTime = Sys_timer_get_msec();
        /*Need to specify a warm-up time of 22msec before taking the first measurement*/
        while (Sys_timer_get_msec() < startTime + 22) {
            ;
        }
    }

    if (Encoder_test == TRUE) {
        Encoder_init();
    }

    printf("\r\nTest Harness %s, %s \r\n", __DATE__, __TIME__);

    while (1) {
        cur_time = Sys_timer_get_msec();
        //check for all events
        if (IMU_test == TRUE) check_IMU_events(); //check for IMU data ready and publish when available

        if (Telemetry_test == TRUE) check_radio_events();

        if (Heartbeat_test == TRUE) check_usb_events();

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
        }

        if (Unidirectional_test == TRUE || Bidirectional_test == TRUE || Servo_test == TRUE) {
            if (Unidirectional_test == TRUE) {
                uni_direction = set_and_publish_pulse(FALSE, BRUSHLESS_PWM_1, uni_test_pulse, uni_direction, RC_ESC_CENTER_PULSE, RC_ESC_MIN_PULSE);
                uni_test_pulse += uni_direction * 10;
            }

            if (Bidirectional_test == TRUE) {
                bi_direction = set_and_publish_pulse(FALSE, BRUSHLESS_PWM_2, bi_test_pulse, bi_direction, RC_ESC_MAX_PULSE, RC_ESC_MIN_PULSE);
                bi_test_pulse += bi_direction * 10;
            }

            if (Servo_test == TRUE) {
                set_and_publish_pulse(TRUE, SERVO_PWM_3, servo_test_pulse, servo_direction, RC_SERVO_MAX_PULSE, RC_SERVO_MIN_PULSE);
                servo_direction = set_and_publish_pulse(TRUE, SERVO_PWM_4, servo_test_pulse, servo_direction, RC_SERVO_MAX_PULSE, RC_SERVO_MIN_PULSE);
                servo_test_pulse += servo_direction * 50;
            }

            motor_start_time = Sys_timer_get_msec();
            motor_cur_time = motor_start_time;
            while ((motor_cur_time - motor_start_time) <= motor_test_time) {
                motor_cur_time = Sys_timer_get_msec();
            }
        }

        if (Radio_test == TRUE) {
            if (RCRX_new_cmd_avail() == TRUE) {
                RCRX_get_cmd(RC_channels);
                ///*Throttle is assigned to elevator channel to center at midpoint for ESCs unlike
                // how an airplane motor is configured.  We need reverse drive in other words.
                // Steering servo is assigned to rudder channel, may be easier to drive on aileron
                // Switch D is for passthrough mode and assigned to channel .  Low is passthrough, High is autonomous*/
                publish_RC_data();
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

        if (Telemetry_test == TRUE) {
            if (Radio_data_available() == TRUE) {
                c = Radio_get_char();
                Radio_put_char(c); //send via the radio
                put_char(c); //send over USB/debug also
            }
        }

        if (Heartbeat_test == TRUE) {
            //publish heartbeat
            if (cur_time - heartbeat_start_time >= HEARTBEAT_PERIOD) {
                heartbeat_start_time = cur_time; //reset the timer
                publish_heartbeat(USB);
            }
        }

        if (Lidar_test == TRUE) {
            startTime = Sys_timer_get_usec();

            if (Sys_timer_get_usec() > startTime + loopTime) {
                startTime = Sys_timer_get_usec();
                publish_LIDAR();
            }
        }

        if (Encoder_test == TRUE) {
            //for now start encoder every ENCODER_PERIOD but publish every CONTROL_PERIOD
            if (cur_time - encoder_start_time >= ENCODER_PERIOD) {
                encoder_start_time = cur_time; //reset control loop timer
                Encoder_start_data_acq(); //initiate Encoder measurement with SPI
            }
            if (Encoder_is_data_ready() == TRUE) {
                Encoder_get_data(encoder_data);
                publish_encoder();
            }
        }
    }
    return 0;
}