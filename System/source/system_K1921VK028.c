/**
  ******************************************************************************
  * @file    system_K1921VK028.c
  * @version 1.0
  * @date:   26.03.2019
  * @brief   Файл содержит настройки тактирования ядра 1921ВК028
  *
  ******************************************************************************
  */

//-- Includes ------------------------------------------------------------------
#include "system_K1921VK028.h"
#include "K1921VK028.h"
#include "plib028_rcu.h"

//-- Variables -----------------------------------------------------------------
uint32_t SystemCoreClock; // System Clock Frequency (SYSCLK)
uint32_t APB0BusClock;    // APB0 Bus Clock Frequency (HCLK)
uint32_t APB1BusClock;    // APB1 Bus Clock Frequency (PCLK)

//-- Functions -----------------------------------------------------------------

/* Начальная инициализация системы (до вызова функции main()) */
void SystemInit(void)
{
	uint32_t timeout_counter = 0;

    /* Ожидаем готовности внешнего кварцевого резонатора (генератора) */
    while ((!RCU->SYSCLKSTAT_bit.SRCCLKOK) && (timeout_counter < RCU_SRCCLK_LOCK_TIMEOUT)){
        timeout_counter++;
        if (timeout_counter == RCU_SRCCLK_LOCK_TIMEOUT)	// Истек таймаут 65,5 мс.
            while (1) { };	// Зависаем в бесконечном цикле, кварцевый резонатор(генератор) неисправен
    }

    /* Настариваем и выбираем PLL в качестве источника системной частоты (SYSCLK) */
    if(RCU_PLL_AutoConfig(100000000,RCU_PLLCFG_REFSRC_OSECLK)!=OK)	// Не удалось настроить PLL
    	while(1){ };	// Зависаем в бесконечном цикле, PLL неисправен

    /* Обновляем текущие частоты тактирования ядра (SYSCLK) и шин (HCLK и PCLK) */
    SystemCoreClockUpdate();
}

/* Обновление текущей частоты тактирования ядра (SYSCLK) и шин (HCLK, PCLK)  */
void SystemCoreClockUpdate(void)
{
	RCU_SysClk_TypeDef SysClk;
	SysClk = RCU_SysClkStatus();
	SystemCoreClock = getSysClkFreq(SysClk);	// SYSCLK
    APB0BusClock = SystemCoreClock;				// HCLK
    APB1BusClock = getSysPeriphClkFreq(SysClk);	// PCLK
}
