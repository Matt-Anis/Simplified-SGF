//
// Created by Toshiba on 12/12/2024.
//

#include "disk.h"

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


void initDisk(disk *disk, int blocsNumber, int blockingFactor, char name[]){
  FILE *file;
  TallocationTable allocationTable;


  checkName(name);
  file = fopen(name, "wb");
  initTable(&allocationTable, blocsNumber, blockingFactor);
  writeAllocationTable(file, allocationTable);

  }