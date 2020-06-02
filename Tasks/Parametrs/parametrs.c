/********************************************************************************
  * @file    parametrs.c
  * @version 1.0
  * @date:   26.03.2019
  * @brief   Подсистема параметров
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "parametrs.h"

/*! Параметры по умолчанию (размещаются в пользовательской FLASH) */
ParamInt_t param1Val = {1,2,3};

ParamDescriptor_t param1 BFLASH =
{0,INTEGERS,GS_CONTROL,OPERATOR,"Время","с",&(param1Val.data),&(param1Val.minValue),&(param1Val.maxValue),3,2,NULL};



/*
ParamFloat_t param2 MEMORY =
{1,FLOAT,SYNCHRO,ADJUSTER,"кВт",1.5,1.0,15.0,"P ном",5,NULL};

ParamList_t param3 MEMORY =
{2,LIST,AMF,ENGINEER,"Гц",1,2,3,"second",3,NULL};

ParamTable_t param4 MEMORY =
{3,TABLE,GS_CONTROL,DEVELOPER,"Темпер",1,2,3,"second",3,NULL};

*/



/*! Пересчетные функции для параметров */

