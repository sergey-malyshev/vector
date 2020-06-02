/*==============================================================================
 * Заголовочный файл диалога с модулем дисплейным контроллера "Вектор"
 *------------------------------------------------------------------------------
 * Copyright 2019 	АО НПП "Проект-Техника"
 * Author:	Проект-Техника, Малышев Сергей <onega.malishev@yandex.ru>
 * Version: v1.0	02/04/19
 *==============================================================================
 * ДАННОЕ ПРОГРАММНОЕ ОБЕСПЕЧЕНИЕ ПРЕДОСТАВЛЯЕТСЯ «КАК ЕСТЬ», БЕЗ КАКИХ-ЛИБО
 * ГАРАНТИЙ, ЯВНО ВЫРАЖЕННЫХ ИЛИ ПОДРАЗУМЕВАЕМЫХ, ВКЛЮЧАЯ ГАРАНТИИ ТОВАРНОЙ
 * ПРИГОДНОСТИ, СООТВЕТСТВИЯ ПО ЕГО КОНКРЕТНОМУ НАЗНАЧЕНИЮ И ОТСУТСТВИЯ
 * НАРУШЕНИЙ, НО НЕ ОГРАНИЧИВАЯСЬ ИМИ. ДАННОЕ ПРОГРАММНОЕ ОБЕСПЕЧЕНИЕ
 * ПРЕДНАЗНАЧЕНО ДЛЯ ОЗНАКОМИТЕЛЬНЫХ ЦЕЛЕЙ И НАПРАВЛЕНО ТОЛЬКО НА
 * ПРЕДОСТАВЛЕНИЕ ДОПОЛНИТЕЛЬНОЙ ИНФОРМАЦИИ О ПРОДУКТЕ, С ЦЕЛЬЮ СОХРАНИТЬ ВРЕМЯ
 * ПОТРЕБИТЕЛЮ. НИ В КАКОМ СЛУЧАЕ АВТОРЫ ИЛИ ПРАВООБЛАДАТЕЛИ НЕ НЕСУТ
 * ОТВЕТСТВЕННОСТИ ПО КАКИМ-ЛИБО ИСКАМ, ЗА ПРЯМОЙ ИЛИ КОСВЕННЫЙ УЩЕРБ, ИЛИ
 * ПО ИНЫМ ТРЕБОВАНИЯМ, ВОЗНИКШИМ ИЗ-ЗА ИСПОЛЬЗОВАНИЯ ПРОГРАММНОГО ОБЕСПЕЧЕНИЯ
 * ИЛИ ИНЫХ ДЕЙСТВИЙ С ПРОГРАММНЫМ ОБЕСПЕЧЕНИЕМ.
 *
 *                              2019 АО "ПРОЕКТ-ТЕХНИКА"
 *==============================================================================
 */

#ifndef DISPLAY_H
#define DISPLAY_H

/*-------------Includes---------------------------------------------------------*/
#include "stdint.h"

/*-------------Defines----------------------------------------------------------*/

/**
  * @brief  Коды светодиодов модуля дисплейного
  */
typedef enum {
	LED_RESERVED0,		/*!<LED 0:  Reserved 						*/
	LED_RESERVED1,		/*!<LED 1:  Reserved 						*/
	LED_PUMP_AUT,		/*!<LED 2:  Авт. режим подкач. насоса 		*/
	LED_ON_OFF_PUMP,	/*!<LED 3:  Состояние подкач. насоса 		*/
	LED_MAINS_STATE,	/*!<LED 4:  Параметры э/э сети 				*/
	LED_MAINS_BREAKER,	/*!<LED 5:  Состояние контактора сети		*/
	LED_LOAD,			/*!<LED 6:  Состояние нагрузки ЭА			*/
	LED_GEN_BREAKER,	/*!<LED 7:  Состояние контактора генератора	*/
	LED_GEN_STATE,		/*!<LED 8:  Параметры э/э генератора		*/
	LED_RESERVED2,		/*!<LED 9:  Reserved						*/
	LED_STATUS_4,		/*!<LED 10: Индикатор статуса ЭА №4			*/
	LED_STATUS_3,		/*!<LED 11: Индикатор статуса ЭА №3			*/
	LED_STATUS_2,		/*!<LED 12: Индикатор статуса ЭА №2			*/
	LED_STATUS_1,		/*!<LED 13: Индикатор статуса ЭА №1			*/
	LED_ATTENT,			/*!<LED 14: Предупреждения ЭА				*/
	LED_ERROR			/*!<LED 15: Ошибки ЭА						*/
} LED_Num_TypeDef;

