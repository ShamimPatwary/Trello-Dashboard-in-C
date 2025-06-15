
/**
 * @file Dashboard.c
 * @author Md Shamim Patwary (shamimpatwary002@gmail.com)
 * @brief
 * @version 0.1
 * @date 2025-05-21
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <stdio.h>
#include <windows.h>


#include "Login.h"
#include "Dashboard.h"
#include "Time.h"
#include "Taskmanager.h"
#include "TaskOperation.h"


result dashBoard(){
    Time t = current_date();
    int choice = 0;
    do
    {
        headMessage("Welcome");
        printf("\n\t\t\t\t\t\tCurrent Date : %02d-%02d-%04d",t.day,t.month,t.year);
        printf("\n\n\n\t\t\t1. Add Task\n");
        printf("\n\t\t\t2. Save Data\n");
        printf("\n\t\t\t3. Display All Tasks\n");
        printf("\n\t\t\t4. Update Task Priority\n");
        printf("\n\t\t\t5. Update Tasks Status\n");
        printf("\n\t\t\t6. Delete Tasks\n");
        printf("\n\t\t\t7. Search Task By Title\n");
        printf("\n\t\t\t8. Exit Dashboard\n");
        printf("\n\n\t\t\tEnter choice => ");
        scanf("%d",&choice);
        switch(choice)
        {
        case 1:
            wait();
            system("cls");
            add_task();
            break;
        case 2:
            wait();
            system("cls");
            save_task();
            break;
        case 3:
            wait();
            system("cls");
            display_task();
            break;
        case 4:
            wait();
            update_task_priority();
            break;
        case 5:
            wait();
            system("cls");
            update_task_status();
            break;
        case 6:
            wait();
            system("cls");
            delete_task();
            break;
        case 7:
            wait();
            system("cls");
        {
            char search_title[100];
            printf("\n\t\t\tEnter task title to search: ");
            while(getchar() != '\n');
            fgets(search_title, sizeof(search_title), stdin);
            search_title[strcspn(search_title, "\n")] = 0;
            search_task(search_title);
        }
            break;
        case 8:
            system("cls");
            ExitProject();
            break;
        default:
            printf("Invalid Input. Try Again\n");
        }
    }while(choice!=0);

    return success;
}
