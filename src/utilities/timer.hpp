//===-- timer.hpp - -----------------------------------------*- C++ -*-===//
//
// Julian M. Toumey
// 29 January 2020
// COMPILATION NOTES:
//   * Compiled against C++17 using g++ 5.4.0 and clang-1000.11.45.5
//   * <chrono> library employed for high-resolution system clock
//===--*- ------------------------------------------------------------ --*-===//
//
/// \file
/// This file contains the declaration and implementation of a Timer class,
/// which is a basic operation timer for use during the course. Note that the
/// elapsedTime() method return the elapsed time in seconds.
//
//===--*- ------------------------------------------------------------ --*-===//
#ifndef TIMER_H
#define TIMER_H

#include <chrono>

namespace Utilities
{

const double MICROSECONDS_TO_SECONDS = 0.000001;

using namespace std::chrono;

class Timer
{
private:
    steady_clock::time_point startTime;
    steady_clock::time_point endTime;
    double elapsedTimeSeconds;

public:
    /// Construct the timer and start timing. Sets the endTime to the current
    /// instant as well in case the elapsedTime() method is called before the
    /// stop() method
    Timer() : startTime(steady_clock::now()), endTime(steady_clock::now()) {}
 
    /// Reset the timer by setting it to current system time
    void reset()
    {
        startTime = steady_clock::now();
    }

    /// Get current system time to establish stop point
    void stop()
    {
        endTime = steady_clock::now();
    }

    /// Return the elapsed time in seconds
    double elapsedTime()
    {
        auto duration = duration_cast<microseconds>(endTime - startTime);
        elapsedTimeSeconds = duration.count()*MICROSECONDS_TO_SECONDS;
        return (elapsedTimeSeconds);
    }
};

}

#endif // TIMER_H
