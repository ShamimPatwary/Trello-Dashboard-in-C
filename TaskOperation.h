/**
 * @file TaskOperation.h
 * @author Md Shamim Patwary (shamimpatwary002@gmail.com)
 * @brief
 * @version 0.1
 * @date 2025-05-19
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef TASKOPERATION_H_INCLUDED
#define TASKOPERATION_H_INCLUDED

#include "TaskManager.h"
#include "Dashboard.h"



/**
 * @brief Adds a new task to the global doubly linked list of tasks.
 *
 * This function performs the following steps:
 * - Allocates memory for a new Task structure.
 * - Assigns a unique ID and creation date to the new task.
 * - Prompts the user to input the task title and description, with input validation.
 * - Prompts the user to input a priority level (LOW, Medium, High), validating the input.
 * - Prompts the user to input a due date (day, month, year), with format and range validation.
 * - Sets the initial status of the task to PENDING.
 * - Inserts the new task at the beginning of the doubly linked list of tasks.
 * - Handles any input or memory allocation errors by freeing allocated memory and returning early.
 *
 * @note The function assumes the existence of the following:
 * - Global pointer `tasks` to the head of the doubly linked list of tasks.
 * - Global counter `tasks_count` that tracks the number of tasks created.
 * - The `Task` struct with fields `id`, `create_date`, `title`, `description`, `priority`, `due_date`, `status`, `next`, and `prev`.
 * - The enums or typedefs `TaskPriority` and `PENDING`.
 * - Helper functions `current_date()` and `due_date(year, month, day)` to handle date assignments.
 *
 * @warning This function blocks and waits for user input via standard input.
 *
 * @return result Returns `success` upon exit.
 */
result add_task();

/**
 * @brief Displays all saved tasks from the file "Task.dat".
 *
 * This function performs the following steps:
 * - Opens the file "Task.dat" in binary read mode.
 * - Reads the number of tasks stored in the file.
 * - If no tasks are found or the file cannot be opened, informs the user.
 * - Iterates through the saved tasks, reading each task's data into a temporary variable.
 * - Prints task details including ID, title, description, status, priority, and due date.
 * - Handles file read errors gracefully.
 * - Waits for user input before returning.
 *
 * @note Assumes:
 * - The tasks are stored in "Task.dat" with the first byte representing the task count.
 * - The `Task` struct and the helper functions `status_to_string()` and `priority_to_string()` are defined.
 * - The task due date is stored in a `due_date` struct with `day`, `month`, and `year` fields.
 *
 * @warning
 * - The function blocks and waits for user input at the end.
 * - The function reads directly from the file and does not reflect changes in the in-memory linked list.
 *
 * @return result Returns `success` upon exit.
 */
result display_task();


/**
 * @brief Updates the status of a selected task in the global task list.
 *
 * This function performs the following steps:
 * - Displays all current tasks to the user.
 * - Prompts the user to enter the Task ID for which the status should be updated.
 * - Validates the entered Task ID to ensure it corresponds to an existing task.
 * - Prompts the user to enter a new status value (1: PENDING, 2: IN-PROGRESS, 3: COMPLETED, 4: OVERDUE).
 * - Validates the new status input and updates the task's status accordingly.
 * - Saves the updated list of tasks to the file "Task.dat" by:
 *   - Counting the total number of tasks.
 *   - Writing the task count followed by each task's data to the file.
 * - Provides feedback to the user about the success or failure of each operation.
 *
 * @note This function assumes:
 * - A global pointer `tasks` pointing to the head of a doubly linked list of Task structures.
 * - Each Task has an `id`, `status`, and `next` pointer.
 * - The existence of a `status_to_string()` helper function that converts status enums to strings.
 * - The file "Task.dat" is used to persist tasks.
 *
 * @warning
 * - User inputs are read via `scanf()`. Invalid inputs will abort the update process.
 * - The function blocks and waits for user input.
 * - The file "Task.dat" will be overwritten when saving tasks.
 *
 * @return result Returns `success` upon exit.
 */
result update_task_status();

/**
 * @brief Updates the priority of a selected task in the global task list.
 *
 * This function performs the following steps:
 * - Displays all current tasks to the user.
 * - Prompts the user to enter the Task ID for which the priority should be updated.
 * - Validates the entered Task ID to ensure it corresponds to an existing task.
 * - Prompts the user to enter a new priority value (1: LOW, 2: MEDIUM, 3: HIGH).
 * - Validates the new priority input and updates the task's priority accordingly.
 * - Saves the updated list of tasks to the file "Task.dat" by:
 *   - Counting the total number of tasks.
 *   - Writing the task count followed by each task's data to the file.
 * - Provides feedback to the user about the success or failure of each operation.
 *
 * @note This function assumes:
 * - A global pointer `tasks` pointing to the head of a doubly linked list of Task structures.
 * - Each Task has an `id`, `priority`, and `next` pointer.
 * - The existence of a `priority_to_string()` helper function that converts priority enums to strings.
 * - The file "Task.dat" is used to persist tasks.
 *
 * @warning
 * - User inputs are read via `scanf()`. Invalid inputs will abort the update process.
 * - The function blocks and waits for user input.
 * - The file "Task.dat" will be overwritten when saving tasks.
 *
 * @return result Returns `success` upon exit.
 */
result update_task_priority();


/**
 * @brief Deletes a task from the global doubly linked list by Task ID.
 *
 * This function performs the following steps:
 * - Displays all current tasks.
 * - Prompts the user to enter the Task ID of the task to delete.
 * - Validates the user input.
 * - Searches the linked list for a task matching the entered ID.
 * - If found, removes the task node from the doubly linked list, updating links accordingly.
 * - Frees the memory allocated for the deleted task.
 * - Provides feedback about success or failure to find the task.
 * - Waits for user input before returning.
 *
 * @note Assumes:
 * - A global pointer `tasks` to the head of the doubly linked list of tasks.
 * - Each task has `id`, `prev`, and `next` pointers.
 * - `display_task()` is a function that lists all current tasks.
 *
 * @warning
 * - User input is read via `scanf()`. Invalid input aborts the deletion process.
 * - This function modifies the linked list and frees memory; use with caution.
 *
 * @return result Returns `success` upon exit.
 */
result delete_task();


/**
 * @brief Updates the status of all overdue tasks in the system.
 *
 */
void update_overdue_tasks();

/**
 * @brief Searches for a task with a title that exactly matches the given query.
 *
 * This function reads all tasks from the "Task.dat" file and compares each task's title
 * with the provided query string using an exact, case-sensitive match. If a match is found,
 * the task's details are displayed. If no match is found, a message is shown indicating so.
 *
 * @param title_query The title string to search for (must match exactly and case-sensitively).
 *
 * @note
 * - Assumes the "Task.dat" file exists and is formatted correctly.
 * - The task list is read from the binary file each time this function is called.
 * - This function uses `system("cls")` which is platform-specific (Windows).
 */
result search_task(const char * title_query);

#endif // TASKOPERATION_H_INCLUDED
