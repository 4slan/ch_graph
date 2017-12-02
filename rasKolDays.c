#include "rasKolDays.h"

// Функция открывающая файл в заданном режиме
FILE *openFile(char *fileName, char *mode) {
    FILE *file;
    file = fopen(fileName, mode);
    if(file == NULL) {
        printf("Error opening file\n");
        exit(1);
    }
    return file;
}

// Функция проверяющая соответствие строки определенному формату
bool matchPattern(char *line) {
    int d, m, y;
    if(sscanf(line, "%d.%d.%d", &d, &m, &y) == 3) // Проверка на возвращаемое значение после считывания из массива определенный формат
        return true;
    return false;
}

// Функция вычисляющая количество сообщений в день
void messagesPerDay(char *argv1) {
    char line[100];
    int count = 0; // lineNum = 0;

    Date current = {0};
    Date previous = {0};

    FILE *file;
    file = openFile(argv1, "r");

    // FILE *writeInFile;
    // writeInFile = openFile("dates.txt", "w");

    while(fgets(line, 100, file)) {
        // lineNum++;
        if(matchPattern(line) == true) { // Если текушая строка соответствует формату то начинаем расчет
            sscanf(line, "%2d.%2d.%2d", &current.day, &current.month, &current.year); // Извлекаем число, месяц и год сохраняя их в структуру Date current
            // fprintf(writeInFile, "%2d.%2d.%2d\n", current.day, current.month, current.year); // Записываем форматированный вывод c точностью в 2 символа в файл writeInFile (не открыт!)
            // printf(" Current date: %.2d.%.2d.%.2d\n", current.day, current.month, current.year);
            // printf("Previous date: %.2d.%.2d.%.2d\n", previous.day, previous.month, previous.year);

            if((current.day != previous.day) || (current.month != previous.month) || (current.year != previous.year)) {
                if(count > 0)
                    printf("%.2d.%.2d.%.2d [%d-раз]\n", previous.day, previous.month, previous.year, count);
                previous.day = current.day;
                previous.month = current.month;
                previous.year = current.year;
                count = 1;
            }
            else
            count++;
        }
        // else
        //     printf("Строка n°%d не соответствует шаблону\n", lineNum);
    }

    printf("%.2d.%.2d.%.2d [%d-раз]\n", current.day, current.month, current.year, count); // Последний из дней

    fclose(file);
    // fclose(writeInFile);
}

// Функция вычисляющая количество дней в месяце в которых отправлялись сообщения
void daysInMonth(char *argv1) {
    char line[100];
    int count = 0;
    int daysInMonth = 0;

    Date current = {0};
    Date previous = {0};

    FILE *file;
    file = openFile(argv1, "r");

    while(fgets(line, 100, file)) {
        if(matchPattern(line) == true) {
            sscanf(line, "%2d.%2d.%2d", &current.day, &current.month, &current.year);

            if((current.month != previous.month) || (current.year != previous.year)) {
                if(count > 0)
                    printf("%.2d.%.2d [%d-сообщейний]\n", previous.month, previous.year, daysInMonth);
                previous.day = current.day;
                previous.month = current.month;
                previous.year = current.year;
                count = 1;
                daysInMonth = 1;
            }
            if(current.month == previous.month)
                daysInMonth++;
            else
                count++;
        }
    }

    // printf("%.2d.%.2d [%d-сообщейний]\n", previous.month, previous.year, daysInMonth);

    fclose(file);
}
