/* Данная программа пропустив через себя загруженный файл, позволяет вычеслить количество одинаковых дней
 * Расчёт выводится в консоль
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h> // strlen()
#include <ctype.h>  // isdigit()

typedef enum {false, true} bool;

FILE *openFile(char *fileName, char *mode) ;
bool matchPattern(char *string);

typedef struct Date {
    int day;
    int month;
    int year;
} Date;


int main(int argc, char *argv[]) {

    int count = 0, lineNum = 0;
    char line[100];
    Date current = {0};
    Date previous = {0};

    FILE *file;
    file = openFile(argv[1], "r");

    // FILE *writeInFile;
    // writeInFile = openFile("dates.txt", "w");

    while(fgets(line, 100, file)) {
        lineNum++;
        if(matchPattern(line) == true) { // Если текушая строка соответствует формату то начинаем расчет
            sscanf(line, "%2d.%2d.%2d", &current.day, &current.month, &current.year); // Извлекаем число, месяц и год сохраняя их в структуру Date current

            // Записываем форматированный вывод c точностью в 2 символа в файл writeInFile (не открыт!)
            //fprintf(writeInFile, "%2d.%2d.%2d\n", current.day, current.month, current.year);

            //printf(" Current date: %.2d.%.2d.%.2d\n", current.day, current.month, current.year);
            //printf("Previous date: %.2d.%.2d.%.2d\n", previous.day, previous.month, previous.year);

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
    printf("%.2d.%.2d.%.2d [%d-раз]\n", current.day, current.month, current.year, count);
    printf("---Расчет завершен---\n");

    fclose(file);
    fclose(writeInFile);
    return 0;
}

// Функция открывающая имя файла в заданном режиме
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