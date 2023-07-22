/* 
 * File:   RC_ESC.c
 * Author: Chiling Han
 * Brief: Library driver for up to four DC brushless motors for the Max32 dev board
 * Created on 07/19/2023 8:30 pm
 */

/*******************************************************************************
 * #INCLUDES                                                                   *
 ******************************************************************************/

#include "RC_ESC.h" // The header file for this source file.
#include "Board.h"   //Max32 setup
#include "SerialM32.h"
#include "System_timer.h"
#include <xc.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/attribs.h>  //for ISR definitions
#include <proc/p32mx795f512l.h>



/*******************************************************************************
 * PRIVATE #DEFINES                                                            *
 ******************************************************************************/
#define USEC_NUM 5  //numerator multiplier to avoid divides
#define USEC_LOG_DEN 1  //right shift to divide by 2^x

/*******************************************************************************
 * PRIVATE VARIABLES                                                            *
 ******************************************************************************/
static uint16_t pulse_width[RC_ESC_NUM_OUTPUTS]; //PW in microseconds
static uint16_t raw_ticks[RC_ESC_NUM_OUTPUTS]; // raw ticks corresponding to pulse width
static int8_t RC_SET_NEW_CMD = FALSE; //flag to indicate when the new command can be loaded 
/*******************************************************************************
 * PRIVATE FUNCTIONS PROTOTYPES                                                 *
 ******************************************************************************/

/**
 * @Function delay(int cycles)
 * @param cycles, number of cycles to delay
 * @brief simple delay loop
 * @note ~500nsec for one delay, then +12.5 nsec for every increment higher
 */
void RC_ESC_delay(int cycles);
/*******************************************************************************
 * PUBLIC FUNCTION IMPLEMENTATIONS                                             *
 ******************************************************************************/

/**
 * @Function RC_ESC_init(void)
 * @param None
 * @return SUCCESS or ERROR
 * @brief initializes hardware required and set it to the correct initial setting
 *  */
