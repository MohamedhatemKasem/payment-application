#ifndef TERMINAL_H_
#define TERMINAL_H_
#define		TransDateLen	10

#define		DayTENS_3		'3'
#define		DayONES_1		'1'

#define		DayZero			'0'

#define		ArrDateLength	10

#include "card.h"
extern char transactionDate[ArrDateLength];
typedef enum EN_terminalError_t
{

	OK_TER, WRONG_DATE, EXPIRED_CARD, INVALID_CARD,
	INVALID_AMOUNT, EXCEED_MAX_AMOUNT,
	INVALID_MAX_AMOUNT

}EN_terminalError_t;


typedef struct ST_terminalData_t
{
	float transAmount;
	float maxTransAmount;
	char transactionDate[ArrDateLength];

}ST_terminalData_t;

EN_terminalError_t get_the_transaction_date(ST_terminalData_t *terminal_data);
EN_terminalError_t isCardExpired(ST_cardData_t *cardData,ST_terminalData_t *terminal_data);
EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData);
EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData);
EN_terminalError_t setMaxAmount(ST_terminalData_t* termData);
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData);
#endif // TERMINAL_H_
