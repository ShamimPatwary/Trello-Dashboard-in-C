/**
 * @file main.h
 * @author Md Shamim Patwary (shamimpatwary002@gmail.com)
 * @brief
 * @version 0.1
 * @date 2025-05-19
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED


#include "TaskManager.h"

/**
 * @brief Terminates the application gracefully.
 *
 * This function should handle any cleanup required before exiting,
 * such as saving data, freeing resources, and setting flags to
 * stop the main program loop.
 *
 * @return result Returns `success` upon exit.
 */
result ExitProject();

/**
 * @brief Entry point of the Trello Dashboard application.
 *
 * Displays the main menu with options to log in or exit the application.
 * The loop continues running as long as the global flag `IsRunning` is true.
 * Based on the user's input:
 * - Option 1: Initializes login data, displays a welcome message, and starts the login process.
 * - Option 2: Calls `ExitProject()` to terminate the application.
 *
 * @return int Returns 0 upon successful program termination.
 */
int main();
#endif // MAIN_H_INCLUDED
