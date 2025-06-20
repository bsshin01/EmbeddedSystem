#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  
#include "colorled.h"

int main(int argc, char *argv[])
{
    if (argc < 4) {
        printf("Usage: %s red green blue (range: 0~100)\n", argv[0]);
        printf("Example: %s 100 0 0  → RED FULL ON\n", argv[0]);
        return 1;
    }

    int red   = atoi(argv[1]);
    int green = atoi(argv[2]);
    int blue  = atoi(argv[3]);

    if (red < 0 || red > 100 || green < 0 || green > 100 || blue < 0 || blue > 100) {
        fprintf(stderr, "Error: Color values must be in range 0 ~ 100.\n");
        return 1;
    }

    // 컬러 LED 초기화 및 색상 설정
    ColorLEDInit();
    ColorLEDSetColor(red, green, blue);

    // 사용자에게 결과 안내
    printf("Color LED set to: R=%d, G=%d, B=%d\n", red, green, blue);
    printf("Hold for 3 seconds...\n");
    sleep(3);

    // 종료 시 LED 끄기
    ColorLEDClose();
    return 0;
}
