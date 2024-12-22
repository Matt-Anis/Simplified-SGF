//
// Created by Toshiba on 12/8/2024.
//

#ifndef TRANSACTION_H
#define TRANSACTION_H
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


void generateUUID(char *uuid);
void generateRandomName(char *name);
const char *generateErrorCode();
Ttransaction randomTransaction();
void printTransaction(Ttransaction transaction);
void createTransaction(char ID[37], //of 36 char
                       char senderName[20],
                       char receiverName[20],
                       unsigned long long senderAccountNo,
                       unsigned long long receiverAccountNo,
                       bool success,
                       char errorCode[35],
                       unsigned long long transactionNumber,
                       int amount,
                       Ttime time);

#endif //TRANSACTION_H
