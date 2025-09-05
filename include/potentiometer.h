/**
 * @file potentiometer.h
 * @author Sasha Zelenski
 * @date 2025-09-04
 *
 * Header file for reading potentiometer value
 * and mapping it to a delay in us.
 *
 * @par Changelog:
 * - 2025-09-04: Initial version.
 */

#include <stdint.h>

#ifndef POT_H
#define POT_H

/**
 * Initialize potentiometer (GPIO28 / ADC2) and set initial value.
 */
void pot_init();

/**
 * Read and filter potentiometer value, then map it
 * to a delay in us
 */
uint32_t pot_delay_us();

#endif
