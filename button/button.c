#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linux/input.h>
#include <unistd.h>       
#include <fcntl.h>       
#include <sys/ioctl.h>    
#include <sys/msg.h>
#include <pthread.h>
#include "button.h"

#define INPUT_DEVICE_LIST "/dev/input/event"
#define PROBE_FILE "/proc/bus/input/devices"
#define HAVE_TO_FIND_1 "N: Name=\"ecube-button\"\n"
#define HAVE_TO_FIND_2 "H: Handlers=kbd event"

static int fd = 0;
static char buttonPath[200];
static int msgID = 0;
static pthread_t buttonTh_id;
static int exitFlag = 0;

static int probeButtonPath(char *newPath);
static void* buttonThFunc(void* arg);

// 버튼 초기화
int buttonInit(void)
{
    if (probeButtonPath(buttonPath) == 0) {
        printf("probeButtonPath() failed\n");  
        return 0;
    }

    printf("probeButtonPath returned: %s\n", buttonPath); 

    fd = open(buttonPath, O_RDONLY);
    if (fd < 0) {
        perror("open failed");  
        return 0;
    }

    msgID = msgget(MESSAGE_ID, IPC_CREAT | 0666);
    if (msgID == -1) {
        perror("msgget failed");  
        return 0;
    }

    pthread_create(&buttonTh_id, NULL, buttonThFunc, NULL);
    return 1;
}


// 버튼 디바이스 경로 탐색
static int probeButtonPath(char *newPath)
{
    int returnValue = 0;
    int number = 0;
    FILE *fp = fopen(PROBE_FILE, "rt");

    if (fp == NULL)
        return 0;

    while (!feof(fp))
    {
        char tmpStr[200];
        fgets(tmpStr, sizeof(tmpStr), fp);

        if (strcmp(tmpStr, HAVE_TO_FIND_1) == 0)
        {
            returnValue = 1;
        }

        if (returnValue == 1 &&
            strncasecmp(tmpStr, HAVE_TO_FIND_2, strlen(HAVE_TO_FIND_2)) == 0)
        {
            number = tmpStr[strlen(tmpStr) - 3] - '0';
            break;
        }
    }

    fclose(fp);

    if (returnValue == 1)
    {
        sprintf(newPath, "%s%d", INPUT_DEVICE_LIST, number);
    }

    return returnValue;
}

// 버튼 스레드 함수
static void* buttonThFunc(void* arg)
{
    struct input_event ev;
    BUTTON_MSG_T msg;

    while (!exitFlag)
    {
        int readSize = read(fd, &ev, sizeof(ev));
        if (readSize != sizeof(ev))
            continue;

        if (ev.type == EV_KEY)
        {
            msg.messageNum = 1;
            msg.keyInput = ev.code;
            msg.pressed = ev.value;
            msgsnd(msgID, &msg, sizeof(BUTTON_MSG_T) - sizeof(long), 0);
        }
    }

    return NULL;
}

// 버튼 종료 함수
int buttonExit(void)
{
    exitFlag = 1;
    pthread_join(buttonTh_id, NULL);
    close(fd);
    msgctl(msgID, IPC_RMID, NULL);
    return 0;
}
