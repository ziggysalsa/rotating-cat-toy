/**
 * @file patterns.h
 * @author Sasha Zelenski
 * @date 2025-09-03
 * 
 * Header file for motor movement patterns. 
 */

#ifndef PATTERNS_H
#define PATTERNS_H

/**
 * Motion sequence to shake back and forth 3-6 times without pausing, 
 * then pause for 6 seconds
 * @param step_idx pointer to current index in sequence array
 */
void pattern_01(int *step_idx);

/**
 * Motion sequence to make a small movement, pause for 6 seconds
 * then repeat 2-5 times
 * @param step_idx pointer to current index in sequence array
 */
void pattern_02(int *step_idx);

/**
 * Motion sequence to move back and forth a random number of times,
 * and pause at random between movements for a random length of time
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