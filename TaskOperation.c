/**
 * @file TaskOperation.c
 * @author Md Shamim Patwary (shamimpatwary002@gmail.com)
 * @brief
 * @version 0.1
 * @date 2025-05-21
 *
 * @copyright Copyright (c) 2025
 *
 */
#include <stdlib.h>

#include "TaskManager.h"
#include "TaskOperation.h"
#include "Time.h"


/**
 * @brief Globals to manage tasks
 *
 */
extern Task *tasks;
extern uint8_t tasks_count;



result add_task(){
    Task * new_task =(Task*) malloc(sizeof(Task));
    if(new_task == NULL){
        printf("\n\t\t\tMemory Allocation failed for new Task..");
        printf("\n\t\t\tPress Any Key to Continue...");
        getchar();
        return failed; // failure
    }

    new_task ->id = ++ tasks_count;
    //new_task ->create_date = current_date();
    new_task ->next = NULL;
    new_task ->prev = NULL;

    printf("\n\n\t\t\t\t\t\t\tAdd New Task");
    printf("\n\n\t\t\tEnter Task Title : ");
    while(getchar() != '\n');

    if(fgets(new_task ->title, MAX_TITLE_LENGTH, stdin) == NULL){
        printf("\n\t\t\tFailed to read title...");
        free(new_task);
        printf("\n\t\t\tPress any key to continue...");
        getchar();
        return failed; // failure
    }

    new_task ->title[strcspn(new_task ->title, "\n")] = 0; //remove new line

    if(strlen(new_task ->title) == 0){
        printf("\n\t\t\tTitle Cannot be empty\n");
        free(new_task);
        printf("\n\t\t\tPress enter to continue...");
        getchar();
        return failed; //failure
    }


    printf("\n\t\t\tEnter Task Description : ");
    //while(getchar() != '\n');
    if(fgets(new_task ->description, MAX_DESCRIPTION_LENGTH, stdin) == NULL){
        printf("\n\t\t\tFailed to read description...");
        free(new_task);
        printf("\n\t\t\tPress any key to continue...");
        getchar();
        return failed; //failure
    }

    new_task ->description[strcspn(new_task->description, "\n")] = 0;

//    if(strlen(new_task ->description) == 0){
//        printf("\n\t\t\tDescription Cannot be empty\n");
//        free(new_task);
//        printf("\n\t\t\tPress enter to continue...");
//        getchar();
//        return;
//    }

    uint8_t priority_input = 0;
    while(1){
        printf("\n\t\t\tPriority (1: LOW, 2: Medium, 3: High) : ");
        uint8_t value = scanf("%hhu",&priority_input);
        while(getchar() != '\n'); // clear input buffer
        if(value == 1 && priority_input >=1 && priority_input <= 3){
            new_task ->priority = (TaskPriority)priority_input;
            break;
        }
        else{
            printf("\n\n\t\t\tInvalid input. Please Enter Valid Number ...");
        }
    }

    unsigned int day, month, years;
    while(1){
        printf("\n\t\t\tEnter Due Date (DD MM YYYY) : ");
        unsigned int value = scanf("%u %u %u", &day, &month, &years);
        while(getchar() != '\n');
        if(value == 3 && years >= 1970 && years <= 3000 && month >= 1 && month <=12 && day >= 1 && day <= 31){
            new_task ->due_date = due_date(years, month, day);
            break;
        }
        else{
            printf("\n\n\t\t\tInvalid due date format. Please try again...");
        }
    }

    new_task ->status = PENDING;

    //Insert at the beginning of the DL List
    new_task ->next = tasks;
    new_task ->prev = NULL;
    if(tasks != NULL){
        tasks ->prev = new_task;
    }
    tasks = new_task;

    printf("\n\t\t\tTask added successfully....");
    printf("\n\n\t\t\tPress any to continue...");
    getchar();

    return success;
}


result display_task(){

    FILE *tasks_file = fopen("Task.dat","rb");
    if (tasks_file == NULL){
        printf("\n\t\t\tNo Saved Tasks found.\n");
        printf("\n\t\t\tPress any key to continue\n");

        getchar();
        return failed;
    }

    uint8_t file_tasks_count;
    if (fread(&file_tasks_count, sizeof(uint8_t), 1, tasks_file) != 1) {
        printf("\n\t\t\tError reading task count\n");
        fclose(tasks_file);
        printf("\n\t\t\tPress any key to continue\n");
        getchar();
        return failed;
    }

    while(getchar() != '\n');

    if (file_tasks_count == 0) {
        printf("\n\t\t\tNo tasks found..\n");
        fclose(tasks_file);
        printf("\n\t\t\tPress any key to continue\n");
        getchar();
        return failed;
    }

    printf("\n\n\t\t\t\t\t\t--- Saved Tasks ---\n");
    for (int i = 0; i < file_tasks_count; i++) {
        Task temp;
        if (fread(&temp, sizeof(Task), 1, tasks_file) != 1) {
            printf("\n\t\t\tThere is no saved tasks\n");
            fclose(tasks_file);
            printf("\n\t\t\tPress any key to continue");
            getchar();
            return failed;
        }

        update_overdue_tasks();

        printf("\n\t\t\tTask ID: %u", temp.id);
        printf("\n\t\t\tTitle: %s", temp.title);
        printf("\n\t\t\tDescription: %s", temp.description);
        printf("\n\t\t\tTask Status : %s", (status_to_string(temp.status)));
        printf("\n\t\t\tTask Priority : %s", (priority_to_string(temp.priority)));
        printf("\n\t\t\tDue Date : %2d-%2d-%4d", temp.due_date.day, temp.due_date.month, temp.due_date.year);
        printf("\n\n");
    }

    //while(getchar() != '\n');

    fclose(tasks_file);
    printf("\n\t\t\tPress any key to continue...");
    getchar();

    return success;
}



