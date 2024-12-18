//
// Created by Toshiba on 12/12/2024.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../transaction/transaction.h"
#include "../disk/disk.h"

#ifndef ALLOCATIONTABLE_H
#define ALLOCATIONTABLE_H

enum element_types{
  m, //meta data
  f, //file
  };

typedef struct Telement{
  bool occupied;
  enum element_types type;
  } Telement;

typedef struct TallocationTable {
  size_t tableSize, blocSize;
  Telement array[];
} TallocationTable;

void initTable(TallocationTable *table, int blocNumber, int blockingFactor);
void writeAllocationTable(FILE *file, TallocationTable allocationTable);
#endif //ALLOCATIONTABLE_H