#define IS_LED_NUM(VALUE) (((VALUE) == LED_PUMP_AUT) 		|| \
                           ((VALUE) == LED_ON_OFF_PUMP) 	|| \
                           ((VALUE) == LED_MAINS_STATE) 	|| \
                           ((VALUE) == LED_MAINS_BREAKER) 	|| \
                           ((VALUE) == LED_LOAD)			|| \
                           ((VALUE) == LED_GEN_BREAKER)		|| \
                           ((VALUE) == LED_GEN_STATE)		|| \
                           ((VALUE) == LED_STATUS_4) 		|| \
                           ((VALUE) == LED_STATUS_3) 		|| \
                           ((VALUE) == LED_STATUS_2) 		|| \
                           ((VALUE) == LED_STATUS_1) 		|| \
                           ((VALUE) == LED_ATTENT) 			|| \
                           ((VALUE) == LED_ERROR))

/**
  * @brief  Коды клавиш модуля дисплейного
  */
typedef enum {
	KEY_RESERVED0,		/*!<KEY 0:  RESERVED 						*/
	KEY_RESERVED1,		/*!<KEY 1:  RESERVED 						*/
	KEY_STOP,			/*!<KEY 2:  ОСТАНОВ ЭА(группы ЭА)	 		*/
	KEY_START,			/*!<KEY 3:  ЗАПУСК ЭА(группы ЭА)	 		*/
	KEY_ON_OFF_GB,		/*!<KEY 4:  ВКЛ/ВЫКЛ КОНТАКТОРА ГЕНЕРАТОРА	*/
	KEY_ON_OFF_MB,		/*!<KEY 5:  ВКЛ/ВЫКЛ КОНТАКТОРА СЕТИ		*/
	KEY_RIGHT,			/*!<KEY 6:  СТРЕЛКА ВПРАВО					*/
	KEY_ENTER,			/*!<KEY 7:  ВВОД							*/
	KEY_ACK,			/*!<KEY 8:  СБРОС							*/
	KEY_ON_OFF_PUMP,	/*!<KEY 9:  ВКЛ/ВЫКЛ ПН						*/
	KEY_UP,				/*!<KEY 10: СТРЕЛКА ВВЕРХ					*/
	KEY_DOWN,			/*!<KEY 11: СТРЕЛКА ВНИЗ					*/
	KEY_MODE_RIGHT,		/*!<KEY 12: РЕЖИМ ВПРАВО					*/
	KEY_AUTO_PUMP,		/*!<KEY 13: ВКЛ/ВЫКЛ АВТ. РЕЖИМ ПН			*/
	KEY_LEFT,			/*!<KEY 14: СТРЕЛКА ВЛЕВО					*/
	KEY_ESC,			/*!<KEY 15: ОТМЕНА							*/
	KEY_MODE_LEFT		/*!<KEY 16: РЕЖИМ ВЛЕВО						*/
}KEY_Num_TypeDef;

#define IS_KEY_NUM(VALUE) (((VALUE) == KEY_STOP) 			|| \
                           ((VALUE) == KEY_START) 			|| \
                           ((VALUE) == KEY_ON_OFF_GB) 		|| \
                           ((VALUE) == KEY_ON_OFF_MB) 		|| \
                           ((VALUE) == KEY_RIGHT)			|| \
                           ((VALUE) == KEY_ENTER)			|| \
                           ((VALUE) == KEY_ACK) 			|| \
						   ((VALUE) == KEY_ON_OFF_PUMP)		|| \
                           ((VALUE) == KEY_UP) 				|| \
                           ((VALUE) == KEY_DOWN) 			|| \
                           ((VALUE) == KEY_MODE_RIGHT) 		|| \
                           ((VALUE) == KEY_AUTO_PUMP) 		|| \
                           ((VALUE) == KEY_LEFT) 			|| \
                           ((VALUE) == KEY_ESC) 			|| \
						   ((VALUE) == KEY_MODE_LEFT))