result update_task_priority(){

    display_task();
    system("cls");

    uint8_t task_id;
    printf("\n\t\t\tEnter Task Id to Update: ");

    if (scanf("%hhu", &task_id) != 1) {
        printf("\n\t\t\tInvalid Input. Press any key to continue\n");
        while (getchar() != '\n');
        getchar();
        return failed;
    }
    while (getchar() != '\n'); // Clear input buffer

    Task * temp = tasks;
    while (temp != NULL) {
        if (temp->id == task_id) {
            printf("\n\t\t\tCurrent Priority of Task ID %hhu: %s\n", temp->id, priority_to_string(temp->priority));

            int new_priority;
            printf("\n\t\t\tEnter new Priority (1: LOW, 2: MEDIUM, 3: HIGH) : ");
            if (scanf("%d", &new_priority) != 1 || new_priority < 1 || new_priority > 3) {
                printf("\n\t\t\tInvalid status. Press any key to continue\n");
                while (getchar() != '\n');
                getchar();
                return failed;
            }
            while (getchar() != '\n');

            temp->priority = (TaskPriority)new_priority;
            printf("\n\t\t\tTask Updated Successfully\n");

            // Save updated tasks to file
            FILE* file = fopen("Task.dat", "wb");
            if (file == NULL) {
                printf("\n\t\t\tError: could not open Task.dat for writing.\nPress Enter to continue...");
                getchar();
                return failed;
            }

            // Count tasks
            uint8_t count = 0;
            Task* cursor = tasks;
            while (cursor != NULL) {
                count++;
                cursor = cursor->next;
            }

            // Write count and each task
            fwrite(&count, sizeof(uint8_t), 1, file);
            cursor = tasks;
            while (cursor != NULL) {
                fwrite(cursor, sizeof(Task), 1, file);
                cursor = cursor->next;
            }

            fclose(file);

            printf("\n\t\t\tTask saved to file.\n\n\t\t\tPress Enter to continue...");
            getchar();
            return success;
        }

        temp = temp->next;
    }

    printf("\n\t\t\tTask ID %hhu is not found.\n\n\t\t\tPress Enter to continue...", task_id);
    getchar();

    return success;
}


result update_task_status() {

    display_task();

    system("cls");




    uint8_t task_id;
    printf("\n\t\t\tEnter Task Id to Update: ");

    if (scanf("%hhu", &task_id) != 1) {
        printf("\n\t\t\tInvalid Input. Press any key to continue\n");
        while (getchar() != '\n');
        getchar();
        return failed;
    }
    while (getchar() != '\n'); // Clear newline

    Task* temp = tasks;
    while (temp != NULL) {
        if (temp->id == task_id) {
            printf("\n\t\t\tCurrent Status of Task ID %hhu: %s\n", temp->id, status_to_string(temp->status));

            int new_status;
            printf("\n\t\t\tEnter new status (1: PENDING, 2: IN-PROGRESS, 3: COMPLETED, 4: OVERDUE): ");
            if (scanf("%d", &new_status) != 1 || new_status < 1 || new_status > 4) {
                printf("\n\t\t\tInvalid status. Press any key to continue\n");
                while (getchar() != '\n');
                getchar();
                return failed;
            }
            while (getchar() != '\n');

            temp->status = (TaskStatus)new_status;
            printf("\n\t\t\tTask Updated Successfully\n");

            // Save updated tasks to file
            FILE* file = fopen("Task.dat", "wb");
            if (!file) {
                printf("\n\t\t\tError: could not open Task.dat for writing.\nPress Enter to continue...");
                getchar();
                return failed;
            }

            // Count tasks
            uint8_t count = 0;
            Task* cursor = tasks;
            while (cursor != NULL) {
                count++;
                cursor = cursor->next;
            }

            // Write count and each task
            fwrite(&count, sizeof(uint8_t), 1, file);
            cursor = tasks;
            while (cursor != NULL) {
                fwrite(cursor, sizeof(Task), 1, file);
                cursor = cursor->next;
            }

            fclose(file);

            printf("\n\t\t\tTask saved to file.\n\n\t\t\tPress Enter to continue...");
            getchar();
            return success;
        }

        temp = temp->next;
    }

    printf("\n\t\t\tTask ID %hhu is not found.\n\n\t\t\tPress Enter to continue...", task_id);
    getchar();

    return success;
}




