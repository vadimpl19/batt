#include <iom128.h>
#include "ina90.h"
//#include "string.h"
//#include "stdio.h"

#include "types.h"
#include "timeservice.h"
#include "hist.h"
#include "coms.h"
#include "adc.h"
#include "func_handle.h"
#include "hwr.h"
UINT get_sp();
char stepcnt;         

void delayloop(unsigned int d){
unsigned int i,i2;
for (i=0;i<d;i++)
  for (i2=0;i2<1100;i2++) _NOP();
};
int setdac(int outb){//установка напряжения в милливольтах
  //1 разряд цап = 1 мв  
   CLR=1;  
   WR=1;
   PORTD_Bit7=outb&1;
   outb=outb>>1;
   PORTD_Bit6=outb&1;
   outb=outb>>1;
   PORTD_Bit6=outb&1;
   outb=outb>>1;
   PORTD_Bit5=outb&1;
   outb=outb>>1;
   PORTD_Bit4=outb&1;
   outb=outb>>1;
   PORTD_Bit3=outb&1;
   outb=outb>>1;
   PORTD_Bit2=outb&1;
   outb=outb>>1;
   PORTD_Bit1=outb&1;
   outb=outb>>1;
   PORTD_Bit0=outb&1;
   outb=outb>>1;
   PORTB_Bit5=outb&1;
   outb=outb>>1;
   PORTB_Bit6=outb&1;
   WR=0;
   WR=0;
   WR=0;
   WR=0;
   LDAC=0;
   WR=1;
   LDAC=1;
   return 0;
}
/*
void setcur (char i){//установка тока активации i - ток в миллиамперах
 long l=169;
 l=l*i;
 l=(a*l+b +5)/10;//делим на 10 с округлением
 setdac(l);
}
*/
typedef struct{
  int offsadc;
  int dac1;
  int dac100;
  long a,b;//коэффициенты прямой, аппроксимации dac
}tcalibr;
tcalibr cal;
void setcur (char i){//установка тока активации i - ток в миллиамперах
  if(i==0){
    setdac(0);
    return;
  }  
 long l=cal.a;
 l=l*i;
 l=(l+cal.b +50)/100;//делим на 10 с округлением
 setdac(l);
}
long activ_time=10000;
///////////////////////////////////////////////////////////////////////////
int calibration(){// калибровка офсетов ацп, офсета цап и коэф. усиления цап
///////////////////////////////////////////////////////////////////////////
  int toutdel=100;
  cal.offsadc=0;
  cal.b=0;
  cal.a=1690;
  red1=1;
  red2=1;
  red3=1;
  red4=1;
  gr1=0;
  gr2=0;
  gr3=0;
  gr4=0;
  yel1=0;
  yel2=0;
  yel3=0;
  yel4=0;
  setcur(0);
  settout(0,toutdel);
  while(!toutexpired(0))__watchdog_reset();
  if(batt[0].v<3){
  red1=0;
  red2=0;
  red3=0;
  red4=0;
  gr1=1;
  gr2=1;
  gr3=1;
  gr4=1;
  yel1=1;
  yel2=1;
  yel3=1;
  yel4=1;
  settout(0,1000);
  while(!toutexpired(0))__watchdog_reset();
     return -1; //калибровка невозможна - отсутствует батарея
  }   
  //cal.offsadc=batt[0].curr-cal.offsadc;
//  cal.offsadc=batt[0].curr-cal.offsadc;
  setcur(1);
  settout(0,toutdel);
  while(!toutexpired(0))__watchdog_reset();
  cal.dac1=batt[0].curr; //оффсет в десятках микроампер

  setcur(100);
  settout(0,toutdel);
  while(!toutexpired(0))__watchdog_reset();
  cal.dac100=batt[0].curr;
  cal.b=(100-cal.dac1)*169 ;//правильный коэф 16.9 - размер шунта
  cal.b=cal.b/10;
  double d=(cal.dac100-cal.dac1);
  d=9900/d;
  cal.a=1690*d+0.5;
  
  char * p=(char *)&cal;
  __watchdog_reset();
  for(int i=0;i<sizeof(tcalibr);i++){
     setch(1000+i,*p++);
     __watchdog_reset();
  }
}  
///////////////////////////////////////////////////////////////////////////
int load_calibr(){//загрузка калибровочных коэффициентов из eeprom
///////////////////////////////////////////////////////////////////////////
  char * p=(char *)&cal;
  char ch;
  for(int i=0;i<sizeof(tcalibr);i++ ){
     ch=*(( unsigned char __eeprom *)(1000+i));
     *p=ch;
     p++;
     __watchdog_reset();
  };
  if(cal.offsadc==0xff){ //eeprom чистое, задаем параметры по умолчанию
     cal.offsadc=0;
     cal.a=1690;
     cal.b=0;
  }
}


