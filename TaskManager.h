/**
 * @file Taskmanager.h
 * @author Md Shamim Patwary (shamimpatwary002@gmail.com)
 * @brief Task management module for a Trello dashboard application
 * @version 0.1
 * @date 2025-05-21
 *
 * This module defines the data structures, enumerations, globals, and
 * function prototypes needed to create, manage, display, and persist tasks.
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef TASKMANAGER_H_INCLUDED
#define TASKMANAGER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "Time.h"

#define MAX_TITLE_LENGTH 50
#define MAX_DESCRIPTION_LENGTH 100

/**
 * @brief Represents the status of a task in the Trello Dashboard.
 *
 * @details Enumerates the possible states a task can be in during its lifecycle.
 */
typedef enum{
    PENDING = 1,
    IN_PROGRESS = 2,
    COMPLETED = 3,
    OVERDUE = 4
} TaskStatus;

/**
 * @brief Represents the priority level of a task.
 *
 * @details Indicates the urgency or importance of a task to help with sorting
 * and decision-making in the Trello Dashboard.
 */
typedef enum{
    LOW = 1,
    MEDIUM = 2,
    HIGH = 3
} TaskPriority;

/**
 * @brief Represents a task in the Trello Dashboard system.
 *
 * @details Stores all relevant information about a task, including metadata such as
 * its title, description, status, priority, creation and due dates. Tasks are linked
 * together in a doubly linked list for efficient navigation and modification.
 */
typedef struct Task{
    uint8_t id;
    char title[MAX_TITLE_LENGTH];
    char description[MAX_DESCRIPTION_LENGTH];
    TaskStatus status;
    TaskPriority priority;
    Time create_date;
    Time due_date;
    struct Task * next;
    struct Task * prev;
} Task;

/**
 * @brief Globals to manage tasks
 *
 */
extern Task * tasks; // Head of the doubly linked list

/**
 * @brief Current count of tasks in the task list.
 *
 * Tracks the number of tasks stored, used for display and management purposes.
 */
extern uint8_t tasks_count;

/**
 * @enum result
 * @brief Represents the return status of operations.
 *
 * This enumeration defines standard return codes for functions
 * throughout the Task Management System. It helps clearly
 * indicate whether a function succeeded or failed.
 *
 * @var success
 * Indicates that the operation completed successfully.
 *
 * @var failed
 * Indicates that the operation failed due to an error.
 */
typedef enum{
    success = 0,
    failed = -1
} result;


#endif // TASKMANAGER_H_INCLUDED
