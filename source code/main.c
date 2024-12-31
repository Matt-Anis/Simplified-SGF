#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdint.h>


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

typedef struct file {
    int next;
    Ttransaction array[];
} file;


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
    for (int j = 0; j < blocsNumber -1 ; j++) {
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


void main() {
    system("color 0A"); // Sets background to black and text to light green
    printf("This text is light green on black.\n");

    system("color 07"); // Sets background to black and text to white (default)

    printf("This text is back to the default color.\n");
    return 0;
}
