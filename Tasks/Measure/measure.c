/**
  ******************************************************************************
  * @file    measure.с
  * @version 1.0
  * @date:   26.03.2019
  * @brief   Реализация измерительной подсистемы
  *
  ******************************************************************************
  */

#include "measure.h"
#include "FreeRTOS.h"
#include "task.h"
#include "K1921VK028.h"
#include "plib028.h"
#include "plib028_adc.h"
#include "plib028_tmr.h"
#include "plib028_dma.h"

void * pxTaskMeasure; 	/* Указатель на задачу измерителя */

ADC_SEQ_Init_TypeDef ADC_SEQ_InitStruct;		// Структура настройки секвенсоров
ADC_DC_Init_TypeDef ADC_DC_Init_Struct;			// Структура настройки цифровых компараторов
DMA_ChannelInit_TypeDef DMA_ChannelInitStruct;	// Структура настройки каналов DMA (4 канала, по 1 на секвенсор)
DMA_Init_TypeDef DMA_InitStruct;				// Структура настройки контроллера DMA

ElectricityMeas_t GeneratorMeas;				// Параметры электроэнергии генератора
ElectricityMeas_t MainsMeas;					// Параметры электроэнергии сети

DMA_CtrlData_TypeDef DMA_CTRLDATA __attribute__ ((aligned (1024)));

uint32_t SEQ0_Buf[TRANSFERS_TOTAL];				// Буфер результатов измерений секвенсора 0
uint32_t SEQ1_Buf[TRANSFERS_TOTAL];				// Буфер результатов измерений секвенсора 1
uint32_t SEQ2_Buf[TRANSFERS_TOTAL];				// Буфер результатов измерений секвенсора 2
uint32_t SEQ3_Buf[TRANSFERS_TOTAL];				// Буфер результатов измерений секвенсора 3

