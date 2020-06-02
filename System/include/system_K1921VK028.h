/**
  ******************************************************************************
  * @file    system_K1921VK028.h
  * @version 1.0
  * @date:   26.03.2019
  * @brief   Настройки тактирования ядра 1921ВК028
  *
  ******************************************************************************
  */

#ifndef SYSTEM_K1921VK028_H
#define SYSTEM_K1921VK028_H

#ifdef __cplusplus
extern "C" {
#endif

//-- Includes ------------------------------------------------------------------
#include <stdint.h>

//-- Defines -------------------------------------------------------------------
#define OSICLK_VAL 16000000				// Внутренний (OSI) генератор на 16 МГц
#define OSECLK_VAL 12000000				// Внешний (OSE) кварцевый резонатор на 12 МГц
#define SYSCLK_PLL						// Источник системной частоты SYSCLK -> PLL

#ifndef CPE
  #define CPE 0
#endif

#ifndef OSECLK_VAL
  #define OSECLK_VAL 0
#endif

#ifndef EXTCLK_VAL
  #define EXTCLK_VAL 0
#endif

#ifndef TRACEEXTCLK_VAL
  #define TRACEEXTCLK_VAL OSECLK_VAL
#endif

#ifndef PLLEXTCLK_VAL
  #define PLLEXTCLK_VAL OSECLK_VAL
#endif

/* Выбор основного источника тактирования */
#if (CPE == 0)		//
  #define REFCLK_VAL OSICLK_VAL
  #define SRCCLK_VAL OSECLK_VAL
#elif (CPE == 1)	//
  #define REFCLK_VAL OSECLK_VAL
  #define SRCCLK_VAL OSICLK_VAL
#else				// не определен
  #error "Please define CPE with correct state!"
#endif

//-- Variables -----------------------------------------------------------------
extern uint32_t SystemCoreClock; // System Clock Frequency (Core Clock)
extern uint32_t APB0BusClock;    // APB0 Bus Clock Frequency
extern uint32_t APB1BusClock;    // APB1 Bus Clock Frequency

//-- Functions -----------------------------------------------------------------
// Initialize the System
extern void SystemInit(void);

// Updates the SystemCoreClock with current core Clock retrieved from registers
extern void SystemCoreClockUpdate(void);

#ifdef __cplusplus
}
#endif

#endif // SYSTEM_K1921VK028_H