/**********************  Экранные элементы **************************/

/**
  * @brief  Коды экранных элементов модуля дисплейного
  */
typedef enum {
	CLEAR_SCREEN 	= 0xFC,	/*!<ScrElem 0:  Очистка экрана заданным кодом 						*/
	CLEAR_INDEX 	= 0xF1,	/*!<ScrElem 1:  Удалить все объекты, заданные командами типа Set_x  */
	BIT_MAP			= 0xE0,	/*!<ScrElem 2:  Рисовать битовый образ						 		*/
	SET_LIST_IN		= 0xE1,	/*!<ScrElem 3:  Установить поле для ввода выбора из списка	 		*/
	SET_FIXED_IN	= 0xE2,	/*!<ScrElem 4:  	*/
	SINGLE_ID		= 0xE3,	/*!<ScrElem 5:  	*/
	SET_SINGLE		= 0xE4,	/*!<ScrElem 6:  	*/
	FIXED_ID		= 0xE5,	/*!<ScrElem 7:  	*/
	SET_FIXED		= 0xE6,	/*!<ScrElem 8:  	*/
	INTEGER_ID		= 0xE5,	/*!<ScrElem 9:  	*/
	SET_INTEGER		= 0xE6,	/*!<ScrElem 10: 	*/
	TEXT_ID			= 0xE7,	/*!<ScrElem 11: 	*/
	SET_TEXT		= 0xE8,	/*!<ScrElem 12: 	*/
	SINGLE			= 0xE9,	/*!<ScrElem 13: 	*/
	FIXED			= 0xEA,	/*!<ScrElem 14: 	*/
	INTEGER			= 0xEB,	/*!<ScrElem 15: 	*/
	CIRCLE			= 0xEC,	/*!<ScrElem 16: 	*/
	LINE			= 0xED,	/*!<ScrElem 17: 	*/
	TEXT			= 0xEE,	/*!<ScrElem 18: 	*/
	LED_MASK		= 0xEF,	/*!<ScrElem 19: 	*/
	MENU_ITEM		= 0xDF,	/*!<ScrElem 20: 	*/
	SET_SINGLE_IN	= 0xDE,	/*!<ScrElem 21: 	*/
	SET_INTEGER_IN	= 0xDD,	/*!<ScrElem 22: 	*/
	SECTOR			= 0xDC,	/*!<ScrElem 23: 	*/
	SET_BG			= 0xDB,	/*!<ScrElem 24: 	*/
	BG_ID			= 0xDA,	/*!<ScrElem 25: 	*/
	BIT_ELEMENT		= 0xD9,	/*!<ScrElem 26: 	*/
	SET_BIT			= 0xD8,	/*!<ScrElem 27: 	*/
	BIT_ID			= 0xD7,	/*!<ScrElem 28: 	*/
	CLEAR_AREA		= 0xD6,	/*!<ScrElem 29: 	*/
	WRITE_HEX		= 0xD5,	/*!<ScrElem 30: 	*/
	SET_PWM			= 0xD4,	/*!<ScrElem 31: 	*/
	WR_TIME			= 0xD3,	/*!<ScrElem 32: 	*/
	WR_DATE			= 0xD2,	/*!<ScrElem 33: 	*/
	SET_TIME_IN		= 0xD1,	/*!<ScrElem 34: 	*/
	SET_DATE_IN		= 0xD0,	/*!<ScrElem 35: 	*/
	WR_TIME_ID		= 0xCF	/*!<ScrElem 36: 	*/

}Screen__Elem_TypeDef;

/**
  * @brief  Строки экрана (0-7)
  */
typedef enum {
	STR0 	= 0x00,	/*!Строка 0					*/
	STR1 	= 0x01,	/*!Строка 1					*/
	STR2 	= 0x02,	/*!Строка 2					*/
	STR3 	= 0x03,	/*!Строка 3					*/
	STR4 	= 0x04,	/*!Строка 4					*/
	STR5 	= 0x05,	/*!Строка 5					*/
	STR6 	= 0x06,	/*!Строка 6					*/
	STR7 	= 0x07	/*!Строка 7					*/
}Screen__String_TypeDef;

