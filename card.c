#include"card.h"
#include"Std.h"
#include"strings.h"

EN_cardError_t get_thecard_holder_name(ST_cardData_t *card_data)
{
    printf("insert the card holder name \n");
    string_scan(&(card_data->cardHolderName),MaxCardHolderNameNo);
    u8 len =string_len(&(card_data->cardHolderName));
    if(len<Min_name)
    {
        return WRONG_NAME;
    }
    else
    {
        return OK_CARD;
    }
}
EN_cardError_t get_thecard_ex_date(ST_cardData_t *card_data)
{
     printf("\nPlease enter card Expiry Date (DD-MM-YY): ");
    string_scan(&(card_data->cardExpirationDate),ArrExDateLength);
    u8 len =string_len(&(card_data->cardExpirationDate));
    u8 days=stringtoint(&(card_data->cardExpirationDate[0]));
    u8 months=stringtoint(&(card_data->cardExpirationDate[3]));
    //printf(" days is %d   month is %d  len is %d ",days,months,len);
    if(len<10||days<=0||days>31||months<=0||months>12)

    {
        return WRONG_EXP_DATE;
    }
    else
    {
        return OK_CARD;
     }
}
EN_cardError_t get_thecard_pan(ST_cardData_t *card_data)
{
    printf("\nPlease enter card pan ");
    string_scan(&(card_data->primaryAccountNumber),MaxPanNO);
    u8 len =string_len(&(card_data->primaryAccountNumber));
    for(u8 i=0;i<len;i++)
    {
        if (card_data->primaryAccountNumber[i]<'0'||card_data->primaryAccountNumber[i]>'9')
        {
            if(card_data->primaryAccountNumber[i]!=' ')
            {

                return WRONG_EXP_DATE;
            }
        }
    }
    if(len<MinPAN ||len>MaxPanNO)
    {
        return WRONG_EXP_DATE;
    }
    else
    {
        return OK_CARD;
    }
}
