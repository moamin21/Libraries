#ifndef MYLIB_TIME_UTILS_H
#define MYLIB_TIME_UTILS_H

#include <limits>  // For std::numeric_limits
#include "io.h"   // For read_number function

namespace mylib {
namespace time {

/**
 * Converts hours to days.
 * 
 * @param hours Number of hours to convert
 * @return Equivalent number of days
 */
template<typename T>
auto hours_to_days(T hours) -> decltype(hours / 24.0) {
    static_assert(std::is_arithmetic_v<T>, "hours_to_days requires numeric type");
    return hours / 24.0;
}

/**
 * Converts hours to weeks.
 * 
 * @param hours Number of hours to convert
 * @return Equivalent number of weeks
 */
template<typename T>
auto hours_to_weeks(T hours) -> decltype(hours / (24.0 * 7.0)) {
    static_assert(std::is_arithmetic_v<T>, "hours_to_weeks requires numeric type");
    return hours / (24.0 * 7.0);
}

/**
 * Converts days to weeks.
 * 
 * @param days Number of days to convert
 * @return Equivalent number of weeks
 */
template<typename T>
auto days_to_weeks(T days) -> decltype(days / 7.0) {
    static_assert(std::is_arithmetic_v<T>, "days_to_weeks requires numeric type");
    return days / 7.0;
}

/**
 * Class representing a duration with days, hours, minutes, and seconds.
 */
class TaskDuration {
public:
    /**
     * Default constructor initializes all values to zero.
     */
    TaskDuration() : days(0), hours(0), minutes(0), seconds(0) {}
    
    /**
     * Constructor with explicit values for each component.
     * 
     * @param d Days
     * @param h Hours
     * @param m Minutes
     * @param s Seconds
     */
    TaskDuration(int d, int h, int m, int s) : 
        days(d), hours(h), minutes(m), seconds(s) {}
    
    /**
     * Gets the number of days.
     * 
     * @return Days component
     */
    int get_days() const { return days; }
    
    /**
     * Gets the number of hours.
     * 
     * @return Hours component
     */
    int get_hours() const { return hours; }
    
    /**
     * Gets the number of minutes.
     * 
     * @return Minutes component
     */
    int get_minutes() const { return minutes; }
    
    /**
     * Gets the number of seconds.
     * 
     * @return Seconds component
     */
    int get_seconds() const { return seconds; }
    
    /**
     * Sets the number of days.
     * 
     * @param d Days value
     */
    void set_days(int d) { days = d; }
    
    /**
     * Sets the number of hours.
     * 
     * @param h Hours value
     */
    void set_hours(int h) { hours = h; }
    
    /**
     * Sets the number of minutes.
     * 
     * @param m Minutes value
     */
    void set_minutes(int m) { minutes = m; }
    
    /**
     * Sets the number of seconds.
     * 
     * @param s Seconds value
     */
    void set_seconds(int s) { seconds = s; }
    
    /**
     * Converts the task duration to total seconds.
     * 
     * @return Total duration in seconds
     */
    int to_seconds() const {
        int total = 0;
        total = days * 24 * 60 * 60;    // Days to seconds
        total += hours * 60 * 60;       // Hours to seconds
        total += minutes * 60;          // Minutes to seconds
        total += seconds;               // Seconds
        return total;
    }
    
private:
    int days;
    int hours;
    int minutes;
    int seconds;
};

/**
 * Reads a TaskDuration from user input with validation.
 * 
 * @return TaskDuration with user-entered values
 */
TaskDuration read_task_duration() {
    TaskDuration duration;
    
    duration.set_days(read_number<int>("Please Enter Number Of Days? ", 1, std::numeric_limits<int>::max()));
    duration.set_hours(read_number<int>("Please Enter Number Of Hours? ", 1, std::numeric_limits<int>::max()));
    duration.set_minutes(read_number<int>("Please Enter Number Of Minutes? ", 1, std::numeric_limits<int>::max()));
    duration.set_seconds(read_number<int>("Please Enter Number Of Seconds? ", 1, std::numeric_limits<int>::max()));
    
    return duration;
}

} // namespace time
} // namespace mylib

#endif // MYLIB_TIME_UTILS_H