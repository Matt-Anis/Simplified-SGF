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

enum bloc_type{
  m, //meta data
  f, //file
  };

typedef struct Tbloc{
  bool occupied;
  enum bloc_type type;
  } Tbloc;

typedef struct TallocationTable {
  // vue que la taille de la table est variable est elle est imperatif pour manipuler la MS, sa taille est placer au
  // element de toute la table
  // array est un vecteur de Tbloc, qui contient si un bloc est occuper, si oui elle indique sont type (meta donne/ donne)
  size_t tableSize, blocSize;
  Tbloc *array;
  int blockingFactor, blocTotal;
} TallocationTable;

TallocationTable initTable(int blocNumber, int blockingFactor);
void writeAllocationTable(FILE *file, TallocationTable allocationTable);
TallocationTable getAllocationTable(FILE *file);
bool isAvailable_contiguous(TallocationTable table, int size);
bool isCompactable_file(TallocationTable table, int size);
void freeFile(TallocationTable *allocationTable, FILE *file);
#endif //ALLOCATIONTABLE_H
