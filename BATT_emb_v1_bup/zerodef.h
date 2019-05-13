#define zero 0

//#define    SEND0ON    PORTE_Bit2=1
//#define    SEND0OFF   PORTE_Bit2=0
#define    SEND0ON    PORTA_Bit0=1;
#define    SEND0      PORTA_Bit0
//PORTC=PORTC|0X1; //gron1
#define    SEND0OFF   PORTA_Bit0=0;
//PORTC=PORTC&0Xfc;
#define    txen0ini   DDRA_Bit0=1;

#define    SEND1      PORTB_Bit6
#define    SEND1ON    PORTB_Bit6=1;
//PORTC=PORTC|0X1; //gron1
#define    SEND1OFF   PORTB_Bit6=0;
//PORTC=PORTC&0Xfc;
#define    txen1ini   DDRB_Bit6=1;;

#define    UPM0Z  UPM00
#define    UPM1Z  UPM10

#define    CTC124_0 0X8f
#define    CTC124_1 0X8d
#define    CTC256_0 0X8e
#define    CTC256_1 0X8c
#define    C8Z 0x80
#define    Cff 0xff

#define    TCCR0CH TCCR0
#define    TCCR1CH TCCR2

#define    OCR0T OCR0
#define    OCR1T OCR2

#define    TCNT0CH TCNT0
#define    TCNT1CH TCNT2

//#define    OCF0CH TIFR_OCF0
//#define    OCF1CH TIFR_OCF2
#define    CH0f 1     
#define    CH1f 7               

#define    OCIE0CH TIMSK_OCIE0
#define    OCIE1CH TIMSK_OCIE2

#define    TIMERch0_COMP_vect TIMER0_COMP_vect
#define    TIMERch1_COMP_vect TIMER2_COMP_vect

#define getrx0 asm("ST  -Y,R16");asm("in R16,0x0c");asm("LD R16,Y+ ");
#define getrx1 asm("ST  -Y,R16");asm("LDS R16,0x9c");asm("LD R16,Y+ ");

//#define enTIMSK|=2


#define _SETADDR u0.addr=u1.addr
#define uZ u0

#ifdef mbslave0
char mbstate; //регистр наличия связи по МБ
#else
extern char mbstate; //регистр наличия связи по МБ
#endif

#define mbst0 0
#define mbst1 1

