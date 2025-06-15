/**
 * @file Login.h
 * @author Md Shamim Patwary (shamimpatwary002@gmail.com)
 * @brief
 * @version 0.1
 * @date 2025-05-21
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef LOGIN_H_INCLUDED
#define LOGIN_H_INCLUDED

#include <stdbool.h>
#include <stdint.h>

#include "TaskManager.h"

/**
 * @def MAX_SIZE_USER_NAME
 * @brief Maximum allowed length for a user's username.
 */
#define MAX_SIZE_USER_NAME 30

/**
 * @def MAX_SIZE_PASSWORD
 * @brief Maximum allowed length for a user's password.
 */
#define MAX_SIZE_PASSWORD 20

/**
 * @def FILE_NAME
 * @brief Name of the binary file used for saving task and user data.
 */
#define FILE_NAME "Trello.bin"

/**
 * @def FILE_HEADER_SIZE
 * @brief Size of the file header, based on the size of the sFileHeader structure.
 */
#define FILE_HEADER_SIZE sizeof(sFileHeader)


/**
 * @brief Structure to represent the header of the binary data file.
 *
 * This structure stores user authentication information including the
 * username and password. It is typically written at the beginning of
 * the binary file to validate user access during file operations.
 */
typedef struct {
    char username[MAX_SIZE_USER_NAME];
    char password[MAX_SIZE_PASSWORD];
} sFileHeader;


/**
 * @brief Initializes the login file with default credentials.
 *
 * Creates a binary file with default username and password ("trello")
 * if it does not already exist. The credentials are stored using the
 * sFileHeader structure.
 *
 * @return result Returns `success` upon exit.
 */
result init();

/**
 * @brief Handles the user login process.
 *
 * Prompts the user to enter a username and password. If the input matches
 * the stored credentials in the file, the user is granted access to the dashboard.
 * Allows a maximum of 2 login attempts. If unsuccessful, displays a failure message.
 *
 * @return result Returns `success` upon exit.
 */
result login();

/**
 * @brief Checks if a specified file exists.
 *
 * @param path The path to the file to check.
 * @return uint8_t Returns 1 if the file exists, otherwise 0.
 */
uint8_t isFileExists(const char *path);

/**
 * @brief Displays the welcome message.
 *
 * This function is typically called at the start of the application
 * to greet the user.
 *
 * @return result Returns `success` upon exit.
 */
result welcomeMessage();

/**
 * @brief Displays a formatted header message.
 *
 * This function prints a header-style message, often used to
 * identify different sections of the interface (e.g., "Welcome", "Dashboard").
 *
 * @return result Returns `success` upon exit.
 */
result headMessage();

/**
 * @brief Shows a "Loading" animation and introduces a short delay.
 *
 * Clears the screen and displays a loading message character by character
 * with a delay, simulating a loading screen.
 *
 * @return result Returns `success` upon exit.
 */
result wait();

/**
 * @brief Launches the dashboard UI.
 *
 * This function provides an interactive menu for the user to manage
 * tasks such as adding, viewing, updating, or deleting tasks.
 * It continuously runs until the user chooses to exit.
 *
 * @return result Returns `success` upon exit.
 */
result dashboard();

#endif // LOGIN_H_INCLUDED