/* Инициализация измерителя */
void vTaskMeasureInit (void)
{
	PMU_ADCLDOCmd(PMU_ADCLDO_All, ENABLE);	// Вклчаем все 4 регулятора напряжения АЦП (LDO)
	while (!(PMU_ADCLDOStatus(PMU_ADCLDOStatus_ReadyAll)))	// Ожидаем готовности всех 4-х LDO ADC
	{	};
	RCU_ADCClkConfig(RCU_PeriphClk_PLLClk, 2, ENABLE); // Частота тактирования АЦП = 200/6=33.3MHz
	RCU_ADCClkCmd(ENABLE);	// Разрешаем тактирование блока АЦП
	RCU_ADCRstCmd(ENABLE);	// Выводим блок АЦП из состояния сброса

	// Настраиваем и включаем все 4 модуля АЦП с запуском внутренней калибровки
	ADC_AM_ResolutionConfig(ADC_AM_Num_0, ADC_AM_Resolution_12bit);
	ADC_AM_CalibCmd(ADC_AM_Num_0, ENABLE);
	ADC_AM_Cmd(ADC_AM_Num_0, ENABLE);
	ADC_AM_ResolutionConfig(ADC_AM_Num_1, ADC_AM_Resolution_12bit);
	ADC_AM_CalibCmd(ADC_AM_Num_1, ENABLE);
	ADC_AM_Cmd(ADC_AM_Num_1, ENABLE);
	ADC_AM_ResolutionConfig(ADC_AM_Num_2, ADC_AM_Resolution_12bit);
	ADC_AM_CalibCmd(ADC_AM_Num_2, ENABLE);
	ADC_AM_Cmd(ADC_AM_Num_2, ENABLE);
	ADC_AM_ResolutionConfig(ADC_AM_Num_3, ADC_AM_Resolution_12bit);
	ADC_AM_CalibCmd(ADC_AM_Num_3, ENABLE);
	ADC_AM_Cmd(ADC_AM_Num_3, ENABLE);

	// Настраиваем 4 секвенсора для управления модулями АЦП (для каждого модуля выделен свой секвенсор)
	ADC_SEQ_StructInit(&ADC_SEQ_InitStruct);					// Инициализация структуры секвенсоров по умолчанию

	// Секвенсор 0 => модуль ADC0
	ADC_SEQ_InitStruct.StartEvent = ADC_SEQ_StartEvent_SwReq;	// Циклическая работа секвенсора
	ADC_SEQ_InitStruct.SWStartEn = ENABLE;						// Программный запуск секвенсора разрешен
	ADC_SEQ_InitStruct.Req[ADC_SEQ_ReqNum_0] = ADC_CH_Num_0;	// UgA - напряжение генератора, фаза А
	ADC_SEQ_InitStruct.Req[ADC_SEQ_ReqNum_1] = ADC_CH_Num_1;	// UgB - напряжение генератора, фаза B
	ADC_SEQ_InitStruct.Req[ADC_SEQ_ReqNum_2] = ADC_CH_Num_2;	// UgC - напряжение генератора, фаза C
	ADC_SEQ_InitStruct.Req[ADC_SEQ_ReqNum_3] = ADC_CH_Num_3;	// UmA - напряжение сети, фаза А
	ADC_SEQ_InitStruct.Req[ADC_SEQ_ReqNum_4] = ADC_CH_Num_4;	// UmB - напряжение сети, фаза B
	ADC_SEQ_InitStruct.Req[ADC_SEQ_ReqNum_5] = ADC_CH_Num_5;	// UmC - напряжение сети, фаза C
	ADC_SEQ_InitStruct.Req[ADC_SEQ_ReqNum_6] = ADC_CH_Num_6;	// Reserved
	ADC_SEQ_InitStruct.Req[ADC_SEQ_ReqNum_7] = ADC_CH_Num_7;	// RES_IN1 - напряжение резистивного датчика 1
	ADC_SEQ_InitStruct.Req[ADC_SEQ_ReqNum_8] = ADC_CH_Num_8;	// RES_IN2 - напряжение резистивного датчика 2
	ADC_SEQ_InitStruct.Req[ADC_SEQ_ReqNum_9] = ADC_CH_Num_9;	// RES_IN3 - напряжение резистивного датчика 3
	ADC_SEQ_InitStruct.Req[ADC_SEQ_ReqNum_10] = ADC_CH_Num_10;	// Reserved
	ADC_SEQ_InitStruct.Req[ADC_SEQ_ReqNum_11] = ADC_CH_Num_11;	// Reserved

	ADC_SEQ_InitStruct.ReqMax = ADC_SEQ_ReqNum_11;				// Очередь опроса = 12 каналов (ReqNum+1)
	ADC_SEQ_InitStruct.RestartCount = 3;						// 3 перезапуска между запусками
	ADC_SEQ_InitStruct.RestartAverageEn = ENABLE;				// Разрешить усреднение по перезапускам
	ADC_SEQ_InitStruct.RestartTimer = 833;						// Перезапуск каждые 25 мкс
//	ADC_SEQ_InitStruct.DMAFIFOLevel = ADC_SEQ_DMAFIFOLevel_8;	// Запрос DMA при 8 результатах в FIFO
//	ADC_SEQ_InitStruct.DMAEn = ENABLE;							// Разрешаем запрос DMA
	ADC_SEQ_InitStruct.DCEn[ADC_DC_Num_0] = ENABLE;				// Компаратор 0 - мониторинг UgA
	ADC_SEQ_InitStruct.DCEn[ADC_DC_Num_1] = ENABLE;				// Компаратор 1 - мониторинг UgB
	ADC_SEQ_InitStruct.DCEn[ADC_DC_Num_2] = ENABLE;				// Компаратор 2 - мониторинг UgC
	ADC_SEQ_InitStruct.DCEn[ADC_DC_Num_3] = ENABLE;				// Компаратор 3 - мониторинг UsA
	ADC_SEQ_InitStruct.DCEn[ADC_DC_Num_4] = ENABLE;				// Компаратор 4 - мониторинг UsB
	ADC_SEQ_InitStruct.DCEn[ADC_DC_Num_5] = ENABLE;				// Компаратор 5 - мониторинг UsC
	ADC_SEQ_Init(ADC_SEQ_Num_0, &ADC_SEQ_InitStruct);			// Применяем настройки

	ADC_SEQ_Cmd(ADC_SEQ_Num_0, ENABLE);							// Включаем секвенсор
	ADC_SEQ_ITConfig(ADC_SEQ_Num_0, 7, ENABLE);					// Настраиваем прерывания от секвенсора
	ADC_SEQ_ITCmd(ADC_SEQ_Num_0, ENABLE);						// Устанавливаем маску прерывания
	NVIC_EnableIRQ(ADC_SEQ0_IRQn);								// Разрешаем прерывания от секвенсора

	// Секвенсор 1 => модуль ADC1
	ADC_SEQ_InitStruct.StartEvent = ADC_SEQ_StartEvent_SwReq;	// Циклическая работа секвенсора
	ADC_SEQ_InitStruct.SWStartEn = ENABLE;						// Программный запуск секвенсора
	ADC_SEQ_InitStruct.Req[ADC_SEQ_ReqNum_0] = ADC_CH_Num_12;	// IgA - ток генератора, фаза А
	ADC_SEQ_InitStruct.Req[ADC_SEQ_ReqNum_1] = ADC_CH_Num_13;	// IgB - ток генератора, фаза B
	ADC_SEQ_InitStruct.Req[ADC_SEQ_ReqNum_2] = ADC_CH_Num_14;	// IgC - ток генератора, фаза C
	ADC_SEQ_InitStruct.Req[ADC_SEQ_ReqNum_3] = ADC_CH_Num_15;	// DtIn1 - датчик тока 1
	ADC_SEQ_InitStruct.Req[ADC_SEQ_ReqNum_4] = ADC_CH_Num_16;	// ImA - ток сети, фаза А
	ADC_SEQ_InitStruct.Req[ADC_SEQ_ReqNum_5] = ADC_CH_Num_17;	// ImB - ток сети, фаза B
	ADC_SEQ_InitStruct.Req[ADC_SEQ_ReqNum_6] = ADC_CH_Num_18;	// DtIn2 - датчик тока 2
	ADC_SEQ_InitStruct.Req[ADC_SEQ_ReqNum_7] = ADC_CH_Num_19;	// DtIn3 - датчик тока 3
	ADC_SEQ_InitStruct.Req[ADC_SEQ_ReqNum_8] = ADC_CH_Num_20;	// ImC - ток сети, фаза C
	ADC_SEQ_InitStruct.Req[ADC_SEQ_ReqNum_9] = ADC_CH_Num_21;	// Reserved
	ADC_SEQ_InitStruct.Req[ADC_SEQ_ReqNum_10] = ADC_CH_Num_22;	// Reserved
	ADC_SEQ_InitStruct.Req[ADC_SEQ_ReqNum_11] = ADC_CH_Num_23;	// Reserved
	ADC_SEQ_InitStruct.ReqMax = ADC_SEQ_ReqNum_11;				// Очередь опроса = 12 каналов (ReqNum+1)
	ADC_SEQ_InitStruct.RestartCount = 3;						// 3 перезапуска между запусками
	ADC_SEQ_InitStruct.RestartAverageEn = ENABLE;				// Разрешить усреднение по перезапускам
	ADC_SEQ_InitStruct.RestartTimer = 833;						// Перезапуск каждые 25 мкс
//	ADC_SEQ_InitStruct.DMAFIFOLevel = ADC_SEQ_DMAFIFOLevel_8;	// Запрос DMA при 8 результатах в FIFO
//	ADC_SEQ_InitStruct.DMAEn = ENABLE;							// Разрешаем запрос DMA
	ADC_SEQ_InitStruct.DCEn[ADC_DC_Num_6] = ENABLE;				// Компаратор 6 - мониторинг UmA
	ADC_SEQ_InitStruct.DCEn[ADC_DC_Num_7] = ENABLE;				// Компаратор 7 - мониторинг UmB
	ADC_SEQ_InitStruct.DCEn[ADC_DC_Num_8] = ENABLE;				// Компаратор 8 - мониторинг UmC
	ADC_SEQ_InitStruct.DCEn[ADC_DC_Num_9] = ENABLE;				// Компаратор 9 - мониторинг ImA
	ADC_SEQ_InitStruct.DCEn[ADC_DC_Num_10] = ENABLE;			// Компаратор 10 - мониторинг ImB
	ADC_SEQ_InitStruct.DCEn[ADC_DC_Num_11] = ENABLE;			// Компаратор 11 - мониторинг ImC
	ADC_SEQ_Init(ADC_SEQ_Num_1, &ADC_SEQ_InitStruct);			// Применяем настройки

	ADC_SEQ_Cmd(ADC_SEQ_Num_1, ENABLE);							// Включаем секвенсор
	ADC_SEQ_ITConfig(ADC_SEQ_Num_1, 7, ENABLE);					// Настраиваем прерывания от секвенсора
	ADC_SEQ_ITCmd(ADC_SEQ_Num_1, ENABLE);						// Устанавливаем маску прерывания
	NVIC_EnableIRQ(ADC_SEQ1_IRQn);								// Разрешаем прерывания

	// Секвенсор 2 => модуль ADC2
	ADC_SEQ_InitStruct.StartEvent = ADC_SEQ_StartEvent_SwReq;	// Циклическая работа секвенсора
	ADC_SEQ_InitStruct.SWStartEn = ENABLE;						// Программный запуск секвенсора
	ADC_SEQ_InitStruct.Req[ADC_SEQ_ReqNum_0] = ADC_CH_Num_24;	// Ubort
	ADC_SEQ_InitStruct.Req[ADC_SEQ_ReqNum_1] = ADC_CH_Num_25;	// Ucorr
	ADC_SEQ_InitStruct.Req[ADC_SEQ_ReqNum_2] = ADC_CH_Num_26;	// SynM - синхроимпульс напряжения сети, фаза А
	ADC_SEQ_InitStruct.Req[ADC_SEQ_ReqNum_3] = ADC_CH_Num_27;	// SynG - синхроимпульс напряжения генератора, фаза А
	ADC_SEQ_InitStruct.Req[ADC_SEQ_ReqNum_4] = ADC_CH_Num_28;	// Reserved
	ADC_SEQ_InitStruct.Req[ADC_SEQ_ReqNum_5] = ADC_CH_Num_29;	// V5In1 - Датчик напряжения 1, 5В
	ADC_SEQ_InitStruct.Req[ADC_SEQ_ReqNum_6] = ADC_CH_Num_30;	// Reserved
	ADC_SEQ_InitStruct.Req[ADC_SEQ_ReqNum_7] = ADC_CH_Num_31;	// V5In2 - Датчик напряжения 2, 5В
	ADC_SEQ_InitStruct.Req[ADC_SEQ_ReqNum_8] = ADC_CH_Num_32;	// Reserved
	ADC_SEQ_InitStruct.Req[ADC_SEQ_ReqNum_9] = ADC_CH_Num_33;	// V5In3 - Датчик напряжения 3, 5В
	ADC_SEQ_InitStruct.Req[ADC_SEQ_ReqNum_10] = ADC_CH_Num_34;	// Reserved
	ADC_SEQ_InitStruct.Req[ADC_SEQ_ReqNum_11] = ADC_CH_Num_35;	// Reserved

	ADC_SEQ_InitStruct.ReqMax = ADC_SEQ_ReqNum_11;				// Очередь опроса = 12 каналов (ReqNum+1)
	ADC_SEQ_InitStruct.RestartCount = 3;						// 3 перезапуска между запусками
	ADC_SEQ_InitStruct.RestartAverageEn = ENABLE;				// Разрешить усреднение по перезапускам
//	ADC_SEQ_InitStruct.RestartTimer = 833;						// Перезапуск каждые 25 мкс
//	ADC_SEQ_InitStruct.DMAFIFOLevel = ADC_SEQ_DMAFIFOLevel_8;	// Запрос DMA при 8 результатах в FIFO
	ADC_SEQ_InitStruct.DMAEn = ENABLE;							// Разрешаем запрос DMA
	ADC_SEQ_Init(ADC_SEQ_Num_2, &ADC_SEQ_InitStruct);			// Применяем настройки

	ADC_SEQ_Cmd(ADC_SEQ_Num_2, ENABLE);							// Включаем секвенсор
	ADC_SEQ_ITConfig(ADC_SEQ_Num_2, 7, ENABLE);					// Настраиваем прерывания от секвенсора
	ADC_SEQ_ITCmd(ADC_SEQ_Num_2, ENABLE);						// Устанавливаем маску прерывания
	NVIC_EnableIRQ(ADC_SEQ2_IRQn);								// Разрешаем прерывания

	// Секвенсор 3 => модуль ADC3
	ADC_SEQ_InitStruct.StartEvent = ADC_SEQ_StartEvent_SwReq;	// Циклическая работа секвенсора
	ADC_SEQ_InitStruct.SWStartEn = ENABLE;						// Программный запуск секвенсора
	ADC_SEQ_InitStruct.Req[ADC_SEQ_ReqNum_0] = ADC_CH_Num_36;	// V10In1 - Датчик напряжения 1, 10В
	ADC_SEQ_InitStruct.Req[ADC_SEQ_ReqNum_1] = ADC_CH_Num_37;	// Reserved
	ADC_SEQ_InitStruct.Req[ADC_SEQ_ReqNum_2] = ADC_CH_Num_38;	// Reserved
	ADC_SEQ_InitStruct.Req[ADC_SEQ_ReqNum_3] = ADC_CH_Num_39;	// Reserved
	ADC_SEQ_InitStruct.Req[ADC_SEQ_ReqNum_4] = ADC_CH_Num_40;	// Reserved
	ADC_SEQ_InitStruct.Req[ADC_SEQ_ReqNum_5] = ADC_CH_Num_41;	// Reserved
	ADC_SEQ_InitStruct.Req[ADC_SEQ_ReqNum_6] = ADC_CH_Num_42;	// Reserved
	ADC_SEQ_InitStruct.Req[ADC_SEQ_ReqNum_7] = ADC_CH_Num_43;	// V10In2 - Датчик напряжения 2, 10В
	ADC_SEQ_InitStruct.Req[ADC_SEQ_ReqNum_8] = ADC_CH_Num_44;	// Reserved
	ADC_SEQ_InitStruct.Req[ADC_SEQ_ReqNum_9] = ADC_CH_Num_45;	// V10In3 - Датчик напряжения 3, 10В
	ADC_SEQ_InitStruct.Req[ADC_SEQ_ReqNum_10] = ADC_CH_Num_46;	// Reserved
	ADC_SEQ_InitStruct.Req[ADC_SEQ_ReqNum_11] = ADC_CH_Num_47;	// Reserved

	ADC_SEQ_InitStruct.ReqMax = ADC_SEQ_ReqNum_11;				// Очередь опроса = 12 каналов (ReqNum+1)
	ADC_SEQ_InitStruct.RestartCount = 3;						// 3 перезапуска между запусками
	ADC_SEQ_InitStruct.RestartAverageEn = ENABLE;				// Разрешить усреднение по перезапускам
	ADC_SEQ_InitStruct.RestartTimer = 833;						// Перезапуск каждые 25 мкс
//	ADC_SEQ_InitStruct.DMAFIFOLevel = ADC_SEQ_DMAFIFOLevel_8;	// Запрос DMA при 8 результатах в FIFO
//	ADC_SEQ_InitStruct.DMAEn = ENABLE;							// Разрешаем запрос DMA
	ADC_SEQ_Init(ADC_SEQ_Num_3, &ADC_SEQ_InitStruct);			// Применяем настройки

	ADC_SEQ_Cmd(ADC_SEQ_Num_3, ENABLE);							// Включаем секвенсор
	ADC_SEQ_ITConfig(ADC_SEQ_Num_3, 7, ENABLE);					// Настраиваем прерывания от секвенсора
	ADC_SEQ_ITCmd(ADC_SEQ_Num_3, ENABLE);						// Устанавливаем маску прерывания
	NVIC_EnableIRQ(ADC_SEQ3_IRQn);								// Разрешаем прерывания

	// Цифровые компараторы (DC0 - DC13)
	ADC_DC_StructInit(&ADC_DC_Init_Struct);						// Инициализация структуры по умолчанию
	ADC_DC_Init_Struct.Condition = ADC_DC_Condition_Low;		// Результат <= ThresholdLow
	ADC_DC_Init_Struct.Mode = ADC_DC_Mode_SingleHyst;			// Режим: однократный с гистерезисом
	ADC_DC_Init_Struct.Source = ADC_DC_Source_EOC;				// Вход: результат измерения АЦП
	ADC_DC_Init_Struct.ThresholdHigh = 2058;					// Верхняя граница гистерезиса
	ADC_DC_Init_Struct.ThresholdLow = 2048;						// Порог срабатывания компаратора

	// Компаратор 0 <=> ADC_CH_Num_0 [UgA]
	ADC_DC_Init_Struct.Channel = ADC_CH_Num_0;
	ADC_DC_Init(ADC_DC_Num_0, &ADC_DC_Init_Struct);
	ADC_DC_ITConfig(ADC_DC_Num_0, ADC_DC_Mode_SingleHyst, ADC_DC_Condition_Low);
	ADC_DC_ITMaskCmd(ADC_DC_Num_0, ENABLE);

	// Компаратор 1 <=> ADC_CH_Num_1 [UgB]
	ADC_DC_Init_Struct.Channel = ADC_CH_Num_1;
	ADC_DC_Init(ADC_DC_Num_1, &ADC_DC_Init_Struct);
	ADC_DC_ITConfig(ADC_DC_Num_1, ADC_DC_Mode_SingleHyst, ADC_DC_Condition_Low);
	ADC_DC_ITMaskCmd(ADC_DC_Num_1, ENABLE);

	// Компаратор 2 <=> ADC_CH_Num_2 [UgC]
	ADC_DC_Init_Struct.Channel = ADC_CH_Num_2;
	ADC_DC_Init(ADC_DC_Num_2, &ADC_DC_Init_Struct);
	ADC_DC_ITConfig(ADC_DC_Num_2, ADC_DC_Mode_SingleHyst, ADC_DC_Condition_Low);
	ADC_DC_ITMaskCmd(ADC_DC_Num_2, ENABLE);

	// Компаратор 3 <=> ADC_CH_Num_3 [UmA]
	ADC_DC_Init_Struct.Channel = ADC_CH_Num_3;
	ADC_DC_Init(ADC_DC_Num_3, &ADC_DC_Init_Struct);
	ADC_DC_ITConfig(ADC_DC_Num_3, ADC_DC_Mode_SingleHyst, ADC_DC_Condition_Low);
	ADC_DC_ITMaskCmd(ADC_DC_Num_3, ENABLE);

	// Компаратор 4 <=> ADC_CH_Num_4 [UmB]
	ADC_DC_Init_Struct.Channel = ADC_CH_Num_4;
	ADC_DC_Init(ADC_DC_Num_4, &ADC_DC_Init_Struct);
	ADC_DC_ITConfig(ADC_DC_Num_4, ADC_DC_Mode_SingleHyst, ADC_DC_Condition_Low);
	ADC_DC_ITMaskCmd(ADC_DC_Num_4, ENABLE);

	// Компаратор 5 <=> ADC_CH_Num_5 [UmC]
	ADC_DC_Init_Struct.Channel = ADC_CH_Num_5;
	ADC_DC_Init(ADC_DC_Num_5, &ADC_DC_Init_Struct);
	ADC_DC_ITConfig(ADC_DC_Num_5, ADC_DC_Mode_SingleHyst, ADC_DC_Condition_Low);
	ADC_DC_ITMaskCmd(ADC_DC_Num_5, ENABLE);

	// Компаратор 6 <=> ADC_CH_Num_12 [IgA]
	ADC_DC_Init_Struct.Channel = ADC_CH_Num_12;
	ADC_DC_Init(ADC_DC_Num_6, &ADC_DC_Init_Struct);
	ADC_DC_ITConfig(ADC_DC_Num_6, ADC_DC_Mode_SingleHyst, ADC_DC_Condition_Low);
	ADC_DC_ITMaskCmd(ADC_DC_Num_6, ENABLE);

	// Компаратор 7 <=> ADC_CH_Num_13 [IgB]
	ADC_DC_Init_Struct.Channel = ADC_CH_Num_13;
	ADC_DC_Init(ADC_DC_Num_7, &ADC_DC_Init_Struct);
	ADC_DC_ITConfig(ADC_DC_Num_7, ADC_DC_Mode_SingleHyst, ADC_DC_Condition_Low);
	ADC_DC_ITMaskCmd(ADC_DC_Num_7, ENABLE);

	// Компаратор 8 <=> ADC_CH_Num_14 [IgC]
	ADC_DC_Init_Struct.Channel = ADC_CH_Num_14;
	ADC_DC_Init(ADC_DC_Num_8, &ADC_DC_Init_Struct);
	ADC_DC_ITConfig(ADC_DC_Num_8, ADC_DC_Mode_SingleHyst, ADC_DC_Condition_Low);
	ADC_DC_ITMaskCmd(ADC_DC_Num_8, ENABLE);

	// Компаратор 9 <=> ADC_CH_Num_16 [ImA]
	ADC_DC_Init_Struct.Channel = ADC_CH_Num_16;
	ADC_DC_Init(ADC_DC_Num_9, &ADC_DC_Init_Struct);
	ADC_DC_ITConfig(ADC_DC_Num_9, ADC_DC_Mode_SingleHyst, ADC_DC_Condition_Low);
	ADC_DC_ITMaskCmd(ADC_DC_Num_9, ENABLE);

	// Компаратор 10 <=> ADC_CH_Num_17 [ImB]
	ADC_DC_Init_Struct.Channel = ADC_CH_Num_17;
	ADC_DC_Init(ADC_DC_Num_10, &ADC_DC_Init_Struct);
	ADC_DC_ITConfig(ADC_DC_Num_10, ADC_DC_Mode_SingleHyst, ADC_DC_Condition_Low);
	ADC_DC_ITMaskCmd(ADC_DC_Num_10, ENABLE);

	// Компаратор 11 <=> ADC_CH_Num_20 [ImC]
	ADC_DC_Init_Struct.Channel = ADC_CH_Num_20;
	ADC_DC_Init(ADC_DC_Num_11, &ADC_DC_Init_Struct);
	ADC_DC_ITConfig(ADC_DC_Num_11, ADC_DC_Mode_SingleHyst, ADC_DC_Condition_Low);
	ADC_DC_ITMaskCmd(ADC_DC_Num_11, ENABLE);

	// Компаратор 12 <=> ADC_CH_Num_26 [SynM]
	ADC_DC_Init_Struct.Channel = ADC_CH_Num_26;
	ADC_DC_Init(ADC_DC_Num_11, &ADC_DC_Init_Struct);
	ADC_DC_ITConfig(ADC_DC_Num_11, ADC_DC_Mode_SingleHyst, ADC_DC_Condition_Low);
	ADC_DC_ITMaskCmd(ADC_DC_Num_11, ENABLE);

	// Компаратор 13 <=> ADC_CH_Num_27 [SynG]
	ADC_DC_Init_Struct.Channel = ADC_CH_Num_27;
	ADC_DC_Init(ADC_DC_Num_11, &ADC_DC_Init_Struct);
	ADC_DC_ITConfig(ADC_DC_Num_11, ADC_DC_Mode_SingleHyst, ADC_DC_Condition_Low);
	ADC_DC_ITMaskCmd(ADC_DC_Num_11, ENABLE);


	// Инициализация каналов DMA
	DMA_BasePtrConfig((uint32_t)(&DMA_CTRLDATA));					// Базовый указатель
	DMA_ChannelStructInit(&DMA_ChannelInitStruct);					// Инициализация структуры по умолчанию
	DMA_ChannelInitStruct.SrcDataSize = DMA_DataSize_32;			// Источник: 32 бита(4 байта)
	DMA_ChannelInitStruct.SrcDataInc = DMA_DataInc_Disable;			// Источник: нет инкремента
	DMA_ChannelInitStruct.DstDataSize = DMA_DataSize_32;			// Приемник: 32 бита(4 байта)
	DMA_ChannelInitStruct.DstDataInc = DMA_DataInc_32;				// Приемник: инкремент 32 бита(4 байта)
	DMA_ChannelInitStruct.ArbitrationRate = DMA_ArbitrationRate_4;	// 4 передачи/запрос
	DMA_ChannelInitStruct.TransfersTotal = TRANSFERS_TOTAL;			// 12 передач/цикл
	DMA_ChannelInitStruct.Mode = DMA_Mode_Basic;					// Режим: основной

	// Канал 0 (SEQ0_FIFO => SEQ0_Buf)
	DMA_ChannelInitStruct.SrcDataEndPtr = (uint32_t*) &(ADC->SEQ[0].SFIFO);
	DMA_ChannelInitStruct.DstDataEndPtr = &(SEQ0_Buf[TRANSFERS_TOTAL - 1]);
	DMA_ChannelInit(&DMA_CTRLDATA.PRM_DATA.CH[0], &DMA_ChannelInitStruct);

	// Канал 1 (SEQ1_FIFO => SEQ1_Buf)
	DMA_ChannelInitStruct.SrcDataEndPtr = (uint32_t*) &(ADC->SEQ[1].SFIFO);
	DMA_ChannelInitStruct.DstDataEndPtr = &(SEQ1_Buf[TRANSFERS_TOTAL - 1]);
	DMA_ChannelInit(&DMA_CTRLDATA.PRM_DATA.CH[1], &DMA_ChannelInitStruct);

	// Канал 2 (SEQ2_FIFO => SEQ2_Buf)
	DMA_ChannelInitStruct.SrcDataEndPtr = (uint32_t*) &(ADC->SEQ[2].SFIFO);
	DMA_ChannelInitStruct.DstDataEndPtr = &(SEQ2_Buf[TRANSFERS_TOTAL - 1]);
	DMA_ChannelInit(&DMA_CTRLDATA.PRM_DATA.CH[2], &DMA_ChannelInitStruct);

	// Канал 3 (SEQ3_FIFO => SEQ3_Buf)
	DMA_ChannelInitStruct.SrcDataEndPtr = (uint32_t*) &(ADC->SEQ[3].SFIFO);
	DMA_ChannelInitStruct.DstDataEndPtr = &(SEQ3_Buf[TRANSFERS_TOTAL - 1]);
	DMA_ChannelInit(&DMA_CTRLDATA.PRM_DATA.CH[3], &DMA_ChannelInitStruct);

	// Инициализация контроллера DMA
	DMA_StructInit(&DMA_InitStruct);
	DMA_InitStruct.Channel = DMA_Channel_0;
	DMA_InitStruct.ChannelEnable = ENABLE;
	DMA_Init(&DMA_InitStruct);
	DMA_MasterEnableCmd(ENABLE);
    NVIC_EnableIRQ(DMA_CH0_IRQn);

    // Ждем завершения калибровки и инициализации всех 4-х модулей АЦП
	while (!(ADC_AM_ReadyStatus(ADC_AM_Num_0) &&
			 ADC_AM_ReadyStatus(ADC_AM_Num_1) &&
			 ADC_AM_ReadyStatus(ADC_AM_Num_2) &&
			 ADC_AM_ReadyStatus(ADC_AM_Num_3)))	{
	};

	// Настраиваем таймер Т0 (измерение фазы сигналов)
	RCU_APBClk0Cmd(RCU_APBClk0_TMR0, ENABLE);	// Разрешить тактирование таймера Т0
	RCU_APBRst0Cmd(RCU_APBRst0_TMR0, ENABLE);	// Вывести таймер Т0 из состояния сброса
	TMR_PeriodConfig(TMR0, APB1BusClock, 1000);	// Настройка периода счета таймера (мкс)
	TMR_ITCmd(TMR0, ENABLE);					// Разрешение работы прерывания от Т0
	NVIC_EnableIRQ(TMR0_IRQn);					// Разрешаем прерывания от Т0

	// Запускаем измерения
	ADC_SEQ_SwStartCmd();	// Команда на запуск всех 4-х секвенсоров
	TMR_Cmd(TMR0, ENABLE);	// Запуск таймера Т0
}

