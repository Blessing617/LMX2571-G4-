/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define KEY_Pin GPIO_PIN_13
#define KEY_GPIO_Port GPIOC
#define KEY_EXTI_IRQn EXTI15_10_IRQn
#define MUX_Pin GPIO_PIN_0
#define MUX_GPIO_Port GPIOA
#define DAT_Pin GPIO_PIN_1
#define DAT_GPIO_Port GPIOA
#define CTL_Pin GPIO_PIN_4
#define CTL_GPIO_Port GPIOA
#define FD1_Pin GPIO_PIN_10
#define FD1_GPIO_Port GPIOB
#define FD2_Pin GPIO_PIN_8
#define FD2_GPIO_Port GPIOA
#define FDV_Pin GPIO_PIN_9
#define FDV_GPIO_Port GPIOA
#define CE_Pin GPIO_PIN_10
#define CE_GPIO_Port GPIOA
#define LE_Pin GPIO_PIN_3
#define LE_GPIO_Port GPIOB
#define FD0_Pin GPIO_PIN_4
#define FD0_GPIO_Port GPIOB
#define CLK_Pin GPIO_PIN_5
#define CLK_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
