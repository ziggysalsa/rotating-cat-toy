/**
 * @file config.h
 * @author Sasha Zelenski
 * @date 2025-09-04
 *
 * Config file for cat toy. Contains pin assignments, motor constants, and
 * timing values.
 *
 * @par Changelog:
 * - 2025-09-04: Initial version.
 */

#ifndef CONFIG_H
#define CONFIG_H

#define POT 28 /**< ADC pin for pot */

#define IN1 18 /**< Motor IN1 pin */
#define IN2 19 /**< Motor IN2 pin */
#define IN3 20 /**< Motor IN3 pin */
#define IN4 21 /**< Motor IN4 pin */

#define STEPS_PER_REV 2048 /**< Number of steps for full rotation of motor */

#define STEP_DELAY_US_MIN 1000 /**< Min step delay for motor (us) - controls motor speed */
#define STEP_DELAY_US_MAX 6000 /**< Max step delay for motor (us) - controls motor speed */

#endif