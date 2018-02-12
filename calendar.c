#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int monthDays[] = {31,29,31,30,31,30,31,31,30,31,30,31};
    int months[] = {1,2,3,4,5,6,7,8,9,10,11,12};
    int i, j;

    for(i=0; i<12; i++) {
        for(j=0; j<monthDays[i]; j++)
            printf("%.2d.%.2d.13\n", j+1, months[i]);
    }

    return 0;
}
