//
// Created by Toshiba on 12/8/2024.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "transaction.h"


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

// Define an array of possible error codes of a transaction
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
