
typedef unsigned char UCHAR;
typedef unsigned int UINT;

enum tpar {none,odd,even};
struct isr_cntx {
  char flag35;
  char state;
  unsigned char l;
  char addr;
  char rbuf[8];
//  char tbuf[263];
  char tbuf[128+8];
 };


#define _clis sregt=SREG; __disable_interrupt();
#define _ID  __disable_interrupt();
#define _IE  __enable_interrupt();

