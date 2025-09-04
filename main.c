/**
 * @file stepper.c
 * @author Sasha Zelenski
 * @date 2025-09-03
 * 
 * Main file for stepper motor cat toy. Uses potentiometer to control
 * motor speed and the stepper motor to move in random patterns.
 */

#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include <stdlib.h>
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

        // Pick a random pattern to run, and call that pattern's function
        // with the current half-step position
        int random_idx = rand() % NUM_PATTERNS;
        PATTERNS[random_idx](&step_idx);

    }
}