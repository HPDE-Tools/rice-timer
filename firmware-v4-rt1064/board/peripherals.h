/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

#ifndef _PERIPHERALS_H_
#define _PERIPHERALS_H_

/***********************************************************************************************************************
 * Included files
 **********************************************************************************************************************/
#include "fsl_common.h"
#include "fsl_gpio.h"
#include "fsl_trng.h"
#include "fsl_gpt.h"
#include "fsl_clock.h"

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/***********************************************************************************************************************
 * Definitions
 **********************************************************************************************************************/
/* Definitions for BOARD_InitPeripherals functional group */
/* GPIO1 interrupt vector ID (number). */
#define GPIO1_GPIO_COMB_0_15_IRQN GPIO1_Combined_0_15_IRQn
/* GPIO1 interrupt handler identifier. */
#define GPIO1_GPIO_COMB_0_15_IRQHANDLER GPIO1_Combined_0_15_IRQHandler
/* GPIO1 interrupt vector ID (number). */
#define GPIO1_GPIO_COMB_16_31_IRQN GPIO1_Combined_16_31_IRQn
/* GPIO1 interrupt handler identifier. */
#define GPIO1_GPIO_COMB_16_31_IRQHANDLER GPIO1_Combined_16_31_IRQHandler
/* GPIO2 interrupt vector ID (number). */
#define GPIO2_GPIO_COMB_0_15_IRQN GPIO2_Combined_0_15_IRQn
/* GPIO2 interrupt handler identifier. */
#define GPIO2_GPIO_COMB_0_15_IRQHANDLER GPIO2_Combined_0_15_IRQHandler
/* GPIO2 interrupt vector ID (number). */
#define GPIO2_GPIO_COMB_16_31_IRQN GPIO2_Combined_16_31_IRQn
/* GPIO2 interrupt handler identifier. */
#define GPIO2_GPIO_COMB_16_31_IRQHANDLER GPIO2_Combined_16_31_IRQHandler
/* Definition of peripheral ID */
#define TRNG_PERIPHERAL TRNG
/* Definition of peripheral ID */
#define GPT2_PERIPHERAL GPT2
/* Definition of the clock source frequency */
#define GPT2_CLOCK_SOURCE 75000000UL
/* Definition of GPT2 channel kGPT_InputCapture_Channel2 */
#define GPT2_IMU_INT_INPUT kGPT_InputCapture_Channel2

/***********************************************************************************************************************
 * Global variables
 **********************************************************************************************************************/
extern const trng_config_t TRNG_config;
extern const gpt_config_t GPT2_config;

/***********************************************************************************************************************
 * Initialization functions
 **********************************************************************************************************************/

void BOARD_InitPeripherals(void);

/***********************************************************************************************************************
 * BOARD_InitBootPeripherals function
 **********************************************************************************************************************/
void BOARD_InitBootPeripherals(void);

#if defined(__cplusplus)
}
#endif

#endif /* _PERIPHERALS_H_ */