/**
  * @brief  Позиция в строке экрана (0-15)
  */
typedef enum {
	POS0 	= 0x00,	/*!Позиция 0					*/
	POS1 	= 0x01,	/*!Позиция 1					*/
	POS2 	= 0x02,	/*!Позиция 2					*/
	POS3 	= 0x03,	/*!Позиция 3					*/
	POS4 	= 0x04,	/*!Позиция 4					*/
	POS5 	= 0x05,	/*!Позиция 5					*/
	POS6 	= 0x06,	/*!Позиция 6					*/
	POS7 	= 0x07,	/*!Позиция 7					*/
	POS8 	= 0x08,	/*!Позиция 8					*/
	POS9 	= 0x09,	/*!Позиция 9					*/
	POS10 	= 0x0A,	/*!Позиция 10					*/
	POS11 	= 0x0B,	/*!Позиция 11					*/
	POS12 	= 0x0C,	/*!Позиция 12					*/
	POS13 	= 0x0D,	/*!Позиция 13					*/
	POS14 	= 0x0E,	/*!Позиция 14					*/
	POS15 	= 0x0F,	/*!Позиция 15					*/
}Screen__Position_TypeDef;

/**
  * @brief  Режим вывода текста
  */
typedef enum {
	MODE0 	= 0x00,	/*!Режим 0 (белое на черном)*/
	MODE1 	= 0x01,	/*!Режим 1 (черное на белом)*/
}Screen__Mode_TypeDef;

/**
  * @brief  Размер поля вывода
  */
typedef enum {
	FSIZE1 	= 0x01,	/*!1 символ*/
	FSIZE2 	= 0x02,	/*!2 символ*/
	FSIZE3 	= 0x03,	/*!3 символ*/
	FSIZE4 	= 0x04,	/*!4 символ*/
	FSIZE5 	= 0x05,	/*!5 символ*/
	FSIZE6 	= 0x06,	/*!6 символ*/
	FSIZE7 	= 0x07,	/*!7 символ*/
	FSIZE8 	= 0x08,	/*!8 символ*/
	FSIZE9 	= 0x09,	/*!9 символ*/
	FSIZE10	= 0x0A,	/*!10 символ*/
}Screen__FSIZE_TypeDef;

/**
  * @brief  Положение точки
  */
typedef enum {
	POINT0 	= 0x00,	/*!0 знаков   */
	POINT1 	= 0x01,	/*!1 знак     */
	POINT2 	= 0x02,	/*!2 знака    */
	POINT3 	= 0x03,	/*!3 знака    */
	POINT4 	= 0x04,	/*!4 знака    */
	POINT5 	= 0x05,	/*!4 знаков   */
	POINT6 	= 0x06,	/*!6 знаков   */
}Screen__Point_TypeDef;

/**
  * @brief Clear_Index. Очистка индексов
  */
typedef struct {
	void *NextElement;			/* Указатель на следующий элемент	*/
	uint8_t CodeElement;		/* Код элемента						*/
	uint8_t Visible;			/* Уровень видимости				*/
} Clear_Index_TypeDef;

/**
  * @brief Clear_Screen. Очистка экрана
  */
typedef struct {
	void *NextElement;			/* Указатель на следующий элемент	*/
	uint8_t CodeElement;		/* Код элемента						*/
	uint8_t Visible;			/* Уровень видимости				*/
	uint8_t ClearCode;			/* Код очистки экрана				*/
} Clear_Screen_TypeDef;

/**
  * @brief Clear_Area. Очистка области экрана
  */
typedef struct {
	void *NextElement;			/* Указатель на следующий элемент	*/
	uint8_t CodeElement;		/* Код элемента						*/
	uint8_t Visible;			/* Уровень видимости				*/
	uint8_t XB;					/* Координата X начала области		*/
	uint8_t YB;					/* Координата Y начала области		*/
	uint8_t XE;					/* Координата X конца области		*/
	uint8_t YE;					/* Координата Y конца области		*/
	uint8_t Mode;				/* Режим отображения (0-2)			*/
} Clear_Area_TypeDef;

