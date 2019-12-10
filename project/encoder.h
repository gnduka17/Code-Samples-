void init_encoder(void);
//void init_pwm(void);
ISR(PCINT1_vect);
extern volatile unsigned char new_state, old_state;
extern volatile unsigned char changed;  // Flag for state change
extern volatile unsigned char a, b;
volatile unsigned char holder;
extern volatile unsigned char maxSpeed;