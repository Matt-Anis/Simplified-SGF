// Ajout des nouvelles fonctions d'interface utilisateur
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdint.h>
#include <windows.h>


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
    bool occupied; // this indicates later if the bloc is used or not, and will also be used for logical suppression
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

    transaction.occupied = true;
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

Ttransaction createTransaction(char ID[37], //of 36 char
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
    transaction.occupied = true;

    return transaction;
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


enum Globale_organization {
    contiguous,
    linked
};

enum Internal_organization {
    ordered,
    unordered
};


typedef struct metaData {
    int file_size_bloc;
    char file_name[50]; // maximum size of the file is 50 chars
    int file_size_record;
    int first_bloc_adress;
    enum Globale_organization globale_organization;
    enum Internal_organization internal_organization;
    int *address_array;
} metaData;

typedef struct TallocationTable {
    // vue que la taille de la table est variable est elle est imperatif pour manipuler la MS, sa taille est placer au
    // element de toute la table
    // array est un vecteur de Tbloc, qui contient si un bloc est occuper, si oui elle indique sont type (meta donne/ donne)
    size_t tableSize, bufferSize;
    Tbloc *array;
    int blockingFactor, blocTotal;
} TallocationTable;

/// this function is for finding the size of the dynamic size of the buffer

size_t find_buffer_size(int blocking_factor) {
    size_t MS_bloc_size = blocking_factor * sizeof(Ttransaction);
    size_t size_of_transaction = sizeof(Ttransaction);
    size_t size_of_buffer = MS_bloc_size - 1;

    while (MS_bloc_size % size_of_buffer != 0 || size_of_buffer % size_of_transaction != 0) {
        size_of_buffer--;
    }

    return size_of_buffer;
}

TallocationTable initTable(int blocNumber, int blockingFactor) {
    TallocationTable table;

    table.blocTotal = blocNumber;
    table.blockingFactor = blockingFactor;

    table.array = malloc(blocNumber * sizeof(Tbloc));
    if (table.array == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    // table.bufferSize = blockingFactor * sizeof(Ttransaction);

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

    table.bufferSize = find_buffer_size(blockingFactor);

    return table;
}

void print_table(TallocationTable table) {
    printf("\ntable size %do, buffer size: %do, blocking factor %d record by MS bloc\n", table.tableSize,
           table.bufferSize, table.blockingFactor);
    for (int i = 0; i < table.blocTotal; i++) {
        printf("%d ", table.array[i].occupied);
    }
}


void writeMetadata(TallocationTable table, FILE *file, metaData meta_data, int position) {
    size_t bloc_size = table.blockingFactor * sizeof(Ttransaction);

    fseek(file, position * bloc_size, SEEK_SET);
    size_t meta_data_size = sizeof(meta_data.file_name) + sizeof(int) * 3 + sizeof(enum Globale_organization) + sizeof(
                                enum Internal_organization)
                            + sizeof(int) * meta_data.file_size_bloc;

    if (meta_data_size > bloc_size) {
        fprintf(stderr, "Error: Allocation table too large to fit in one block.\n");
        exit(EXIT_FAILURE);
    }

    unsigned char buffer[bloc_size];

    // Alternatively, if VLAs are not available or the size is too large:
    // unsigned char *buffer = malloc(bloc_size);
    // if (buffer == NULL) {
    //     perror("malloc failed");
    //     exit(EXIT_FAILURE);
    // }
    // memset(buffer, 0, bloc_size);

    size_t bytes_written = 0;

    // Use memcpy to copy the data into the buffer
    memcpy(buffer + bytes_written, &meta_data.file_size_bloc, sizeof(int));
    bytes_written += sizeof(int);
    memcpy(buffer + bytes_written, &meta_data.file_name, sizeof(meta_data.file_name));
    bytes_written += sizeof(meta_data.file_name);
    memcpy(buffer + bytes_written, &meta_data.file_size_record, sizeof(int));
    bytes_written += sizeof(int);
    memcpy(buffer + bytes_written, &meta_data.first_bloc_adress, sizeof(int));
    bytes_written += sizeof(int);
    memcpy(buffer + bytes_written, &meta_data.globale_organization, sizeof(enum Globale_organization));
    bytes_written += sizeof(enum Globale_organization);
    memcpy(buffer + bytes_written, &meta_data.internal_organization, sizeof(enum Internal_organization));
    bytes_written += sizeof(enum Internal_organization);
    memcpy(buffer + bytes_written, meta_data.address_array, sizeof(int) * meta_data.file_size_bloc);
    bytes_written += sizeof(int) * meta_data.file_size_bloc;

    // Padding (using memset is more efficient)
    memset(buffer + bytes_written, 0, bloc_size - bytes_written);

    // Now write the entire buffer to the file in one operation
    size_t write_count = fwrite(buffer, 1, bloc_size, file);
    if (write_count != bloc_size) {
        perror("Error writing allocation table to file");
        exit(EXIT_FAILURE);
    }
}

metaData getMetaData(FILE *file, TallocationTable table, int position) {
    int size_in_blocs;
    metaData meta_data;
    size_t bloc_size = table.blockingFactor * sizeof(Ttransaction);


    fseek(file, position * bloc_size, SEEK_SET);

    fread(&meta_data.file_size_bloc, sizeof(int), 1, file);
    fread(&meta_data.file_name, sizeof(meta_data.file_name), 1, file);
    fread(&meta_data.file_size_record, sizeof(int), 1, file);
    fread(&meta_data.first_bloc_adress, sizeof(int), 1, file);
    fread(&meta_data.globale_organization, sizeof(enum Globale_organization), 1, file);
    fread(&meta_data.internal_organization, sizeof(enum Internal_organization), 1, file);

    meta_data.address_array = malloc(sizeof(int) * meta_data.file_size_bloc);
    fread(meta_data.address_array, sizeof(int) * meta_data.file_size_bloc, 1, file);

    return meta_data;
}

//writes the allocation table to the first bloc of the file
void writeAllocationTable(FILE *file, TallocationTable table) {
    fseek(file, 0, SEEK_SET); // Ensure we're at the beginning of the file

    size_t bloc_size = table.blockingFactor * sizeof(Ttransaction);
    size_t table_data_size = sizeof(size_t) * 2 + sizeof(int) * 2 + sizeof(Tbloc) * table.blocTotal;

    if (table_data_size > bloc_size) {
        fprintf(stderr, "Error: Allocation table too large to fit in one block.\n");
        exit(EXIT_FAILURE);
    }

    // Use a VLA (Variable Length Array) if your compiler supports it (C99 and later).
    // This is generally preferred to malloc for small, stack-allocated buffers.
    unsigned char buffer[bloc_size];

    // Alternatively, if VLAs are not available or the size is too large:
    // unsigned char *buffer = malloc(bloc_size);
    // if (buffer == NULL) {
    //     perror("malloc failed");
    //     exit(EXIT_FAILURE);
    // }
    // memset(buffer, 0, bloc_size);

    size_t bytes_written = 0;

    // Use memcpy to copy the data into the buffer
    memcpy(buffer + bytes_written, &table.tableSize, sizeof(size_t));
    bytes_written += sizeof(size_t);
    memcpy(buffer + bytes_written, &table.bufferSize, sizeof(size_t));
    bytes_written += sizeof(size_t);
    memcpy(buffer + bytes_written, &table.blockingFactor, sizeof(int));
    bytes_written += sizeof(int);
    memcpy(buffer + bytes_written, &table.blocTotal, sizeof(int));
    bytes_written += sizeof(int);
    memcpy(buffer + bytes_written, table.array, sizeof(Tbloc) * table.blocTotal);
    bytes_written += sizeof(Tbloc) * table.blocTotal;

    // Padding (using memset is more efficient)
    memset(buffer + bytes_written, 0, bloc_size - bytes_written);

    // Now write the entire buffer to the file in one operation
    size_t write_count = fwrite(buffer, 1, bloc_size, file);
    if (write_count != bloc_size) {
        perror("Error writing allocation table to file");
        exit(EXIT_FAILURE);
    }

    // if you used malloc you'd have to free it here
    // free(buffer);
}

TallocationTable getAllocationTable(FILE *file) {

    fseek(file, 0, SEEK_SET);
    TallocationTable table;

    // Read the tableSize first
    if (fread(&table.tableSize, sizeof(size_t), 1, file) != 1) {
        fprintf(stderr, "Error reading tableSize.\n");
        exit(EXIT_FAILURE);
    }
    fseek(file, 0, SEEK_SET); //reset the pointer to read all the table

    if (fread(&table.tableSize, sizeof(size_t), 1, file) != 1 ||
        fread(&table.bufferSize, sizeof(size_t), 1, file) != 1 ||
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

/// this part is for the manipulation of the MS

/// we'll set that the metaData files are always stored in the end of the MS

bool isAvailable_linked(TallocationTable table, int size) {
    int available = 0;
    for (int i = 1; i < table.blocTotal; i++) {
        // we start from 1 because bloc 1 is always occupied by the allocation table
        if (!table.array[i].occupied) {
            available++;
        }
    }

    return available >= (size + 1);
}

bool isAvailable_contiguous(TallocationTable table, int size) {
    int available = 0;

    if (size + 1 > table.blocTotal - 1) return false;

    for (int i = 1; i < table.blocTotal; i++) {
        while (!table.array[i].occupied && i < table.blocTotal) {
            available++;
            i++;
        }
        if (available > size) {
            return true;
        } else if (available == size) {
            for (int j = i; j < table.blocTotal; j++) {
                if (!table.array[j].occupied) {
                    return true;
                }
            }
            return false; // car il n'a pas trouver d'espace pour le fichier de meta donne
        } else {
            available = 0;
        }
    }
    return false;
}


bool isCompactable(TallocationTable table) {
    /// il va verifier si un bloc est fichier si oui il verifier le bloc suivant si le bloc suivant est vide il marque
    /// gap = true
    /// il verifier si le bloc suivant est occuper, si oui et le bloc suivant est un fichier alors return true
    /// si le bloc suiavnt occuper est metaDonne alors il return false, car il est deja compacter
    bool gap = false;

    for (int i = 1; i < table.blocTotal; i++) {
        if (!table.array[i].occupied) {
            gap = true;
        } else if (gap && table.array[i].occupied && table.array[i].type == f) {
            return true;
        } else if (gap && table.array[i].type == m) {
            return false; // car les meta donne sont toujour placee a la fin
        }
    }
    return false;
}


// attention on doit d'abbor verifier si l'espace est disponible avant d'appeler cette fonction !!
int create_file(FILE *file, char file_name[50], enum Globale_organization globale_organization,
                enum Internal_organization internal_organization,
                int file_size_in_blocs, TallocationTable table) {
    // returns the position of the metaData file
    int meta_data_adress;
    size_t bloc_size = table.blocTotal * sizeof(Ttransaction);
    metaData meta_data;
    strcpy(meta_data.file_name, file_name);
    meta_data.file_size_bloc = file_size_in_blocs;


    // on va a la fin de la MS et on cherche depuis la fin un bloc libre pour y stocker le fichier de metadonne
    for (int i = table.blocTotal - 1; i >= 1; i--) {
        if (!table.array[i].occupied) {
            meta_data_adress = i; // ici on sauvgarde l'address du fichier de metadonne
            break;
        }
    }
    // on met a jour la table d'allocation pour indiquer que le bloc alloue au fihcier de metadonne est occuper
    // et que ce bloc est de type metadonne
    table.array[meta_data_adress].occupied = true;
    table.array[meta_data_adress].type = m;

    meta_data.file_size_record = 0; // initialement le fichier est vide
    meta_data.internal_organization = internal_organization;

    if (globale_organization == contiguous) {
        // dans le cas ou l'organisation est contigue
        int available = 0; // initialise le nombre de bloc contigue disponible a 0
        for (int i = 1; i < table.blocTotal; i++) {
            // a partir de 1 car l'address 0 est pour la table d'allocation
            if (!table.array[i].occupied) {
                available++;
            } else {
                available = 0;
                // si le bloc n'est pas disponible alors, le compteur de bloc disponible est renitialiser a 0
            }

            if (available == file_size_in_blocs) {
                // si le nombre de bloc contigue dispo atteint la taille du fichier alors on sauvegarde l'address
                // du premier bloc, et o sort de la  boucle
                meta_data.first_bloc_adress = i - available + 1;
                break;
            }
        }

        // on met a jour la table d'allocation, on marquent les blocs alloues au fichier comme occupes
        // le type de ces bloc est  aussi marquer comme fichier
        for (int i = meta_data.first_bloc_adress; i < file_size_in_blocs + meta_data.first_bloc_adress; i++) {
            table.array[i].occupied = true;
            table.array[i].type = f;
        }

        // on allouent le vecteur d'address des blocs de fichier du fichier de meta Donne
        meta_data.address_array = malloc(file_size_in_blocs * sizeof(int));

        for (int i = 0; i < file_size_in_blocs; i++) {
            meta_data.address_array[i] = meta_data.first_bloc_adress + i;
        }

        // on met a jour la table d'allocation dans la Memoire secondaire
        writeAllocationTable(file, table);

        // on met a jour le fichier de metadonne dans la memoire secondare
        writeMetadata(table, file, meta_data, meta_data_adress);

        return meta_data_adress;
    } else if (globale_organization == linked) {
        // on alloue l'espace

        meta_data.address_array = malloc(file_size_in_blocs * sizeof(int));

        // tant qu'on a pas fini de touver une adrress pour  les bloc du fichier
        int temp = file_size_in_blocs;
        int j = 0; // compteur pour parcourir le vecyeur d'adderess de meta donne
        for (int i = 1; temp != 0; i++) {
            if (!table.array[i].occupied) {
                if (temp == file_size_in_blocs) {
                    // si c'est le premier bloc a etre enregistrer on va mettre a jour le champs
                    // meta_data.first_bloc_adress
                    meta_data.first_bloc_adress = i;
                }
                //decrement le nombre de bloc restant
                temp--;

                // met a jour la table d'allocation
                table.array[i].occupied = true;
                table.array[i].type = f;

                // met a jour le vecteur de meta donne
                meta_data.address_array[j] = i;
                j++;
            }
        }
        writeAllocationTable(file, table);
        writeMetadata(table, file, meta_data, meta_data_adress);

        return meta_data_adress;
    }
}


///
///this par is for the disk structure and its functions
///
///


TallocationTable initDisk(FILE *file, int blocsNumber, int blockingFactor, char name[]) {
    TallocationTable allocationTable;

    file = fopen(name, "wb+");
    allocationTable = initTable(blocsNumber, blockingFactor);
    // print_table(allocationTable);
    writeAllocationTable(file, allocationTable);

    Ttransaction emptyTransaction = {
        .occupied = false,
        .ID = "",
        .senderName = "",
        .receiverName = "",
        .senderAccountNo = 0,
        .receiverAccountNo = 0,
        .success = false,
        .errorCode = "",
        .transactionNumber = 0,
        .amount = 0,
        .time = {0, 0, 0, 0, 0, 0} // year, month, day, hour, minute, second
    };

    // deplacer le curseur:
    fseek(file, blockingFactor * sizeof(Ttransaction), SEEK_SET);

    // Écrire la transaction vide
    for (int j = 0; j < blocsNumber - 1; j++) {
        for (int i = 0; i < allocationTable.blockingFactor; i++) {
            if (fwrite(&emptyTransaction, sizeof(Ttransaction), 1, file) != 1) {
                perror("Error writing to file");
                fclose(file);
                exit(EXIT_FAILURE);
            }
        }
    }
    return allocationTable;
}


void print_bloc(bool isEmpty, char fileName[50], int numberOfRecords) {
    if (isEmpty && numberOfRecords != -1) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN); // Green text
        printf("# # # # # # # # #\n");
        printf("#               #\n");
        printf("#               #\n");
        printf("#               # ----> Libre\n");
        printf("#               #\n");
        printf("#               #\n");
        printf("# # # # # # # # #\n");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        printf("------------------\n");
    } else if (isEmpty && numberOfRecords == -1) {
        printf("##################\n");
        printf("##################\n");
        printf("##################\n");
        printf("################## ----> meta data file of: %s \n", fileName);
        printf("##################\n");
        printf("##################\n");
        printf("##################\n");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        printf("------------------\n");
    } else {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN); //yellow
        printf("##################\n");
        printf("##################\n");
        printf("##################\n");
        printf("################## ----> %s, %d records\n", fileName, numberOfRecords);
        printf("##################\n");
        printf("##################\n");
        printf("##################\n");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        printf("------------------\n");
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    // Reset to default (Important!)
}

void printMS(FILE *file, TallocationTable table) {
    struct info {
        bool occupied;
        int Nb;
        char fileName[50];
        enum bloc_type type;
    };
    print_table(table);
    printf("\n");
    struct info *array;
    int *metaArray; // vecteur qui represent l'address des fichier de meta donne
    int size = 0; // le nombre de fichier de meta donne


    // aloue l'espace pour le vecteur final qui va servire de guide pour afficher la MS
    array = malloc(sizeof(struct info) * table.blocTotal);


    // indique que la premiere case est resreve pour la table
    array[0].occupied = true;
    array[0].type = t;

    // copie l'etat des bloc dans le nouveau vecteurs
    for (int i = 1; i < table.blocTotal; i++) {
        array[i].occupied = table.array[i].occupied;
        if (array[i].occupied) {
            array[i].type = table.array[i].type;
        }
    }

    // on met a jour le vecteur a afficher
    for (int i = table.blocTotal - 1; i > 0; i--) {
        // si le bloc est reserver pour un fichier meta donne on parcour le vecreur d'address des meta donnes et
        // on affecte le nom, et le nombre d'enregistrement dans le fichier a la case correspondente dans array
        if (table.array[i].occupied && table.array[i].type == m) {
            // on obtient meta donne
            metaData meta_data = getMetaData(file, table, i);
            array[i].type = m;
            strcpy(array[i].fileName, meta_data.file_name);

            // on copie le nom du fichier depuis meta donne
            char name[50];
            strcpy(name, meta_data.file_name);
            int recordsNb = meta_data.file_size_record;
            for (int j = 0; j < meta_data.file_size_bloc; j++) {
                // met a jour la case correspondent
                strcpy(array[meta_data.address_array[j]].fileName, name);
                array[meta_data.address_array[j]].Nb = recordsNb % table.blockingFactor;
                array->type = f;
                recordsNb -= recordsNb % table.blockingFactor;
            }
        }
    }

    // affichage
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE); //blue
    printf("##################\n");
    printf("##################\n");
    printf("##################\n");
    printf("################## ----> Allocation table\n");
    printf("##################\n");
    printf("##################\n");
    printf("##################\n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    printf("------------------\n");

    for (int i = 1; i < table.blocTotal; i++) {
        if (array[i].occupied && array[i].type == f) {
            print_bloc(false, array[i].fileName, array[i].Nb);
        } else if (array[i].occupied && array[i].type == m) {
            print_bloc(true, array[i].fileName, -1);
        } else {
            print_bloc(true, "", 0);
        }
    }

    free(array);
}


// Structure pour stocker les statistiques du système
typedef struct SystemStats {
    int totalBlocks;
    int freeBlocks;
    int usedBlocks;
    int fragmentedBlocks;
} SystemStats;

// Fonction pour obtenir les statistiques actuelles du système
SystemStats getSystemStats(TallocationTable table) {
    SystemStats stats = {0, 0, 0, 0};
    bool foundUsed = false;

    stats.totalBlocks = table.blocTotal;

    for (int i = 0; i < table.blocTotal; i++) {
        if (!table.array[i].occupied) {
            stats.freeBlocks++;
            if (foundUsed) {
                stats.fragmentedBlocks++;
            }
        } else {
            stats.usedBlocks++;
            foundUsed = true;
        }
    }

    return stats;
}

// Fonction pour vérifier si un nom de fichier existe déjà
bool fileExists(FILE *file, TallocationTable table, const char *filename) {
    for (int i = 0; i < table.blocTotal; i++) {
        if (table.array[i].occupied && table.array[i].type == m) {
            metaData meta = getMetaData(file, table, i);
            if (strcmp(meta.file_name, filename) == 0) {
                return true;
            }
            free(meta.address_array); // Libération de la mémoire
        }
    }
    return false;
}

// Fonction pour rechercher un fichier par son nom et retourner son meta_data_address
int findFileByName(FILE *file, TallocationTable table, const char *filename) {
    for (int i = 0; i < table.blocTotal; i++) {
        if (table.array[i].occupied && table.array[i].type == m) {
            metaData meta = getMetaData(file, table, i);
            if (strcmp(meta.file_name, filename) == 0) {
                free(meta.address_array);
                return i;
            }
            free(meta.address_array);
        }
    }
    return -1;
}

// Fonction pour renommer un fichier
bool renameFile(FILE *file, TallocationTable table, const char *oldName, const char *newName) {
    if (fileExists(file, table, newName)) {
        return false; // Le nouveau nom existe déjà
    }

    int metaAddress = findFileByName(file, table, oldName);
    if (metaAddress == -1) {
        return false; // Ancien fichier non trouvé
    }

    metaData meta = getMetaData(file, table, metaAddress);
    strncpy(meta.file_name, newName, 49);
    meta.file_name[49] = '\0';

    writeMetadata(table, file, meta, metaAddress);
    free(meta.address_array);
    return true;
}

// Fonction pour supprimer un fichier
bool deleteFile(FILE *file, TallocationTable *table, const char *filename) {
    int metaAddress = findFileByName(file, *table, filename);
    if (metaAddress == -1) {
        return false;
    }

    TallocationTable table2;
    table2 = *table;
    metaData meta = getMetaData(file, table2, metaAddress);

    // Libérer tous les blocs du fichier
    for (int i = 0; i < meta.file_size_bloc; i++) {
        table->array[meta.address_array[i]].occupied = false;
        table->array[meta.address_array[i]].type = u;
    }

    // Libérer le bloc de métadonnées
    table->array[metaAddress].occupied = false;
    table->array[metaAddress].type = u;

    writeAllocationTable(file, *table);
    free(meta.address_array);
    return true;
}

// Structure pour stocker le résultat d'une recherche
typedef struct SearchResult {
    bool found;
    int blockNumber;
    int offset;
    Ttransaction transaction;
} SearchResult;

// Fonction pour rechercher un enregistrement par ID
SearchResult searchTransactionById(FILE *file, TallocationTable table, const char *filename, const char *id) {
    SearchResult result = {false, -1, -1};
    int metaAddress = findFileByName(file, table, filename);

    if (metaAddress == -1) {
        return result;
    }

    metaData meta = getMetaData(file, table, metaAddress);
    size_t bloc_size = table.blockingFactor * sizeof(Ttransaction);
    Ttransaction *buffer = malloc(bloc_size);

    for (int i = 0; i < meta.file_size_bloc; i++) {
        int blockAddr = meta.address_array[i];
        fseek(file, blockAddr * bloc_size, SEEK_SET);
        fread(buffer, bloc_size, 1, file);

        for (int j = 0; j < table.blockingFactor; j++) {
            if (buffer[j].occupied && strcmp(buffer[j].ID, id) == 0) {
                result.found = true;
                result.blockNumber = blockAddr;
                result.offset = j;
                result.transaction = buffer[j];
                free(buffer);
                free(meta.address_array);
                return result;
            }
        }
    }

    free(buffer);
    free(meta.address_array);
    return result;
}

// Fonction pour insérer un enregistrement
// bool insertTransaction(FILE *file, TallocationTable *table, const char *filename, Ttransaction transaction) {
//     int metaAddress = findFileByName(file, *table, filename);
//     if (metaAddress == -1) {
//         return false;
//     }
//
//
//     TallocationTable table2 = *table;
//     metaData meta = getMetaData(file, table2, metaAddress);
//     size_t bloc_size = table->blockingFactor * sizeof(Ttransaction);
//     Ttransaction *buffer = malloc(bloc_size);
//
//     // Pour organisation interne ordonnée
//     if (meta.internal_organization == ordered) {
//         // TODO: Implémenter l'insertion ordonnée
//     } else {
//         // Insertion non ordonnée - chercher le premier espace libre
//         for (int i = 0; i < meta.file_size_bloc; i++) {
//             int blockAddr = meta.address_array[i];
//             fseek(file, blockAddr * bloc_size, SEEK_SET);
//             fread(buffer, bloc_size, 1, file);
//
//             for (int j = 0; j < table->blockingFactor; j++) {
//                 if (!buffer[j].occupied) {
//                     buffer[j] = transaction;
//                     buffer[j].occupied = true;
//
//                     fseek(file, blockAddr * bloc_size, SEEK_SET);
//                     fwrite(buffer, bloc_size, 1, file);
//
//                     meta.file_size_record++;
//                     writeMetadata(*table, file, meta, metaAddress);
//
//                     free(buffer);
//                     free(meta.address_array);
//                     return true;
//                 }
//             }
//         }
//     }
//
//     free(buffer);
//     free(meta.address_array);
//     return false; // Pas d'espace trouvé
// }
bool insertTransaction(FILE *file, TallocationTable *table, const char *filename, Ttransaction transaction) {
    int metaAddress = findFileByName(file, *table, filename);
    if (metaAddress == -1) {
        return false; // Fichier non trouvé
    }

    TallocationTable table2 = *table;
    metaData meta = getMetaData(file, table2, metaAddress);
    size_t bloc_size = table->blockingFactor * sizeof(Ttransaction);
    Ttransaction *buffer = malloc(bloc_size);
    if (!buffer) {
        free(meta.address_array);
        return false; // Erreur d'allocation mémoire
    }

    // Pour organisation interne ordonnée
    if (meta.internal_organization == ordered) {
        for (int i = 0; i < meta.file_size_bloc; i++) {
            int blockAddr = meta.address_array[i];
            fseek(file, blockAddr * bloc_size, SEEK_SET);
            fread(buffer, bloc_size, 1, file);

            for (int j = 0; j < table->blockingFactor; j++) {
                if (!buffer[j].occupied || strcmp(buffer[j].ID, transaction.ID) > 0) {
                    // Décaler les transactions suivantes pour faire de la place
                    for (int k = table->blockingFactor - 1; k > j; k--) {
                        buffer[k] = buffer[k - 1];
                    }
                    buffer[j] = transaction;
                    buffer[j].occupied = true;

                    fseek(file, blockAddr * bloc_size, SEEK_SET);
                    fwrite(buffer, bloc_size, 1, file);

                    meta.file_size_record++;
                    writeMetadata(*table, file, meta, metaAddress);

                    free(buffer);
                    free(meta.address_array);
                    return true;
                }
            }
        }
    } else {
        // Insertion non ordonnée - chercher le premier espace libre
        for (int i = 0; i < meta.file_size_bloc; i++) {
            int blockAddr = meta.address_array[i];
            fseek(file, blockAddr * bloc_size, SEEK_SET);
            fread(buffer, bloc_size, 1, file);

            for (int j = 0; j < table->blockingFactor; j++) {
                if (!buffer[j].occupied) {
                    buffer[j] = transaction;
                    buffer[j].occupied = true;

                    fseek(file, blockAddr * bloc_size, SEEK_SET);
                    fwrite(buffer, bloc_size, 1, file);

                    meta.file_size_record++;
                    writeMetadata(*table, file, meta, metaAddress);

                    free(buffer);
                    free(meta.address_array);
                    return true;
                }
            }
        }
    }

    free(buffer);
    free(meta.address_array);
    return false; // Pas d'espace trouvé
}

void afficherFichier(FILE *file, TallocationTable table) {
    char filename[50];
    printf("Nom du fichier a afficher: ");
    fgets(filename, 50, stdin);
    filename[strcspn(filename, "\n")] = 0; // Supprimer le newline

    int metaAddress = findFileByName(file, table, filename);
    if (metaAddress == -1) {
        printf("Fichier non trouve!\n");
        return;
    }

    metaData meta = getMetaData(file, table, metaAddress);
    size_t bloc_size = table.blockingFactor * sizeof(Ttransaction);
    Ttransaction *buffer = malloc(bloc_size);
    if (!buffer) {
        free(meta.address_array);
        perror("Allocation memoire echouee");
        return;
    }

    printf("\nContenu du fichier %s:\n", filename);
    for (int i = 0; i < meta.file_size_bloc; i++) {
        int blockAddr = meta.address_array[i];
        fseek(file, blockAddr * bloc_size, SEEK_SET);
        if (fread(buffer, bloc_size, 1, file) != 1) {
            perror("Erreur de lecture du fichier");
            free(buffer);
            free(meta.address_array);
            return;
        }

        for (int j = 0; j < table.blockingFactor; j++) {
            if (buffer[j].occupied) {
                printTransaction(buffer[j]);
                printf("\n"); // Nouvelle ligne après chaque transaction
            }
        }
    }

    free(buffer);
    free(meta.address_array);
}


// Fonction pour la suppression logique
bool logicalDelete(FILE *file, TallocationTable table, const char *filename, const char *id) {
    SearchResult search = searchTransactionById(file, table, filename, id);
    if (!search.found) {
        return false;
    }

    size_t bloc_size = table.blockingFactor * sizeof(Ttransaction);
    Ttransaction *buffer = malloc(bloc_size);

    fseek(file, search.blockNumber * bloc_size, SEEK_SET);
    fread(buffer, bloc_size, 1, file);

    buffer[search.offset].occupied = false;

    fseek(file, search.blockNumber * bloc_size, SEEK_SET);
    fwrite(buffer, bloc_size, 1, file);

    free(buffer);
    return true;
}

// Fonction pour vider la MS
void clearMS(FILE *file, TallocationTable *table) {
    // Réinitialiser la table d'allocation
    for (int i = 1; i < table->blocTotal; i++) {
        table->array[i].occupied = false;
        table->array[i].type = u;
    }

    writeAllocationTable(file, *table);

    // Réécrire des blocs vides
    size_t bloc_size = table->blockingFactor * sizeof(Ttransaction);
    Ttransaction emptyTransaction = {0};

    for (int i = 1; i < table->blocTotal; i++) {
        fseek(file, i * bloc_size, SEEK_SET);
        for (int j = 0; j < table->blockingFactor; j++) {
            fwrite(&emptyTransaction, sizeof(Ttransaction), 1, file);
        }
    }
}

// fonction qui copie un fichier a une address indique
void copyFile(FILE *file, TallocationTable table, int act_pos, int dest_pos) {
    Ttransaction temp_transaction;
    Ttransaction buffer_transaction[table.blockingFactor];

    fseek(file, act_pos * table.blockingFactor * sizeof(Ttransaction), SEEK_SET);

    fread(buffer_transaction, sizeof(Ttransaction), table.blockingFactor, file);

    fseek(file, dest_pos * table.blockingFactor * sizeof(Ttransaction), SEEK_SET);
    fwrite(buffer_transaction, sizeof(Ttransaction), table.blockingFactor, file);
}

// Fonction de compactage de la MS
void compactMS(FILE *file, TallocationTable *table) {
    if (!isCompactable(*table)) {
        printf("\nfile isn't compactible!\n");
    } else {
        bool gaps[table->blocTotal];

        for (int i = 0; i < table->blocTotal; i++) {
            gaps[i] = table->array[i].occupied;
        }


        for (int i = table->blocTotal - 1; i > 1; i--) {
            if (!gaps[i] && gaps[i - 1] && table->array[i - 1].type == m) {
                metaData meta_data = getMetaData(file, *table, i - 1);
                writeMetadata(*table, file, meta_data, i);
                table->array[i - 1].occupied = false;
                table->array[i - 1].type = u;
                table->array[i].type = m;
                table->array[i].occupied = true;
                gaps[i] = true;
                gaps[i - 1] = false;
            }
        }


        int address_array[table->blocTotal];
        for (int i = 1; i < table->blocTotal; i++) {
            if (table->array[i].type == m && table->array[i].occupied) {
                metaData meta_data = getMetaData(file, *table, i);
                for (int j = 0; j < meta_data.file_size_bloc; j++) {

                    address_array[meta_data.address_array[j]] = i;
                }
            }
        }

        for (int i = 1; i < table->blocTotal-1; i++) {
            if (!gaps[i] && gaps[i + 1] && table->array[i + 1].type == f) {
                metaData meta_data = getMetaData(file, *table, address_array[i + 1]);
                for (int k = 0; k < meta_data.file_size_bloc; k++) {
                    if (meta_data.address_array[k] == i + 1) {
                        meta_data.address_array[k] = i;
                        break;
                    }
                }
                copyFile(file, *table, i + 1, i);
                table->array[i + 1].occupied = false;
                table->array[i + 1].type = u;
                table->array[i].type = f;
                table->array[i].occupied = true;
                gaps[i] = true;
                gaps[i + 1] = false;
                address_array[i] = address_array[i + 1];
                writeMetadata(*table, file, meta_data, address_array[i]);
            }
        }

        writeAllocationTable(file, *table);
    }
}


bool defragmentFile(FILE *file, TallocationTable *table, const char *filename) {
    int metaAddress = findFileByName(file, *table, filename);
    if (metaAddress == -1) {
        return false;
    }

    metaData meta = getMetaData(file, *table, metaAddress);
    size_t bloc_size = table->blockingFactor * sizeof(Ttransaction);
    Ttransaction *buffer = malloc(bloc_size);
    if (!buffer) {
        free(meta.address_array);
        return false;
    }

    // Create a temporary buffer to store all valid records
    Ttransaction *temp_records = malloc(meta.file_size_record * sizeof(Ttransaction));
    if (!temp_records) {
        free(buffer);
        free(meta.address_array);
        return false;
    }

    int valid_count = 0;

    // Read all valid records
    for (int i = 0; i < meta.file_size_bloc; i++) {
        fseek(file, meta.address_array[i] * bloc_size, SEEK_SET);
        fread(buffer, bloc_size, 1, file);

        for (int j = 0; j < table->blockingFactor; j++) {
            if (buffer[j].occupied) {
                temp_records[valid_count++] = buffer[j];
            }
        }
    }

    // Update the number of records
    meta.file_size_record = valid_count;

    // Rearrange the records
    int record_index = 0;
    for (int i = 0; i < meta.file_size_bloc && record_index < valid_count; i++) {
        // Initialize the buffer with empty records
        for (int j = 0; j < table->blockingFactor; j++) {
            buffer[j].occupied = false;
        }

        // Fill the block with valid records
        for (int j = 0; j < table->blockingFactor && record_index < valid_count; j++) {
            buffer[j] = temp_records[record_index++];
        }

        // Write the block
        fseek(file, meta.address_array[i] * bloc_size, SEEK_SET);
        fwrite(buffer, bloc_size, 1, file);
    }

    // Free memory
    free(buffer);
    free(temp_records);

    // Update metadata
    writeMetadata(*table, file, meta, metaAddress);
    free(meta.address_array);

    return true;
}

// Update the menu to include the defragmentation option

void mainMenu() {
    int choice;
    FILE *file = NULL;
    TallocationTable table;
    char filename[50];
    char id[37];
    SystemStats stats;
    bool initialized = false;

    do {
        printf("\nMenu Principal:\n");
        printf("1. Initialiser la memoire secondaire\n");
        printf("2. Creer un fichier\n");
        printf("3. Afficher l'etat de la MS\n");
        printf("4. Afficher les metadonnees\n");
        printf("5. Rechercher un enregistrement\n");
        printf("6. Inserer un enregistrement\n");
        printf("7. Supprimer un enregistrement\n");
        printf("8. Defragmenter un fichier\n");
        printf("9. Supprimer un fichier\n");
        printf("10. Renommer un fichier\n");
        printf("11. Compactage de la MS\n");
        printf("12. Vider la MS\n");
        printf("13. afficher un fichier\n");
        printf("0. Quitter\n");
        printf("Votre choix: ");

        scanf("%d", &choice);
        getchar(); // Clear input buffer

        if (!initialized && choice != 1 && choice != 0) {
            printf("Vous devez d'abord initialiser la memoire secondaire!\n");
            continue;
        }

        switch (choice) {
            case 1: {
                if (initialized) {
                    printf("La memoire secondaire est deja initialisee!\n");
                    break;
                }
                char msName[50];
                int blocNumber, blockingFactor;

                printf("Nom du fichier MS: ");
                fgets(msName, 50, stdin);
                msName[strcspn(msName, "\n")] = 0;

                printf("Nombre de blocs: ");
                scanf("%d", &blocNumber);

                printf("Facteur de blocage: ");
                scanf("%d", &blockingFactor);

                table = initDisk(file, blocNumber, blockingFactor, msName);
                file = fopen(msName, "rb+");
                if (!file) {
                    printf("Erreur lors de l'initialisation!\n");
                    break;
                }
                initialized = true;
                printf("Memoire secondaire initialisee avec succes!\n");
                break;
            }

            case 2: {
                char fileName[50];
                int fileSize;
                int orgChoice;
                enum Globale_organization globOrg;
                enum Internal_organization intOrg;

                printf("Nom du fichier: ");
                fgets(fileName, 50, stdin);
                fileName[strcspn(fileName, "\n")] = 0;

                if (fileExists(file, table, fileName)) {
                    printf("Ce nom de fichier existe deja!\n");
                    break;
                }

                printf("Taille en blocs: ");
                scanf("%d", &fileSize);

                printf("Organisation globale (1: Contigue, 2: Non-contigue): ");
                scanf("%d", &orgChoice);
                globOrg = (orgChoice == 1) ? contiguous : linked;

                printf("Organisation interne (1: Ordonnee, 2: Non-ordonnee): ");
                scanf("%d", &orgChoice);
                intOrg = (orgChoice == 1) ? ordered : unordered;

                if (globOrg == contiguous && !isAvailable_contiguous(table, fileSize)) {
                    printf("Espace contigu non disponible!\n");
                    break;
                } else if (globOrg == linked && !isAvailable_linked(table, fileSize)) {
                    printf("Espace non contigu non disponible!\n");
                    break;
                }

                int metaAddress = create_file(file, fileName, globOrg, intOrg, fileSize, table);
                if (metaAddress != -1) {
                    printf("Fichier cree avec succes!\n");
                    table = getAllocationTable(file);
                }
                break;
            }

            case 3: {
                printMS(file, table);
                break;
            }

            case 4: {
                printf("Nom du fichier: ");
                fgets(filename, 50, stdin);
                filename[strcspn(filename, "\n")] = 0;

                int metaAddress = findFileByName(file, table, filename);
                if (metaAddress == -1) {
                    printf("Fichier non trouve!\n");
                    break;
                }

                metaData meta = getMetaData(file, table, metaAddress);
                printf("\nMetadonnees du fichier %s:\n", filename);
                printf("Taille en blocs: %d\n", meta.file_size_bloc);
                printf("Nombre d'enregistrements: %d\n", meta.file_size_record);
                printf("Premier bloc: %d\n", meta.first_bloc_adress);
                printf("Organisation globale: %s\n",
                       meta.globale_organization == contiguous ? "Contigue" : "Non-contigue");
                printf("Organisation interne: %s\n",
                       meta.internal_organization == ordered ? "Ordonnee" : "Non-ordonnee");
                printf("Adresses des blocs: ");
                for (int i = 0; i < meta.file_size_bloc; i++) {
                    printf("%d ", meta.address_array[i]);
                }
                printf("\n");
                free(meta.address_array);
                break;
            }

            case 5: {
                printf("Nom du fichier: ");
                fgets(filename, 50, stdin);
                filename[strcspn(filename, "\n")] = 0;

                printf("ID de la transaction: ");
                fgets(id, 37, stdin);
                id[strcspn(id, "\n")] = 0;

                SearchResult result = searchTransactionById(file, table, filename, id);
                if (result.found) {
                    printf("\nTransaction trouvee:\n");
                    printf("Bloc: %d, Offset: %d\n", result.blockNumber, result.offset);
                    printTransaction(result.transaction);
                    printf("\n");
                } else {
                    printf("Transaction non trouvee!\n");
                }
                break;
            }

            case 6: {
                printf("Nom du fichier: ");
                fgets(filename, 50, stdin);
                filename[strcspn(filename, "\n")] = 0;

                Ttransaction newTrans = randomTransaction();
                if (insertTransaction(file, &table, filename, newTrans)) {
                    printf("Transaction inseree avec succes!\n");
                    table = getAllocationTable(file);
                } else {
                    printf("Erreur lors de l'insertion!\n");
                }
                break;
            }

            case 7: {
                printf("Nom du fichier: ");
                fgets(filename, 50, stdin);
                filename[strcspn(filename, "\n")] = 0;

                printf("ID de la transaction: ");
                fgets(id, 37, stdin);
                id[strcspn(id, "\n")] = 0;

                if (logicalDelete(file, table, filename, id)) {
                    printf("Transaction supprimee avec succes!\n");
                } else {
                    printf("Transaction non trouvee!\n");
                }
                break;
            }

            case 8: {
                printf("Nom du fichier: ");
                fgets(filename, 50, stdin);
                filename[strcspn(filename, "\n")] = 0;

                if (defragmentFile(file, &table, filename)) {
                    printf("Fichier defragmente avec succes!\n");
                } else {
                    printf("Erreur lors de la defragmentation!\n");
                }
                break;
            }

            case 9: {
                printf("Nom du fichier a supprimer: ");
                fgets(filename, 50, stdin);
                filename[strcspn(filename, "\n")] = 0;

                if (deleteFile(file, &table, filename)) {
                    printf("Fichier supprime avec succes!\n");
                } else {
                    printf("Fichier non trouve!\n");
                }
                break;
            }

            case 10: {
                char newName[50];
                printf("Ancien nom: ");
                fgets(filename, 50, stdin);
                filename[strcspn(filename, "\n")] = 0;

                printf("Nouveau nom: ");
                fgets(newName, 50, stdin);
                newName[strcspn(newName, "\n")] = 0;

                if (renameFile(file, table, filename, newName)) {
                    printf("Fichier renomme avec succes!\n");
                } else {
                    printf("Erreur lors du renommage!\n");
                }
                break;
            }

            case 11: {
                if (isCompactable(table)) {
                    compactMS(file, &table);
                    printf("Compactage effectue avec succes.\n");
                } else {
                    printf("Compactage non necessaire.\n");
                }
                break;
            }

            case 12: {
                char confirm;
                printf("Etes-vous sur de vouloir vider la MS? (o/n): ");
                scanf(" %c", &confirm);
                if (confirm == 'o' || confirm == 'O') {
                    clearMS(file, &table);
                    printf("MS videe avec succes!\n");
                }
                break;
            }

            case 13: {
                afficherFichier(file, table);
                break;
            }

            case 0: {
                if (file) {
                    fclose(file);
                }
                printf("Au revoir!\n");
                break;
            }

            default:
                printf("Choix invalide!\n");
        }
    } while (choice != 0);
}

int main() {
    srand(time(NULL)); // Initialize random seed
    mainMenu();
    return 0;
}
