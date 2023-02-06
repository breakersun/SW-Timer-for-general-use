
#include <windows.h>
#include <stdio.h>
#include <stdint.h>
#include "SoftTimer.h"

unsigned int clock_time(void) { return (int)GetTickCount(); }

int timer_cb(void* args)
{
    printf("timer called\n");
}

void main(void)
{
    int ret;

    printf("main started\n");
    ret = TimersInit(clock_time);
    if (ret != SW_OK)
        printf("failed to init timer\n");
    if (!CreatTimer(1000, 1, timer_cb, 0))
        printf("failed to create timer\n");
    Sleep(1000);
    printf("main setup done\n");
    while (1) {
        ProcessTimer();
    }
}
