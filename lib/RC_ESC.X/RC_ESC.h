/* 
 * File:   RC_ESC.h
 * Author: Chiling Han
 * Brief: Library driver for up to four DC brushless motors for the Max32 dev board
 * Created on 07/19/2023 8:30pm
 */


#ifndef RCESC_H
#define	RCESC_H

/*******************************************************************************
 * PUBLIC #INCLUDES                                                            *
 ******************************************************************************/

#include <stdint.h>

/*******************************************************************************
 * PUBLIC #DEFINES                                                            *
 ******************************************************************************/

#define RC_ESC_MIN_PULSE 1000
#define RC_ESC_CENTER_PULSE 1500
#define RC_ESC_MAX_PULSE 2000
#define RC_ESC_TRIM -10
#define RC_ESC_NUM_OUTPUTS 4


/*******************************************************************************
 * PUBLIC FUNCTIONS                                                           *
 ******************************************************************************/

/*******************************************************************************
 * PUBLIC TYPEDEF                                                              *
 ******************************************************************************/
enum {
    ESC_UNIDIRECTIONAL_TYPE,
    ESC_BIDIRECTIONAL_TYPE
};

enum {
    BRUSHLESS_PWM_1,
    BRUSHLESS_PWM_2,
    BRUSHLESS_PWM_3,
    BRUSHLESS_PWM_4
};

/**
 * @Function RC_ESC_init(void)
 * @param output_type, unidirectional or bidirectional DC brushless motor
 * @param output_channel, motor number to initialize
 * @return SUCCESS or ERROR
 * @brief initializes hardware required and set it to the MIN or CENTER PULSE */
int8_t RC_ESC_init(uint8_t output_type, uint8_t output_channel);

/**
 * @Function int RC_ESC_set_pulse(uint16_t in_pulse, uint8_t which_motor)
 * @param in_pulse, integer representing PWM width in microseconds
 * @param which_motor, motor number to set
 * @return SUCCESS or ERROR
 * @brief takes in microsecond count, converts to ticks and updates the internal variables
 * @warning This will update the timing for the next pulse, not the current one */
int8_t RC_ESC_set_pulse(uint16_t in_pulse, uint8_t which_motor);

/**
 * @Function RC_ESC_cmd_needed(void)
 * @brief returns TRUE when the brushless motor period register is ready for a new
 * pulsewidth 
 * @return TRUE or FALSE
 */
uint8_t RC_ESC_cmd_needed(void);

/**
 * @Function int RC_ESC_get_pulse(uint8_t which_motor)
 * @param which_motor, motor number to retrieve PWM value from 
 * @return Pulse in microseconds currently set */
uint16_t RC_ESC_get_pulse(uint8_t which_motor);

/**
 * @Function int RC_ESC_get_raw_ticks(void)
 * @param which_motor, motor number to retrieve raw timer compare value from 
 * @return raw timer ticks required to generate current pulse. */
uint16_t RC_ESC_get_raw_ticks(uint8_t which_motor);

#endif	/* RCESC_H */