int8_t RC_ESC_init(uint8_t output_type, uint8_t output_channel) {
    uint8_t i;
    uint16_t ticks_center = (RC_ESC_CENTER_PULSE * USEC_NUM) >> USEC_LOG_DEN;
    uint16_t ticks_min = (RC_ESC_MIN_PULSE * USEC_NUM) >> USEC_LOG_DEN;
    printf("min ticks %d \r\n", ticks_min);

    __builtin_disable_interrupts();
    /* timer 2 settings */
    T2CON = 0;
    TMR2 = 0x0;
    T2CONbits.TCKPS = 0b101; // prescaler set to 1:32
    PR2 = 12499; //5 msec <=> 200 Hz; period = PB_CLOCK_FREQ / prescaler / 
    /*setup timer2 interrupt on period rollover*/
    IPC2bits.T2IP = 0b110; //priority 6
    IPC2bits.T2IS = 0b10; // subpriority 2
    IFS0bits.T2IF = 0; // clear interrupt flag
    IEC0bits.T2IE = 1; //enable interrupt

    /* Output Capture configuration*/
    switch (output_channel) {
        case BRUSHLESS_PWM_1:
            if (output_type == ESC_BIDIRECTIONAL_TYPE) {
                pulse_width[BRUSHLESS_PWM_1] = RC_ESC_CENTER_PULSE;
                raw_ticks[BRUSHLESS_PWM_1] = ticks_center;
            } else {
                pulse_width[BRUSHLESS_PWM_1] = RC_ESC_MIN_PULSE;
                raw_ticks[BRUSHLESS_PWM_1] = ticks_min;
            }
            OC2CON = 0x0000; //Turn off OC3 while doing setup.
            OC2R = 0x0000; // Initialize primary Compare Register
            OC2RS = 0x0000; // Initialize secondary Compare Register
            OC2CONbits.OC32 = 0; //16 bit mode
            OC2CONbits.OCTSEL = 0; //use timer 2
            OC2CONbits.OCM = 0b110; // PWM mode, no fault detection
            OC2R = raw_ticks[BRUSHLESS_PWM_2]; // need load this register initially
            OC2RS = raw_ticks[BRUSHLESS_PWM_2]; // OCxRS -> OCxR at timer rollover
            printf("OC2RS: %d\r\n", OC2RS);
            OC2CONbits.ON = 1; //turn on the peripheral
            break;
        case BRUSHLESS_PWM_2:
            if (output_type == ESC_BIDIRECTIONAL_TYPE) {
                pulse_width[BRUSHLESS_PWM_2] = RC_ESC_CENTER_PULSE;
                raw_ticks[BRUSHLESS_PWM_2] = ticks_center;
            } else {
                pulse_width[BRUSHLESS_PWM_2] = RC_ESC_MIN_PULSE;
                raw_ticks[BRUSHLESS_PWM_2] = ticks_min;
            }
            OC3CON = 0x0;
            OC3R = 0x0000; // Initialize primary Compare Register
            OC3RS = 0x0000; // Initialize secondary Compare Register
            OC3CONbits.OC32 = 0; //16 bit mode
            OC3CONbits.OCTSEL = 0; //use timer 2
            OC3CONbits.OCM = 0b110; // PWM mode, no fault detection
            OC3R = raw_ticks[BRUSHLESS_PWM_2]; // need load this register initially 
            OC3RS = raw_ticks[BRUSHLESS_PWM_2]; // OCxRS -> OCxR at timer rollover
            OC3CONbits.ON = 1; //turn on the peripheral
            break;
        case BRUSHLESS_PWM_3:
            if (output_type == ESC_BIDIRECTIONAL_TYPE) {
                pulse_width[BRUSHLESS_PWM_3] = RC_ESC_CENTER_PULSE;
                raw_ticks[BRUSHLESS_PWM_3] = ticks_center;
            } else {
                pulse_width[BRUSHLESS_PWM_3] = RC_ESC_MIN_PULSE;
                raw_ticks[BRUSHLESS_PWM_3] = ticks_min;
            }
            OC4CON = 0x0;
            OC4R = 0x0000; // Initialize primary Compare Register
            OC4RS = 0x0000; // Initialize secondary Compare Register
            OC4CONbits.OC32 = 0; //16 bit mode
            OC4CONbits.OCTSEL = 0; //use timer 2
            OC4CONbits.OCM = 0b110; // PWM mode, no fault detection
            OC4R = raw_ticks[BRUSHLESS_PWM_3]; // need load this register initially 
            OC4RS = raw_ticks[BRUSHLESS_PWM_3]; // OCxRS -> OCxR at timer rollover
            OC4CONbits.ON = 1; //turn on the peripheral
            break;
        case BRUSHLESS_PWM_4:
            if (output_type == ESC_BIDIRECTIONAL_TYPE) {
                pulse_width[BRUSHLESS_PWM_4] = RC_ESC_CENTER_PULSE;
                raw_ticks[BRUSHLESS_PWM_4] = ticks_center;
            } else {
                pulse_width[BRUSHLESS_PWM_4] = RC_ESC_MIN_PULSE;
                raw_ticks[BRUSHLESS_PWM_4] = ticks_min;
            }
            OC5CON = 0x0;
            OC5R = 0x0000; // Initialize primary Compare Register
            OC5RS = 0x0000; // Initialize secondary Compare Register
            OC5CONbits.OC32 = 0; //16 bit mode
            OC5CONbits.OCTSEL = 0; //use timer 2
            OC5CONbits.OCM = 0b110; // PWM mode, no fault detection
            OC5R = raw_ticks[BRUSHLESS_PWM_4]; // need load this register initially 
            OC5RS = raw_ticks[BRUSHLESS_PWM_4]; // OCxRS -> OCxR at timer rollover
            OC5CONbits.ON = 1; //turn on the peripheral
            break;
        default:
            break;
    }
    /* turn on the timer */
    T2CONbits.ON = 1;
    __builtin_enable_interrupts();
    return SUCCESS;
}

/**
 * @Function int RC_ESC_set_pulse(uint16_t in_pulse, uint8_t which_motor)
 * @param in_pulse, integer representing PWM width in microseconds
 * @param which_motor, motor number to set
 * @return SUCCESS or ERROR
 * @brief takes in microsecond count, converts to ticks and updates the internal variables
 * @warning This will update the timing for the next pulse, not the current one */
