/********************************************************************************
  * @file    parametrs.h
  * @version 1.0
  * @date:   26.03.2019
  * @brief   Подсистема параметров
  *
  ******************************************************************************
  */

#ifndef TASKS_PARAMETRS_PARAMETRS_H_
#define TASKS_PARAMETRS_PARAMETRS_H_

#include <string.h>

/* Атрибуты секции для параметров */
#define BFLASH __attribute__((section (".parametrs")))

/* Группы параметров */
typedef enum {
  GS_CONTROL   	 = 0UL,  	/*! УПРАВЛЕНИЕ ЭА					 	*/
  AMF     		 = 1UL,  	/*! АВР 							 	*/
  SYNCHRO		 = 2UL,		/*! СИНХРОНИЗАЦИЯ 						*/
  COMMUNICATION	 = 3UL,		/*! КОММУНИКАЦИИ  						*/
  ENG_PROTECT	 = 4UL,		/*! ЗАЩИТА ДВИГАТЕЛЯ 					*/
  FUEL_PUMP		 = 5UL,		/*! ПОДКАЧ. НАСОС 						*/
  GEN_PROTECT	 = 6UL,		/*! ЗАЩИТА ГЕНЕРАТОРА 					*/
  NOMINAL		 = 7UL,		/*! НОМИНАЛЬНЫЕ 						*/
  EWC			 = 8UL,		/*! ЭПЖ 								*/
  LOAD_UNIT		 = 9UL,		/*! НАГРУЗОЧНОЕ УСТРОЙСТВО 				*/
  MAINS_PROTECT	 = 10UL,	/*! ЗАЩИТА СЕТИ 						*/
  SYSTEM		 = 11UL,	/*! СИСТЕМНЫЕ 							*/
  U_CONTROL		 = 12UL,	/*! АРН 								*/
  CALIBRATION	 = 13UL		/*! КАЛИБРОВКИ 							*/
} ParamGroup_t;

#define IS_PARAM_GROUP(VALUE) (((VALUE) == GS_CONTROL) 		|| \
                           	   ((VALUE) == AMF) 			|| \
							   ((VALUE) == SYNCHRO) 		|| \
							   ((VALUE) == COMMUNICATION) 	|| \
							   ((VALUE) == ENG_PROTECT)		|| \
							   ((VALUE) == FUEL_PUMP)		|| \
							   ((VALUE) == GEN_PROTECT)		|| \
							   ((VALUE) == NOMINAL) 		|| \
							   ((VALUE) == EWC) 			|| \
							   ((VALUE) == LOAD_UNIT) 		|| \
							   ((VALUE) == MAINS_PROTECT) 	|| \
							   ((VALUE) == SYSTEM) 			|| \
							   ((VALUE) == U_CONTROL)		|| \
							   ((VALUE) == CALIBRATION))

/* Уровень доступа к параметрам */
typedef enum {
  OPERATOR   	 = 0x0UL,   /*! Оператор    */
  ADJUSTER 		 = 0x1UL,   /*! Наладчик    */
  ENGINEER		 = 0x2UL,	/*! Инженер     */
  DEVELOPER		 = 0x3UL	/*! Разработчик */
} AccessLevel_t;

#define IS_ACCESS_LEVEL(VALUE) (((VALUE) == OPERATOR)	|| \
                           	   ((VALUE) == ADJUSTER) 	|| \
							   ((VALUE) == ENGINEER) 	|| \
							   ((VALUE) == DEVELOPER))

/* Тип параметра */
typedef enum {
  INTEGERS   = 0x0UL,	/*! целое со знаком    			*/
  FLOAT 	 = 0x1UL,   /*! число с плавающей точкой    */
  LIST		 = 0x2UL,	/*! список					    */
  TABLE		 = 0x3UL	/*! таблица						*/
} ParamType_t;

