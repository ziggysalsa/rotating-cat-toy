/**
 * @file stepper.c
 * @author Sasha Zelenski
 * @date 2025-09-03
 * 
 * Main file for stepper motor cat toy. Uses potentiometer to control
 * motor speed and the stepper motor to move in random patterns.
 */

#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/gpio.h"
#include <stdlib.h>
#include "config.h" 
#include "stepper.h"
#include "potentiometer.h"
#include "patterns.h"

/**
 * Application entry point. Sets up I/O and controls motor.
 */
int main() {

    // Sets up I/O
    stdio_init_all();

    // Set up potentiometer
    pot_init();

    // Set up stepper motor
    stepper_init();

    int step_idx = 0; // keep track of which half-step position we're on
    int direction = 1; // Motor direction: +1 is forward, -1 is backward

    while (true) {

        // Random number of steps (less than one revolution)
        int num_steps = rand() % (STEPS_PER_REV + 1);

        // Step random number of steps
        step_n_times(&step_idx, direction, num_steps);

        // Random pause with probability = 1/PAUSE_PROBABILITY
        if ((rand() % PAUSE_PROBABILITY) == 0) {
            uint32_t pause_ms = PAUSE_MS_MIN + (rand() % (PAUSE_MS_MAX - PAUSE_MS_MIN));
            sleep_ms(pause_ms);
        }

        // Reverse direction
        direction = -direction;
    }
}