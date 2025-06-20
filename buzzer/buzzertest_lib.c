#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/msg.h>
#include "button.h"
#include "buzzer.h"
#include <linux/input.h>

int mapKeyToScale(int keycode)
{
    switch (keycode)
    {
        case KEY_VOLUMEUP:   return 1; // 도
        case KEY_HOME:       return 2; // 레
        case KEY_SEARCH:     return 3; // 미
        case KEY_BACK:       return 4; // 파
        case KEY_MENU:       return 5; // 솔
        case KEY_VOLUMEDOWN: return 6; // 라
        default:             return 0;
    }
}

int main()
{
    if (!buttonInit())
    {
        printf("Button init failed!\n");
        return -1;
    }

    if (!buzzerInit())
    {
        printf("Buzzer init failed!\n");
        return -1;
    }

    printf("Press button to play sound!\n");

    BUTTON_MSG_T msg;
    while (1)
    {
        if (msgrcv(msgget(MESSAGE_ID, 0666), &msg, sizeof(msg) - sizeof(long), 0, 0) < 0)
        {
            perror("msgrcv failed");
            break;
        }

        if (msg.pressed == 1)  
        {
            int scale = mapKeyToScale(msg.keyInput);
            if (scale > 0)
            {
                printf("Pressed key %d → scale %d\n", msg.keyInput, scale);
                buzzerPlaySong(scale);
                usleep(300000); 
                buzzerStopSong();
            }
        }
    }

    buttonExit();
    buzzerExit();
    return 0;
}
