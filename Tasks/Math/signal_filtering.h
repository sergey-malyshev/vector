/***
* signal_filtering.h - классический цифровой фильтр сигналов (низкочастотный RC фильтр)
* Версия: 1.0
* Создан: 11.12.18
*
*/

#ifndef _SIGNAL_FILTERING_H_
#define _SIGNAL_FILTERING_H_

/* Размер окна накопления фильтра */
#define FILTER_SIZE 5

/* Частота дискретизации АЦП, Гц */
#define SPS 1000

typedef struct {
	float values[FILTER_SIZE];
	float sorted[FILTER_SIZE];
	int pointer;
	float K, Vacc, Vout;
} SignalFiltering;

void  sfInit(SignalFiltering *fs, float T, float initialValue);
void  sfAddValue(SignalFiltering *fs, float value);
float sfGetValue(SignalFiltering *fs);

#endif /* _SIGNAL_FILTERING_H_ */