/**
  * @brief Text. Статический текст
  */
typedef struct {
	void *NextElement;			/* Указатель на следующий элемент	*/
	uint8_t CodeElement;		/* Код элемента						*/
	uint8_t Visible;			/* Уровень видимости				*/
	uint8_t Position;			/* Номер позиции в строке (0-15)	*/
	uint8_t String;				/* Номер строки (0-7)				*/
	uint8_t Mode;				/* Режим отображения (0-2)			*/
	uint8_t *Text;				/* Указатель на текст				*/
} Text_TypeDef;

/**
  * @brief Bit_Map. Графическое прямоугольное изображение
  */
typedef struct {
	void *NextElement;			/* Указатель на следующий элемент	*/
	uint8_t CodeElement;		/* Код элемента						*/
	uint8_t Visible;			/* Уровень видимости				*/
	uint8_t XGB;				/* Координата X начала изображения	*/
	uint8_t YGB;				/* Координата Y начала изображения	*/
	uint8_t XSZ;				/* Размер изображения по оси X		*/
	uint8_t YSZ;				/* Размер изображения по оси Y		*/
	uint8_t Mode;				/* Режим отображения (0-2)			*/
	uint8_t *BitMap;			/* Указатель на битовый образ		*/
} Bit_Map_TypeDef;

/**
  * @brief Set_M_Item. Установка элемента меню
  */
typedef struct {
	void *NextElement;			/* Указатель на следующий элемент	*/
	uint8_t CodeElement;		/* Код элемента						*/
	uint8_t Visible;			/* Уровень видимости				*/
	uint8_t Id;					/* Идентификатор элемента меню		*/
	uint8_t Select;				/* Флаг текущего элемента меню		*/
	uint8_t Position;			/* Номер позиции в строке (0-15)	*/
	uint8_t String;				/* Номер строки (0-7)				*/
	uint8_t Mode;				/* Режим отображения (0-2)			*/
	uint8_t *Text;				/* Указатель на текст элемента меню	*/
	uint8_t *Screen;			/* Указатель на экран				*/
	uint8_t *Action;			/* Указатель на процедуру выбора	*/
} Set_Menu_Item_TypeDef;

/**
  * @brief Set_Single. Задание поля для вывода числа типа Single
  */
typedef struct {
	void *NextElement;			/* Указатель на следующий элемент	*/
	uint8_t CodeElement;		/* Код элемента						*/
	uint8_t Visible;			/* Уровень видимости				*/
	uint8_t Id;					/* Идентификатор 					*/
	uint8_t Position;			/* Номер позиции в строке (0-15)	*/
	uint8_t String;				/* Номер строки (0-7)				*/
	uint8_t Fsize;				/* Размер поля вывода				*/
	uint8_t Point;				/* Позици точки						*/
	uint8_t Mode;				/* Режим отображения (0-2)			*/
} Set_Single_TypeDef;

/**
  * @brief  Single_Id. Вывод объекта типа Single в поле, определенное в Set_Single
  */
typedef struct {
	void *NextElement;			/* Указатель на следующий элемент	*/
	uint8_t CodeElement;		/* Код элемента						*/
	uint8_t Visible;			/* Уровень видимости				*/
	uint8_t Id;					/* Идентификатор 					*/
	float *Single;				/* Указатель на Single				*/
} Single_Id_TypeDef;

/**
  * @brief Set_Fixed. Задание поля для вывода числа типа Fixed
  */
typedef struct {
	void *NextElement;			/* Указатель на следующий элемент	*/
	uint8_t CodeElement;		/* Код элемента						*/
	uint8_t Visible;			/* Уровень видимости				*/
	uint8_t Id;					/* Идентификатор 					*/
	uint8_t Position;			/* Номер позиции в строке (0-15)	*/
	uint8_t String;				/* Номер строки (0-7)				*/
	uint8_t Fsize;				/* Размер поля вывода				*/
	uint8_t Point;				/* Позици точки						*/
	uint8_t Mode;				/* Режим отображения (0-2)			*/
} Set_Fixed_TypeDef;