#define IS_PARAM_TYPE(VALUE)  (((VALUE) == INTEGER)	|| \
                           	   ((VALUE) == FLOAT) 	|| \
							   ((VALUE) == LIST) 	|| \
							   ((VALUE) == TABLE))

/* Структура целочисленного параметра */
typedef struct ParamDescriptor {
	uint32_t index;				/*! Порядковый номер параметра в системе (0...N) */
	ParamType_t type;			/*! Тип параметра */
	ParamGroup_t group;			/*! Группа параметров */
	AccessLevel_t accessLevel;	/*! Уровень доступа к параметру */
	char *name;					/*! Наменование параметра */
	char *units; 				/*! Единицы измерения параметра */
	void *data;					/*! Данные по умолчанию */
	void *minValue;				/*! Минимальное значение параметра */
	void *maxValue;				/*! Максимальное значение параметра */
	uint32_t size;				/*! Размер поля для вывода на экран */
	uint32_t point;				/*! Положение десятичной точки */
	void (*ParamRecalc)(void);	/*! Указатель на пересчетную функцию */
} ParamDescriptor_t;

typedef struct ParamInt {
	uint32_t data;				/*! Данные по умолчанию */
	uint32_t minValue;			/*! Минимальное значение параметра */
	uint32_t maxValue;			/*! Максимальное значение параметра */
} ParamInt_t;

/* Структура вещественного параметра */
typedef struct ParamFloat {
	uint32_t index;				/*! Порядковый номер параметра в системе (0...N) */
	ParamType_t type;			/*! Тип параметра */
	ParamGroup_t group;			/*! Группа параметров */
	AccessLevel_t accessLevel;	/*! Уровень доступа к параметру */
	char *units;				/*! Единицы измерения параметра */
	void *data;					/*! Данные по умолчанию */
	void *minValue;				/*! Минимальное значение параметра */
	void *maxValue;				/*! Максимальное значение параметра */
	char *name;					/*! Наменование параметра */
	uint32_t size;				/*! Размер поля для вывода на экран */
	uint32_t point;				/*! Положение десятичной точки */
	void (*ParamRecalc)(void);	/*! Указатель на пересчетную функцию */
} ParamFloat_t;

/* Структура списочного параметра  */
typedef struct ParamList {
	uint32_t index;				/*! Порядковый номер параметра в системе (0...N) */
	char *identificator;		/*! Название параметра в системе */
	ParamType_t type;			/*! Тип параметра */
	ParamGroup_t group;			/*! Группа параметров */
	AccessLevel_t accessLevel;	/*! Уровень доступа к параметру */
	char *units;				/*! Единицы измерения параметра */
	char data;					/*! Индекс элемента списка по умолчанию */
	char *list;					/*! Минимальное значение параметра */

	char *name;					/*! Наменование параметра */
	uint32_t size;				/*! Размер поля для вывода на экран */
	uint32_t point;				/*! Положение десятичной точки */
	void (*ParamRecalc)(void);	/*! Указатель на пересчетную функцию */
} ParamList_t;

/* Структура табличного параметра  */
typedef struct ParamTable {
	uint32_t index;				/*! Порядковый номер параметра в системе (0...N) */
	ParamType_t type;			/*! Тип параметра */
	ParamGroup_t group;			/*! Группа параметров */
	AccessLevel_t accessLevel;	/*! Уровень доступа к параметру */
	char *units;				/*! Единицы измерения параметра */
	float data;					/*! Данные по умолчанию */
	float minValue;				/*! Минимальное значение параметра */
	float maxValue;				/*! Максимальное значение параметра */
	char *name;					/*! Наменование параметра */
	uint32_t size;				/*! Размер поля для вывода на экран */
	uint32_t point;				/*! Положение десятичной точки */
	void (*ParamRecalc)(void);	/*! Указатель на пересчетную функцию */
} ParamTable_t;

#endif /* TASKS_PARAMETRS_PARAMETRS_H_ */
