/**
 * @file potentiometer.c
 * @author Sasha Zelenski
 * @date 2025-09-04
 *
 * Implements functions in @ref potentiometer.h to read potentiometer
 * value and map it to a delay in us.
 * 
 * @par Changelog:
 * - 2025-09-04: Initial version. 
 */

#include "hardware/adc.h"
#include "include/config.h"
#include "include/potentiometer.h"

/**
 * ADC value, filtered to remove jitters
 */
static uint32_t filtered_adc;

/**
 * Initialize potentiometer (GPIO28 / ADC2) and set initial value.
 */
void pot_init() {
    adc_init();
    adc_gpio_init(POT);
    adc_select_input(2);
    filtered_adc = adc_read(); // Initialize filtered ADC value so it's not 0 when we start
}

/**
 * Read and filter potentiometer value, then map it
 * to a delay in us
 */
uint32_t pot_delay_us() {
    filtered_adc = (filtered_adc * 7 + adc_read()) / 8; // read ADC and filter it to eliminate jitters
    return STEP_DELAY_US_MAX 
        - (uint32_t)((STEP_DELAY_US_MAX - STEP_DELAY_US_MIN) 
        * (uint32_t)filtered_adc / 4095);
}