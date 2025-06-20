#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fnd.h"

int main(int argc, char *argv[])
{
    if (argc < 2) {
        // 인자가 없으면 기본 동작: 현재 시각 출력
        printf("No option provided. Default: show current time.\n");
        fndDispTime();
        return 0;
    }

    if (strcmp(argv[1], "s") == 0) {
        if (argc < 3) {
            fprintf(stderr, "Usage: %s s [number]\n", argv[0]);
            return 1;
        }
        int num = atoi(argv[2]);
        fndDisp(num, 0);
    }
    else if (strcmp(argv[1], "t") == 0) {
        fndDispTime();
    }
    else if (strcmp(argv[1], "c") == 0) {
        if (argc < 3) {
            fprintf(stderr, "Usage: %s c [maxNum]\n", argv[0]);
            return 1;
        }
        int max = atoi(argv[2]);
        fndDispCountUp(max);
    }
    else if (strcmp(argv[1], "o") == 0 || strcmp(argv[1], "0") == 0) {
        fndDisp(0, 0); // 모든 자리 0으로 출력
    }
    else {
        fprintf(stderr, "Unknown option: %s\n", argv[1]);
        printf("Usage:\n");
        printf("  %s s [number]   : static display (0~999999)\n", argv[0]);
        printf("  %s t            : show current time\n", argv[0]);
        printf("  %s c [maxNum]   : count from 0 to maxNum\n", argv[0]);
        printf("  %s o            : turn off display\n", argv[0]);
    }

    return 0;
}
