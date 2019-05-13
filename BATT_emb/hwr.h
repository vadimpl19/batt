//инициализация управления передатчиком UART 0 - отключено
/*
#define    SEND0ON    PORTA_Bit0=1;
#define    SEND0      PORTA_Bit0
#define    SEND0OFF   PORTA_Bit0=0;
#define    txen0ini   DDRA_Bit0=1;
*/
#define    SEND0ON    ;
#define    SEND0      ;
#define    SEND0OFF   ;
#define    txen0ini   ;

//инициализация управления передатчиком UART 1 - отключено
#define    SEND1      ;//PORTB_Bit6
#define    SEND1ON    ;//PORTB_Bit6=1;
#define    SEND1OFF   ;//PORTB_Bit6=0;
#define    txen1ini   ;//DDRB_Bit6=1;;

//send_begin - макрос осуществляющий начало передачи. Обычно просто открывает
//             прерывание на передачу по UART

#define send_begin ;
#include <iom128.h>
#include <ina90.h>
// Макрос запрещающий все прерывания
#define CLI  __disable_interrupt();
// Макрос разрешающий все прерывания
#define EI  __enable_interrupt();

#define rbuf_size 512
#define sbuf_size 1024

//дефайны для лампочек
#define gron4  ;
#define redon4 ;

#define off4   ;

#define gron3 ;
#define redon3 ;
#define off3   ;

#define red1 PORTC_Bit2
#define yel1 PORTC_Bit1
#define gr1 PORTC_Bit0

#define red2 PORTC_Bit5
#define yel2 PORTC_Bit4
#define gr2 PORTC_Bit3

#define red3 PORTA_Bit3
#define yel3 PORTC_Bit7
#define gr3 PORTC_Bit6

#define red4 PORTA_Bit0
#define yel4 PORTA_Bit1
#define gr4 PORTA_Bit2

#define xk1 PING_Bit3
#define xk2 PING_Bit4

#define WR PORTB_Bit7
#define LDAC PORTG_Bit4
#define CLR PORTG_Bit3
