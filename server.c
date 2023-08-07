#include	"server.h"
#include	<stdio.h>



#include	"strings.h"
#include"card.h"
#include"terminal.h"
#include"server.h"
#define DataBase_Max_SIZE 255
u32 flag_check = 0;
u32 sequence = 0;
ST_transaction_t Arr_transactionsDB_t[DataBase_Max_SIZE];

/*Data base for the card info {Balance, PAN, Name/ID}*/
ST_accountsDB_t Arr_accountsDB_t[DataBase_Max_SIZE] =
{
    {1000,  "1234 5678 9101 1121","Ahmed Khaled Mohammed",valid},
    {900,   "3141 5161 7181 9202","Mohammed Esmail Elsayed",valid},
    {300,   "1222 3242 5262 7282","Essam Mostafa Atyaa",valid},
    {50,    "9303 1323 3343 5363","Mohamed Abdelshafy Ayman",valid},
    {35000, "1478 5202 3669 9874","Elsayed Mostafa Hussain",stolen},
    {9000,   "1014 7852 3214 5698","Bayoumi Mohamed Khaled",stolen},
    {4500,   "1570 5780 3454 9856","mahmoud sabry abdelaziz",valid},
     {9000,  "1012 8795 3568 2568","Ahmed hussein hafez",stolen},
     {9000,  "1268 7489 2572 2568","omar sakr samir",valid}
};
EN_transState_t recieveTransactionData(ST_transaction_t* transData)
{
    u32  isValidCard;
    u32  isAvailableAmount;
    u32  isTransactionSaved;
    //  uint8   isValidTransDate;

    //  isValidTransDate = getTransactionDate(&(transData->terminalData));

    //
    //  isValidTransDate = isValidDATE(&(transData->terminalData));
    isValidCard         = isValidAccount(&(transData->cardHolderData));
    isAvailableAmount   = isAmountAvailable(&(transData->terminalData));

    /*checks if the card is stolen -> wrong ID - Date and if the card has low balance*/

    if (isValidCard ==not_founded)
    {


        return card_not_founded;
    }
    else if (isValidCard == STOLEN_CARD)
    {
          return DECLINED_STOLEN_CARD;
    }


    if (isAvailableAmount == LOW_BALANCE)
    {

        return no_balance;
    }

    else
    {

        if (flag_check <= 255)
        {
            transData->transactionSequenceNumber = sequence;
            isTransactionSaved = saveTransaction(transData);
        if (isTransactionSaved == SAVING_FAILED)
        {
            return INTERNAL_SERVER_ERROR;
        }
        else
        {

             Arr_accountsDB_t[flag_check].balance -= transData->terminalData.transAmount;

              return APPROVED;
        }


    }
    }
    /*start saving the card info*/

    /*checks if the card is valid or not and if so, print succeeded and finsh the withdraw process and decrease the balance*/

    }
EN_cardError_t get_card_info(ST_transaction_t *transaction)
{
    EN_cardError_t isValidName;
    EN_cardError_t   isValidExDate;
    EN_cardError_t  isValidPrimaryAccountNumber;
    isValidName = get_thecard_holder_name(&(transaction->cardHolderData));

    /*loop until the the user writes a valid Name - ex date - pan*/
    while (isValidName == WRONG_NAME)
    {
        isValidName=get_thecard_holder_name(&(transaction->cardHolderData));
    }
    isValidPrimaryAccountNumber = get_thecard_pan(&(transaction->cardHolderData));

    while (isValidPrimaryAccountNumber == WRONG_PAN)
    {
        isValidPrimaryAccountNumber = get_thecard_pan(&(transaction->cardHolderData));
        // isTransactionSaved = saveTransaction(cardData);

    }
     isValidExDate=get_thecard_ex_date(&(transaction->cardHolderData));

    while (isValidExDate == WRONG_EXP_DATE)
    {
        isValidExDate=get_thecard_ex_date(&(transaction->cardHolderData));
    }

}
EN_account_status isValidAccount(ST_cardData_t* cardData)
{

    u8   isTransactionSaved;

    int flag = 0;


    /*condition to check if the card details if right and valid*/
        u8 i = 0;
        for (i = 0; i < DataBase_Max_SIZE; i++)
        {
            if (string_compare(&(cardData->primaryAccountNumber),(&(Arr_accountsDB_t[i].primaryAccountNumber)))==1)
            {
                if (string_compare(&(cardData->cardHolderName),&(Arr_accountsDB_t[i].CardNameHolder))==0)
                {

                    return not_founded;
                }
               else if (string_compare(&(cardData->cardHolderName),&(Arr_accountsDB_t[i].CardNameHolder))==1)
                {
                    if((Arr_accountsDB_t[i].status==stolen))
                    {
                        return STOLEN_CARD;
                    }
                    flag_check = i;
                    return OK_CARD;
                }
            }

        }
        flag_check = DataBase_Max_SIZE;
        return not_founded;
}

