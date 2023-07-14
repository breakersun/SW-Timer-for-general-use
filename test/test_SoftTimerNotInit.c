
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
}

void tearDown(void)
{
}

void test_SoftTimer_TimerHeadShouldBeNullIfNoTimerSource(void)
{
    TimersInit(NULL);
    TEST_ASSERT_NULL(sg_ptTimeTableHead);
}

void test_SoftTimer_CreateFailIfNotInit(void)
{
    TIMER_TABLE *timer1 = CreatTimer(1000, 1, timer_cb, 0);
    TEST_ASSERT_NULL(timer1);
}

void test_SoftTimer_KillFailIfNotInit(void)
{
    TEST_ASSERT_EQUAL(SW_ERROR, KillSoftTimer(NULL));
}

#endif // TEST
