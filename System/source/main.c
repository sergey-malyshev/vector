/**
  ******************************************************************************
  * @file    main.c
  * @version 1.0
  * @date:   26.03.2019
  * @brief   Выполняется создание задач и запуск планировщика FREERTOS
  *
  ******************************************************************************
  */

/* Include General */
#include "FreeRTOS.h"
#include "task.h"
#include "misc.h"

/* Include Tasks */
#include "measure.h"
#include "RTC_Clock.h"

/* Точка входа в систему */
int main(void)
{
	/* Конфигурируем распределение бит приоритета. 4 bits for pre-emption priority; 0 bits for subpriority */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);

	/************************************ Создаем задачи **************************************/

	/* Измеритель параметров электроэнергии */
	xTaskCreate( vTaskMeasure, ( const char * const ) "Measure", configMINIMAL_STACK_SIZE, NULL, 2,
			                            ( xTaskHandle * ) &pxTaskMeasure);

	/* Часы реального времени */
	xTaskCreate( vTaskRTC, ( const char * const ) "RTC", configMINIMAL_STACK_SIZE, NULL, 2,
				                            ( xTaskHandle * ) &pxTaskRTC);




	/*----------------------------------------------------------------------------------------*/

	/* Запускаем планировщик задач */
	vTaskStartScheduler();

	/* бесконечный цикл, сюда мы попасть не должны (только если по ошибке) */
	for(;;);

	return 0;
}
