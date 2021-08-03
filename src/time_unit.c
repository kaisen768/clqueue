#include "time_unit.h"

uint64_t second_to_second(const uint64_t time)
{
    return time;
}

uint64_t second_to_milli(const uint64_t time)
{
    return time * 1000;
}

uint64_t second_to_nano(const uint64_t time)
{
    return time * 1000 * 1000 * 1000;
}

const struct time_unit_t TIME_UNIT_SECOND = {
    .to_second = second_to_second,
    .to_milli = second_to_milli,
    .to_nano = second_to_nano,
};

uint64_t milli_to_second(const uint64_t time)
{
    return !time ? 0 : (time / 1000);
}

uint64_t milli_to_milli(const uint64_t time)
{
    return time;
}

uint64_t milli_to_nano(const uint64_t time)
{
    return time * 1000 * 1000;
}

const struct time_unit_t TIME_UNIT_MILLI = {
    .to_second = milli_to_second,
    .to_milli = milli_to_milli,
    .to_nano = milli_to_nano,
};

uint64_t nano_to_second(const uint64_t time)
{
    return !time ? 0 : (time / (1000 * 1000 * 1000));
}

uint64_t nano_to_milli(uint64_t time)
{
    return !time ? 0 : (time / (1000 * 1000));
}

uint64_t nano_to_nano(const uint64_t time)
{
    return time;
}

const struct time_unit_t TIME_UNIT_NANO = {
    .to_second = nano_to_second,
    .to_milli = nano_to_milli,
    .to_nano = nano_to_nano,
};

