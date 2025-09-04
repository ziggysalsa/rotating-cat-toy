/**
 * @file stepper.h
 * @author Sasha Zelenski
 * @date 2025-09-03
 * 
 * Stepper motor driver header file
 */

#ifndef STEPPER_H
#define STEPPER_H
#include "config.h"

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

#endif