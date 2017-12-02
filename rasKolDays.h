#ifndef _RASKOLDAYS_
#define _RASKOLDAYS_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

typedef enum {false, true} bool;
typedef struct Date {
    int day;
    int month;
    int year;
} Date;

FILE *openFile(char *fileName, char *mode);
bool matchPattern(char *string);
void messagesPerDay(char *argv1);
void daysInMonth(char *argv1);

#endif
