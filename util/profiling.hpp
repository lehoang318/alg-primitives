#ifndef __PROFILING_HPP__
#define __PROFILING_HPP__

#include <cstdint>
#include <limits>

#include <chrono>
#include <map>

namespace util {

typedef enum {
    TIME_UNIT_NANOSECOND,
    TIME_UNIT_MICROSECOND,
    TIME_UNIT_MILLISECOND,
    TIME_UNIT_SECOND
} TimeUnitIdType;

class Profiler {
public:
    Profiler() {}

    void start(int timerId) {
        mTimerMap[timerId] = std::chrono::steady_clock::now();
    }

    uint64_t stop(int timerId, TimeUnitIdType unit=TIME_UNIT_MILLISECOND) {
        auto now = std::chrono::steady_clock::now();

        if (mTimerMap.end() == mTimerMap.find(timerId)) {
            return std::numeric_limits<uint64_t>::max();
        }

        auto _duration = now - mTimerMap[timerId];
        uint64_t duration;

        switch (unit)
        {
            case TIME_UNIT_NANOSECOND:
                duration = std::chrono::duration_cast<std::chrono::nanoseconds>(_duration).count();
                break;
            case TIME_UNIT_MICROSECOND:
                duration = std::chrono::duration_cast<std::chrono::microseconds>(_duration).count();
                break;
            case TIME_UNIT_MILLISECOND:
                duration = std::chrono::duration_cast<std::chrono::milliseconds>(_duration).count();
                break;
            case TIME_UNIT_SECOND:
                duration = std::chrono::duration_cast<std::chrono::seconds>(_duration).count();
                break;
            default:
                duration = std::numeric_limits<uint64_t>::max();
                break;
        }

        mTimerMap[timerId] = std::chrono::steady_clock::now();

        return duration;
    }

private:
    std::map<int, std::chrono::time_point<std::chrono::steady_clock>> mTimerMap;
};

}   // util

#endif // __PROFILING_HPP__