int8_t RC_ESC_set_pulse(uint16_t in_pulse, uint8_t which_motor) {
    if (in_pulse < RC_ESC_MIN_PULSE) { //prevent motors from exceeding limits
        in_pulse = RC_ESC_MIN_PULSE;
    }
    if (in_pulse > RC_ESC_MAX_PULSE) {
        in_pulse = RC_ESC_MAX_PULSE;
    }
    if (in_pulse != pulse_width[which_motor]) { //only update struct and OCxRS register if new value
        pulse_width[which_motor] = in_pulse;
        raw_ticks[which_motor] = (in_pulse * USEC_NUM) >> USEC_LOG_DEN; //only update PW register if the value has changed
        switch (which_motor) {
            case BRUSHLESS_PWM_1:
                OC2RS = raw_ticks[which_motor]; //load new PWM value into OCxRS
                break;
            case BRUSHLESS_PWM_2:
                OC3RS = raw_ticks[which_motor]; //load new PWM value into OCxRS
                break;
            case BRUSHLESS_PWM_3:
                OC4RS = raw_ticks[which_motor]; //load new PWM value into OCxRS
                break;
            case BRUSHLESS_PWM_4:
                OC5RS = raw_ticks[which_motor]; //load new PWM value into OCxRS
                break;
            default:
                break;
        }
    }
    RC_SET_NEW_CMD = FALSE; //reset flag after new command is set
    return SUCCESS;
}

/**
 * @Function int RC_ESC_get_pulse(uint8_t which_motor)
 * @param which_motor, motor number to retrieve PWM value from 
 * @return Pulse in microseconds currently set */
uint16_t RC_ESC_get_pulse(uint8_t which_motor) {
    return pulse_width[which_motor];
}

/**
 * @Function int RC_ESC_get_raw_ticks(void)
 * @param which_motor, motor number to retrieve raw timer compare value from 
 * @return raw timer ticks required to generate current pulse. */
uint16_t RC_ESC_get_raw_ticks(uint8_t which_motor) {
    return raw_ticks[which_motor];
}

/**
 * @Function RC_ESC_cmd_needed(void)
 * @brief returns TRUE when the brushless motor period register is ready for a new
 * pulsewidth 
 * @return TRUE or FALSE
 */
uint8_t RC_ESC_cmd_needed(void) {
    return RC_SET_NEW_CMD;
}
/*******************************************************************************
 * PRIVATE FUNCTION IMPLEMENTATIONS                                            *
 ******************************************************************************/

/**
 * @Function delay(int cycles)
 * @param cycles, number of cycles to delay
 * @brief simple delay loop
 * @note ~500nsec for one delay, then +12.5 nsec for every increment higher
 * @author ahunter
 */
void RC_ESC_delay(int cycles) {
    int i;
    for (i = 0; i < cycles; i++) {
        Nop();
    }
}

/**
 * @Function __ISR(_Timer_2_Vector, ipl6) RC_ESC_T2_handler(void)
 * @brief sets a flag when the period register rolls over
 * @author ahunter
 */
void __ISR(_TIMER_2_VECTOR, ipl6auto) RC_ESC_T2_handler(void) {
    RC_SET_NEW_CMD = TRUE; //set new command needed boolean
    // printf("ISR\r\n");
    IFS0bits.T2IF = 0; //clear interrupt flag
}

/*Test harness*/
#ifdef RCESC_TESTING

