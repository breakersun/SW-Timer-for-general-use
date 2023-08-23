/**
 * @file
 * @brief software timer module
 * @note please provide a 1ms system tick timer source callback
 * @note please call ProcessTimer function in your main loop
 */

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "SoftTimer.h"

#ifdef TEST
TIMER_TABLE* sg_ptTimeTableHead = NULL;
#else
static TIMER_TABLE* sg_ptTimeTableHead = NULL;
#endif

static TMRSOURCE    sg_pfSysClk        = NULL; // system 1ms timer callback

/**
 * @brief Init software timer module
 *
 * @param pfTimer 1ms system timer; should be provided by user
 * @return SW_ERROR or SW_OK
 */
int TimersInit(TMRSOURCE pfTimer)
{
    if (NULL == pfTimer)
    {
        return SW_ERROR;
    }

    // create head for timer list;
    // head doesn't contain valid timer function, it's just a handle
    sg_ptTimeTableHead = (TIMER_TABLE*)malloc(sizeof(TIMER_TABLE));
    if (NULL == sg_ptTimeTableHead)
    {
        return SW_ERROR;
    }

    sg_ptTimeTableHead->next = NULL;
    sg_pfSysClk              = (TMRSOURCE)pfTimer;
    memset(&(sg_ptTimeTableHead->data), 0, sizeof(TIMER));

    return SW_OK;
}

TIMER_TABLE* CreatTimer(uint32_t dwTimeout, uint8_t ucPeriodic, TMRCALLBACK pfTimerCallback, void *pArg)
{
    TIMER_TABLE* ptTimerNode;
    TIMER_TABLE* ptFind;
    if (NULL == sg_ptTimeTableHead)
    {
        // if head is not created, simply fail exit
        return NULL;
    }

    // create a timer node
    ptTimerNode = (TIMER_TABLE*)malloc(sizeof(TIMER_TABLE));
    if (NULL == ptTimerNode)
    {
        return NULL;
    }

    // initial this new timer node
    ptTimerNode->next                 = NULL;
    ptTimerNode->data.periodic        = ucPeriodic;
    ptTimerNode->data.start           = sg_pfSysClk();
    ptTimerNode->data.now             = ptTimerNode->data.start;
    ptTimerNode->data.elapse          = 0;
    ptTimerNode->data.timeout         = dwTimeout;
    ptTimerNode->data.pfTimerCallback = pfTimerCallback;
    ptTimerNode->data.pArg            = pArg;

    // insert it into timer list
    ptFind = sg_ptTimeTableHead;
    // find tail of the list
    while(NULL != ptFind->next)
    {
        ptFind = ptFind->next;
    }
    // found the tail, we attach new timer node to the tail
    ptFind->next= ptTimerNode;

    return ptTimerNode;
}

int KillSoftTimer(TIMER_TABLE* ptNode)
{
    TIMER_TABLE* ptFind;

    if (NULL == ptNode)
    {
        return SW_ERROR;
    }

    ptFind = sg_ptTimeTableHead;
    while (ptFind)
    {
        // found previous node of the current one(to be deleted)
        if (ptFind->next == ptNode)
        {
            // manipulate previous node to unlink current node
            ptFind->next = ptNode->next;
            free(ptNode);
            return SW_OK;
        }
        ptFind = ptFind->next;
    }
    return SW_ERROR;
}

int KillSoftTimerLater(TIMER_TABLE* ptNode)
{
    if (NULL == ptNode) {
        return SW_ERROR;
    }

    // make it onetime, and leave it to TimerCore to clean it up
    ptNode->data.periodic = 0;
}

int ResetTimer(TIMER_TABLE* ptNode)
{
    if (NULL == ptNode)
    {
        return SW_ERROR;
    }

    ptNode->data.start = sg_pfSysClk();
    return SW_OK;
}

int ProcessTimer(void)
{
    TIMER_TABLE* ptFind;
    TIMER_TABLE* ptNodeFree;
    if (NULL == sg_ptTimeTableHead)
    {
        return SW_OK;
    }

    // find first valid timer node
    ptFind = sg_ptTimeTableHead->next;
    while(ptFind)
    {
        ptFind->data.now = sg_pfSysClk();

        ptFind->data.elapse = ptFind->data.now - ptFind->data.start;

        if(ptFind->data.elapse >= ptFind->data.timeout)
        {
            if(ptFind->data.pfTimerCallback)
            {
                ptFind->data.pfTimerCallback(ptFind->data.pArg);
            }
            if(ptFind->data.periodic)
            {
                ResetTimer(ptFind);
            }
            else
            {
                ptNodeFree = ptFind;
                ptFind = ptFind->next;
                KillSoftTimer(ptNodeFree);
                continue;
            }
        }
        ptFind = ptFind->next;
    }
    return SW_OK;
}

/* end of file */
