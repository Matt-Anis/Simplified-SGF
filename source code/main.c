#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


///
///this part is for the Transaction structure and its functions
///

typedef struct Ttime {
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
} Ttime;

typedef struct Ttransaction {
    // bool occupied; // this indicates later if the bloc is used or not, and will also be used for logical suppression
    int next;
    // if the global organization of a file is a linked list, this will indicate the index of the next element (next bloc in the file)
    char ID[37]; //of 36 char
    char senderName[20];
    char receiverName[20];
    unsigned long long senderAccountNo;
    unsigned long long receiverAccountNo;
    bool success;
    char errorCode[35];
    unsigned long long transactionNumber;
    int amount;
    Ttime time;
} Ttransaction;

// a list of names, to automatically fill the files
const char *names[] = {
    "Donovan Archer",
    "Kadence Rosario",
    "Jedidiah Simmons",
    "Reagan Arroyo",
    "Alberto Espinoza",
    "Lucille Matthews",
    "Preston West",
    "Remi Douglas",
    "Derek Dyer",
    "Estrella Campbell",
    "Christopher Farrell",
    "Kassidy Dean",
    "Ronan Stafford",
    "Bridget Butler",
    "Ryder Deleon",
    "Gabrielle Bryant",
    "Jonah Khan",
    "Mabel Shaffer",
    "Dexter Li",
    "Paige Spears",
    "Ameer Villegas",
    "Jessie Levy",
    "Harold Costa",
    "Robin Holt",
    "Niko Meza",
    "Rosa Diaz",
    "Nathan Burch",
    "Freyja Dillon",
    "Alvin Durham",
    "Tiffany Bowman",
    "Francisco Walsh",
    "Leia Gillespie",
    "Forest Garrison",
    "Cadence Perez",
    "Owen Mayo",
    "Aarya Burch",
    "Gerald Hampton",
    "Leona Kirby",
    "Tony Campos",
    "Sutton Phillips",
    "Andrew Reynolds",
    "Isabelle Bell",
    "Emmett McLean",
    "Sky Haley",
    "Leif Elliott",
    "Noelle Hurst",
    "Neil Hicks",
    "Alina Burch",
    "Gerald Hodge",
    "Coraline McDonald",
    "Calvin Hughes",
    "Samantha McCullough",
    "Briar Hogan",
    "Kathryn Harmon",
    "Roberto Greer",
    "Reina Spence",
    "Cillian Brennan",
    "Elodie Atkinson",
    "Duke Hurley",
    "Rylan Lawson",
    "Lane English",
    "Kelly Huynh",
    "Layton Sandoval",
    "Elsie Pacheco",
    "Erik Gonzales",
    "Hadley Wolfe",
    "Donovan Strong",
    "Margo Shaffer",
    "Dexter Mack",
    "Nadia Jordan",
    "Sawyer Klein",
    "Elianna Gross",
    "Quinn Medrano",
    "Halle Ryan",
    "Timothy Ashley",
    "Khalani Peterson",
    "Santiago Kirby",
    "Skyla Villarreal",
    "Nikolai McGee",
    "Kayleigh Nava",
    "Stefan Hopkins",
    "Gabriela Dillon",
    "Alvin Manning",
    "Jennifer Calhoun",
    "Gary Gilmore",
    "Chanel Pope",
    "Gunnar Santos",
    "Alana Bryant",
    "Jonah Leblanc",
    "Novalee Walls",
    "Larry Jaramillo",
    "Guadalupe Short",
    "Hezekiah Fischer",
    "Maci Guevara",
    "Tommy Combs",
    "Irene Ashley",
    "Kylen Campbell",
    "Addison Bates",
    "Ellis Meyers",
    "Leyla Washington",
    "Juan Singh"
};

// an array of possible error codes of a transaction
const char *errorCodes[] = {
    "ERR001: Insufficient Funds",
    "ERR002: Account Not Found",
    "ERR003: Transaction Limit Exceeded",
    "ERR004: Unauthorized Access",
    "ERR005: Invalid Account Number",
    "ERR006: Invalid Amount",
    "ERR007: System Maintenance",
    "ERR008: Timeout Error",
    "ERR009: Invalid Transaction Type",
};

//to generate unique IDs, the function generates random IDs in format long with a very long length to unsure uniqueness
void generateUUID(char *uuid) {
    const char *chars = "0123456789abcdef";
    // srand(time(NULL));
    for (int i = 0; i < 36; i++) {
        if (i == 8 || i == 13 || i == 18 || i == 23) {
            uuid[i] = '-';
        } else {
            uuid[i] = chars[rand() % 16];
        }
    }
    uuid[36] = '\0';
}

// Function to generate a random name of exactly 20 characters
void generateRandomName(char *name) {
    int randomIndex = rand() % (sizeof(names) / sizeof(names[0]));
    strncpy(name, names[randomIndex], 20);
    int len = strlen(name);
    for (int i = len; i < 20; i++) {
        name[i] = ' '; // Fill with spaces
    }
    name[19] = '\0'; // Null-terminate
}


