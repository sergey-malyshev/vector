/***
* interpolation.c - интерполятор
* Version: 1.0  11/12/18
*/

#include "interpolation.h"


/** Линейный интерполятор по 2 точкам
 *
 * x1 - аргумент первой точки
 * y1 - значение первой точки
 * x2 - аргумент второй точки
 * y2 - значение первой точки
 * X  - аргумент для интерполяции
 *
 */


float interpolate(float x1, float y1, float x2, float y2, float x) {
	if (x1 == x2) {
		return -1;
	}
	float a = INTERPOLATION_A(x1, y1, x2, y2);
	float b = y1 - a * x1;
	float result = a * x + b;
	return result;
}

