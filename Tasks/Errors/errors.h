/*
 * errors.h
 *
 *  Created on: 5 окт. 2019 г.
 *      Author: sergey
 */

#ifndef TASKS_ERRORS_ERRORS_H_
#define TASKS_ERRORS_ERRORS_H_

/*-------------Includes---------------------------------------------------------*/


/*-------------Defines----------------------------------------------------------*/
/* Зона действия ошибки */
typedef enum {
  ALL         = 0x0UL,                /*! Реакция всегда */
  RUN_ONLY    = 0x1UL,                /*! Реакция только после запуска двигателя */
  NOT_STOPING = 0x2UL,				  /*! Реакция вне режима останова двигателя */
  ON_PROTECT  = 0x3UL,                /*! Реакция только при включенной защите */
} ErrorArea_t;

/* Класс ошибки */
typedef enum {
  WARNING     = 0x0UL,                /*! Предупреждение (не имеет действия) */
  ERRORS      = 0x1UL,                /*! Ошибка (имеет действие, нет блокировки запуска двигателя) */
  FATAL		  = 0x2UL,				  /*! Фатальная ошибка (имеет действие, есть блокировка запуска двигателя */
} ErrorClass_t;

typedef struct Error_Descriptor_TyprDef {
	uint32_t ErrorCode;				/*! Порядковый номер ошибки в системе (0...N) */
	ErrorClass_t ErrorClass;		/*! Класс ошибки (WARNING, ERROR, FATAL) */
	ErrorArea_t ErrorArea;			/*! Зона действия ошибки */
	char *ErrorMessage;				/*! Текст сообщения об ошибке */
	char  TestConditional;			/*! Условие проверки (<, >, =) */
	void *TestObject;				/*! Указатель на проверяемый объект */
	void *TestValue;				/*! Указатель на контрольное значение для проверки */
	void (*ErrorAction)(void);		/*! Указатель на обработчик ошибки */
} Error_Descriptor_t;

/*-------------Variables--------------------------------------------------------*/
extern void * pxTaskErrors;			  /*! Указатель на подсистему обработки ошибок */
extern uint32_t ErrorCounter;	  	  /*! Счетчик активных ошибок класса ERROR */
extern uint32_t NotAckErrorCounter;	  /*! Счетчик неподтвержденных ошибок класса ERROR */
extern uint32_t FatalCounter;		  /*! Счетчик активных ошибок класса FATAL */
extern uint32_t NotAckFatalCounter;	  /*! Счетчик неподтвержденных ошибок класса FATAL */
extern uint32_t WarningCounter;	  	  /*! Счетчик активных ошибок класса WARNING */
extern uint32_t NotAckWarningCounter; /*! Счетчик неподтвержденных ошибок класса WARNING */

/*-------------Function prototypes-----------------------------------------------*/
void vTaskErrorsInit (void);		  /*! Инициализация Task Errors 	*/
void vTaskErrors(void *pvParameters); /*! Задача Errors		*/
void ErrorActionNone(void);			  /*! Реакция на ошибку NONE */
void ErrorActionGBOpen(void);		  /*! Реакция на ошибку GB_OPEN */
void ErrorActionMBOpen(void);		  /*! Реакция на ошибку MB_OPEN */
void ErrorActionStop(void);		 	  /*! Реакция на ошибку STOP */
void ErrorActionShutdown(void);		  /*! Реакция на ошибку SHUTDOWN */
void ErrorActionAutoReset(void);	  /*! Реакция на ошибку AUTORESET */
void SetError(uint32_t Id);			  /*! Активировать ошибку по идентификатору */
void ReSetError(uint32_t Id);		  /*! Деактивировать ошибку по идентификатору */
void DisplayError(uint32_t Id);		  /*! Активировать и деативировать ошибку по идентификатору */
void TestError(uint32_t Id);		  /*! Проверить ошибку по идентификатору */
uint32_t StatusError(uint32_t Id);	  /*! Запрос статуса ошибки по идентификатору */




#endif /* TASKS_ERRORS_ERRORS_H_ */