/**
  * @brief  Fixed_Id. Вывод объекта типа Fixed в поле, определенное в Set_Fixed
  */
typedef struct {
	void *NextElement;			/* Указатель на следующий элемент	*/
	uint8_t CodeElement;		/* Код элемента						*/
	uint8_t Visible;			/* Уровень видимости				*/
	uint8_t Id;					/* Идентификатор 					*/
	float *Single;				/* Указатель на Single				*/
} Fixed_Id_TypeDef;

/**
  * @brief Set_Single_In. Вывод объекта типа Single для редактирования
  */
typedef struct {
	void *NextElement;			/* Указатель на следующий элемент	*/
	uint8_t CodeElement;		/* Код элемента						*/
	uint8_t Visible;			/* Уровень видимости				*/
	uint8_t Id;					/* Идентификатор 					*/
	uint8_t Position;			/* Номер позиции в строке (0-15)	*/
	uint8_t String;				/* Номер строки (0-7)				*/
	uint8_t Fsize;				/* Размер поля вывода				*/
	uint8_t Point;				/* Позици точки						*/
	uint8_t Mode;				/* Режим отображения (0-2)			*/
	float *Single;				/* Начальное значение Single		*/
	float *MinSingle;			/* Минимальное значение Single		*/
	float *MaxSingle;			/* Максимальное значение Single		*/
	void  *OnChange;			/* Указатель на процедуру редакт.	*/
} Set_Single_In_TypeDef;

/**
  * @brief Set_Integer_In. Вывод объекта типа Integer для редактирования
  */
typedef struct {
	void *NextElement;			/* Указатель на следующий элемент	*/
	uint8_t CodeElement;		/* Код элемента						*/
	uint8_t Visible;			/* Уровень видимости				*/
	uint8_t Id;					/* Идентификатор 					*/
	uint8_t Position;			/* Номер позиции в строке (0-15)	*/
	uint8_t String;				/* Номер строки (0-7)				*/
	uint8_t Fsize;				/* Размер поля вывода				*/
	uint8_t Mode;				/* Режим отображения (0-2)			*/
	int  *Integer;				/* Начальное значение Integer		*/
	int  *MinInteger;			/* Минимальное значение Integer		*/
	int  *MaxInteger;			/* Максимальное значение Integer	*/
	void *OnChange;				/* Указатель на процедуру редакт.	*/
} Set_Integer_In_TypeDef;

/**
  * @brief Set_List_In. Вывод объекта типа List для редактирования
  */
typedef struct {
	void *NextElement;			/* Указатель на следующий элемент	*/
	uint8_t CodeElement;		/* Код элемента						*/
	uint8_t Visible;			/* Уровень видимости				*/
	uint8_t Id;					/* Идентификатор 					*/
	uint8_t Position;			/* Номер позиции в строке (0-15)	*/
	uint8_t String;				/* Номер строки (0-7)				*/
	uint8_t Fsize;				/* Размер поля вывода				*/
	uint8_t Mode;				/* Режим отображения (0-2)			*/
	uint8_t List;				/* Начальное значение List			*/
	char *ListStrings;			/* Указатель на массив строк списка	*/
	void *OnChange;				/* Указатель на процедуру редакт.	*/
} Set_List_In_TypeDef;

/**
  * @brief Line. Рисование линии
  */
typedef struct {
	void *NextElement;			/* Указатель на следующий элемент	*/
	uint8_t CodeElement;		/* Код элемента						*/
	uint8_t Visible;			/* Уровень видимости				*/
	uint8_t XB;					/* Координата X начала линии		*/
	uint8_t YB;					/* Координата Y начала линии		*/
	uint8_t XE;					/* Координата X конца линии			*/
	uint8_t YE;					/* Координата Y конца линии			*/
	uint8_t Mode;				/* Режим отображения (0-2)			*/
} Line_TypeDef;

/**
  * @brief Circle. Рисование окружности
  */
