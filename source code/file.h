//
// Created by Toshiba on 12/8/2024.
//
#include "transaction.h"

#ifndef FILE_H
#define FILE_H
typedef struct Tfile{
  int index;
  bool occupied;
  char name[20];
  
  Ttransaction *array;
  }Tfile;
#endif //FILE_H
