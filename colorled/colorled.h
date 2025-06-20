#ifndef __COLORLED_H__
#define __COLORLED_H__

#define MAX_INPUT_VALUE 100
#define PWM_FREQUENCY 100000

#define RED_INDEX   0
#define GREEN_INDEX 1
#define BLUE_INDEX  2

void ColorLEDInit(void);
void ColorLEDSetColor(int red, int green, int blue);
void ColorLEDClose(void);

#endif // __COLORLED_H__
