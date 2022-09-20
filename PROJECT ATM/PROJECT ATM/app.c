#include "app.h"

void appStart()
{
	ST_cardData_t c1;
	ST_terminalData_t  t1;
	
	printf("\t\t CARD \t\t\n\n");
	
	if (getCardHolderName(&c1) == OK1)
	{
		printf("Correct Name\n\n");
	}
	else
	{
		printf("Incorrect Name\n\n");
		return;
	}
	
	if (getCardExpiryDate(&c1) == OK1)
	{
		printf("Correct Expiry Date\n\n");
	}
	else
	{
		printf("Incorrect Expiry Date\n\n");
		return;
	}
	
	if (getCardPAN(&c1) == OK1)
	{
		printf("Correct PAN\n\n");
	}
	else
	{
		printf("Incorrect PAN\n\n");
		return;
	}
	
	printf("\t\t Terminal \t\t\n\n");

	getTransactionDate(&t1);
	printf("Transaction Date: %s\n", t1.transactionDate);
	
	if (isCardExpired(c1, t1) == OK2)
	{
		printf("Card is not expired\n");
	}
	else
	{
		printf("card is expired\n");
		return;
	}
	
	if (isValidCardPAN(&c1) == OK2)
	{
		printf("Valid Card\n\n");
	}
	else
	{
		printf("Invalid Card\n\n");
		return;
	}

	setMaxAmount(&t1);

	if (getTransactionAmount(&t1) != OK2)
	{
		printf("Invalid Amount\n");
		return;
	}
	
	if (isBelowMaxAmount(&t1) == OK2)
	{
		printf("%f is a Valid Amount\n\n", t1.transAmount);

	}
	else
	{
		printf("Invalid Amount, Max Amount is %f\n", t1.maxTransAmount);
		return;
	}

	printf("\t\t Server \t\t\n\n");


	ST_transaction_t tr1;
	tr1.cardHolderData = c1;
	tr1.terminalData = t1;

	switch (recieveTransactionData(&tr1)) 
	{
		case DECLINED_INSUFFECIENT_FUND: printf("Insufficient Funds\n"); return; 
		case DECLINED_STOLEN_CARD: printf("Stolen Card\n");	return;
		case INTERNAL_SERVER_ERROR: printf("Transaction Couldn't be Saved\n"); return;
		case APPROVED: printf("Transaction is done successfully\n"); return;
	}
	
}


	


