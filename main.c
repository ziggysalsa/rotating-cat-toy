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

/**
 * Application entry point. Sets up I/O and controls motor.
 */
int main() {

    // Sets up I/O
    stdio_init_all();

    // Set up ADC for pot (GPIO28 / ADC2)
    adc_init();
    adc_gpio_init(POT);
    adc_select_input(2);
    uint32_t filtered_adc = adc_read(); // Initialize filtered ADC value (0 to 4095) so it's not 0 when we start

    // Set up stepper motor
    stepper_init();

    int step_idx = 0; // keep track of which half-step position we're on
    int direction = 1; // Motor direction: +1 is forward, -1 is backward

    while (true) {

        // Random number of steps (less than one revolution)
        int num_steps = rand() % (STEPS_PER_REV + 1);

        // Step the motor the random number of steps
        for (int i = 0; i < num_steps; i++) {

            // Read ADC and filter value with EMA filter
            filtered_adc = (filtered_adc * 7 + adc_read()) / 8; 

            // map filtered ADC value to delay in us (controls motor speed)
            uint32_t delay_us = STEP_DELAY_US_MAX 
                              - (uint32_t)((STEP_DELAY_US_MAX - STEP_DELAY_US_MIN) 
                              * (uint32_t)filtered_adc / 4095);
            sleep_us(delay_us);

            // Set motor to next half-step position
            step_motor(&step_idx, direction);
        }

        // Random pause with probability = 1/PAUSE_PROBABILITY
        if ((rand() % PAUSE_PROBABILITY) == 0) {
            uint32_t pause_ms = PAUSE_MS_MIN + (rand() % (PAUSE_MS_MAX - PAUSE_MS_MIN));
            sleep_ms(pause_ms);
        }

        // Reverse direction
        direction = -direction;
    }
}