/* Task измерителя */
void vTaskMeasure(void *pvParameters)
{
	/* Инициализация измерительной подсистемы */
	vTaskMeasureInit();

	/* Запуск измерительной подсистемы */
	for (;;)
	{

    }
}

/*---------------------------------------------------------------*/
/* Прерывание секвенсора 0(данные в FIFO)						 */
/*---------------------------------------------------------------*/
void ADC_SEQ0_IRQHandler()
{
    ADC_SEQ_ITStatusClear(ADC_SEQ_Num_0); // Сброс флага прерывания

}
/*---------------------------------------------------------------*/

/*---------------------------------------------------------------*/
/* Прерывание секвенсора 1(данные в FIFO)						 */
/*---------------------------------------------------------------*/
void ADC_SEQ1_IRQHandler()
{
    ADC_SEQ_ITStatusClear(ADC_SEQ_Num_1); // Сброс флага прерывания

}
/*---------------------------------------------------------------*/

/*---------------------------------------------------------------*/
/* Прерывание секвенсора 2(данные в FIFO)						 */
/*---------------------------------------------------------------*/
void ADC_SEQ2_IRQHandler()
{
    ADC_SEQ_ITStatusClear(ADC_SEQ_Num_2); // Сброс флага прерывания

}
/*---------------------------------------------------------------*/