result delete_task() {

    display_task();
    system("cls");

    uint8_t task_id;
    printf("\n\t\t\tEnter Task Id to Delete : ");
    if(scanf("%hhu", &task_id) != 1) {
        printf("\n\t\t\tInvalid Input\n");
        while(getchar() != '\n');
        return failed;
    }
    while(getchar() != '\n'); // Clear buffer after successful scanf

    if(tasks == NULL) {
        printf("\n\t\t\tNo Tasks to Delete\n");
        printf("\n\t\t\tPress any key to continue\n");
        getchar();
        return failed;
    }

    Task *current_task = tasks;
    while(current_task != NULL && current_task->id != task_id) {
        current_task = current_task->next;
    }

    if(current_task == NULL) {
        printf("\n\t\t\tTask not found\n");
        printf("\n\t\t\tPress any key to continue\n");
        getchar();
        return failed;
    }

    // Delete the node
    if(current_task->prev != NULL) {
        current_task->prev->next = current_task->next;
    }
    else {
        tasks = current_task->next;
    }

    if(current_task->next != NULL) {
        current_task->next->prev = current_task->prev;
    }

    free(current_task);

    printf("\n\t\t\tTask deleted successfully\n");
    printf("\n\t\t\tPress any key to continue\n");
    getchar();

    return success;
}





result save_task(){
    system("cls");  // Clear screen for better UI

    FILE *task_file = fopen("Task.dat", "wb");

    if (task_file == NULL) {
        printf("\n\t\t\tError: Unable to open file for saving\n");
        printf("\n\t\t\tPress any key to continue...");
        getchar();
        getchar();  // Extra getchar to handle potential newline
        return failed;
    }

    // Write task count
    if (fwrite(&tasks_count, sizeof(uint8_t), 1, task_file) != 1) {
        printf("\n\t\t\tError: Failed to write task count\n");
        fclose(task_file);
        printf("\n\t\t\tPress any key to continue...");
        getchar();
        return failed;
    }

    // Write tasks
    Task *current_task = tasks;
    while (current_task != NULL) {
        Task temp_task = *current_task;
        temp_task.next = NULL;
        temp_task.prev = NULL;

        if (fwrite(&temp_task, sizeof(Task), 1, task_file) != 1) {
            printf("\n\t\t\tError: Failed to write task data\n");
            fclose(task_file);
            printf("\n\t\t\tPress any key to continue...");
            getchar();
            getchar();
            return failed;
        }
        current_task = current_task->next;
    }

    fclose(task_file);
    printf("\n\n\t\t\t\t\t\t--- Tasks Saved Successfully ---\n");
    printf("\n\t\t\tPress any key to continue...");
    while(getchar() != '\n');
    getchar();

    return success;
}





result search_task(const char *title_query) {

    system("cls");

    FILE *task_file = fopen("Task.dat", "rb");
    if (task_file == NULL) {
        printf("\n\t\t\tError: Unable to open task file.\n");
        printf("\n\t\t\tPress Enter to continue...");
        getchar();
        return failed;
    }

    uint8_t task_count;
    if (fread(&task_count, sizeof(uint8_t), 1, task_file) != 1) {
        printf("\n\t\t\tError: Failed to read task count.\n");
        fclose(task_file);
        printf("\n\t\t\tPress Enter to continue...");
        getchar();
        return failed;
    }

    Task temp;
    int found = 0;

    printf("\n\t\t\tSearch results for \"%s\":\n\n", title_query);

    for (int i = 0; i < task_count; i++) {
        if (fread(&temp, sizeof(Task), 1, task_file) != 1) {
            printf("\n\t\t\tError: Failed to read task data.\n");
            break;
        }

        if (strcmp(temp.title, title_query) == 0) {
            found = 1;
            printf("\n\t\t\tTask ID: %u", temp.id);
            printf("\n\t\t\tTitle: %s", temp.title);
            printf("\n\t\t\tDescription: %s", temp.description);
            printf("\n\t\t\tTask Status : %s", (status_to_string(temp.status)));
            printf("\n\t\t\tTask Priority : %s", (priority_to_string(temp.priority)));
            printf("\n\t\t\tDue Date : %2d-%2d-%4d", temp.due_date.day, temp.due_date.month, temp.due_date.year);
            printf("\n\n");
        }
    }

    if (!found) {
        printf("\n\t\t\tNo task found with the title \"%s\".\n", title_query);
    }

    fclose(task_file);
    printf("\n\t\t\tPress Enter to continue...");
    getchar();

    return success;
}
