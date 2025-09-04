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
