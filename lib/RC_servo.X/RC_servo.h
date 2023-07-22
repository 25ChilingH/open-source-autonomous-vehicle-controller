/* 
 * File:   RC_servo.h
 * Author: Aaron Hunter
 * Brief: Library driver for up to four servos for the Max32 dev board
 * 
 * History
 * When     Who             What/Why
 * -------  ------------    ---------
 * 12/18/20 Aaron Hunter    Created RC_servo driver file
 * 07/19/23 Chiling Han     Remove brushless motor logic
 */


#ifndef RCSERVO_H
#define	RCSERVO_H

/*******************************************************************************
 * PUBLIC #INCLUDES                                                            *
 ******************************************************************************/

#include <stdint.h>

/*******************************************************************************
 * PUBLIC #DEFINES                                                            *
 ******************************************************************************/

#define RC_SERVO_MIN_PULSE 544
#define RC_SERVO_CENTER_PULSE 1472
#define RC_SERVO_MAX_PULSE 2400
#define RC_SERVO_NUM_OUTPUTS 4


/*******************************************************************************
 * PUBLIC FUNCTIONS                                                           *
 ******************************************************************************/

/*******************************************************************************
 * PUBLIC TYPEDEF                                                              *
 ******************************************************************************/
enum {
    SERVO_PWM_1,
    SERVO_PWM_2,
    SERVO_PWM_3,
    SERVO_PWM_4
};

/**
 * @Function RC_servo_init(void)
 * @param None
 * @return SUCCESS or ERROR
 * @brief initializes hardware required and set it to the CENTER PULSE */
int8_t RC_servo_init(uint8_t output_channel);

/**
 * @Function int RC_servo_set_pulse(uint16_t in_pulse, uint8_t which_servo)
 * @param in_pulse, integer representing PWM width in microseconds
 * @param which_servo, servo number to set
 * @return SUCCESS or ERROR
 * @brief takes in microsecond count, converts to ticks and updates the internal variables
 * @warning This will update the timing for the next pulse, not the current one */
int8_t RC_servo_set_pulse(uint16_t in_pulse, uint8_t which_servo);

/**
 * @Function RC_servo_cmd_needed(void)
 * @brief returns TRUE when the RC servo period register is ready for a new
 * pulsewidth 
 * @return TRUR or FALSE
 * @author Aaron Hunter
 */
uint8_t RC_servo_cmd_needed(void);

/**
 * @Function int RC_servo_get_pulse(uint8_t which_servo)
 * @param which_servo, servo number to retrieve PWM value from 
 * @return Pulse in microseconds currently set */
uint16_t RC_servo_get_pulse(uint8_t which_servo);

/**
 * @Function int RC_servo_get_raw_ticks(void)
 * @param which_servo, servo number to retrieve raw timer compare value from 
 * @return raw timer ticks required to generate current pulse. */
uint16_t RC_servo_get_raw_ticks(uint8_t which_servo);

#endif	/* RCSERVO_H */

