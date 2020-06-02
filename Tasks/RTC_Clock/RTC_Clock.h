/**
  ******************************************************************************
  * @file    RTC_Clock.h
  * @version 1.0
  * @date:   26.03.2019
  * @brief   Часы реального времени
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion ---------------------------------------*/
#ifndef RTC_CLOCK_H
#define RTC_CLOCK_H

/*-------------Includes---------------------------------------------------------*/
#include "plib028_rtc.h"

/*-------------Defines----------------------------------------------------------*/
#define HoursInDay 24		// Часов в дне
#define MinutesInHour 60	// Минут в часе
#define SecondInMinutes 60	// Секунд в минуте

/* Счетчик наработки */
typedef struct {
	uint32_t Minute;	/* Минуты */
	uint32_t Hour;		/* Часы	  */
	uint32_t Day;		/* Дни	  */
} ClockCntr_TypeDef;

/*-------------Variables--------------------------------------------------------*/
extern void * pxTaskRTC;				/* Указатель на задачу RTC */

/*-------------Function prototypes-----------------------------------------------*/
void vTaskRTCInit (void);				/* Инициализация RTC 	*/
void vTaskRTC(void *pvParameters);		/* Задача RTC			*/

#endif /* RTC_CLOCK_H */