/*---------------------------------------------------------------*/
/* Прерывание секвенсора 3(данные в FIFO)						 */
/*---------------------------------------------------------------*/
void ADC_SEQ3_IRQHandler()
{
    ADC_SEQ_ITStatusClear(ADC_SEQ_Num_3); // Сброс флага прерывания

}
/*---------------------------------------------------------------*/

/*---------------------------------------------------------------*/
/* Прерывание от компараторов (успешное сравнение)				 */
/*---------------------------------------------------------------*/
void ADC_DC_IRQHandler()
{

	ADC_DC_ITMaskedStatus(ADC_DC_Num_9);

	ADC_DC_ITStatusClear(ADC_DC_Num_9); // Сброс флага прерывания

}
/*---------------------------------------------------------------*/

/*---------------------------------------------------------------*/
/* Прерывание DMA (канал 0, данные в SEQ0_Buf)					 */
/*---------------------------------------------------------------*/
void DMA_CH0_IRQHandler()
{

}
/*---------------------------------------------------------------*/

/*---------------------------------------------------------------*/
/* Прерывание DMA (канал 1, данные в SEQ1_Buf)					 */
/*---------------------------------------------------------------*/
void DMA_CH1_IRQHandler()
{

}
/*---------------------------------------------------------------*/

/*---------------------------------------------------------------*/
/* Прерывание DMA (канал 2, данные в SEQ2_Buf)					 */
/*---------------------------------------------------------------*/
void DMA_CH2_IRQHandler()
{

}
/*---------------------------------------------------------------*/

/*---------------------------------------------------------------*/
/* Прерывание DMA (канал 3, данные в SEQ3_Buf)					 */
/*---------------------------------------------------------------*/
void DMA_CH3_IRQHandler()
{

}
/*---------------------------------------------------------------*/

/*---------------------------------------------------------------*/
/* Прерывание таймера Т0										 */
/*---------------------------------------------------------------*/
void TMR0_IRQHandler()
{
    TMR_ITStatusClear(TMR0);	// Сброс флага прерывания

}
/*---------------------------------------------------------------*/
