#include <stdio.h>
#include <unistd.h>  
#include "led.h"    

int main()
{
    if (ledLibInit() < 0)
    {
        printf("LED Driver Open Failed!\n");
        return -1;
    }

    printf("Turn on LED 0\n");
    ledOnOff(0, 1);  // 0번 LED ON
    sleep(1);        // 1초 대기

    printf("Turn off LED 0\n");
    ledOnOff(0, 0);  // 0번 LED OFF
    sleep(1);

    ledLibExit();    // 자원 해제
    return 0;
}
