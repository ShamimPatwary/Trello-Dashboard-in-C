/**
 * @file Time.h
 * @author Md Shamim Patwary (shamimpatwary002@gmail.com)
 * @brief
 * @version 0.1
 * @date 2025-05-21
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef TIME_H_INCLUDED
#define TIME_H_INCLUDED

#include <time.h>
#include <stdlib.h>
#include <stdint.h>


/**
 * @struct Time
 * @brief Represents a calendar date using compact bit fields.
 *
 * This structure uses bit fields to efficiently store the components
 * of a date: year, month, and day within a single unsigned int.
 *
 * Bit field sizes:
 * - year: 12 bits (0 - 4095)
 * - month: 4 bits (0 - 15)
 * - day: 5 bits (0 - 31)
 *
 * @note The values should be validated before assignment to ensure
 *       they represent a valid date (e.g., month between 1 and 12,
 *       day appropriate for the month).
 *
 * @warning The exact memory size and alignment can depend on the compiler.
 */
typedef struct{
    unsigned int year : 12;
    unsigned int month : 4;
    unsigned int day : 5;
} Time;

/**
 * @brief Retrieves the current date as a Time struct.
 *
 * This function obtains the system's current date and returns
 * it packed into a Time structure with bit fields for year, month,
 * and day.
 *
 * @return Time The current date.
 */
Time current_date();


/**
 * @brief Creates a Time struct representing a specified due date.
 *
 * This function initializes a Time struct with the provided
 * year, month, and day values.
 *
 * @param year The year component (valid range: 0 - 4095).
 * @param month The month component (valid range: 1 - 12).
 * @param day The day component (valid range: 1 - 31).
 *
 * @return Time The constructed due date.
 *
 * @note Input parameters should be validated by the caller to ensure
 *       they represent a valid calendar date.
 */
Time due_date(unsigned int year, unsigned int month, unsigned int day);



/**
 * @brief Compares two dates and determines if the first is later than or equal to the second.
 *
 * This function compares two Time structures and returns whether the first date
 * (`date1`) is the same as or later than the second (`date2`).
 *
 * @param date1 The first date to compare.
 * @param date2 The second date to compare.
 *
 * @return 1 if date1 is the same or after date2, 0 otherwise.
 *
 * @note This function performs a simple chronological comparison by year, then month, then day.
 */
uint8_t compare_days(Time date1, Time date2);


/**
 * @brief Updates the status of tasks that are past their due date.
 *
 * This function iterates through the global linked list of tasks and updates the status
 * of each task to `OVERDUE` if:
 * - The task is not already marked as `COMPLETED`, and
 * - Its due date is earlier than the current system date.
 *
 * The current date is retrieved using `current_date()`, and date comparison is performed
 * using `compare_days()`.
 *
 * @note
 * - Assumes the global `tasks` pointer is initialized and points to the head of the task list.
 * - Tasks marked as `COMPLETED` are not updated.
 * - Relies on `current_date()` and `compare_days()` functions to determine overdue status.
 */
void update_overdue_tasks();

#endif // TIME_H_INCLUDED
