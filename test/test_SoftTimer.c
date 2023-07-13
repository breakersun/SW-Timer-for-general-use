#ifdef TEST

#include "unity.h"

#include "SoftTimer.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_SoftTimer_TimerListShouldOnlyHaveHeadAfterInit(void)
{
    TEST_IGNORE_MESSAGE("test_SoftTimer_TimerListShouldOnlyHaveHeadAfterInit");
}

void test_SoftTimer_TimerHeadShouldHaveNoDataAfterInit(void)
{
    TEST_IGNORE_MESSAGE("test_SoftTimer_TimerHeadShouldHaveNoDataAfterInit");
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
