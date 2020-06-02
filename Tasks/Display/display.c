/*==============================================================================
 * Диалог с модулем дисплейным контроллера "Вектор"
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

/*-------------Includes---------------------------------------------------------*/
#include "display.h"
#include "parametrs.h"

/*-------------Defines----------------------------------------------------------*/


/*-------------Variables--------------------------------------------------------*/


/*-------------Function---------------------------------------------------------*/
Screen_t Menu1;
Screen_t Measure0;
Screen_t Measure1;
Screen_t Measure2;
Screen_t Measure3;
Screen_t Measure4;
Screen_t Measure5;
Screen_t Measure6;
Screen_t Measure7;
Screen_t Measure8;
Screen_t Measure9;
Screen_t Measure10;
Screen_t Measure11;
Text_TypeDef scrMeasure0;
Set_Single_TypeDef Fg;
Set_Single_TypeDef UgAB;

Screen_t Menu1 = {&Measure11, &Measure1,&Menu1,OPERATOR,0,0,0,0};

Screen_t Measure0  = {&Measure11, &Measure1,&Menu1,OPERATOR,0,0,0,0};
Text_TypeDef scrMeasure0 = {&Fg,TEXT,OPERATOR,POS0,STR0,MODE1};
Set_Single_TypeDef Fg = {&UgAB,SET_SINGLE,OPERATOR,0,POS8,STR0,FSIZE4,POINT1,MODE1};
Set_Single_TypeDef UgAB = {0,SET_SINGLE,OPERATOR,1,POS8,STR1,FSIZE4,POINT1,MODE1};






Screen_t Measure1  = {&Measure0, &Measure2,&Menu1,OPERATOR,0,0,0,0};
Screen_t Measure2  = {&Measure1, &Measure3,&Menu1,OPERATOR,0,0,0,0};
Screen_t Measure3  = {&Measure2, &Measure4,&Menu1,OPERATOR,0,0,0,0};
Screen_t Measure4  = {&Measure3, &Measure5,&Menu1,OPERATOR,0,0,0,0};
Screen_t Measure5  = {&Measure4, &Measure6,&Menu1,OPERATOR,0,0,0,0};
Screen_t Measure6  = {&Measure5, &Measure7,&Menu1,OPERATOR,0,0,0,0};
Screen_t Measure7  = {&Measure6, &Measure8,&Menu1,OPERATOR,0,0,0,0};
Screen_t Measure8  = {&Measure7, &Measure9,&Menu1,OPERATOR,0,0,0,0};
Screen_t Measure9  = {&Measure8, &Measure10,&Menu1,OPERATOR,0,0,0,0};
Screen_t Measure10 = {&Measure9, &Measure11,&Menu1,OPERATOR,0,0,0,0};
Screen_t Measure11 = {&Measure10, &Measure0,&Menu1,OPERATOR,0,0,0,0};