typedef struct {
	void *NextElement;			/* Указатель на следующий элемент	*/
	uint8_t CodeElement;		/* Код элемента						*/
	uint8_t Visible;			/* Уровень видимости				*/
	uint8_t X0;					/* Координата X центра окружности	*/
	uint8_t Y0;					/* Координата Y центра окружности	*/
	uint8_t R;					/* Радиус окружности				*/
} Circle_TypeDef;

/**
  * @brief Integer. Вывод объекта типа Integer
  */
typedef struct {
	void *NextElement;			/* Указатель на следующий элемент	*/
	uint8_t CodeElement;		/* Код элемента						*/
	uint8_t Visible;			/* Уровень видимости				*/
	uint8_t Position;			/* Номер позиции в строке (0-15)	*/
	uint8_t String;				/* Номер строки (0-7)				*/
	uint8_t Fsize;				/* Размер поля вывода				*/
	uint8_t Mode;				/* Режим отображения (0-2)			*/
	int *Integer;				/* Указатель на Integer				*/
} Integer_TypeDef;

/**
  * @brief Single. Вывод объекта типа Single
  */
typedef struct {
	void *NextElement;			/* Указатель на следующий элемент	*/
	uint8_t CodeElement;		/* Код элемента						*/
	uint8_t Visible;			/* Уровень видимости				*/
	uint8_t Position;			/* Номер позиции в строке (0-15)	*/
	uint8_t String;				/* Номер строки (0-7)				*/
	uint8_t Fsize;				/* Размер поля вывода				*/
	uint8_t Point;				/* Позиция точки					*/
	uint8_t Mode;				/* Режим отображения (0-2)			*/
	float *Single;				/* Указатель на Single				*/
} Single_TypeDef;

/**
  * @brief Set_Text. Задание поля для вывода текста
  */
typedef struct {
	void *NextElement;			/* Указатель на следующий элемент	*/
	uint8_t CodeElement;		/* Код элемента						*/
	uint8_t Visible;			/* Уровень видимости				*/
	uint8_t Id;					/* Идентификатор 					*/
	uint8_t Position;			/* Номер позиции в строке (0-15)	*/
	uint8_t String;				/* Номер строки (0-7)				*/
	uint8_t Fsize;				/* Размер поля вывода				*/
	uint8_t Mode;				/* Режим отображения (0-2)			*/
} Set_Text_TypeDef;

/**
  * @brief Text_Id. Вывод объекта типа Text в поле, определенное в Set_Text
  */
typedef struct {
	void *NextElement;			/* Указатель на следующий элемент	*/
	uint8_t CodeElement;		/* Код элемента						*/
	uint8_t Visible;			/* Уровень видимости				*/
	uint8_t Id;					/* Идентификатор 					*/
	char *Text;					/* Указатель на текст				*/
} Text_Id_TypeDef;

/**
  * @brief Bit_Elem. Вывод обекта типа bit
  */
typedef struct {
	void *NextElement;			/* Указатель на следующий элемент	*/
	uint8_t CodeElement;		/* Код элемента						*/
	uint8_t Visible;			/* Уровень видимости				*/
	uint8_t Position;			/* Номер позиции в строке (0-15)	*/
	uint8_t String;				/* Номер строки (0-7)				*/
	uint8_t Mode;				/* Режим отображения (0-2)			*/
	uint8_t *Bit;				/* Указатель на бит					*/
} Bit_Elem_TypeDef;

/**
  * @brief Set_Bit. Задание поля для вывода бита
  */
typedef struct {
	void *NextElement;			/* Указатель на следующий элемент	*/
	uint8_t CodeElement;		/* Код элемента						*/
	uint8_t Visible;			/* Уровень видимости				*/
	uint8_t Id;					/* Идентификатор 					*/
	uint8_t Position;			/* Номер позиции в строке (0-15)	*/
	uint8_t String;				/* Номер строки (0-7)				*/
	uint8_t Mode;				/* Режим отображения (0-2)			*/
} Set_Bit_TypeDef;

/**
  * @brief Bit_Id. Вывод объекта типа Bit в поле, определенное в Set_Bit
  */
