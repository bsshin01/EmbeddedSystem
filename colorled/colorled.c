#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "colorled.h"

#define PWM_BASE_SYS_PATH "/sys/class/pwm/pwmchip"
#define PWM_ENABLE_NAME   "enable"
#define PWM_PERIOD_NAME   "period"
#define PWM_DUTY_NAME     "duty_cycle"

static void pwmActivate(int pwmIndex, int activate)
{
    char cmd[128];
    sprintf(cmd, "echo '0' > %s%d/%sport", PWM_BASE_SYS_PATH, pwmIndex, activate ? "ex" : "unex");
    system(cmd);
}

static void pwmEnable(int pwmIndex, int enable)
{
    char cmd[128];
    sprintf(cmd, "echo '%d' > %s%d/pwm0/%s", enable, PWM_BASE_SYS_PATH, pwmIndex, PWM_ENABLE_NAME);
    system(cmd);
}

static void pwmSetPeriod(int pwmIndex, int period)
{
    char cmd[128];
    sprintf(cmd, "echo '%d' > %s%d/pwm0/%s", period, PWM_BASE_SYS_PATH, pwmIndex, PWM_PERIOD_NAME);
    system(cmd);
}

static void pwmSetDuty(int pwmIndex, int duty)
{
    char cmd[128];
    sprintf(cmd, "echo '%d' > %s%d/pwm0/%s", duty, PWM_BASE_SYS_PATH, pwmIndex, PWM_DUTY_NAME);
    system(cmd);
}

void ColorLEDInit(void)
{
    for (int i = 0; i < 3; i++)
    {
        pwmSetPeriod(i, PWM_FREQUENCY);
        pwmSetDuty(i, PWM_FREQUENCY); 
        pwmEnable(i, 1);
    }
}

void ColorLEDSetColor(int red, int green, int blue)
{
    if (red < 0) red = 0; if (red > MAX_INPUT_VALUE) red = MAX_INPUT_VALUE;
    if (green < 0) green = 0; if (green > MAX_INPUT_VALUE) green = MAX_INPUT_VALUE;
    if (blue < 0) blue = 0; if (blue > MAX_INPUT_VALUE) blue = MAX_INPUT_VALUE;

    red = MAX_INPUT_VALUE - red;
    green = MAX_INPUT_VALUE - green;
    blue = MAX_INPUT_VALUE - blue;

    pwmSetDuty(RED_INDEX,   PWM_FREQUENCY * red   / MAX_INPUT_VALUE);
    pwmSetDuty(GREEN_INDEX, PWM_FREQUENCY * green / MAX_INPUT_VALUE);
    pwmSetDuty(BLUE_INDEX,  PWM_FREQUENCY * blue  / MAX_INPUT_VALUE);
}

void ColorLEDClose(void)
{
    for (int i = 0; i < 3; i++)
    {
        pwmEnable(i, 0);
    }
}
