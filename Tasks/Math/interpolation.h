/***
* interpolation.h - Интерполятор
* Версия: 1.0
* Создан: 11.12.18
*/

#ifndef _INTERPOLATION_H_
#define _INTERPOLATION_H_

#define INTERPOLATION_A(x1, y1, x2, y2) ((y1 - y2) / (x1 - x2))

float interpolate(float x1, float y1, float x2, float y2, float x);

#endif /* _INTERPOLATION_H_ */
