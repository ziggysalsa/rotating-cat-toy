/**
 * @file stepper.h
 * @author Sasha Zelenski
 * @date 2025-09-04
 * 
 * Stepper motor driver header file.
 * 
 * @par Changelog:
 * - 2025-09-04: Initial version. 
 */

#ifndef STEPPER_H
#define STEPPER_H
#include "include/config.h"

/**
 * GPIO pins for stepper motor
 */
extern const int PINS[4];

/**
 * Half-step sequence table for stepper motor
 */
extern const int SEQ[8][4];

/** 
 * Initialize stepper motor GPIO pins
 */
void stepper_init();

/**
 * Advances motor forward or backward by a half-step
 * 
 * @param step_idx : pointer to current index in sequence array
 * @param direction : rotation direction (+1 is forward, -1 is backward)
 */
void step_motor(int *step_idx, int direction);

/**
 * Advances motor n half-steps, with a delay between each step dependent
 * on the potentiometer value.
 * @param step_idx : pointer to current index in sequence array
 * @param direction : rotation direction (+1 is forward, -1 is backward)
 * @param num_steps : number of half-steps to advance
 */
void step_n_times(int *step_idx, int direction, int num_steps);

#endif