void isValidDATE(ST_terminalData_t* termData)
{
    u8   isValidTransDate;
    //uint32  flag = 0;
    isValidTransDate = get_the_transaction_date(termData);

    /*loop until the the user writes a valid date*/
    while (isValidTransDate == WRONG_DATE)
    {
        isValidTransDate = get_the_transaction_date(&(termData->transactionDate));
        //printf("%d\n", isValidTransDate);
    }

}

EN_serverError_t isAmountAvailable(ST_terminalData_t* termData)
{

        if (termData->transAmount > Arr_accountsDB_t[flag_check].balance)
        {
            return LOW_BALANCE;
        }

        return OK_SER;
}
EN_serverError_t saveTransaction(ST_transaction_t* transData)
{
    if (sequence > 255)
    {
        return SAVING_FAILED;
    }

    copy_string(&(Arr_transactionsDB_t[sequence].cardHolderData.cardExpirationDate),&(transData->cardHolderData.cardExpirationDate));
    copy_string(&(Arr_transactionsDB_t[sequence].cardHolderData.cardHolderName), &(transData->cardHolderData.cardHolderName));
    copy_string(&(Arr_transactionsDB_t[sequence].cardHolderData.primaryAccountNumber), &(transData->cardHolderData.primaryAccountNumber));
    Arr_transactionsDB_t[sequence].terminalData.maxTransAmount = transData->terminalData.maxTransAmount;
    Arr_transactionsDB_t[sequence].terminalData.transAmount = transData->terminalData.transAmount;
    copy_string(&(Arr_transactionsDB_t[sequence].terminalData.transactionDate), &(transData->terminalData.transactionDate));
    Arr_transactionsDB_t[sequence].transactionSequenceNumber = transData->transactionSequenceNumber;
    sequence++;

    return OK_SER;

}

EN_serverError_t getTransaction(u32 transactionSequenceNumber, ST_transaction_t* transData)
{
    if(transactionSequenceNumber<sequence)
    {

            printf("\n\nYour Transaction details:\n");



             printf("the transaction date                          :\t%s\n", transData[transactionSequenceNumber].terminalData.transactionDate);
            printf("Your Card Holder Name - ID                    :\t%s\n", transData[transactionSequenceNumber].cardHolderData.cardHolderName);

            printf("Your Card Primary Account Number              :\t%s\n", transData[transactionSequenceNumber].cardHolderData.primaryAccountNumber);

            printf("The Card Expiry Date                          :\t%s\n", transData[transactionSequenceNumber].cardHolderData.cardExpirationDate);
            printf("The Transaction Amount                        :\t%f\n", transData[transactionSequenceNumber].terminalData.transAmount);

            printf("The Max Amount Your Can Transact              :\t%f\n", transData[transactionSequenceNumber].terminalData.maxTransAmount);

            printf("The Transaction Sequence Number               :\t%d\n", transData[transactionSequenceNumber].transactionSequenceNumber);
           // printf("your current balance is                         %f\n",Arr_accountsDB_t[flag_check].balance);



            return OK_SER;
        }

    //puts("Transaction Not Found\n");
    printf("Transaction Not Found\n");
    return TRANSACTION_NOT_FOUND;
}