///////////////////////////////////////////////////////////////////////////
void setredon(char num){// зажечь красную лампочку на соотв. номеру батарейке
///////////////////////////////////////////////////////////////////////////
  switch(num){
  case 0: red1=0;
    break;
  case 1: red2=0;
    break;
  case 2: red3=0;
    break;
  case 3: red4=0;
  }
}
///////////////////////////////////////////////////////////////////////////
void setredoff(char num){// потушить красную лампочку на соотв. номеру батарейке
///////////////////////////////////////////////////////////////////////////
  switch(num){
  case 0: red1=1;
    break;
  case 1: red2=1;
    break;
  case 2: red3=1;
    break;
  case 3: red4=1;
  }
}
///////////////////////////////////////////////////////////////////////////
void setyelon(char num){// зажечь желт. лампочку на соотв. номеру батарейке
///////////////////////////////////////////////////////////////////////////
  switch(num){
  case 0: yel1=0;
    break;
  case 1: yel2=0;
    break;
  case 2: yel3=0;
    break;
  case 3: yel4=0;
  }
}
///////////////////////////////////////////////////////////////////////////
void setyeloff(char num){// потушить желт. лампочку на соотв. номеру батарейке
///////////////////////////////////////////////////////////////////////////
  switch(num){
  case 0: yel1=1;
    break;
  case 1: yel2=1;
    break;
  case 2: yel3=1;
    break;
  case 3: yel4=1;
  }
}
///////////////////////////////////////////////////////////////////////////
void setyel(char num,char state){// установить свечение желт лампы в соотв с зад. состоянием
///////////////////////////////////////////////////////////////////////////
  switch(num){
  case 0: yel1=state;
    break;
  case 1: yel2=state;
    break;
  case 2: yel3=state;
    break;
  case 3: yel4=state;
  }
}
///////////////////////////////////////////////////////////////////////////
void setgron(char num){// зажечь зел. лампочку на соотв. номеру батарейке
///////////////////////////////////////////////////////////////////////////
  switch(num){
  case 0: gr1=0;
    break;
  case 1: gr2=0;
    break;
  case 2: gr3=0;
    break;
  case 3: gr4=0;
  }
}
///////////////////////////////////////////////////////////////////////////
void setgroff(char num){// потушить зел. лампочку на соотв. номеру батарейке
///////////////////////////////////////////////////////////////////////////
  switch(num){
  case 0: gr1=1;
    break;
  case 1: gr2=1;
    break;
  case 2: gr3=1;
    break;
  case 3: gr4=1;
  }
}

///////////////////////////////////////////////////////////////////////////
void inistates(){// иниц2иация нач. состояния активации батарей
///////////////////////////////////////////////////////////////////////////
  for(int i=0;i<3;i++){
    batt[i].state=0;
    setgroff(i);
    setyeloff(i);
    setredoff(i);
  }
};
///////////////////////////////////////////////////////////////////////////
void setstate(int num){// автомат состояния батареи
///////////////////////////////////////////////////////////////////////////
  tbatt* b=&batt[num];
  if (b->curr>profile.act_cur_level*100)setredon(num);
  else setredoff(num);
  if(work_mode!=0){
    char allowcur=1;
    for(int i=0;i<4;i++){
       if(batt[i].state==3)allowcur=0;
    };   
    if(allowcur){
       setcur(profile.act_cur);
       work_mode=0;
    };   
  } 
  switch (b->state){
  case 0://нач. состояние, ожидаем установки батареи
    setgroff(num);
    setyeloff(num);
    if(!(batt[0].state||batt[1].state||batt[2].state||batt[3].state))
             work_mode=0; //сброс установленной моды когда все бат. вытащены
    b->charge=0;
    b->charge_hi=0;
  //  if(work_mode!=0)break;
    if(b->v>300){
      b->time=0;
      if(work_mode!=0) {
        b->state=2;
        b->begt=0;
        b->endt=0;
        b->state=2;
        break;
      }  
       b->state=1;
       b->begt=curtime;
       b->endt=b->begt+activ_time;
       
       setcur(profile.act_cur);
    }
    break;
 case 1: //идет активация
   setgroff(num);
  setyelon(num);
  if(curtime!=b->begt){
    b->time+=curtime-b->begt;
    b->begt=curtime;
  }
  if(b->time>=profile.act_time){
     b->state=3;
     setcur(0);
     work_mode=1;
     break;
  }
     if(work_mode==1){
      setyel(num,(curtime&0x0f)>>2);
      b->time+=curtime-b->begt;
      b->begt=0;
      b->endt=0;
      b->state=2;
      break;
   }

  if(b->v<300){ //аварийное завершение автивации - батарею вытащили.
      b->time=0;
        b->state=0;
        b->begt=0;
        b->endt=0;
        break;
  }  


  break;
  case 2://ток снят, но активация незавершена
    setyel(num,(curtime&0x0f)>>2);
     if(b->v<300){ //аварийное завершение автивации - батарею вытащили.
      b->time=0;
        b->state=0;
        b->begt=0;
        b->endt=0;
        break;
     }  
   
    if(work_mode==0){//возвращаемся в режим активации
      b->state=1;
      b->begt=curtime;
      b->endt=b->begt+(activ_time-b->time);
    }
    break;
  case 3: //активация завершена  
    setgron(num);
    setyeloff(num);
    if(b->v<100){
        b->state=0;
        
    }
  }  
}
///////////////////////////////////////////////////////////////////////////
// Инициируем порты ввода вывода для чтения перемычек и зажигания лампочек
void iniports(){
  DDRA=0x0f;
  DDRB=0xe0;
  DDRC=0xff;
  DDRD=0xff;
  DDRE =0xfc;
  DDRG=0xff;
  
//DDRF |= 0xc0;//KT1 KT2
}
/*
getstack()
      { char * st; int i;
          st=(char*)hrem[0x10]; 
          for (i=1;i<0x80;i++){hrem[i+0x10]=*st; st--;}
      };    
*/
extern thist hist;
//extern enum {data,adrLo,adrHi,page,compl} state;

