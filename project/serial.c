#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>

#include "serial.h"

char transferOutputBuffer[5];
volatile unsigned char initial = 0;
volatile int indexCount = 0;
volatile unsigned char dataTrue = 0;
volatile char bufferarray[5];
int getSpeed;
#define FOSC 16000000           // Clock frequency
#define BAUD 9600               // Baud rate used
#define MYUBRR (FOSC/16/BAUD-1) // Value for UBRR0 register

//serial initialization 
void serial_init()
{
    // Set up USART0 registers
    UBRR0 = MYUBRR;  // Setting baud rate
    UCSR0B |= (1 <<  RXCIE0); //enabling interrupts
    UCSR0C = (3 << UCSZ00);    
    UCSR0B |= (1 << TXEN0 | 1 << RXEN0);  // Enabling RX and TX
}
//function to send over speed
void transferData(int speed){
    if (speed > 9999){
        return;
    }
    transferOutputBuffer[4] = '\0';
    snprintf(transferOutputBuffer, 5, "%4d", speed);
    serial_txchar('<');
    serial_stringout(transferOutputBuffer);
    serial_txchar('>');
}

//helper functions 
void serial_txchar(char ch)
{
    UDR0 = ch;
    while ((UCSR0A & (1<<UDRE0)) == 0); 
}

void serial_stringout(char *s) { //stringout serial message
    int i = 0;
    while (s[i] != '\0'){
        if ((s[i] >= '0') && (s[i] <= '9')) {
            serial_txchar(s[i]); 
        }
        i++;
    }
}

//interrupt
ISR(USART_RX_vect)
{
    char ch;
    ch = UDR0;       // Get the received charater
    //read in starting flag
    if(ch=='<'){
        initial = 1;
        dataTrue = 0; // disabled to not retrieve wrong data
        indexCount = 0; 
    }else{
        //reading ending flag when chars retreived 
        if(ch == '>'){
            if(indexCount!=0){
                initial = 0;
                sscanf(bufferarray, "%d", &getSpeed);
                dataTrue = 1;
            }
        } 
        else if(initial!=0){
            if(ch<'0' || ch>'9'){
                indexCount = 0;
                initial = 0;
            }
            else{
                //excessive chars -> restart
                if(indexCount>3){
                    indexCount =0;
                    dataTrue = 0;
                }
                else{
                    //valid ->proceed
                    bufferarray[indexCount] = ch;
                    indexCount++;
                }

            }
        }
    }
}