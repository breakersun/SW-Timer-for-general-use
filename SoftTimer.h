/**
 * @file SoftTimer.h
 * @brief header file for generic timer module
 */

#ifndef __SOFTTIMER_H_
#define __SOFTTIMER_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define SW_ERROR               (-1)
#define SW_OK                   (0)

typedef int (*TMRCALLBACK)(void *pArg);
typedef uint32_t (*TMRSOURCE)(void);

/**
 * @typedef _TIMER
 * @brief structure for soft timer
 * @param
 *     uint32_t       start;           0~0xFFFFFFFF starting timestamp
 *     uint32_t       now;             0~0xFFFFFFFF current time
 *     uint32_t       elapse;          0~0xFFFFFFFF time elapsed
 *     uint32_t       timeout;         0~0xFFFFFFFF target time
 *     TMRCALLBACK  pfTimerCallback;              callback when timer goes off
 *     void        *pArg;                         args for callback
 *     uint8_t        periodic;        SINGLE       one-time trigger
 *                                   PERIODIC        periodic trigger
 */
typedef struct _TIMER
{
    uint32_t    start;           /* starting timestamp */
    uint32_t    now;             /* current time */
    uint32_t    elapse;          /* time elapsed */
    uint32_t    timeout;         /* target time */
    TMRCALLBACK pfTimerCallback; /* callback when timer goes off */
    void        *pArg;            /* args for callback */
    uint8_t     periodic;        /* one-time or periodic trigger */
} TIMER;

/**
 * @typedef _TIMER_TABLE
 * @brief link-list for software timers
 *
 */
typedef struct _TIMER_TABLE
{
    struct _TIMER_TABLE* next; /* next timer node */
    TIMER                data; /* data of current timer node */
}TIMER_TABLE;

/**
 * @brief timer init
 *
 * @param pfTimer 1ms system timer
 * @return SW_ERROR or SW_OK
 */
int TimersInit(TMRSOURCE pfTimer);

/**
 * @brief create timer
 *
 * @param dwTimeout uint32_t: 0~0xFFFFFFFF timeout
 * @param ucPeriodic SINGLE or PERIODIC
 * @param pfTimerCallback callback function
 * @param pArg args for callback
 * @return pointer for timer or NULL
 */
TIMER_TABLE* CreatTimer(uint32_t dwTimeout, uint8_t ucPeriodic, TMRCALLBACK pfTimerCallback, void *pArg);

/**
 * @brief kill a timer
 *
 * @param ptNode timer node to be killed
 * @return SW_ERROR or SW_OK
 * @note DO NOT KILL A TIMER INSIDE A TIMER CALLBACK
 */
int KillSoftTimer(TIMER_TABLE* ptNode);

/**
 * @brief tag a timer to be killed
 *
 * @param ptNode timer to be killed
 * @return SW_ERROR or SW_OK
 * @note you can use this to kill a timer inside a timer callback safely
 */
int KillSoftTimerLater(TIMER_TABLE* ptNode);

/**
 * @brief reset a timer
 *
 * @param ptNode timer to be reset
 * @return SW_ERROR or SW_OK
 */
int ResetTimer(TIMER_TABLE* ptNode);

/**
 * @brief process timer in main loop
 *
 * @return
 */
int ProcessTimer(void);

#ifdef __cplusplus
}
#endif

#endif

/* end of file */
