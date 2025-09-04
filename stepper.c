/**
 * @file stepper.c
 * @author Sasha Zelenski
 * @date 2025-09-03
 * 
 * Implements functions in @ref stepper.h to control unipolar stepper motor
 * through a ULN2003 driver.
 */

#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include "config.h"
#include "potentiometer.h"
#include "stepper.h"

/**
 * GPIO pins used to drive the stepper motor. 
 * IN1-IN4 are defined in config.h.
 */
const int PINS[4] = {IN1, IN2, IN3, IN4};

/**
 * Half-step sequence table for stepper motor. Each row
 * defines coil activation pattern for a half-step.
 */
const int SEQ[8][4] = {
    {1,0,0,0},{1,1,0,0},{0,1,0,0},{0,1,1,0},
    {0,0,1,0},{0,0,1,1},{0,0,0,1},{1,0,0,1}
};

/**
 * Initializes stepper motor pins and sets them to output mode.
 */
void stepper_init() {
    for (int i = 0; i < 4; i++) { 
        gpio_init(PINS[i]); 
        gpio_set_dir(PINS[i], 1); 
    }
}

/**
 * Advances motor one half-step
 * @param step_idx : pointer to current index in sequence array
 * @param direction : rotation direction (+1 is forward, -1 is backward)
 */
void step_motor(int *step_idx, int direction) {
    for (int j = 0; j < 4; j++) {
        gpio_put(PINS[j], SEQ[*step_idx][j]);
    }
    *step_idx = (*step_idx + direction) & 7;
}

/**
 * Advances motor n half-steps, with a delay between each step dependent
 * on the potentiometer value.
 * @param step_idx : pointer to current index in sequence array
 * @param direction : rotation direction (+1 is forward, -1 is backward)
 * @param num_steps : number of half-steps to advance
 */
void step_n_times(int *step_idx, int direction, int num_steps) {
    for (int i = 0; i < num_steps; i++) {
        step_motor(step_idx, direction);
        uint32_t delay_us = pot_delay_us();
        sleep_us(delay_us);
    }
}

