/**
 * @file main.c
 * @author Md Shamim Patwary (shamimpatwary002@gmail.com)
 * @brief
 * @version 0.1
 * @date 2025-05-21
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

#include "Login.h"
#include "main.h"



/**
 * @brief Global flag to control the application's main loop.
 *
 * Used to indicate whether the application should continue running.
 * Set to `true` initially, and may be updated to `false` to exit
 * the main loop or terminate the program.
 */
bool IsRunning = true;


result ExitProject() {
    system("cls");
    const char *msg3 = "\n\t\t\t\t\t    ========= Thank You =========\n";

    printf("\n\n");
    for (int i = 0; i < strlen(msg3); i++) { printf("%c", msg3[i]); Sleep(40); }

    printf("\n\n");
    exit(0);
}




int main() {
    while (IsRunning) {
        system("cls");
        printf("\t\t\t###########################################################################\n");
        printf("\t\t\t############                                                   ############\n");
        printf("\t\t\t############     Trello Dashboard Project in C Language        ############\n");
        printf("\t\t\t############                                                   ############\n");
        printf("\t\t\t###########################################################################\n");
        printf("\t\t\t---------------------------------------------------------------------------\n");

        int choice;
        printf("\n\n\n\t\t\t1. Login to Dashboard\n");
        printf("\n\t\t\t2. Exit Project");
        printf("\n\n\n\t\t\tEnter choice => ");
        scanf("%d", &choice);

        getchar(); // Clear newline left in buffer

        switch (choice) {
            case 1:
                system("cls");
                init();
                welcomeMessage();
                login();
                break;
            case 2:
                ExitProject();
                break;
            default:
                printf("\n\t\t\tInvalid Input. Press Enter to try again...");
                getchar();
        }
    }

    return 0;
}
