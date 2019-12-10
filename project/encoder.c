#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include "encoder.h"

volatile unsigned char new_state, old_state;
volatile unsigned char changed = 0;  // Flag for state change
volatile unsigned char a, b;
volatile unsigned char holder;
volatile unsigned char maxSpeed = 1;

//encoder initializer
void init_encoder() {
    maxSpeed = eeprom_read_byte((void *) 0);
    if(maxSpeed>99){
    	maxSpeed = 99;
    }
    else if(maxSpeed<1){
    	maxSpeed = 1;
    }
	
	//enabling the rotary encoders PC4 and PC5
	//enable pull up
	PORTC |= ((1<<5) | (1<<4));
    PCICR |=(1<<PCIE1);
    //enabling interrupts 
    PCMSK1 |= ((1<<PCINT12) | (1<<PCINT13));

    // Read the A and B inputs to determine the intial state
    // Warning: Do NOT read A and B separately.  You should read BOTH inputs
    // at the same time, then determine the A and B values from that value. 
    holder = PINC;
    a = holder & (1<<4);
    b = holder & (1<<5);

    if (!b && !a)
	old_state = 0;
    else if (!b && a)
	old_state = 1;
    else if (b && !a)
	old_state = 2;
    else
	old_state = 3;
    new_state = old_state;


}
//INTERRUPT FUNCTION
ISR(PCINT1_vect){
	// Read the input bits and determine A and B
	holder = PINC;
	a = holder & (1<<4);
	b = holder & (1<<5);


	// For each state, examine the two input bits to see if state
	// has changed, and if so set "new_state" to the new state,
	// and adjust the maxSpeed value.
	if (old_state == 0) {
	    // Handle A and B inputs for state 0
	    if(a){
	    	maxSpeed++;
	    	new_state = 1;
	    }
	    else if(b){
	    	maxSpeed--;
	    	new_state = 2;
	    }

	}
	else if (old_state == 1) {

	    // Handle A and B inputs for state 1
	    if(!a){
	    	maxSpeed--;
	    	new_state = 0;
	    }
	    else if(b){
	    	maxSpeed++;
	    	new_state = 3;
	    }

	}
	else if (old_state == 2) {

	    // Handle A and B inputs for state 2
	    if(a){
	    	maxSpeed--;
	    	new_state = 3;
	    }
	    else if(!b){
	    	maxSpeed++;
	    	new_state = 0;
	    }

	}
	else {   // old_state = 3

	    // Handle A and B inputs for state 3
	    if(!a){
	    	maxSpeed++;
	    	new_state = 2;
	    }
	    else if(!b){
	    	maxSpeed--;
	    	new_state = 1;
	    }
	}

	// If state changed, update the value of old_state,
	// and set a flag that the state has changed.

	if (new_state != old_state) {
	    changed = 1;
	    old_state = new_state;

	    if(maxSpeed>99){
	    	maxSpeed=99;
	    }
	    else if(maxSpeed<1){
	    	maxSpeed=1;
	    }
	 
	}
    	
}
