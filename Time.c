/**
 * @file Time.c
 * @author Md Shamim Patwary (shamimpatwary002@gmail.com)
 * @brief
 * @version 0.1
 * @date 2025-05-21
 *
 * @copyright Copyright (c) 2025
 *
 */

 #include <stdint.h>

#include "Time.h"
#include "TaskManager.h"



Time current_date(){
    time_t now = time(NULL);  // to get current time
    struct tm * time_info = localtime(&now);  // convert to local time
    Time date;
    date.year = time_info -> tm_year + 1900; // 1900 to get actual year
    date.month = time_info -> tm_mon + 1; // to get actual month because it is 0 based
    date.day = time_info -> tm_mday;
    return date;
}



Time due_date(unsigned int year, unsigned int month, unsigned int day){
    Time date;
    date.year = year;
    date.month = month;
    date.day = day;
    return date;
}


Time create_date(unsigned int year, unsigned int month, unsigned int day){
    Time date;
    date.year = year;
    date.month = month;
    date.day = day;
    return date;
}



uint8_t compare_days(Time date1, Time date2) {

    if (date1.year < date2.year) return 0;
    if (date1.year > date2.year) return 1;

    if (date1.month < date2.month) return 0;
    if (date1.month > date2.month) return 1;

    if (date1.day < date2.day) return 0;
    if (date1.day > date2.day) return 1;

    return 0; // dates are equal
}



void update_overdue_tasks(){
    Time now = current_date();
    Task * temp = tasks;

    while(temp != NULL){
        if(temp->status != COMPLETED && compare_days(temp ->due_date, now) < 0){
            temp ->status = OVERDUE;
        }
        temp = temp ->next;
    }
}
