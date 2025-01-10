# Simplified SGF

This project is a simplified implementation of a Secondary Global File (SGF) system in C. It provides functionalities for managing files, transactions, and metadata on a secondary storage device.

## Features

*   Initialize secondary storage
*   Create files with contiguous or linked allocation
*   Display the state of the secondary storage
*   Display file metadata
*   Search for transactions by ID
*   Insert transactions
*   Logically delete transactions
*   Defragment files
*   Delete files
*   Rename files
*   Compact the secondary storage
*   Clear the secondary storage

## System Structure

### `Ttransaction`

A structure representing a transaction with the following fields:

*   `occupied` (bool): Indicates if the block is used or not
*   `ID` (char[37]): Unique identifier for the transaction
*   `senderName` (char[20]): Name of the sender
*   `receiverName` (char[20]): Name of the receiver
*   `senderAccountNo` (unsigned long long): Account number of the sender
*   `receiverAccountNo` (unsigned long long): Account number of the receiver
*   `success` (bool): Indicates if the transaction was successful
*   `errorCode` (char[35]): Error code if the transaction failed
*   `transactionNumber` (unsigned long long): Number of the transaction
*   `amount` (int): Amount of the transaction
*   `time` (`Ttime`): Time of the transaction

### `TallocationTable`

A structure representing the allocation table of the secondary storage with the following fields:

*   `tableSize` (size_t): Size of the table
*   `bufferSize` (size_t): Size of the buffer
*   `blockingFactor` (int): Blocking factor
*   `blocTotal` (int): Total number of blocks
*   `array` (`Tbloc*`): Array of blocks

### `metaData`

A structure representing the metadata of a file with the following fields:

*   `file_size_bloc` (int): Size of the file in blocks
*   `file_name` (char[50]): Name of the file
*   `file_size_record` (int): Size of the file in records
*   `first_bloc_adress` (int): Address of the first block
*   `globale_organization` (`enum Globale_organization`): Global organization (contiguous or linked)
*   `internal_organization` (`enum Internal_organization`): Internal organization (ordered or unordered)
*   `address_array` (`int*`): Array of block addresses

## Functions

### Initialization

*   `TallocationTable initDisk(FILE *file, int blocsNumber, int blockingFactor, char name[])`: Initialize the secondary storage.

### File Management

*   `int create_file(FILE *file, char file_name[50], enum Globale_organization globale_organization, enum Internal_organization internal_organization, int file_size_in_blocs, TallocationTable table)`: Create a new file.
*   `bool fileExists(FILE *file, TallocationTable table, const char *filename)`: Check if a file exists.
*   `int findFileByName(FILE *file, TallocationTable table, const char *filename)`: Find a file by name.
*   `bool renameFile(FILE *file, TallocationTable table, const char *oldName, const char *newName)`: Rename a file.
*   `bool deleteFile(FILE *file, TallocationTable *table, const char *filename)`: Delete a file.
*   `void afficherFichier(FILE *file, TallocationTable table)`: Display the contents of a file.
*   `bool defragmentFile(FILE *file, TallocationTable *table, const char *filename)`: Defragment a file.

### Transaction Management

*   `Ttransaction randomTransaction()`: Generate a random transaction.
*   `SearchResult searchTransactionById(FILE *file, TallocationTable table, const char *filename, const char *id)`: Search for a transaction by ID.
*   `bool insertTransaction(FILE *file, TallocationTable *table, const char *filename, Ttransaction transaction)`: Insert a transaction.
*   `bool logicalDelete(FILE *file, TallocationTable table, const char *filename, const char *id)`: Logically delete a transaction.

### Storage Management

*   `size_t find_buffer_size(int blocking_factor)`: Find the buffer size.
*   `TallocationTable initTable(int blocNumber, int blockingFactor)`: Initialize the allocation table.
*   `void writeMetadata(TallocationTable table, FILE *file, metaData meta_data, int position)`: Write metadata to a file.
*   `metaData getMetaData(FILE *file, TallocationTable table, int position)`: Get metadata from a file.
*   `void writeAllocationTable(FILE *file, TallocationTable table)`: Write the allocation table to a file.
*   `TallocationTable getAllocationTable(FILE *file)`: Get the allocation table from a file.
*   `bool isAvailable_contiguous(TallocationTable table, int size)`: Check if contiguous space is available.
*   `bool isAvailable_linked(TallocationTable table, int size)`: Check if linked space is available.
*   `bool isCompactable(TallocationTable table)`: Check if the storage is compactable.
*   `void compactMS(FILE *file, TallocationTable *table)`: Compact the storage.
*   `void clearMS(FILE *file, TallocationTable *table)`: Clear the storage.
*   `void copyFile(FILE *file, TallocationTable table, int act_pos, int dest_pos)`: Copy a file.
*   `SystemStats getSystemStats(TallocationTable table)`: Get system statistics.
*   `void printMS(FILE *file, TallocationTable table)`: Print the state of the secondary storage.
*   `void print_table(TallocationTable table)`: Print the allocation table.

### Utility Functions

*   `void generateUUID(char *uuid)`: Generate a unique ID.
*   `void generateRandomName(char *name)`: Generate a random name.
*   `const char *generateErrorCode()`: Generate a random error code.
*   `void printTransaction(Ttransaction transaction)`: Print a transaction.
*   `void print_bloc(bool isEmpty, char fileName[50], int numberOfRecords)`: Print a block.

## Usage

The program provides a main menu with options to perform various operations on the secondary storage. To run the program, execute the `main` function.
