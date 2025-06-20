#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include "fnd.h"

#define FND_DRIVER_NAME "/dev/perifnd"

// 단일 정수 숫자 출력
int fndDisp(int num, int dotflag) {
    int fd;
    int temp, i;
    stFndWriteForm stWriteData;

    for (i = 0; i < MAX_FND_NUM ; i++) {
        stWriteData.DataDot[i] = (dotflag & (0x1 << i)) ? 1 : 0;
        stWriteData.DataValid[i] = 1;
    }

    temp = num % 1000000; stWriteData.DataNumeric[0] = temp / 100000;
    temp = num % 100000;  stWriteData.DataNumeric[1] = temp / 10000;
    temp = num % 10000;   stWriteData.DataNumeric[2] = temp / 1000;
    temp = num % 1000;    stWriteData.DataNumeric[3] = temp / 100;
    temp = num % 100;     stWriteData.DataNumeric[4] = temp / 10;
                          stWriteData.DataNumeric[5] = num % 10;

    fd = open(FND_DRIVER_NAME, O_RDWR);
    if (fd < 0) {
        perror("FND driver open error");
        return 0;
    }

    write(fd, &stWriteData, sizeof(stFndWriteForm));
    close(fd);
    return 1;
}

// 현재 시각 출력 (ex. 15:34:12 → 153412)
int fndDispTime(void) {
    struct tm *ptmcur;
    time_t tTime;
    int number;

    if (-1 == time(&tTime)) {
        perror("time get failed");
        return 0;
    }

    ptmcur = localtime(&tTime);
    number = ptmcur->tm_hour * 10000 + ptmcur->tm_min * 100 + ptmcur->tm_sec;

    // 시:분:초 형식에서 점을 찍고 싶다면 dotflag 예: 0b1010
    return fndDisp(number, 0b1010); 
}

// 0부터 특정 수까지 카운트 출력
int fndDispCountUp(int maxNum) {
    int counter = 0;

    while (counter <= maxNum) {
        if (!fndDisp(counter, 0)) break;
        sleep(1);
        counter++;
    }
    return 1;
}
