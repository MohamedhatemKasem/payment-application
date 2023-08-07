#ifndef _CARD_H_
#define _CARD_H_
#define		Min_name			15
#define		MaxCardHolderNameNo	25
#define		ArrExDateLength		10
#define		MinPAN				16
#define		MaxPanNO			20
#include"Std.h"
typedef enum
{

	OK_CARD, WRONG_NAME, WRONG_EXP_DATE, WRONG_PAN

}EN_cardError_t;



typedef struct
{
	u8	primaryAccountNumber[MaxPanNO];
	u8	cardHolderName[MaxCardHolderNameNo];
	u8	cardExpirationDate[ArrExDateLength];


}ST_cardData_t;

EN_cardError_t get_thecard_holder_name(ST_cardData_t* cardData);
EN_cardError_t get_thecard_ex_date(ST_cardData_t   *card_data);
EN_cardError_t get_thecard_pan(ST_cardData_t*card_data);
#endif // _CARD_H_