typedef struct {
	void *NextElement;			/* Указатель на следующий элемент	*/
	uint8_t CodeElement;		/* Код элемента						*/
	uint8_t Visible;			/* Уровень видимости				*/
	uint8_t Id;					/* Идентификатор 					*/
	uint8_t *Bit;				/* Указатель на бит					*/
} Bit_Id_TypeDef;

/**
  * @brief Set_BG. Задание поля для вывода барграфа
  */
typedef struct {
	void *NextElement;			/* Указатель на следующий элемент	*/
	uint8_t CodeElement;		/* Код элемента						*/
	uint8_t Visible;			/* Уровень видимости				*/
	uint8_t Id;					/* Идентификатор 					*/
	uint8_t XB;					/* Координата X начала барографа	*/
	uint8_t YB;					/* Координата Y начала барографа	*/
	uint8_t XE;					/* Координата X конца барографа		*/
	uint8_t YE;					/* Координата Y конца барографа		*/
	uint8_t Mode;				/* Режим отображения (0-2)			*/
} Set_BG_TypeDef;

/**
  * @brief BG_Id. Вывод объекта типа барграф в поле, определенное в Set_BG
  */
typedef struct {
	void *NextElement;			/* Указатель на следующий элемент	*/
	uint8_t CodeElement;		/* Код элемента						*/
	uint8_t Visible;			/* Уровень видимости				*/
	uint8_t Id;					/* Идентификатор 					*/
	uint8_t *Bargraf;			/* Указатель на барграф				*/
} BG_Id_TypeDef;

/**
  * @brief Wr_Hex. Вывод обекта типа HEX
  */
typedef struct {
	void *NextElement;			/* Указатель на следующий элемент	*/
	uint8_t CodeElement;		/* Код элемента						*/
	uint8_t Visible;			/* Уровень видимости				*/
	uint8_t Position;			/* Номер позиции в строке (0-15)	*/
	uint8_t String;				/* Номер строки (0-7)				*/
	uint8_t Size;				/* Размер							*/
	uint8_t Mode;				/* Режим отображения (0-2)			*/
	uint16_t *HEX;				/* Указатель на слово HEX			*/
} Wr_Hex_TypeDef;

/**
  * @brief Set_PWM. Задание ШИМ нагревателя экрана
  */
typedef struct {
	void *NextElement;			/* Указатель на следующий элемент	*/
	uint8_t CodeElement;		/* Код элемента						*/
	uint8_t Visible;			/* Уровень видимости				*/
	uint8_t *PWM;				/* Указатель на PWM					*/
} Set_PWM_TypeDef;

/**
  * @brief LED_Control. Управление светодиодами
  */
typedef struct {
	void *NextElement;			/* Указатель на следующий элемент	*/
	uint8_t CodeElement;		/* Код элемента						*/
	uint8_t Visible;			/* Уровень видимости				*/
	uint8_t LedNumber;			/* Номер светодиода					*/
} LED_Control_TypeDef;

/**
  * @brief LED_Mask. Вывод маски светодиодов
  */
typedef struct {
	void *NextElement;			/* Указатель на следующий элемент	*/
	uint8_t CodeElement;		/* Код элемента						*/
	uint8_t Visible;			/* Уровень видимости				*/
	uint16_t Mask;				/* Маска светодиодов				*/
} LED_Mask_TypeDef;

/**
  * @brief Структура описания экрана
  */
typedef struct Screen {
	struct Screen *PrevScreen;	/*! Указатель на предыдущий экран	*/
	struct Screen *NextScreen;	/*! Указатель на следующий экран	*/
	struct Screen *ESCScreen;	/*! Указатель на экран возврата ESC	*/
	uint8_t Visible;			/*! Уровень видимости				*/
	void (*StaticAction)(void);	/*! Процедура активации статического списка*/
	void (*DynamicAction)(void);/*! Процедура активации динамического списка*/
	void *pStaticList;			/*! Указатель на начало статического список для вывода*/
	void *pDynamicList;			/*! Указатель на начало динамического списока для вывода*/
} Screen_t;



/*-------------Variables--------------------------------------------------------*/


/*-------------Function prototypes-----------------------------------------------*/

void LedOn(int Number);
void LedOff(int Number);
void LedFlash(int Number);

#endif // DISPLAY_H
