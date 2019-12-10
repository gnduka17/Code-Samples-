/********************************************
 *
 *  Name:Gloria Nduka
 *  Email:nduka@usc.edu
 *  Section:Friday 11am 
 *  Assignment: Project - SpeedTrap
 *
 ********************************************/




#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include "speedtrap.h"
#include "lcd.h"
#include "encoder.h"
#include "serial.h"
#define FOSC 16000000           // Clock frequency
#define BAUD 9600               // Baud rate used
#define MYUBRR (FOSC/16/BAUD-1) // Value for UBRR0 register
#define DISTANCE (unsigned int)50

volatile unsigned int total;
volatile unsigned char beginTime = 0;
volatile unsigned char state =1;
volatile unsigned char pinHolder;
volatile unsigned char bits;
volatile unsigned char onesplace;
volatile unsigned char tenthsplace;
volatile unsigned char thousandthsplace;
volatile unsigned char hundredthsplace;
char timeholder[7];
char speedholder[7];
char maxholder[20];
char rsHolder[20];
unsigned int speed;
int getSpeedHolder;


int main(void) { 

	// Enable tri-state buffer
    DDRD |= (1 << PD3);
    PORTD &= ~(1<<PD3);

	lcd_init(); //initialize lcd
	init_encoder();
	serial_init();
	sei(); //enable the global interrupts

	DDRC |= (1 << PC1); //output for buzzer

	//initializing speed sensor interrupts
	PORTB |= ((1 << PB3) | (1 << PB4)); 
	PCICR |= (1 << PCIE0); 
	PCMSK0 |= ((1 << PCINT3) | (1 << PCINT4));
	

	DDRB |= (1 << PB5);//PB5 LED output


	//initialize timer
	TIMSK1 |= (1 << OCIE1A); 
    TCCR1B |= (1 << WGM12);
	OCR1A = 16000; 
	TCCR1B |= (1 << CS10);


	// Write splash screen
    lcd_writecommand(1);
    lcd_stringout("Gloria Nduka");
    lcd_moveto(1, 0);
    lcd_stringout("Final Project");
    _delay_ms(500);
    lcd_writecommand(1);

    //printing time and max speed
	snprintf(timeholder, 7, "%d.%d%d%d",onesplace, tenthsplace, hundredthsplace, thousandthsplace);
	snprintf(maxholder, 20, "Max=%2d", maxSpeed);
	lcd_moveto(0, 0);
	lcd_stringout(timeholder);
	lcd_moveto(1, 0);
	lcd_stringout(maxholder);


	while (1) {// Loop forever
		if (changed) { 
			snprintf(maxholder, 20, "Max=%2d", maxSpeed);
			lcd_moveto(1, 0);
			lcd_stringout(maxholder);
			eeprom_update_byte((void*)0, maxSpeed);
		}
		if (beginTime!=0)
		{
			lightOn();
			lcd_moveto(0, 0);
			displayTime();
		}
		if (!state)
		{
			lightOff();
			outputTS();
		}
		if (dataTrue == 1)
		{
			lcd_moveto(1, 7);
			getSpeedHolder = getSpeed;
			getSpeed /= 10;
			snprintf(rsHolder, 20, "RS: %d.%d", getSpeedHolder/10, getSpeedHolder%10);
			lcd_stringout(rsHolder);
			if (getSpeed > maxSpeed)
			{
				playBuzzer();
			}
			dataTrue = 0;
		}
	}
	return 0;
}
//function to play buzzer when speed over max
void playBuzzer() {
	unsigned long period;
    unsigned short freq = 349;
    period = 1000000 / freq; // Period of note in microsecond
      	while (freq--) {
             // Make Pc1 high
              PORTC |= (1<<PC1);
	        // Use variable_delay_us to delay for half the period
	        int i = ((period/2) + 5) / 10;
	        while (i--)
	            _delay_us(10);
	        // Make PC1 low
	        PORTC &= ~(1<<PC1);
	        // Delay for half the period again
	        i = ((period/2) + 5) / 10;
	        while (i--)
	            _delay_us(10);
	    }
}
//output ts speed cm/sec
void outputTS(){
	speed = (DISTANCE*100) / total;
	snprintf(speedholder, 20, "TS: %d", speed);
	lcd_moveto(0, 7);
	lcd_stringout(speedholder);
	transferData(speed*10);
	state = 1;
}
//display time function 
void displayTime(){
	snprintf(timeholder, 7, "%d.%d%d%d",onesplace,tenthsplace, hundredthsplace, thousandthsplace);
	lcd_stringout(timeholder);
}
void lightOn(){
	PORTB |= 1 << PB5;
}
void lightOff(){
	PORTB &= ~(1 << PB5);
}
//timer interrupt 
ISR(TIMER1_COMPA_vect)
{
	//similar to lab8
	if (beginTime)
	{
		total++;
		thousandthsplace++;
		if (thousandthsplace == 10)
		{
			thousandthsplace = 0;
			hundredthsplace++;
		}
		if (hundredthsplace == 10)
		{
			hundredthsplace = 0;
			tenthsplace++;
		}
		if (tenthsplace == 10)
		{
			tenthsplace = 0;
			onesplace++;
		}
	}
}
//interrupt initialization for photosensors and timing
ISR(PCINT0_vect)
{
	unsigned char pinHolder = PINB;
	unsigned char x = (pinHolder & (1<<PB3));
	unsigned char y = (pinHolder & (1<<PB4));
	
	if(!y)
	{
		state = 0;
		beginTime = 0;
	}
	else if (!x)
	{	
		state = 1;
		beginTime = 1;
		total = 0;
		thousandthsplace =0;
		onesplace = 0;
		tenthsplace = 0;
		hundredthsplace = 0;
	}	
}
