/***
* signal_filtering.c - ôèëüòð àíàëîãîâûõ ñèãíàëîâ (íèçêî÷àñòîòíûé RC ôèëüòð)
* Version: 1.0  11/12/18
*/

#ifndef _SIGNAL_FILTERING_C_
#define _SIGNAL_FILTERING_C_

#include "signal_filtering.h"

void sfInit(SignalFiltering *fs, float T, float initialValue) {
	fs->pointer = 0;
	fs->K = T * SPS;
	fs->Vout = initialValue;
	fs->Vacc = initialValue * fs->K;
}

static void addCopyAndSort(SignalFiltering *fs, float value) {
	fs->values[fs->pointer] = value;
	fs->pointer = ++fs->pointer == FILTER_SIZE ? 0 : fs->pointer;

	for (int i = 0; i < FILTER_SIZE; i++)
		fs->sorted[i] = fs->values[i];

	for (int i = 0; i < FILTER_SIZE; i++)
		for (int j = i + 1; j < FILTER_SIZE; j++)
			if (fs->sorted[i] < fs->sorted[j]) {
				float temp = fs->sorted[i];
				fs->sorted[i] = fs->sorted[j];
				fs->sorted[j] = temp;
			}
}

void sfAddValue(SignalFiltering *fs, float value) {
	addCopyAndSort(fs, value);
	float Vin = fs->sorted[FILTER_SIZE / 2];

	fs->Vacc += Vin - fs->Vout;
	fs->Vout = fs->Vacc / fs->K;
}

float sfGetValue(SignalFiltering *fs) {
	return fs->Vout;
}

#endif /* _SIGNAL_FILTERING_C_ */
