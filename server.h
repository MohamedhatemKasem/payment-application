#ifndef SERVER_H_
#define	SERVER_H_

#include "terminal.h"

#define DataBase_Max_SIZE	255
#include"Std.h"
#define valid 1
#define stolen 0

extern u32 flag_check ;
extern u32 sequence  ;

typedef enum EN_transState_t
{

    APPROVED, DECLINED_INSUFFECIENT_FUND,
    DECLINED_STOLEN_CARD, INTERNAL_SERVER_ERROR,EXPIREDED_CARD,card_not_founded,no_balance


} EN_transState_t;
typedef enum
{

    STOLEN_CARD=1,not_founded,ok_account,


} EN_account_status;


typedef struct ST_transaction_t
{
    ST_cardData_t		cardHolderData;
    ST_terminalData_t	terminalData;
    u32				transactionSequenceNumber;

} ST_transaction_t;


typedef enum EN_serverError_t
{
    OK_SER, SAVING_FAILED, ACCOUNT_NOT_FOUND,
    TRANSACTION_NOT_FOUND, LOW_BALANCE

} EN_serverError_t;

typedef struct ST_accountsDB_t
{
    float				balance;
    u8				primaryAccountNumber[MaxPanNO];
    u8				CardNameHolder[MaxCardHolderNameNo];
    u8              status;

} ST_accountsDB_t;

EN_transState_t			recieveTransactionData(ST_transaction_t* transData);
EN_account_status       isValidAccount(ST_cardData_t* cardData);
EN_serverError_t		isAmountAvailable(ST_terminalData_t* termData);
EN_serverError_t		saveTransaction(ST_transaction_t* transData);
EN_serverError_t		getTransaction(u32 transactionSequenceNumber, ST_transaction_t* transData);
void                    isValidDATE(ST_terminalData_t* termData);

ST_accountsDB_t			Arr_accountsDB_t[DataBase_Max_SIZE];
ST_transaction_t		Arr_transactionsDB_t[DataBase_Max_SIZE];
#endif // !SERVER_H_

