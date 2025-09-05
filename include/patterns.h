/**
 * @file patterns.h
 * @author Sasha Zelenski
 * @date 2025-09-04
 *
 * Header file for motor movement patterns.
 *
 * @par Changelog:
 * - 2025-09-04: Initial version.
 */

#ifndef PATTERNS_H
#define PATTERNS_H

/**
 * Pattern to shake back and forth 3-6 times without pausing,
 * then pause for 6 seconds
 * @param step_idx pointer to current index in sequence array
 */
void pattern_01(int *step_idx);

/**
 * Pattern to make a small movement, pause for 10 seconds,
 * then repeat 1-4 more times
 * @param step_idx pointer to current index in sequence array
 */
void pattern_02(int *step_idx);

/**
 * Pattern to move a random number of steps, switch direction, and repeat 1-3
 * more times After each movement, there's a 25% chance of pausing for 1-5
 * seconds before the next movement.
 * @param step_idx pointer to current index in sequence array
 */
void pattern_03(int *step_idx);

/**
 * Array of function pointers to movement patterns
 */
extern void (*PATTERNS[])(int *step_idx);

/**
 * Number of patterns in the pattern array
 */
extern const int NUM_PATTERNS;

#endif