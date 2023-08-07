#include "terminal.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include"strings.h"
#include"Std.h"
#include <time.h>

EN_terminalError_t get_the_transaction_date(ST_terminalData_t *terminal_data)
{
     /*printf("\nPlease enter the  transaction Date (DD-MM-YY): ");
    string_scan(&(terminal_data->transactionDate),ArrExDateLength);
    u8 len =string_len(&(terminal_data->transactionDate));
    u8 days=stringtoint(&(terminal_data->transactionDate[0]));
    u8 months=stringtoint(&(terminal_data->transactionDate[3]));
    printf(" days is %d   month is %d  len is %d ",days,months,len);
    if(len<10||days<=0||days>31||months<=0||months>12)

    {
        return WRONG_DATE;
    }
    else
    {
        return OK_TER;
     }*/
     // Get the current time
    time_t current_time = time(NULL);

    // Convert the time to a string using the desired format
    char date_string[20];
    strftime(date_string,20, "%d/%m/%Y", localtime(&current_time));
    u8 i;
    for(i=0;i<ArrDateLength;i++)
    {
        terminal_data->transactionDate[i]=date_string[i];
    }
    terminal_data->transactionDate[i]=0;

    // Print the date string
    printf("The current date is: %s\n",&(terminal_data->transactionDate));
}
EN_terminalError_t isCardExpired(ST_cardData_t *cardData,ST_terminalData_t *terminal_data)
{


	if (card_compare(cardData,terminal_data)==0)
	{

		return EXPIRED_CARD;

	}
	else
	{
		return OK_TER;
	}


}
EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData)
{

	printf("\nEnter Your Transaction Amount: ");
	scanf_s("%f", &(termData->transAmount));
	/*Checks if the transaction amount is valid*/
	if (termData->transAmount <= 0)
	{

		return INVALID_AMOUNT;

	}

	else
	{
		return OK_TER;

	}
}
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData)
{

	/*Checks if the transaction amount is lower than the Max Amount that is allowed to be transacted each time*/
	if (termData->transAmount > termData->maxTransAmount)
	{

		printf("\nYou Exceeded The allowed amount to be transacted\n");
		return EXCEED_MAX_AMOUNT;

	}

	else
	{
		return OK_TER;

	}

}
EN_terminalError_t setMaxAmount(ST_terminalData_t* termData)
{
	/*if (max <= 0)
	{
		return INVALID_MAX_AMOUNT;
	}

	termData->maxTransAmount = max;
	return OK_TER;*/


	printf("\nEnter Your MAX Amount: ");
	scanf_s("%f", &(termData->maxTransAmount));
	//gets(termData->maxTransAmount);

	if (termData->maxTransAmount <= 0)
	{
		return	INVALID_MAX_AMOUNT;
	}

	else
	{
		return	OK_TER;
	}
}

