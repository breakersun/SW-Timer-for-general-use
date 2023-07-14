#ifdef TEST

#include "unity.h"
#include "stdint.h"

#include "SoftTimer.h"

uint32_t fake_time_in_ms;
unsigned int fake_time(void) { return fake_time_in_ms; }
extern TIMER_TABLE* sg_ptTimeTableHead;
uint32_t timer_get_called_times;
uint32_t timer_get_called_arg;
TIMER_TABLE *timer_self_destruct;

int timer_cb(void* args)
{
    timer_get_called_times++;
    timer_get_called_arg = *((uint32_t *)args);
}

int timer_cb_remove_self(void* args)
{
    KillSoftTimerLater(timer_self_destruct);
}

void setUp(void)
{
    fake_time_in_ms = 0;
    timer_get_called_times = 0;
    timer_get_called_arg = 0;
    TimersInit(fake_time);
}

void tearDown(void)
{
}

void test_SoftTimer_TimerListShouldOnlyHaveHeadAfterInit(void)
{
    // TEST_ASSERT_NOT_EMPTY((int *)sg_ptTimeTableHead);
    TEST_ASSERT_NOT_EQUAL(NULL, sg_ptTimeTableHead);
    TEST_ASSERT_EQUAL(NULL, sg_ptTimeTableHead->next);
    TIMER data;
    memset(&data, 0, sizeof(data));
    TEST_ASSERT_EQUAL_MEMORY(&data, &(sg_ptTimeTableHead->data), sizeof(TIMER));
}

void test_SoftTimer_NewCreateStayInListTail(void)
{
    TIMER_TABLE *timer1 = CreatTimer(1000, 1, timer_cb, 0);
    TEST_ASSERT_EQUAL(timer1, sg_ptTimeTableHead->next);
    TEST_ASSERT_NULL(timer1->next);

    TIMER_TABLE *timer2 = CreatTimer(1000, 1, timer_cb, 0);
    TEST_ASSERT_EQUAL(timer1, sg_ptTimeTableHead->next);
    TEST_ASSERT_EQUAL(timer2, timer1->next);
    TEST_ASSERT_NULL(timer2->next);
}

void test_SoftTimer_KillFailIfDeleteInvalidTimer(void)
{
    TEST_ASSERT_EQUAL(SW_ERROR, KillSoftTimer(NULL));
}

void test_SoftTimer_TimerListRemainIntegratedAfterKill(void)
{
    TIMER_TABLE *timer1 = CreatTimer(1000, 1, timer_cb, 0);
    TIMER_TABLE *timer2 = CreatTimer(1000, 1, timer_cb, 0);
    TIMER_TABLE *timer3 = CreatTimer(1000, 1, timer_cb, 0);
    KillSoftTimer(timer1);
    TEST_ASSERT_EQUAL(timer2, sg_ptTimeTableHead->next);
    TEST_ASSERT_EQUAL(timer3, timer2->next);
    TEST_ASSERT_NULL(timer3->next);
    KillSoftTimer(timer3);
    TEST_ASSERT_EQUAL(timer2, sg_ptTimeTableHead->next);
    TEST_ASSERT_NULL(timer2->next);
    KillSoftTimer(timer2);
    TEST_ASSERT_NULL(sg_ptTimeTableHead->next);
    // timer2 alreay gone, removed it again should not touch timer list
    KillSoftTimer(timer2);
    TEST_ASSERT_NULL(sg_ptTimeTableHead->next);

    timer3 = CreatTimer(1000, 1, timer_cb, 0);
    TEST_ASSERT_EQUAL(timer3, sg_ptTimeTableHead->next);
    TEST_ASSERT_NULL(timer3->next);
}

void test_SoftTimer_TimerExpireWhenItsTime(void)
{
    fake_time_in_ms = 1;
    uint32_t timer_arg = 0xbeaf;
    TIMER_TABLE *timer1 = CreatTimer(1000, 0, timer_cb, (void *)&timer_arg);
    fake_time_in_ms = 1001;
    ProcessTimer();
    TEST_ASSERT_EQUAL(1, timer_get_called_times);
    TEST_ASSERT_EQUAL_HEX(timer_arg, timer_get_called_arg);
}

void test_SoftTimer_TimerWontExpireWhenItsNotTime(void)
{
    fake_time_in_ms = 1;
    uint32_t timer_arg = 0xbeaf;
    TIMER_TABLE *timer1 = CreatTimer(1000, 0, timer_cb, (void *)&timer_arg);
    fake_time_in_ms = 1000;
    ProcessTimer();
    TEST_ASSERT_EQUAL(0, timer_get_called_times);
    TEST_ASSERT_NOT_EQUAL_HEX32(timer_arg, timer_get_called_arg);
}

void test_SoftTimer_OnetimeTimerExpiredAndRemovedOnTimeAndWontGetCalledAgain(void)
{
    fake_time_in_ms = 1;
    uint32_t timer_arg = 0xbeaf;
    TIMER_TABLE *timer1 = CreatTimer(1000, 0, timer_cb, (void *)&timer_arg);
    fake_time_in_ms = 1001;
    ProcessTimer();
    fake_time_in_ms = 2001;
    ProcessTimer();
    TEST_ASSERT_EQUAL(1, timer_get_called_times);
    TEST_ASSERT_NULL(sg_ptTimeTableHead->next);
}

void test_SoftTimer_RepeatTimerExpiredEveryRoundOnTime(void)
{
    fake_time_in_ms = 1;
    uint32_t timer_arg = 0xbeaf;
    TIMER_TABLE *timer1 = CreatTimer(1000, 1, timer_cb, (void *)&timer_arg);
    fake_time_in_ms = 1001;
    ProcessTimer();
    fake_time_in_ms = 2001;
    ProcessTimer();
    fake_time_in_ms = 3001;
    ProcessTimer();
    TEST_ASSERT_EQUAL(3, timer_get_called_times);
}

void test_SoftTimer_RemoveSelfInCallbackShouldNotEffectOthers(void)
{
    fake_time_in_ms = 1;
    uint32_t timer_arg = 0xbeaf;
    TIMER_TABLE *timer1 = CreatTimer(1000, 1, timer_cb, (void *)&timer_arg);
    timer_self_destruct = CreatTimer(2000, 1, timer_cb_remove_self, (void *)&timer_arg);
    fake_time_in_ms = 1001;
    ProcessTimer();
    fake_time_in_ms = 2001;
    ProcessTimer();
    fake_time_in_ms = 3001;
    ProcessTimer();
    TEST_ASSERT_EQUAL(3, timer_get_called_times);
}
#endif // TEST
