#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include "buzzer.h"

#define MAX_SCALE_STEP 8
#define BUZZER_BASE_SYS_PATH "/sys/bus/platform/devices/"
#define BUZZER_FILENAME "peribuzzer"
#define BUZZER_ENABLE_NAME "enable"
#define BUZZER_FREQUENCY_NAME "frequency"

static char gBuzzerBaseSysDir[128]; // ex) "/sys/bus/platform/devices/peribuzzer.0/"
static const int musicScale[MAX_SCALE_STEP] = {262, 294, 330, 349, 392, 440, 494, 523};

int findBuzzerSysPath()
{
    DIR *dir_info = opendir(BUZZER_BASE_SYS_PATH);
    int ifNotFound = 1;
    if (dir_info != NULL) {
        while (1) {
            struct dirent *dir_entry;
            dir_entry = readdir(dir_info);
            if (dir_entry == NULL) break;
            if (strncasecmp(BUZZER_FILENAME, dir_entry->d_name, strlen(BUZZER_FILENAME)) == 0) {
                ifNotFound = 0;
                sprintf(gBuzzerBaseSysDir, "%s%s/", BUZZER_BASE_SYS_PATH, dir_entry->d_name);
            }
        }
        closedir(dir_info);
    }
    printf("find %s\n", gBuzzerBaseSysDir);  
    return ifNotFound;
}

// 버저 초기화
int buzzerInit(void)
{
    if (findBuzzerSysPath()) {
        printf("buzzerInit: Device not found!\n");
        return 0;
    }
    return 1;
}

// 주파수 설정
static void setFrequency(int frequency)
{
    char path[200];
    sprintf(path, "%s%s", gBuzzerBaseSysDir, BUZZER_FREQUENCY_NAME);
    int fd = open(path, O_WRONLY);
    if (fd < 0) {
        perror("setFrequency: open failed");
        return;
    }
    dprintf(fd, "%d", frequency);
    close(fd);
}

// 버저 ON/OFF
static void buzzerEnable(int enable)
{
    char path[200];
    sprintf(path, "%s%s", gBuzzerBaseSysDir, BUZZER_ENABLE_NAME);
    int fd = open(path, O_WRONLY);
    if (fd < 0) {
        perror("buzzerEnable: open failed");
        return;
    }
    write(fd, enable ? "1" : "0", 1);
    close(fd);
}

// 음계 재생
int buzzerPlaySong(int scale)
{
    if (scale < 1 || scale > MAX_SCALE_STEP) return 0;
    setFrequency(musicScale[scale - 1]);
    buzzerEnable(1);
    return 1;
}

// 음 끄기
int buzzerStopSong(void)
{
    buzzerEnable(0);
    return 1;
}

// 종료
int buzzerExit(void)
{
    return 1;
}
