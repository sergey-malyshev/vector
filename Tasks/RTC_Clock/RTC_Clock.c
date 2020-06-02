/**
  ******************************************************************************
  * @file    RTC_Clock.с
  * @version 1.0
  * @date:   26.03.2019
  * @brief   Часы реального времени + счетчики наработки
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "plib028_rtc.h"
#include "plib028_rcu.h"
#include "RTC_Clock.h"
#include "measure.h"

/* Varibles ------------------------------------------------------------------*/
void * pxTaskRTC; 				// Указатель на задачу часов реального времени
RTC_Time_TypeDef CurrentTime;	// Текущее время (доли секунды, секунды, минуты, часы)
RTC_Date_TypeDef CurrentDate;	// Текущая дата (день недели, день, месяц, год)
ClockCntr_TypeDef PowerCounter;	// Счетчик общей наработки дд:чч:мм (включено питание контроллера)
ClockCntr_TypeDef MotoCounter;	// Счетчик моточасов двигателя дд:чч:мм (двигатель запущен)
uint32_t LoadCounter;			// Счетчик наработки под нагрузкой кВт-ч (контактор замкнут)
uint32_t PowerOnCntr = 0;		// Счетчик секунд с момента запуска системы
uint32_t MotoOnCntr = 0;		// Счетчик секунд запущенного двигателя
uint32_t LoadOnCntr = 0;		// Счетчик секунд замкутого состояния контактора

/* Function ------------------------------------------------------------------*/

/*---------------------------------------------------------------*/
/* Инициализация часов реального времени 						 */
/*---------------------------------------------------------------*/
void vTaskRTCInit (void)
{
    uint32_t is_configured = 0;
    uint32_t timeout_counter = 0;

    RCU_APBClk0Cmd(RCU_APBClk0_RTC, ENABLE);	// Разрешаем тактирование блока RTC
    RCU_APBRst0Cmd(RCU_APBRst0_RTC, ENABLE);	// Включаем блок RTC

    //ждём обновления в теневые регистры
    while (!is_configured && (timeout_counter < 1000000)) {
    	RTC_GetDate(RTC_Format_BCD, &CurrentDate);
    	if(CurrentDate.Year == 0x15){
    		is_configured = 0;
    	}
    	else {
    		is_configured = 1;
    	}
        timeout_counter++;
    }

    if (!is_configured) {	/* Часы выключены, устанавливаем дату и время по умолчанию */
    	CurrentDate.Day = 0x01;
    	CurrentDate.Month = RTC_Month_January;
    	CurrentDate.Year = 0x15;
    	CurrentDate.Weekday = RTC_Weekday_Thursday;
    	CurrentTime.Second = 0x00;
    	CurrentTime.Minute = 0x00;
    	CurrentTime.Hour = 0x09;
    	RTC_SetDate(RTC_Format_BCD, &CurrentDate);
    	RTC_SetTime(RTC_Format_BCD, &CurrentTime);
    }
    else {					/* Часы включены, читаем текущую дату и время */
    	RTC_GetDate(RTC_Format_BCD, &CurrentDate);
    	RTC_GetTime(RTC_Format_BCD, &CurrentTime);
    }
    NVIC_EnableIRQ(RTC_IRQn);	// Разрешаем прерывания от RTC
}
/*---------------------------------------------------------------*/

/*---------------------------------------------------------------*/
/* Task RTC 													 */
/*---------------------------------------------------------------*/
void vTaskRTC(void *pvParameters)
{
	/* Инициализация RTC */
	vTaskRTCInit();

	/* Запуск RTC */
	for (;;)
	{
		PowerCounter.Minute = (uint32_t)(PowerOnCntr);
		PowerCounter.Hour = PowerOnCntr % 60;
		PowerCounter.Day = (uint32_t)(PowerOnCntr / 86400);

		MotoCounter.Minute = MotoOnCntr % 60;
		MotoCounter.Hour = MotoOnCntr % 60;
		MotoCounter.Day = MotoOnCntr % 60;
    }
}
/*---------------------------------------------------------------*/

/*---------------------------------------------------------------*/
/* Прерывания RTC, каждую секунду 								 */
/*---------------------------------------------------------------*/
void RTC_IRQHandler()
{
	RTC_GetDate(RTC_Format_BCD, &CurrentDate);	// Читаем текущую дату
	RTC_GetTime(RTC_Format_BCD, &CurrentTime);	// Читаем текущее время
	PowerOnCntr++;				// Инкремент счетчика общей наработки
/*	if(EngineRun == 1){			// Двигатель запущен
		MotoOnCntr++;			// Инкремент счетчика моточасов двигателя
	}
	if(GBBreaker == 1){			// Контактор генератора замкнут
		LoadOnCntr += (uint32_t) GeneratorMeas.Ps/3600;	// Расчет кВт-ч работы под нагрузкой
	}
*/
}
/*---------------------------------------------------------------*/
