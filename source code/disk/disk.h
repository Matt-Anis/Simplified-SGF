//
// Created by Toshiba on 12/12/2024.
//
#include<stdio.h>
#include<string.h>
#include "../allocation table/allocationTable.h"
#include "../transaction/transaction.h"
#ifndef DISK_H
#define DISK_H


typedef struct file{
  int next;
  Ttransaction array[];
} file;


typedef struct disk {
  int BlocsNumber;
  int BlockingFactor;
} disk;

void initDisk(disk *disk, int blocsNumber, int blockingFactor, char name[]);
#endif //DISK_H
