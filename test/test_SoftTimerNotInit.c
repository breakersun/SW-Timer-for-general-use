
#ifdef TEST

#include "unity.h"

#include "SoftTimer.h"

uint32_t fake_time_in_ms = 0;
unsigned int fake_time(void) { return fake_time_in_ms; }
extern TIMER_TABLE* sg_ptTimeTableHead;

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
    TEST_IGNORE_MESSAGE("test_SoftTimer_CreateFailIfNotInit");
}

#endif // TEST
