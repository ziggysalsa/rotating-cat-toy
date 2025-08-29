#include "pico/stdlib.h"
#include "hardware/adc.h"
#include <stdlib.h> 

#define POT 28 // ADC pin for pot
#define IN1 18 // Motor IN1 pin
#define IN2 19 // Motor IN2 pin
#define IN3 20 // Motor IN3 pin
#define IN4 21 // Motor IN4 pin
#define STEPS_PER_REV 2048  // Number of steps for full rotation of motor
#define PAUSE_PROBABILITY 3 // Probability of pausing between rotations ( P = 1/PAUSE_PROBABILITY)
#define PAUSE_MS_MIN 1000 // Min pause length (ms)
#define PAUSE_MS_MAX 5000 // Max pause length (ms)
#define STEP_DELAY_US_MIN 1000 // Min step delay for motor (us)
#define STEP_DELAY_US_MAX 6000 // Max step delay for motor (us)

static const uint PINS[4] = {IN1, IN2, IN3, IN4};

// Define the half-step positions of the motor
static const uint8_t SEQ[8][4] = {
    {1,0,0,0},{1,1,0,0},{0,1,0,0},{0,1,1,0},
    {0,0,1,0},{0,0,1,1},{0,0,0,1},{1,0,0,1}
};

int main() {

    // Sets up I/O
    stdio_init_all();

    // Set up ADC for pot
    adc_init();
    adc_gpio_init(POT);
    adc_select_input(2); // pin 28 is ADC2

    // Enables motor pins for use and sets them as outputs
    for (int i = 0; i < 4; i++) { 
        gpio_init(PINS[i]); 
        gpio_set_dir(PINS[i], true); 
    }

    int step_idx = 0; // keep track of which half-step position we're on
    int direction = 1; // 1 is forward, -1 is backward

    // Initialize filtered ADC value so it's not 0 when we start. Value ranges from 0 to 4095
    uint32_t filtered_adc = adc_read(); 

    while (true) {

        int num_steps = rand() % (STEPS_PER_REV + 1);  // want number of steps to always be fewer than a full revolution

        // Go a random number of steps
        for (int i = 0; i < num_steps; i++) {

            filtered_adc = (filtered_adc * 7 + adc_read()) / 8; // Read ADC and filter value with EMA filter

            // map filtered ADC value to delay in us
            uint32_t delay_us = STEP_DELAY_US_MAX - (uint32_t)((STEP_DELAY_US_MAX - STEP_DELAY_US_MIN) * (uint64_t)filtered_adc / 4095);
            sleep_us(delay_us);

            // Set motor to next half-step position
            for (int j = 0; j < 4; j++) { 
                gpio_put(PINS[j], SEQ[step_idx][j]);
            }
            step_idx = (step_idx + direction) & 7;
        }

        // Randomly pause for a random length of time
        // Likelihood that it pauses is 1/PAUSE_PROBABILITY
        if ((rand() % PAUSE_PROBABILITY) == 0) {
            int pause_ms = PAUSE_MS_MIN + (rand() % (PAUSE_MS_MAX-PAUSE_MS_MIN)); 
            sleep_ms(pause_ms);
        }

        // Reverse direction
        direction = -direction;
    }
}