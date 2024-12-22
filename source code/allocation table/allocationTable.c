//
// Created by Toshiba on 12/12/2024.
//

#include "allocationTable.h"


TallocationTable initTable(int blocNumber, int blockingFactor){
  TallocationTable table;

  table.blocTotal = blocNumber;
  table.blockingFactor = blockingFactor;

  table.array = malloc( blocNumber * sizeof(Tbloc));
  if (table.array == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

  table.blocSize = blockingFactor * sizeof(Ttransaction);

  table.array[0].occupied = true;
  for(int i = 1; i < blocNumber; i++){
    table.array[i].occupied = false;
  }

  table.tableSize = sizeof(TallocationTable) + blocNumber * sizeof(Tbloc);

  return table;
}


//writes the allocation table to the first bloc of the file
void writeAllocationTable(FILE *file, TallocationTable allocationTable){
  char *block = (char *)malloc(allocationTable.blocSize);

//  fclose(file);
//  fopen(file, "rb+");
  rewind(file);
  memcpy(block, &allocationTable, sizeof(allocationTable.tableSize));
  fwrite(block, sizeof(allocationTable.tableSize), 1, file);
  rewind(file);
  free(block);
}

TallocationTable getAllocationTable(FILE *file){
  TallocationTable allocationTable;
  size_t tableSize;
  rewind(file);
  fread(&tableSize, sizeof(size_t), 1, file);
  rewind(file);
  fread(&allocationTable, sizeof(tableSize), 1, file);

  return allocationTable;
}

bool isAvailable_contiguous(TallocationTable table, int size){
  int temp;
  size++; //car on prend en compte le bloc allouer au meta donne
  if (size > table.blocTotal - 1) return false;

  for(int i = 1; i < table.blocTotal ; i++){
    while (!table.array[i].occupied && i < table.blocTotal ){
      temp --;
    }
    if(temp == 0 ){
      return true;
    } else {
      temp = size;
    }
  }
  return false;
}

bool isCompactable_file(TallocationTable table, int size){
  int available_count = 0;
  size++; //car en prend en considration le bloc des meta donnes
  for (int i = 1 ; i < table.blocTotal ; i++){
    if(!table.array[i].occupied){
      available_count ++;
    }
  }

  if (size <= available_count){
    return true;
  }
  return false;
}


void freeFile(TallocationTable *allocationTable, FILE *file){
  for (int i = 1 ; i < allocationTable->blocTotal ; i++){
    allocationTable->array[i].occupied = false;
  }
  writeAllocationTable(file, *allocationTable);
}

