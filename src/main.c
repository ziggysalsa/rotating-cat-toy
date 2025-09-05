/**
 * @file main.c
 * @author Sasha Zelenski
 * @date 2025-09-03
 *
 * Main file for stepper motor cat toy. Uses potentiometer to control
 * motor speed, and moves stepper motor in several patterns.
 *
 * @par Changelog:
 * - 2025-09-03: Initial version.
 * - 2025-09-04: Moved motor and potentiometer functionality to separate files.
 * Added usage of movement patterns. Renamed to main.c.
 */

#include "include/patterns.h"
#include "include/potentiometer.h"
#include "include/stepper.h"
#include <pico/stdio.h>
#include <stdlib.h>

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

  // Keep track of which half-step position we're on
  int step_idx = 0;

  while (true) {

    // Pick a random pattern to run, and call that pattern's function
    // with the current half-step position
    int random_idx = rand() % NUM_PATTERNS;
    PATTERNS[random_idx](&step_idx);
  }
}