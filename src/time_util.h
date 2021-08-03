#ifndef _TIME_UTIL_H_
#define _TIME_UTIL_H_

#include <time.h>
#include <stdint.h>
#include "time_unit.h"

/**
 * Returns the current value of the nanoseconds.
 */
static inline uint64_t nano_time(void)
{
    struct timespec time;
    if (clock_gettime(CLOCK_MONOTONIC, &time) < 0)
        return -1;

    return TIME_UNIT_SECOND.to_nano(time.tv_sec) + time.tv_nsec;
}

static inline uint64_t timespec_to_nano(const struct timespec *const time)
{
    if (!time)
        return 0;

    return TIME_UNIT_SECOND.to_nano(time->tv_sec) + time->tv_nsec;
}

static inline void nano_to_timespec(struct timespec *time, uint64_t nano)
{
    if (!time)
        return;

    time->tv_sec = TIME_UNIT_NANO.to_second(nano);
    time->tv_nsec = !nano ? 0 : (nano % 1000000000);
}

static inline int32_t calc_timeout(struct timespec *const time, const uint64_t timeout, const struct time_unit_t *const unit)
{
    if (!time)
        return -1;

    if (!timeout) {
        time->tv_nsec = 0;
        time->tv_sec = 0;
        return 0;
    }

    struct time_unit_t *u = (struct time_unit_t *)unit;
    if (!u) {
        u = (struct time_unit_t *)&TIME_UNIT_MILLI;
    }

    struct timespec jiffies;
    if (clock_gettime(CLOCK_MONOTONIC, &jiffies) < 0)
        return -1;

    uint64_t curr_time = TIME_UNIT_SECOND.to_nano(jiffies.tv_sec) + jiffies.tv_nsec;
    uint64_t offset_time = curr_time + (unit->to_nano(timeout));
    time->tv_sec = TIME_UNIT_NANO.to_second(offset_time);
    time->tv_nsec = offset_time % 1000000000;

    return 0;
}

#endif

