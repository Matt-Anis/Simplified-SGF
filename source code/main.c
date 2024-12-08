#include "transaction.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>



int main(void) {
    srand(time(NULL));
    Ttransaction transaction = randomTransaction();
    printTransaction(transaction);

    return 0;
}