const char *generateErrorCode() {
    int randomIndex = rand() % (sizeof(errorCodes) / sizeof(errorCodes[0]));

    static char result[36];

    strcpy(result, errorCodes[randomIndex]);

    result[35] = '\0';

    return result;
}

Ttransaction randomTransaction() {
    Ttransaction transaction;
    generateUUID(transaction.ID);

    generateRandomName(transaction.senderName);
    generateRandomName(transaction.receiverName);

    transaction.senderAccountNo = (rand() % 9000000000LL) + 1000000000LL;
    transaction.receiverAccountNo = (rand() % 9000000000LL) + 1000000000LL;

    transaction.transactionNumber = (rand() % 999999999LL) + 1000000000LL;

    transaction.time.year = 2024;
    transaction.time.month = (rand() % 12) + 1;
    if (transaction.time.month == 2) {
        transaction.time.day = (rand() % 28) + 1;
    } else {
        transaction.time.day = (rand() % 30) + 1;
    }
    transaction.time.hour = (rand() % 23) + 1;
    transaction.time.minute = (rand() % 59) + 1;
    transaction.time.second = (rand() % 59) + 1;

    transaction.amount = rand() % 1000000 + 1000;

    transaction.success = (rand() % 100) < 80; // to make the chance of success of a transaction 80%
    if (transaction.success) {
        strcpy(transaction.errorCode, "success");
    } else {
        strcpy(transaction.errorCode, generateErrorCode());
    }

    return transaction;
}

void printTransaction(Ttransaction transaction) {
    printf("| %s ", transaction.ID);
    printf("| %s ", transaction.senderName);
    printf("| %s ", transaction.receiverName);
    printf("| %llu ", transaction.senderAccountNo);
    printf("| %llu ", transaction.receiverAccountNo);
    printf("| %d/%d/%d\t%d:%d:%d ", transaction.time.day, transaction.time.month, transaction.time.year,
           transaction.time.hour, transaction.time.minute, transaction.time.second);
    printf("| %d ", transaction.amount);
    printf("| %s ", transaction.errorCode);
    printf("| %llu |", transaction.transactionNumber);
}

void createTransaction(char ID[37], //of 36 char
                       char senderName[20],
                       char receiverName[20],
                       unsigned long long senderAccountNo,
                       unsigned long long receiverAccountNo,
                       bool success,
                       char errorCode[35],
                       unsigned long long transactionNumber,
                       int amount,
                       Ttime time) {
    Ttransaction transaction;
    transaction.amount = amount;
    transaction.senderAccountNo = senderAccountNo;
    transaction.receiverAccountNo = receiverAccountNo;
    transaction.success = success;
    transaction.time = time;
    strcpy(transaction.errorCode, errorCode);
    strcpy(transaction.senderName, senderName);
    strcpy(transaction.receiverName, receiverName);
    transaction.transactionNumber = transactionNumber;
}


/**
 * this part is for the struct of allocation table and its functions
 */
enum bloc_type {
    m, //meta data
    f, //file
    t, //table
    u //undetermined
};

