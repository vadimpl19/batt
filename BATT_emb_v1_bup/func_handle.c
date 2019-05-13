
#include "types.h"
#include "hwr.h"
#include "timeservice.h"

#include "coms.h"
#include "func_handle.h"
#include "adc.h"
char cmd_active=false;
char fnum=0;
char param1,param2;
char paramfl1;
#define nack 1
#define bipolar_coag 1
#define pure_cut 2
#define force 3
/*
extern unsigned char adcbuf[1000];
///////////////////////////////////////////////////////////////////////////////////////
void idle(){
///////////////////////////////////////////////////////////////////////////////////////
  req0handle();
  delayed_func();
}
UCHAR ledstate;
UCHAR l_avg;
UCHAR l_cnt;
UCHAR l_max;
int l_samples;
int iabs(int i){
  if(i>0)return i;
  else return -i;
}  
*/