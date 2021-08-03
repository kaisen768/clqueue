#ifndef _TIME_UNIT_H_
#define _TIME_UNIT_H_

#include <inttypes.h>

struct time_unit_t
{
    uint64_t (*to_second)(const uint64_t);
    uint64_t (*to_milli)(const uint64_t);
    uint64_t (*to_nano)(const uint64_t);
};

extern const struct time_unit_t TIME_UNIT_SECOND;
extern const struct time_unit_t TIME_UNIT_MILLI;
extern const struct time_unit_t TIME_UNIT_NANO;

#endif