typedef struct Tbloc {
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

TallocationTable initTable(int blocNumber, int blockingFactor) {
    TallocationTable table;

    table.blocTotal = blocNumber;
    table.blockingFactor = blockingFactor;

    table.array = malloc(blocNumber * sizeof(Tbloc));
    if (table.array == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    table.blocSize = blockingFactor * sizeof(Ttransaction);

    table.array[0].occupied = true;
    table.array[0].type = t;
    for (int i = 1; i < blocNumber; i++) {
        table.array[i].occupied = false;
        table.array[i].type = u;
    }

    table.tableSize = sizeof(TallocationTable) + blocNumber * sizeof(Tbloc);
    // in this part we should define the size of the blocs of the file
    // la taille du bloc doit verifier ceci: taille fichier % taille bloc = 0
    // mais aussi taille bloc % taille transaction = 0
    // on l'initialise au debut a la meme taille que la taille d'un fichier a un bloc de MS --> taille = FB*sizeof(transaction)

    size_t MS_blocSize = blockingFactor * sizeof(Ttransaction);
    size_t blocSize = MS_blocSize - 1;
    while (MS_blocSize % blocSize != 0 && blocSize % sizeof(Ttransaction) != 0) {
        blocSize--;
    }
    return table;
}

void print_table(TallocationTable table) {
    printf("table size %do, file bloc size: %do, blocking factor %d record by MS bloc\n", table.tableSize,
           table.blocSize, table.blockingFactor);
    for (int i = 0; i < table.blocTotal; i++) {
        printf("%d ", table.array[i].occupied);
    }
}

//writes the allocation table to the first bloc of the file
void writeAllocationTable(FILE *file, TallocationTable table) {

    fseek(file, 0 , SEEK_SET);
    size_t table_data_size = sizeof(size_t) * 2 + sizeof(int) * 2 + sizeof(Tbloc) * table.blocTotal;

    if (table_data_size > table.blocSize) {
        fprintf(stderr, "Error: Allocation table too large to fit in one block.\n");
        exit(EXIT_FAILURE); // Or handle the error differently
    }

    unsigned char padding[table.blocSize];
    memset(padding, 0, table.blocSize); // Initialize padding with zeros

    size_t bytes_written = 0;

    bytes_written += fwrite(&table.tableSize, sizeof(size_t), 1, file);
    bytes_written += fwrite(&table.blocSize, sizeof(size_t), 1, file);
    bytes_written += fwrite(&table.blockingFactor, sizeof(int), 1, file);
    bytes_written += fwrite(&table.blocTotal, sizeof(int), 1, file);
    bytes_written += fwrite(table.array, sizeof(Tbloc), table.blocTotal, file);

    // Calculate remaining space and add padding
    size_t remaining_in_block = table.blocSize - bytes_written;
    if (remaining_in_block > 0) {
        fwrite(padding, 1, remaining_in_block, file);
    }
}

TallocationTable getAllocationTable(FILE *file) {
    fseek(file, 0 , SEEK_SET);
    TallocationTable table;

    // Read the tableSize first
    if (fread(&table.tableSize, sizeof(size_t), 1, file) != 1) {
        fprintf(stderr, "Error reading tableSize.\n");
        exit(EXIT_FAILURE);
    }
    fseek(file, 0, SEEK_SET); //reset the pointer to read all the table

    if (fread(&table.tableSize, sizeof(size_t), 1, file) != 1 ||
        fread(&table.blocSize, sizeof(size_t), 1, file) != 1 ||
        fread(&table.blockingFactor, sizeof(int), 1, file) != 1 ||
        fread(&table.blocTotal, sizeof(int), 1, file) != 1) {
        fprintf(stderr, "Error reading table header.\n");
        exit(EXIT_FAILURE);
        }

    table.array = malloc(table.blocTotal * sizeof(Tbloc));
    if (table.array == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    if (fread(table.array, sizeof(Tbloc), table.blocTotal, file) != table.blocTotal) {
        fprintf(stderr, "Error reading table data.\n");
        free(table.array);
        exit(EXIT_FAILURE);
    }

    return table;
}

bool isAvailable_contiguous(TallocationTable table, int size) {
    int temp;
    size++; //car on prend en compte le bloc allouer au meta donne
    if (size > table.blocTotal - 1) return false;

    for (int i = 1; i < table.blocTotal; i++) {
        while (!table.array[i].occupied && i < table.blocTotal) {
            temp--;
        }
        if (temp == 0) {
            return true;
        } else {
            temp = size;
        }
    }
    return false;
}

bool isCompactable_file(TallocationTable table, int size) {
    int available_count = 0;
    size++; //car en prend en considration le bloc des meta donnes
    for (int i = 1; i < table.blocTotal; i++) {
        if (!table.array[i].occupied) {
            available_count++;
        }
    }

    if (size <= available_count) {
        return true;
    }
    return false;
}


void freeFile(TallocationTable *allocationTable, FILE *file) {
    for (int i = 1; i < allocationTable->blocTotal; i++) {
        allocationTable->array[i].occupied = false;
    }
    writeAllocationTable(file, *allocationTable);
}


///
///this par is for the disk structure and its functions
///
///

typedef struct file {
    int next;
    Ttransaction array[];
} file;

// char *checkName(char *name) {
//     int len = strlen(name);
//     char *temp = malloc(len + 1); // Allocate memory for the new string
//     if (temp == NULL) {
//         return NULL; // Handle memory allocation failure
//     }
//
//     int i = 0;
//     while (name[i] != '.' && name[i] != '\0') {
//         temp[i] = name[i];
//         i++;
//     }
//     strcat(temp, ".bin");
//     temp[i+3] = '\0'; // Null-terminate the string
//
//     return temp;
// }

void initDisk(FILE *file, int blocsNumber, int blockingFactor, char name[]) {
    TallocationTable allocationTable, table2;

    // char *fileName = checkName(name);
    printf("File name: %s\n", name);
    file = fopen(name, "wb+");
    allocationTable = initTable(blocsNumber, blockingFactor);
    // print_table(allocationTable);
    writeAllocationTable(file, allocationTable);
    fseek(file, 0, SEEK_SET);
    size_t tableSize;
    fread(&tableSize, sizeof(size_t), 1, file);
    // fseek(file, 0, SEEK_SET);
    // fread(&table2, sizeof(allocationTable), 1, file);
    // print_table(table2);
}


typedef struct test {
    char name[50];
    int number;
} test;

void main() {
    FILE *file;
    TallocationTable table2;
    // initDisk(file, 5, 134, "test.bin");
    file = fopen("test.bin", "rb+");
    table2 = getAllocationTable(file);
    printf("\ncopied table:\n");
    print_table(table2);
    printf("size of Ttransaction %lld", sizeof(Ttransaction));
}
