/**
 * @file patterns.c
 * @author Sasha Zelenski
 * @date 2025-09-04
 *
 * Definitions of motor movement patterns in @ref patterns.h
 *
 * Each function corresponds to a distinct movement pattern of the
 * stepper motor. To add a new pattern, create a new function and
 * add it to the PATTERNS array. Also update NUM_PATTERNS to reflect
 * the new number of patterns, and update patterns.h.
 * 
 * @par Changelog:
 * - 2025-09-04: Initial version. 
 */

#include "pico/stdlib.h"
#include <stdlib.h>
#include "include/stepper.h"
#include "include/patterns.h"

/**
 * Pattern to shake back and forth 3-6 times, then pause for 6 seconds
 * @param step_idx Pointer to the current step index
 */
void pattern_01(int *step_idx) {
   int reps = 3 + rand()%4; // 3-6 repetitions
   int rep_length = 100 + rand()%51; // Go 100-150 half-steps per rep

   for (int i = 0; i < reps; i++) {
      step_n_times(step_idx, +1, rep_length); // move motor forward
      step_n_times(step_idx, -1, rep_length); // move motor backward
   }
   sleep_ms(6000); // pause for 6 seconds
}

/**
 * Pattern to make small movement, pause for 10 seconds, and repeat 1-4 more times
 * @param step_idx Pointer to the current step index
 */
void pattern_02(int *step_idx) {
   int reps = 2 + rand()%4; // 2-5 repetitions
   int rep_length = 125 + rand()%51; // Go 125-175 half-steps per rep

   for (int i = 0; i < reps; i++) {
      step_n_times(step_idx, +1, rep_length); // move motor forward
      sleep_ms(10000); // pause for 10 seconds
   }
}

/**
 * Pattern to move a random number of steps, switch direction, and repeat 1-3 more times
 * After each movement, there's a 25% chance of pausing for 1-5 seconds before the 
 * next movement.
 * @param step_idx Pointer to the current step index
 */
void pattern_03(int *step_idx) {
   int reps = 2 + rand()%3; // 2-4 repetitions
   int direction = 1;       // start by moving forward (+1 is forward, -1 is backward)

   for (int i = 0; i < reps; i++) {
      int rep_length = rand()%(STEPS_PER_REV + 1); // will go a random number of steps (always less than a full revolution)
      step_n_times(step_idx, direction, rep_length); // move motor forward or backward

      // 25% chance of pausing before next movement
      if ((rand() % 4) == 0) {
         uint32_t pause_ms = 1000 + rand()%5000; // Pause 1-5 seconds
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