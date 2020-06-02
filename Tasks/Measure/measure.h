/**
  ******************************************************************************
  * @file    measure.h
  * @version 1.0
  * @date:   26.03.2019
  * @brief   Измеритель параметров электроэнергии
  *
  ******************************************************************************
  */

#ifndef TASKS_MEASURE_MEASURE_H_
#define TASKS_MEASURE_MEASURE_H_

#include <stdint.h>

/* Распределение каналов измерения АЦП по назначению */
/*---Модуль ADC 0------*		*---Модуль ADC 1------*		*---Модуль ADC 2------*		*---Модуль ADC 3--*
 * ADC_CH0  - UgA	   *		* ADC_CH12 - IgA	  *		* ADC_CH24 - Ubort	  *		* ADC_CH36 - 10V_IN1  *
 * ADC_CH1  - UgB	   *		* ADC_CH13 - IgB	  *		* ADC_CH25 - Ucorr	  *		* ADC_CH37 - Reserved *
 * ADC_CH2  - UgC	   *		* ADC_CH14 - IgC	  *		* ADC_CH26 - SYNM	  *		* ADC_CH38 - Reserved *
 * ADC_CH3  - UsA	   *		* ADC_CH15 - DT_IN1	  *		* ADC_CH27 - SYNG	  *		* ADC_CH39 - Reserved *
 * ADC_CH4  - UsB	   *		* ADC_CH16 - ImA      *		* ADC_CH28 - Reserved *		* ADC_CH40 - Reserved *
 * ADC_CH5  - UsC	   *		* ADC_CH17 - ImB      * 	* ADC_CH29 - 5V_IN1   *		* ADC_CH41 - Reserved *
 * ADC_CH6  - Reserved *		* ADC_CH18 - DT_IN2   *		* ADC_CH30 - Reserved *		* ADC_CH42 - Reserved *
 * ADC_CH7  - RES_IN1  *		* ADC_CH19 - DT_IN3   *		* ADC_CH31 - 5V_IN2   *		* ADC_CH43 - 10V_IN2  *
 * ADC_CH8  - RES_IN2  *		* ADC_CH20 - ImC      *		* ADC_CH32 - Reserved *		* ADC_CH44 - Reserved *
 * ADC_CH9  - RES_IN3  *		* ADC_CH21 - Reserved *		* ADC_CH33 - 5V_IN3   *		* ADC_CH45 - 10V_IN3  *
 * ADC_CH10 - Reserved *		* ADC_CH22 - Reserved *		* ADC_CH34 - Reserved *		* ADC_CH46 - Reserved *
 * ADC_CH11 - Reserved *		* ADC_CH23 - Reserved *		* ADC_CH35 - Reserved *		* ADC_CH47 - Reserved *
 */

#define TRANSFERS_TOTAL 12 /*! 12 передач DMA по запросу от АЦП */

/* Параметры электроэнергии измерительного канала			*/
typedef struct ElectricityMeas
{
	float F;	/* Частота напряжения, [Гц]					*/
	float Ua;	/* Напряжение, фаза А, [В] 					*/
	float Ub;	/* Напряжение, фаза B, [В]					*/
	float Uc;	/* Напряжение, фаза C, [В]					*/
	float Ia;	/* Ток, фаза А, [А]							*/
	float Ib;	/* Ток, фаза B, [А]							*/
	float Ic;	/* Ток, фаза C, [А]							*/
	float Uab;	/* Напряжение межфазное AB, [В]				*/
	float Ubc;	/* Напряжение межфазное BC, [В]				*/
	float Uac;	/* Напряжение межфазное AC, [В]				*/
	float Pa; 	/* Активная мощность в фазе А, [кВт] 		*/
	float Pb;	/* Активная мощность в фазе B, [кВт] 		*/
	float Pc;	/* Активная мощность в фазе C, [кВт] 		*/
	float Ps;	/* Активная мощность суммарная, [кВт] 		*/
	float Qa;	/* Реактивная мощность в фазе А, [кВАР] 	*/
	float Qb;	/* Реактивная мощность в фазе B, [кВАР] 	*/
	float Qc;	/* Реактивная мощность в фазе C, [кВАР] 	*/
	float Qs;	/* Реактивная мощность суммарная, [кВАР] 	*/
	float Sa;	/* Полная мощность в фазе А, [кВА] 			*/
	float Sb;	/* Полная мощность в фазе B, [кВА] 			*/
	float Sc;	/* Полная мощность в фазе C, [кВА] 			*/
	float Ss;	/* Полная мощность суммарная, [кВА] 		*/
	float cosA;	/* Косинус угла между UgA и IgA, [0...1]	*/
	float cosB;	/* Косинус угла между UgB и IgB, [0...1]	*/
	float cosC;	/* Косинус угла между UgC и IgC, [0...1]	*/
	float sinA;	/* Синус угла между UgA и IgA, [0...1]		*/
	float sinB;	/* Синус угла между UgB и IgB, [0...1]		*/
	float sinC;	/* Синус угла между UgC и IgC, [0...1]		*/
	float FiUa;	/* Угол между UgA и UgB, [град]				*/
	float FiUb;	/* Угол между UgB и UgC, [град]				*/
	float FiUc;	/* Угол между UgA и UgC, [град]				*/
	float FiIa;	/* Угол между IgA и IgB, [град]				*/
	float FiIb;	/* Угол между IgB и IgC, [град]				*/
	float FiIc;	/* Угол между IgA и IgC, [град]				*/
	float Uabc;	/* Напряжение среднее по фазам А,В,C, [В]	*/
	int   Faza; /* Нарушение чередования фаз напряжения		*/
} ElectricityMeas_t;

/* Аналоговые входы датчиков (резистивные, тока, напряжения)*/
typedef struct AnalogSensor
{
	float ResIn1;	/* Резистивный датчик 1					*/
	float ResIn2;	/* Резистивный датчик 2					*/
	float ResIn3;	/* Резистивный датчик 3					*/
	float DtIn1;	/* Датчик тока 1						*/
	float DtIn2;	/* Датчик тока 2						*/
	float DtIn3;	/* Датчик тока 3						*/
	float V5In1;	/* Датчик напряжения 1 (5V) 			*/
	float V5In2;	/* Датчик напряжения 2 (5V)				*/
	float V5In3;	/* Датчик напряжения 3 (5V)				*/
	float V10In1;	/* Датчик напряжения 1 (10V)			*/
	float V10In2;	/* Датчик напряжения 2 (10V)			*/
	float V10In3;	/* Датчик напряжения 3 (10V)			*/
} AnalogSensor_t;

/* Аналоговые входы системного назначения */
typedef struct AnalogSystem
{
	float Ubort;	/* Напряжение бортовой сети, Uборт, [В]	*/
	float Ucorr;	/* Напряжение коррекции, Uкорр, [В]		*/
} AnalogSystem_t;

	extern void * pxTaskMeasure;			/* Указатель на задачу измерителя */
	extern ElectricityMeas_t GeneratorMeas;	/* Параметры электроэнергии генератора */
	extern ElectricityMeas_t MainsMeas;		/* Параметры электроэнергии сети */

	/* Инициализация измерителя */
	void vTaskMeasureInit (void);

	/* Задача измерителя */
	void vTaskMeasure(void *pvParameters);

#endif /* TASKS_MEASURE_MEASURE_H_ */
