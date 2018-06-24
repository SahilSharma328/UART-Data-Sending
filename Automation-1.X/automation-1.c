/*
 * File:   automation-1.c
 * Author: Sahil
 *
 * Created on 10 January, 2018, 10:04 AM
 */

#define _XTAL_FREQ 16000000

#include<xc.h>

void uart_init1(unsigned long);
void uart_send1(unsigned char);

void uart_init1(unsigned long baud)
{
    unsigned int n;
    TXSTA1 = 0x00;						
    RCSTA1 = 0x00;						 
    TXSTAbits.SYNC = 0;               
    BAUDCON1bits.BRG16 = 1;          
    RCSTA1bits.SPEN = 1;           
    RCSTA1bits.CREN = 1;           
    TXSTA1bits.BRGH = 1;           
    TXSTA1bits.TXEN = 1;           
    n = ((_XTAL_FREQ/4)/baud) - 1;
    SPBRGH1 = (n>>8);
    SPBRG1 = n & 0xFF;
}

/*unsigned char uart_rec1()
{
    while(!RC1IF);	
	return RCREG1;
}*/

void uart_send1(unsigned char ch)
{
    while(!TX1IF);
    TXREG1=ch;
}

void uart_string1(unsigned char *str)
{
	while((*str)!='\0')
	{
        while(!TX1IF);
		TXREG1=(*str);
		str++;
	}
}

void main()
{
    ANSELC=0;
    TRISC=0x00;
    char name[6]={"Sahil"};
    uart_init1(115200);
    __delay_ms(2000);
    uart_string1(name);
    __delay_ms(2000);
    int i;
    while(1)
    {
        for(i=0;i<5;i++)
        {
            uart_send1(name[i]);
        }
        uart_string1("\r\n");
        __delay_ms(2000);
    }
}