#include "server.h"

ST_accountsDB_t Account[255] = { {35250, "6562935742272051"} ,{682131,"8212649688233098"} ,{1000.5,"5187564009458612"} };
int acc_no = 0;
ST_transaction_t Transactions[255] = { 0 };
int trans_no = 0;

EN_transState_t recieveTransactionData(ST_transaction_t* transData)
{
	if (isValidAccount(&transData->cardHolderData) == ACCOUNT_NOT_FOUND)
	{
		return DECLINED_STOLEN_CARD;
	}
	if (isAmountAvailable(&transData->terminalData)== LOW_BALANCE)
	{
		return DECLINED_INSUFFECIENT_FUND;
	}
	if (saveTransaction(&transData)==SAVING_FAILED)
	{
		return INTERNAL_SERVER_ERROR;
	}
	Account[acc_no].balance -= transData->terminalData.transAmount;
	return APPROVED;
}

EN_serverError_t isValidAccount(ST_cardData_t* cardData)
{


	unsigned char y[20] = {'0'};
	int z = 0;
	for (int j = 0; cardData->primaryAccountNumber[j] != NULL; j++)
	{
		if (cardData->primaryAccountNumber[j] == ' ')
		{
			continue;
		}
		y[z] = cardData->primaryAccountNumber[j];
		z++;
	}

	int i;
	for (i = 0; i < 255; i++)
	{
		int x;
		x = strcmp(y, Account[i].primaryAccountNumber);
		acc_no = i;
		if (x == 0)
		{
		return OK3;
		}
	}
	return ACCOUNT_NOT_FOUND;
}

EN_serverError_t isAmountAvailable(ST_terminalData_t* termData)
{
	if (termData->transAmount < Account[acc_no].balance)
	{
		return OK3;
	}
	
	return LOW_BALANCE;
}

EN_serverError_t saveTransaction(ST_transaction_t* transData)
{
	transData->transactionSequenceNumber = trans_no;
	if (transData->transactionSequenceNumber < 255)
	{
		Transactions[transData->transactionSequenceNumber].cardHolderData = transData->cardHolderData;
		Transactions[transData->transactionSequenceNumber].terminalData = transData->terminalData;
		Transactions[transData->transactionSequenceNumber].transState = transData->transState;
		Transactions[transData->transactionSequenceNumber].transactionSequenceNumber = transData->transactionSequenceNumber;

		trans_no++;
		return OK3;
	}
	return SAVING_FAILED;
}

//EN_serverError_t getTransaction(unsigned int transactionSequenceNumber, ST_transaction_t* transData){}
