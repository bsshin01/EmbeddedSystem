#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <linux/input.h>  
#include "button.h"
#include "led.h"

int main(void)
{
    BUTTON_MSG_T msg;
    int msgID;

    // 버튼 초기화
    if (buttonInit() == 0) {
        printf("Button init failed!\n");
        return -1;
    }

    // LED 초기화
    if (ledLibInit() < 0) {
        printf("LED driver init failed!\n");
        return -1;
    }

    msgID = msgget(MESSAGE_ID, IPC_CREAT | 0666);
    if (msgID == -1) {
        perror("msgget");
        return -1;
    }

    printf("Button-LED test start...\n");

    while (1)
    {
        if (msgrcv(msgID, &msg, sizeof(BUTTON_MSG_T) - sizeof(long), 0, 0) == -1)
            continue;

        if (msg.pressed == 1)  // 버튼 눌렸을 때
        {
            switch (msg.keyInput)
            {
                case KEY_VOLUMEUP:
                    printf("KEY_VOLUMEUP: LED 0 ON\n");
                    ledOnOff(0, 1);
                    break;
                case KEY_VOLUMEDOWN:
                    printf("KEY_VOLUMEDOWN: LED 0 OFF\n");
                    ledOnOff(0, 0);
                    break;
                case KEY_HOME:
                    printf("KEY_HOME: LED 1 ON\n");
                    ledOnOff(1, 1);
                    break;
                case KEY_BACK:
                    printf("KEY_BACK: LED 1 OFF\n");
                    ledOnOff(1, 0);
                    break;
                default:
                    printf("Unknown key %d pressed\n", msg.keyInput);
                    break;
            }
        }
    }

    buttonExit();
    ledLibExit();
    return 0;
}
