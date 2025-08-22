#include "pico/stdlib.h"
#include <stdlib.h> 

#define IN1 18
#define IN2 19
#define IN3 20
#define IN4 21           
#define STEPS_PER_REV 2048  
#define STEP_DELAY_MS 4
#define PAUSE_PROBABILITY 3
#define PAUSE_LOWER_BOUND_MS 1000
#define PAUSE_UPPER_BOUND_MS 5000

static const uint PINS[4] = {IN1, IN2, IN3, IN4};

// Define the half-step positions of the motor
static const uint8_t SEQ[8][4] = {
    {1,0,0,0},{1,1,0,0},{0,1,0,0},{0,1,1,0},
    {0,0,1,0},{0,0,1,1},{0,0,0,1},{1,0,0,1}
};

int main() {

    // Sets up I/O
    stdio_init_all();

    // Enables pins for use and sets them as outputs
    for (int i = 0; i < 4; i++) { 
        gpio_init(PINS[i]); 
        gpio_set_dir(PINS[i], true); 
    }

    int step_idx = 0; // keep track of which half-step position we're on
    int direction = 1; // 1 is forward, -1 is backward

    while (true) {

        int num_steps = rand() % (STEPS_PER_REV + 1);  // want number of steps to always be fewer than a full revolution

        // Go a random number of steps
        for (int i = 0; i < num_steps; i++) {
            for (int j = 0; j < 4; j++) { 
                gpio_put(PINS[j], SEQ[step_idx][j]);
            }
            sleep_ms(STEP_DELAY_MS);
            step_idx = (step_idx + direction) & 7; // proceed to next step
        }

        // Randomly pause for a random length of time
        if ((rand() % PAUSE_PROBABILITY) == 0) {
            int pause_ms = PAUSE_LOWER_BOUND_MS + (rand() % (PAUSE_UPPER_BOUND_MS-PAUSE_LOWER_BOUND_MS)); 
            sleep_ms(pause_ms);
        }

        // Reverse direction
        direction = -direction;
    }
}