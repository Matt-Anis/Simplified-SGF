//
// Created by Toshiba on 12/12/2024.
//

#include "allocationTable.h"

//writes the allocation table to the first bloc of the file
void writeAllocationTable(FILE *file, TallocationTable allocationTable){
  char *block = (char *)malloc(allocationTable.blocSize);

  fclose(file);
  fopen(file, "rb+");
  rewind(file);
  memcpy(block, &allocationTable, sizeof(allocationTable.tableSize));
  fwrite(block, sizeof(allocationTable.tableSize), 1, file);

  free(block);
}

void initTable(TallocationTable *table, int blocNumber, int blockingFactor){
  table = malloc(sizeof(TallocationTable) + blocNumber * sizeof(Telement));
//  table->blocSize = blocNumber * sizeof(Ttransaction);
  table->blocSize = blockingFactor * sizeof(file);
  table->array[0].occupied = true;
  for(int i = 1; i < blocNumber; i++){
    table->array[i].occupied = false;
  }

  table->tableSize = sizeof(TallocationTable) + blocNumber * sizeof(Telement);
}