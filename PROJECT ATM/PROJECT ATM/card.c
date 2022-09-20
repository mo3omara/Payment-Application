#include "card.h"

EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
{
	printf("Please Enter Card Holder Name: ");
	gets (cardData->cardHolderName);

	if (strlen(cardData->cardHolderName) < 20 || cardData->cardHolderName == NULL || strlen(cardData->cardHolderName) > 24)
	{
		return WRONG_NAME;
	}

	return OK1;
}

EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData) {

	printf("Please enter the Expiry date as MM/YY: ");
	gets(cardData->cardExpirationDate);
	
	
	if (strlen(cardData->cardExpirationDate) > 5 || cardData->cardExpirationDate[2] != '/') 
	{
		return WRONG_EXP_DATE;
	}
	if (cardData->cardExpirationDate[0] - '0' != 0 && cardData->cardExpirationDate[0] - '0' != 1)
	{
		return WRONG_EXP_DATE;
	}
	if ((cardData->cardExpirationDate[0] - '0' == 1) && (cardData->cardExpirationDate[1] - '0' > 2))
	{
		return WRONG_EXP_DATE;
	}
	for (int i = 0; i<5; i++)
	{
		if (i == 2)
		{
		continue;
		}
		if ((cardData->cardExpirationDate[i] - '0' > 9 || cardData->cardExpirationDate[i] - '0' < 0))
		{
			return WRONG_EXP_DATE;
		}
	}


	return OK1;
}


EN_cardError_t getCardPAN(ST_cardData_t* cardData) 
{
	printf("Please enter the card PAN: ");
	gets(cardData->primaryAccountNumber);

	if (strlen(cardData->primaryAccountNumber) > 19 || strlen(cardData->primaryAccountNumber) < 16)
	{
		return WRONG_PAN;
	}

	int count = 0;
	for (int i = 0; cardData->primaryAccountNumber[i] != NULL ; i++)
	{
		if (cardData->primaryAccountNumber[i] == ' ')
		{
		 continue;
		}
		if (cardData->primaryAccountNumber[i] - '0' <= 9 && cardData->primaryAccountNumber[i] >= 0)
		{
			count++;
		}
	
	}
	if (count > 16)
	{
		return WRONG_PAN;
	}

	for (int i = 0; cardData->primaryAccountNumber[i] != NULL ; i++)
	{
		if (cardData->primaryAccountNumber[i] == ' ')
		{
		continue;
		}
		if (cardData->primaryAccountNumber[i] - '0' > 9 || cardData->primaryAccountNumber[i] - '0' < 0)
		{
			return WRONG_PAN;
		}
	}

	

	return OK1;
}




