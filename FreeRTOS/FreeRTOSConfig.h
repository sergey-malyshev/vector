/* 	FreeRTOSConfig.h - Конфигурационный файл ОСРВ FREERTOS
*	Version: 1.0
*	Date: 22.06.18
*/

#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H


/* Тип многозадачности (0 - кооперативная, 1 - вытесняющая)	*/
#define configUSE_PREEMPTION            1

/* Частота тактирования ядра */
#define configCPU_CLOCK_HZ              ( ( unsigned long ) 200000000 )

/* Частота срабатывания системного таймера, Гц				 */
#define configTICK_RATE_HZ              ( ( portTickType ) 1000 )

/* Максимальное количество приоритетов задач */
#define configMAX_PRIORITIES            ( 8 )

/* Минимальный размер стека задачи (слов, 1 слово = 4 байта) */
#define configMINIMAL_STACK_SIZE        ( ( unsigned short ) 100 )

/* Размер кучи, Bytes */
#define configTOTAL_HEAP_SIZE           ( ( size_t ) ( 18 * 1024 ) )

/* максимальная длина имени задачи(в символах ASCII) */
#define configMAX_TASK_NAME_LEN         ( 16 )

/* разрядность системного таймера  (0 - 32 бит; 1 - 16 бит) */
#define configUSE_16_BIT_TICKS          0

/* Поддержка трасировки (0 - трассировка выключена, 1 - трассировка включена) */
#define configUSE_TRACE_FACILITY        0

#define configIDLE_SHOULD_YIELD         1

#define configUSE_MUTEXES               0
#define configUSE_COUNTING_SEMAPHORES   0
#define configUSE_ALTERNATIVE_API       0
#define configCHECK_FOR_STACK_OVERFLOW  0
#define configUSE_RECURSIVE_MUTEXES     0
#define configQUEUE_REGISTRY_SIZE       8
#define configGENERATE_RUN_TIME_STATS   0
#define configUSE_IDLE_HOOK             0
#define configUSE_TICK_HOOK             0

/* Сопрограммы */
#define configUSE_CO_ROUTINES             0
#define configMAX_CO_ROUTINE_PRIORITIES ( 2 )

/* Настройки службы таймеров */
#define configUSE_TIMERS				1
#define configTIMER_TASK_PRIORITY		( 2 )
#define configTIMER_QUEUE_LENGTH		10
#define configTIMER_TASK_STACK_DEPTH	( configMINIMAL_STACK_SIZE * 2 )

/* API функции (1 - используется, 0 - не используется). */
#define INCLUDE_vTaskPrioritySet                1
#define INCLUDE_uxTaskPriorityGet               1
#define INCLUDE_vTaskDelete                     1
#define INCLUDE_vTaskCleanUpResources   		1
#define INCLUDE_vTaskSuspend                    1
#define INCLUDE_vTaskDelayUntil                 1
#define INCLUDE_vTaskDelay                      1
#define INCLUDE_xTaskAbortDelay                 1
#define INCLUDE_uxTaskGetStackHighWaterMark 	1

/* Cortex-M specific definitions. */
#ifdef __NVIC_PRIO_BITS
	/* __NVIC_PRIO_BITS will be specified when CMSIS is being used. */
	#define configPRIO_BITS       		__NVIC_PRIO_BITS
#else
	#define configPRIO_BITS       		4        /* 15 priority levels */
#endif

/* The lowest interrupt priority that can be used in a call to a "set priority"
function. */
#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY			0xf

/* The highest interrupt priority that can be used by any interrupt service
routine that makes calls to interrupt safe FreeRTOS API functions.  DO NOT CALL
INTERRUPT SAFE FREERTOS API FUNCTIONS FROM ANY INTERRUPT THAT HAS A HIGHER
PRIORITY THAN THIS! (higher priorities are lower numeric values. */
#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY	5

/* Interrupt priorities used by the kernel port layer itself.  These are generic
to all Cortex-M ports, and do not rely on any particular library functions. */
#define configKERNEL_INTERRUPT_PRIORITY 		( configLIBRARY_LOWEST_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )
/* !!!! configMAX_SYSCALL_INTERRUPT_PRIORITY must not be set to zero !!!!
See http://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html. */
#define configMAX_SYSCALL_INTERRUPT_PRIORITY 	( configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )

/* Normal assert() semantics without relying on the provision of an assert.h
header file. */
#define configASSERT( x ) if( ( x ) == 0 ) { taskDISABLE_INTERRUPTS(); for( ;; ); }	

/* Переопределение обработчиков прерываний для порта*/
#define vPortSVCHandler 		SVC_Handler		// 	Запуск первой задачи на планирование
#define xPortPendSVHandler 		PendSV_Handler	//	Планировщик, переключение контекста
#define xPortSysTickHandler 	SysTick_Handler	//	Системный таймер


#endif /* FREERTOS_CONFIG_H */