void main(void) {
    uint16_t test_pulse_uni = RC_ESC_MIN_PULSE;
    uint16_t test_pulse_bi = RC_ESC_CENTER_PULSE;
    uint16_t start_time;
    uint16_t cur_time;
    uint16_t ESC_time = 5000;
    uint16_t test_time = 250;
    int direction_uni = 1;
    int direction_bi = 1;
    int DONE_TESTING_UNI = FALSE;
    int DONE_TESTING_BI = FALSE;

    Board_init();
    Serial_init();
    Sys_timer_init();
    printf("\r\nRC_ESC Test Harness %s %s\r\n", __DATE__, __TIME__);

    RC_ESC_init(ESC_UNIDIRECTIONAL_TYPE, BRUSHLESS_PWM_1);
    RC_ESC_init(ESC_UNIDIRECTIONAL_TYPE, BRUSHLESS_PWM_2);
    RC_ESC_init(ESC_BIDIRECTIONAL_TYPE, BRUSHLESS_PWM_3);
    RC_ESC_init(ESC_BIDIRECTIONAL_TYPE, BRUSHLESS_PWM_4);
    printf("Exiting init() functions\r\n");
    start_time = Sys_timer_get_msec();
    cur_time = start_time;
    while ((cur_time - start_time) <= ESC_time) {
        cur_time = Sys_timer_get_msec();
    }

    printf("ESC delay over\r\n");

    while (DONE_TESTING_UNI == FALSE || DONE_TESTING_BI == FALSE) {
        if (RC_ESC_cmd_needed() == TRUE) {
            if (!DONE_TESTING_UNI) {
                if (direction_uni == 1) {
                    RC_ESC_set_pulse(test_pulse_uni, BRUSHLESS_PWM_1);
                    RC_ESC_set_pulse(test_pulse_uni, BRUSHLESS_PWM_2);
                    test_pulse_uni += 10;
                    if (test_pulse_uni > RC_ESC_CENTER_PULSE) {
                        direction_uni = -1;
                    }

                }
                else if (direction_uni == -1) {
                    RC_ESC_set_pulse(test_pulse_uni, BRUSHLESS_PWM_1);
                    RC_ESC_set_pulse(test_pulse_uni, BRUSHLESS_PWM_2);
                    test_pulse_uni -= 10;
                    if (test_pulse_uni < RC_ESC_MIN_PULSE) {
                        direction_uni = 1;
                        DONE_TESTING_UNI = TRUE;
                    }
                }
            }
            if (!DONE_TESTING_BI) {
                if (direction_bi == 1) {
                    RC_ESC_set_pulse(test_pulse_bi, BRUSHLESS_PWM_3);
                    RC_ESC_set_pulse(test_pulse_bi, BRUSHLESS_PWM_4);
                    test_pulse_bi += 10;
                    if (test_pulse_bi > RC_ESC_MAX_PULSE) {
                        direction_bi = -1;
                    }
                }
                else if (direction_bi == -1) {
                    RC_ESC_set_pulse(test_pulse_bi, BRUSHLESS_PWM_3);
                    RC_ESC_set_pulse(test_pulse_bi, BRUSHLESS_PWM_4);
                    test_pulse_bi -= 10;
                    if (test_pulse_bi < RC_ESC_MIN_PULSE) {
                        direction_bi = 1;
                        DONE_TESTING_BI = TRUE;
                    }
                }
            }
            
        }
        printf("UNIDIRECTIONAL_PWM_1: %d, current ticks: %d \r\n", RC_ESC_get_pulse(BRUSHLESS_PWM_1), RC_ESC_get_raw_ticks(BRUSHLESS_PWM_1));
        printf("UNIDIRECTIONAL_PWM_2: %d, current ticks: %d \r\n", RC_ESC_get_pulse(BRUSHLESS_PWM_2), RC_ESC_get_raw_ticks(BRUSHLESS_PWM_2));
        printf("BIDIRECTIONAL_PWM_3: %d, current ticks: %d \r\n", RC_ESC_get_pulse(BRUSHLESS_PWM_3), RC_ESC_get_raw_ticks(BRUSHLESS_PWM_3));
        printf("BIDIRECTIONAL_PWM_4: %d, current ticks: %d \r\n", RC_ESC_get_pulse(BRUSHLESS_PWM_4), RC_ESC_get_raw_ticks(BRUSHLESS_PWM_4));
        start_time = Sys_timer_get_msec();
        cur_time = start_time;
        while ((cur_time - start_time) <= test_time) {
            cur_time = Sys_timer_get_msec();
        }
    }
}

#endif //RCESC_TESTING