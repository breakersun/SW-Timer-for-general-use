#include <string.h>
#ifdef TEST

#include "unity.h"

#include "SoftTimer.h"

uint32_t fake_time_in_ms = 0;
unsigned int fake_time(void) { return fake_time_in_ms; }
extern TIMER_TABLE* sg_ptTimeTableHead;

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

void test_SoftTimer_TimerHeadShouldBeNullIfNoTimerSource(void)
{
    TEST_IGNORE_MESSAGE("test_SoftTimer_TimerHeadShouldBeNullIfNoTimerSource");
}

void test_SoftTimer_CreateFailIfNotInit(void)
{
    TEST_IGNORE_MESSAGE("test_SoftTimer_CreateFailIfNotInit");
}

void test_SoftTimer_NewCreateStayInListTail(void)
{
    TEST_IGNORE_MESSAGE("test_SoftTimer_NewCreateStayInListTail");
}

void test_SoftTimer_KillFailIfNotInit(void)
{
    TEST_IGNORE_MESSAGE("test_SoftTimer_KillFailIfNotInit");
}

void test_SoftTimer_KillFailIfDeleteInvalidTimer(void)
{
    TEST_IGNORE_MESSAGE("test_SoftTimer_KillFailIfDeleteInvalidTimer");
}

void test_SoftTimer_TimerListRemainIntegratedAfterKill(void)
{
    TEST_IGNORE_MESSAGE("test_SoftTimer_TimerListRemainIntegratedAfterKill");
}

#endif // TEST
