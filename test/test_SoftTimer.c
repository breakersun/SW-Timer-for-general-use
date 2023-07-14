#ifdef TEST

#include "unity.h"

#include "SoftTimer.h"

uint32_t fake_time_in_ms = 0;
unsigned int fake_time(void) { return fake_time_in_ms; }
extern TIMER_TABLE* sg_ptTimeTableHead;

int timer_cb(void* args)
{}

void setUp(void)
{
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

void test_SoftTimer_TimerWontExpireWhenItsNotTime(void)
{
    TEST_IGNORE_MESSAGE("test_SoftTimer_TimerWontExpireWhenItsNotTime");
}

void test_SoftTimer_OnetimeTimerExpiredAndRemovedOnTimeAndWontGetCalledAgain(void)
{
    TEST_IGNORE_MESSAGE("test_SoftTimer_OnetimeTimerExpiredAndRemovedOnTimeAndWontGetCalledAgain");
}

void test_SoftTimer_RepeatTimerExpiredEveryRoundOnTime(void)
{
    TEST_IGNORE_MESSAGE("test_SoftTimer_RepeatTimerExpiredEveryRoundOnTime");
}

#endif // TEST
