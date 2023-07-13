
#include <windows.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "SoftTimer.h"

unsigned int clock_time(void) { return (int)GetTickCount(); }
TIMER_TABLE *timer1;
TIMER_TABLE *timer2;
TIMER_TABLE *timer3;

bool its_time = false;

int timer_cb(void* args)
{
    printf("1s timer called\n");
    its_time = true;
    timer1->data.periodic = false;
}
int timer_2_cb(void* args)
{
    printf("2s timer called\n");
}

int timer_3_cb(void* args)
{
    printf("3s timer called\n");
}

void main(void)
{
    int ret;

    printf("main started\n");
    ret = TimersInit(clock_time);
    if (ret != SW_OK)
        printf("failed to init timer\n");

    timer1 = CreatTimer(1000, 1, timer_cb, 0);
    if (!timer1)
        printf("failed to create timer 1\n");

    timer2 = CreatTimer(500, 1, timer_2_cb, 0);
    if (!timer2)
        printf("failed to create timer 2\n");

    timer3 = CreatTimer(500, 1, timer_3_cb, 0);
    if (!timer3)
        printf("failed to create timer 3\n");

    // KillSoftTimer(timer3);

    printf("main setup done\n");
    while (1) {
        ProcessTimer();
        if (its_time)
            KillSoftTimer(timer3);
    }
}
