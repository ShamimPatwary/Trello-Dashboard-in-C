/**
 * @file Dashboard.h
 * @author Md Shamim Patwary (shamimpatwary002@gmail.com)
 * @brief
 * @version 0.1
 * @date 2025-05-21
 *
 * @copyright Copyright (c) 2025
 *
 */


#ifndef DASHBOARD_H_INCLUDED
#define DASHBOARD_H_INCLUDED

#include "TaskManager.h"


/**
 * @brief Displays the main dashboard menu for the Task Management System.
 *
 * This function continuously displays a menu that allows the user to:
 * - Add a new task
 * - Save tasks to a file
 * - Display all tasks
 * - Update the priority of a task
 * - Update the status of a task
 * - Delete a task
 * - Search for a task by title
 * - Exit the dashboard
 *
 * It shows the current date and calls corresponding functions based on user input.
 * The menu loops until the user selects the exit option (choice 8).
 *
 * The function depends on the following utilities and task-related functions:
 * - `current_date()` to retrieve the current date
 * - `headMessage(const char*)` to print a formatted header
 * - `wait()` to pause before screen transitions
 * - `system("cls")` to clear the screen (platform-dependent)
 * - Task functions: `add_task()`, `display_task()`, `update_task_priority()`, `update_task_status()`,
 *   `delete_task()`, `save_task()`, `search_task(const char*)`, `ExitProject()`
 *
 * @note This function assumes a console-based interface and uses `system("cls")`, which may not be portable.
 *
 * @return result Returns `success` upon exit.
 */
result dashboard();

/**
 * @brief Prompts the user to input details for a new task and adds it to the task list.
 */
result add_task();

/**
 * @brief Displays all tasks including all information.
 */
result display_task();

/**
 * @brief Updates the status of a specific task based on user input.
 */
result update_task_status();

/**
 * @brief Checks for tasks past their due date and updates their status to OVERDUE.
 */
void update_overdue_tasks();

/**
 * @brief Deletes a specified task from the task list.
 */
result delete_task();

/**
 * @brief Saves the current list of tasks to a file for persistence.
 */
result save_task();

/**
 * @brief search tasks from a previously saved file into the application.
 */
result search_task();

/**
 * @brief Converts a TaskStatus enum value to its corresponding string representation.
 *
 * @param status The status to convert.
 * @return A string representation of the status.
 */
const char * status_to_string(TaskStatus status);

/**
 * @brief Converts a TaskPriority enum value to its corresponding string representation.
 *
 * @param priority The priority to convert.
 * @return A string representation of the priority.
 */
const char * priority_to_string(TaskPriority priority);

#endif // DASHBOARD_H_INCLUDED
