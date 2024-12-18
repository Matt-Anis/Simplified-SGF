// #include "transaction.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


typedef struct Tallocation_table {
    int numberOfFiles;
    int BlocBlockingFactor;
    int array[];
} Tallocation_table;

void initAllocationTable(Tallocation_table *table, int numberOfFiles){

    table->numberOfFiles = numberOfFiles;

}

void checkName(char *name) {
    int len = strlen(name);
    int i = 0;
    char temp[len + 1]; // Allocate enough space including the null-terminator
    while (name[i] != '.' && name[i] != '\0') {
        temp[i] = name[i];
        i++;
    }
    temp[i] = '\0';
    strcpy(name, temp);
}

int main(void) {
    char name[] = "test.txt";
    checkName(name);  // Pass 'name' directly (not &name)
    printf("%s\n", name); // Output will be "test"
    return 0;
}