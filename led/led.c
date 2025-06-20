#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "led.h"

static unsigned int ledValue = 0;
static int fd = 0;

int ledLibInit(void)
{
    fd = open("/dev/periled", O_WRONLY);
    ledValue = 0;
    if (fd < 0) return -1;
    return 0;
}

int ledOnOff(int ledNum, int onOff)
{
    int i = 1 << ledNum;
    ledValue &= ~i;
    if (onOff != 0) ledValue |= i;
    return write(fd, &ledValue, 4);
}

int ledLibExit(void)
{
    ledValue = 0;
    ledOnOff(0, 0);  // 모두 끄기
    close(fd);
    return 0;
}
