/**
 * @file TaskManager.c
 * @author Md Shamim Patwary (shamimpatwary002@gmail.com)
 * @brief
 * @version 0.1
 * @date 2025-05-19
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "Time.h"
#include "Taskmanager.h"

Task *tasks = NULL;

uint8_t tasks_count = 0;


/**
 * @brief Converts a TaskStatus enum value to a human-readable string.
 *
 * Maps the task status enumeration to its corresponding string
 * representation for display purposes.
 *
 * @param status The TaskStatus enum value.
 * @return const char* Pointer to the corresponding status string.
 */
const char * status_to_string(TaskStatus status){
    switch(status){
        case PENDING : return "Pending";
        case IN_PROGRESS : return "In Progress";
        case COMPLETED : return "Completed";
        case OVERDUE : return "Overdue";
        default : return "Invalid";
    }
}


/**
 * @brief Converts a TaskPriority enum value to a human-readable string.
 *
 * Maps the task priority enumeration to its corresponding string
 * representation for display purposes.
 *
 * @param priority The TaskPriority enum value.
 * @return const char* Pointer to the corresponding priority string.
 */
const char * priority_to_string(TaskPriority priority){
    switch(priority){
        case LOW : return "Low";
        case MEDIUM : return "Medium";
        case HIGH : return "High";
        default : return "Invalid";
    }
}
