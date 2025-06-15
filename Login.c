/**
 * @file Login.c
 * @author Md Shamim Patwary (shamimpatwary002@gmail.com)
 * @brief
 * @version 0.1
 * @date 2025-05-21
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <string.h>


/**
 * @file Login.h
 * @brief Header file for user authentication and file initialization.
 *
 * Contains function declarations and constants used for initializing the
 * login system, verifying credentials, and managing the login data file.
 */
#include "Login.h"

/**
 * @file main.h
 * @brief Main header for the task management application.
 *
 * Includes declarations for core UI components like dashboard and messages,
 * as well as utility functions shared across modules.
 */
#include "main.h"



result init(){
    FILE *fp = NULL;
    const char defaultUsername[] = "trello";
    const char defaultPassword[] = "trello";
    sFileHeader fileHeaderInfo = {0};

    if (!isFileExists(FILE_NAME)) {
        fp = fopen(FILE_NAME, "wb");
        if (fp != NULL) {
            strncpy(fileHeaderInfo.username, defaultUsername, MAX_SIZE_USER_NAME - 1);
            strncpy(fileHeaderInfo.password, defaultPassword, MAX_SIZE_PASSWORD - 1);
            fwrite(&fileHeaderInfo, FILE_HEADER_SIZE, 1, fp);
            fclose(fp);
        }
        else {
            printf("Error creating credentials file.\n");
        }
    }

    return success;
}


result login(){
    char userName[MAX_SIZE_USER_NAME] = {0};
    char password[MAX_SIZE_PASSWORD] = {0};
    uint8_t attempts = 0;
    sFileHeader fileHeaderInfo = {0};
    FILE *fp = fopen(FILE_NAME, "rb");

    if (fp == NULL) {
        printf("Unable to open credentials file.\n");
        exit(EXIT_FAILURE);
        return failed;
    }

    fread(&fileHeaderInfo, FILE_HEADER_SIZE, 1, fp);
    fclose(fp);

    headMessage("Login");

    while (attempts < 2) {
        printf("\n\n\n\t\t\t\tUsername: ");
        fgets(userName, sizeof(userName), stdin);
        userName[strcspn(userName, "\n")] = '\0';  // Remove newline

        printf("\n\t\t\t\tPassword: ");
        fgets(password, sizeof(password), stdin);
        password[strcspn(password, "\n")] = '\0';

        if (strcmp(userName, fileHeaderInfo.username) == 0 &&
            strcmp(password, fileHeaderInfo.password) == 0) {
            wait();
            dashBoard();
            return;
        } else {
            printf("\n\t\t\t\tLogin Failed. Try again.\n");
            attempts++;
        }
    }

    headMessage("Login Failed");
    const char msg[] = "\n\n\n\n\t\t\t\t\t ========= Sorry Unknown User ======\n";
    for (int i = 0; i < strlen(msg); i++) {
        printf("%c", msg[i]);
        Sleep(40);
    }

    printf("\n\n\n\t\t\t Enter any key to continue.....");
    getchar();
    system("cls");

    return success;
}


uint8_t isFileExists(const char *path){
    FILE *fp = fopen(path, "rb");
    if (fp) {
        fclose(fp);
        return 1;
    }
    return 0;
}


result headMessage() {
    system("cls");
    printf("\t\t\t###########################################################################\n");
    printf("\t\t\t############                                                   ############\n");
    printf("\t\t\t############            Welcome To Trello Dashboard            ############\n");
    printf("\t\t\t############                                                   ############\n");
    printf("\t\t\t###########################################################################\n");
    printf("\t\t\t---------------------------------------------------------------------------\n");

    return success;
}


result welcomeMessage(){
    system("cls");
    printf("\t\t\t###########################################################################\n");
    printf("\t\t\t############                                                   ############\n");
    printf("\t\t\t############            Welcome To Trello Dashboard            ############\n");
    printf("\t\t\t############                                                   ############\n");
    printf("\t\t\t###########################################################################\n");
    printf("\t\t\t---------------------------------------------------------------------------\n");
    printf("\n\n\n\t\t\t Enter any key to continue.....");
    getchar();
    return success;
}


result wait(){
    system("cls");
    const char msg[] = "\n\t\t\t\t\t ========= Loading Please Wait ======\n";
    for (int i = 0; i < strlen(msg); i++) {
        printf("%c", msg[i]);
        Sleep(16);
    }
    return success;
}
