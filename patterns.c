/**
 * @file patterns.c
 * @author Sasha Zelenski
 * @date 2025-09-03
 * 
 * Definitions of motor movement patterns.
 * 
 * Each function corresponds to a distinct movement pattern of the
 * stepper motor. To add a new pattern, create a new function and 
 * add it to the PATTERNS array. Also update NUM_PATTERNS to reflect
 * the new number of patterns, and patterns.h.
 */

#include "pico/stdlib.h"
#include <stdlib.h>
#include "stepper.h"
#include "patterns.h"

/**
 * Pattern to shake back and forth 3-6 times, then pause
 * @param step_idx Pointer to the current step index
 */
void pattern_01(int *step_idx) {
   int reps = 3 + rand()%4; // 3-6 repetitions
   int rep_length = 25 + rand()%11; // Go 25-35 half-steps per rep

   for (int i = 0; i < reps; i++) {
      step_n_times(step_idx, +1, rep_length); // move motor forward
      step_n_times(step_idx, -1, rep_length); // move motor backward
   }
   sleep_ms(6000); // pause for 6 seconds
}

/**
 * Pattern to make small movement, pause for a while, and repeat
 * @param step_idx Pointer to the current step index
 */
void pattern_02(int *step_idx) {
   int reps = 2 + rand()%4; // 2-5 repetitions
   int rep_length = 15 + rand()%6; // Go 15-20 half-steps per rep

   for (int i = 0; i < reps; i++) {
      step_n_times(step_idx, +1, rep_length); // move motor forward
      sleep_ms(6000); // pause for 6 seconds
   }
}

/**
 * Pattern to move back and forth random lengths of time, with random pauses
 * @param step_idx Pointer to the current step index
 */
void pattern_03(int *step_idx) {
   int reps = 1 + rand()%3; // 1-3 repetitions
   int direction = 1;       // start by moving forward (+1 is forward, -1 is backward)

   for (int i = 0; i < reps; i++) {
      int rep_length = rand() % (STEPS_PER_REV + 1); // will go a random number of steps
      step_n_times(step_idx, direction, rep_length);

      // Random pause with probability = 1/PAUSE_PROBABILITY
        if ((rand() % PAUSE_PROBABILITY) == 0) {
            uint32_t pause_ms = PAUSE_MS_MIN + (rand() % (PAUSE_MS_MAX - PAUSE_MS_MIN));
            sleep_ms(pause_ms);
        }

        direction = -direction; // Reverse direction
      } 
}

/**
 * Number of patterns in the pattern array
 */
const int NUM_PATTERNS = 3;

/**
 * Array of function pointers to movement patterns
 */
void (*PATTERNS[])(int *step_idx) = {
    pattern_01,
    pattern_02,
    pattern_03,
};