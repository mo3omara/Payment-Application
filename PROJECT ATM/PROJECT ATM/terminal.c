#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS
#include "terminal.h"

EN_terminalError_t getTransactionDate(ST_terminalData_t* termData)
{
    time_t currenttime;
    time(&currenttime);
    struct tm* mytime = localtime(&currenttime);
   // printf("%i/%i/%i", mytime->tm_mday, mytime->tm_mon + 1, mytime->tm_year + 1900);

    strftime(termData->transactionDate, 11, "%d/%m/%Y", mytime);

    return OK2;
}

EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData)
{
    int cmon = (cardData.cardExpirationDate[0] - '0') * 10 + (cardData.cardExpirationDate[1] - '0');
    int cyear = (cardData.cardExpirationDate[3] - '0') * 10 + (cardData.cardExpirationDate[4] - '0');
    int tmon = (termData.transactionDate[3] - '0') * 10 + (termData.transactionDate[4] - '0');
    int tyear = (termData.transactionDate[8] - '0') * 10 + (termData.transactionDate[9] - '0');

    if (tyear > cyear)
    {
        return EXPIRED_CARD;
    }
    else if (tyear == cyear && tmon > cmon)
    {
        return EXPIRED_CARD;
    }

    return OK2;
}

EN_terminalError_t isValidCardPAN(ST_cardData_t* cardData)
{
    int  x, counter = -1, sum = 0;

    for (int i = 0; cardData->primaryAccountNumber[i] != NULL; i++)
    {
       
        if (cardData->primaryAccountNumber[i] == ' ')
        {
            continue;
        }

        x = cardData->primaryAccountNumber[i]-'0';

        if (x <= 9)
        {
           // printf("%i", cardData->primaryAccountNumber[i] - '0');
            //printf("%i\n", x);
            counter++;
            if (counter % 2 == 0)
            {
                x = x * 2;
                if (x > 9)
                {
                    int y;        //x=12
                    y = x % 10;   //y=2
                    x -= y;       //x=10
                    x /= 10;      //x=1
                    x += y;       //x=3
                }
            }
          // printf("%i\n", x);
            sum += x;
        }
    }
    //printf("\n%i\n", sum);
    if (sum % 10 != 0)
    {
        return INVALID_CARD;
    }
    return OK2;
}

EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData)
{
    printf("Please enter the Transaction Amount: ");
    scanf_s("%f", &termData->transAmount);

    if (termData->transAmount<=0)
    {
        return INVALID_AMOUNT;
    }

    return OK2;
}


EN_terminalError_t setMaxAmount(ST_terminalData_t* termData)
{

    termData->maxTransAmount = 10000;
    printf("Max Transaction amount is 10000\n");

    return OK2;
}

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData) 
{
    if (termData->transAmount > termData->maxTransAmount)
    {
        return EXCEED_MAX_AMOUNT;
    }
    return OK2;

}