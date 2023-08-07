#include<stdio.h>
#include <stdlib.h>
#include"Std.h"
#include "terminal.h";
#include"card.h"
void string_scan(char*x,int maxsize)
{
    fflush(stdin);
    int i=0;
    scanf(" %c",&x[i]);
    for(; x[i]!='\n'&&i<maxsize;)
    {
        i++;
        scanf("%c",&x[i]);
    }
    x[i]=0;

}
int string_len(char*x)
{
    int i;
    for(i=0;x[i]!=0;i++)
    {

    }
    return i;
}
u16 stringtoint(u8 *x)
{
    int i=0,sum=0,flag=0;
    if(x[i]=='-')
    {
      return 0;
    }
    for(;x[i]!='/'&&x[i]!=0&&i<4;i++)
    {
        if(x[i]<'0'||x[i]>'9')
        {
            return 0;
        }
        sum=sum*10+(x[i]-'0');
    }
   return sum;

}
int card_compare(ST_cardData_t *card_data,ST_terminalData_t *terminal_data)
{

    u16 days=stringtoint(&(terminal_data->transactionDate[0]));
    u16 months=stringtoint(&(terminal_data->transactionDate[3]));
     u16     years=stringtoint(&(terminal_data->transactionDate[6]));
   u16 days_d=stringtoint(&(card_data->cardExpirationDate[0]));
    u16 months_d=stringtoint(&(card_data->cardExpirationDate[3]));
    u16 years_d=stringtoint(&(card_data->cardExpirationDate[6]));
   // printf(" days is %d   month is %d  years is %d \n",days,months,years);
  // printf(" days is %d   month is %d  years is %d \n",days_d,months_d,years_d);
   if(years_d<years)
   {
       return 0;
   }
   else if(years_d==years)
   {
       if(months_d<months)
       {
           return 0;
       }
       else if (months_d==months)
       {
        if(days_d<days)
       {
           return 0;
       }
       }

   }
   return 1;
}
int string_compare (char*x,char*y)
{
    int i,j;
    i=string_len(x);
    j=string_len(y);
    if(i!=j)
    {
        return 0;
    }
    for(char i=0;x[i]!=0&&y[i]!=0;i++)
    {
        if(x[i]!=y[i])
        {
         return 0;
        }

    }
    return 1;

}
void copy_string(char*x,char *y)
{
    u8 i;
    for( i=0;y[i]!=0;i++)
    {
        x[i]=y[i];
    }
    x[i]=0;
}

