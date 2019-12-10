// Serial communications functions and variables
extern void serial_init(void);
extern void transferData(int speed);
extern void serial_txchar(char ch);
extern void serial_stringout(char *s);
ISR(USART_RX_vect);
extern volatile char bufferarray[5];
char transferOutputBuffer[5];
extern volatile unsigned char initial;
extern volatile int indexCount;
extern volatile unsigned char dataTrue;
extern int getSpeed;