extern unsigned int ADCw, ADCo;
unsigned int Uref;//опорное напряжение

void Init(void)
{
	/******** Timer1 init ********/
	TCCR1A = 0;
	TCCR1B = (1<<CS11);//CTC mode, Fclk = Fmclk
	OCR1A = 0xffff;//68 us
	
	/******** Timer3 init ********/
//      TIMSK |= (1<<OCIE1A); разрешили прерывание от таймера.
    	TCCR3A = 0;
      TCCR3B = (1<<CS31);// / делитель на 8
      TCNT3 = 0;
      OCR3A=0xffff;
      
      TIFR = (1<<OCF3A); //сбросили имевшееся прерывание.
}
void setind_prof(){ //индикация в режиме работы по профилю
    yel1=(time>>7)&1;
    yel2=yel1;
    yel3=yel1;
    yel4=yel1;
    int c=profile.act_cur_level*100;
    if(batt[0].curr>c)red1=0;
    else red1=1;
    if(batt[1].curr>c)red2=0;
    else red2=1;
    if(batt[2].curr>c)red3=0;
    else red3=1;
    if(batt[3].curr>c)red4=0;
    else red4=1;
    if(batt[0].v>300)gr1=yel1;
    else gr1=1;
    if(batt[1].v>300)gr2=yel1;
    else gr2=1;
    if(batt[2].v>300)gr3=yel1;
    else gr3=1;
    if(batt[3].v>300)gr4=yel1;
    else gr4=1;

}
void ini_addsamples();
void addsamples();
extern long nextsampletime;
extern char * forsend;
////////////////////////////////////////////////////////////////////////////////
void ini_workbyprofile(){ //инициация режима работы по профилю
////////////////////////////////////////////////////////////////////////////////  
  work_mode=10;
  stepcnt=0;
  long_settout(0,profile.dur[stepcnt]);
  setcur(profile.curr[stepcnt]);
  nextsampletime=curtime=0;
  forsend=prbuf1; //передаем с 1-го, заполняем 0-й
  curbuf=prbuf0;
     //senlen=curoffset+1;
  curoffset=  framenum+2;
}
extern char* forsend;
////////////////////////////////////////////////////////////////////////////////
void ini_activation(){ //инициация режима активации
////////////////////////////////////////////////////////////////////////////////  
     work_mode=0;
     for(int i=0;i<4;i++){
       batt[i].charge=0;
       batt[i].time=0;
       batt[i].state=0;
     }
     setcur(profile.act_cur);
}
main(){
__disable_interrupt(); 
WDTCR |= (1<<WDCE);
WDTCR |= (1<<WDP0) | (1<<WDP1) | (1<<WDP2);
__enable_interrupt();

iniports();

Init();

//redonw                                                     

//inibase();
initime();
//inihist(0xa1,0xff);

//iniuart0(576,0);
//ini_addsamles();
ini_addsamples();
iniuart0(1152,0);
//iniuart1(576,0);

__watchdog_reset();

//delayloop(50);    
hist.harr[0]=1;
hist.harr[1]=0x2002;
hist.harr[3]=3;


adcini();
setcur(profile.act_cur);
work_mode=0;
read_settings();
load_calibr();

//ini_workbyprofile();
ini_activation();
for (;;){//int ii;
  addsamples();
  if(work_mode==10){
     //разряд по профилю
    setind_prof();
    if(long_toutexpired(0)){
      stepcnt++;
      if(stepcnt>=profile.cnt)stepcnt=0;
      long_settout(0,profile.dur[stepcnt]);
      setcur(profile.curr[stepcnt]);
        
    }
  }else{
     for(int i=0;i<4;i++) setstate(i);
  }   
  __watchdog_reset();
  req0handle();
}};
