/*
 * app.c
 *
 *  Created on: AUG 04, 2022
 *      Author: Nabil Gamal
 */
#include "app.h"
#include "card.h"
#include "terminal.h"
#include "server.h"

#include <stdio.h>
#include <string.h>
void appStart(void)
{

	ST_transaction_t transData;
	ST_transaction_t* transactionPtr = &transData;
//ST_Fill_Zero(Arr_transactionsDB_t, DataBase_Max_SIZE);
	ST_terminalData_t MaxAmount;
	ST_terminalData_t* PTR_MaxAmount = &MaxAmount;

	u8   isValidTransDate;
	EN_terminalError_t transaction_amount;
	EN_terminalError_t transaction_max_amount;
	EN_transState_t received_transaction;
	u8 Case='y';
	u32	AnotherTransaction = 'y';

	 isValidDATE(&(transData.terminalData));
	 while(AnotherTransaction=='y')
     {
	 get_card_info(&transData);
	 if(isCardExpired(&(transactionPtr->cardHolderData), &(transactionPtr->terminalData)) == EXPIRED_CARD)
     {
         printf("expired card \n");
         printf("thank you\n");
     }
     else
     {
         transaction_max_amount=setMaxAmount(&(transData.terminalData));

             while(transaction_max_amount==INVALID_MAX_AMOUNT)
             {
                 transaction_max_amount=setMaxAmount(&(transData.terminalData));
             }
             transaction_amount=getTransactionAmount(&(transData.terminalData));

                 while(transaction_amount==INVALID_AMOUNT)
                 {
                       transaction_amount=getTransactionAmount(&(transData.terminalData));
                 }
                 if(isBelowMaxAmount(&(transData.terminalData))==EXCEED_MAX_AMOUNT)
                 {
                     printf("exceed max amount");
                     printf("thank you");
                 }

                 if(isBelowMaxAmount(&(transData.terminalData))==OK_SER)
                {
	received_transaction=recieveTransactionData(transactionPtr);
	if(received_transaction==no_balance)
    {
        printf("low balance your current balance is %0.2f \n",Arr_accountsDB_t[flag_check].balance);
    }
    else if(received_transaction==DECLINED_STOLEN_CARD)
    {
           printf("this card is stolen");
           printf("\nThe Card has been withdrawn because it was blocked by the owner\nContact your bank for more info\n");
    }
    else if(received_transaction==card_not_founded)
    {
        printf("account not found\n");
    }
    else if(received_transaction==INTERNAL_SERVER_ERROR)
    {
       printf("Internal Server Error\n");
    }

	else if(received_transaction==APPROVED)
    {
         printf("Succeeded\n");
        printf("PAN: %s\t\tCard Name - ID: %s\t\t new Balance: %0.2f  your sequence is %d\n", Arr_accountsDB_t[flag_check].primaryAccountNumber, Arr_accountsDB_t[flag_check].CardNameHolder, Arr_accountsDB_t[flag_check].balance,sequence-1);
        printf("Do you want to get transaction in details? (Yes/No) : ");
				scanf(" %c", &Case);
				switch (Case)
				{
				case 'y':;
					u32 uint32Sequence;
					printf("\nEnter the sequence: ");
					scanf("%d", &uint32Sequence);
					getTransaction(uint32Sequence, Arr_transactionsDB_t);
					break;

				case 'n':
					printf("\n\nAnother transaction? (y/n): ");
					scanf(" %c", &AnotherTransaction);
					break;

				default:
					break;
				}
    }
                }
}
     }
}
