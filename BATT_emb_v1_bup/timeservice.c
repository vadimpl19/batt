#include <ina90.h>
#include <iom128.h>
//#include "led.h"
#include "types.h"
#include "base.h"
#include "timeservice.h"
int time;
int touttable[maxtout];
long longtouttable[maxtout];
long curtime=0;
char tmp=60;
void initime(){
char i;
  time=0;
  for(i=0;i<maxtout;i++)touttable[i]=0;
  //TCCR0 = (2<<WGM00) | (5<<CS00); //prescaler=128 CTC Moda c перезагрузкой по 1-му
  TCCR0=0X0D;
//  OCR3A=115; //прерывания каждую миллисекунду
  //OCR3A=115*2;
//  OCR0 = 239;
  OCR0 = 192; //1 тик 1,666666 мс
  TIMSK |= (1<<OCIE0); //разрешили прерывания

  //служба таймаутов перенесена на таймер 2
  TCCR2=0X0b; //прескалер 64
  OCR2=230;
  TIMSK |= (1<<OCIE2); //разрешили прерывания
   
}

void adcstart();//запуск на измерение всех 8-ми каналов

#pragma vector=TIMER0_COMP_vect
__interrupt void t0_comp_isr(){
//   time++;
//   time &=0x7fff;
   tmp--;
   adcstart();
   if(tmp==0){
     tmp=60;
     curtime++; //считаются 100 мс тики
   }
};
#pragma vector=TIMER2_COMP_vect
__interrupt void t2_comp_isr(){ //считаются 1 мс тики.
   time++;
   time &=0x7fff;
  // PORTC_Bit2=time&1;
};

void settout(char num, int tout){
int tt;

   _CLI();
   tt=time;
  _SEI();
   touttable[num]=tt+tout;
};
void  long_settout(char num, long tout){
  settout(num,tout&0x1fff);
  longtouttable[num]=tout&0xffe000;
}

char toutexpired(char num){
int tt;
   _CLI();
   tt=time;
   _SEI();

   if (touttable[num]<0) {
       if(tt<0x4000) {
           touttable[num] += 0x8000; //коррекция значения времени при переполнении таймера
           if (touttable[num]>tt) return 0; //таймаут не истек;
           else return 1;   
       }else return 0;    //таймаут не истек;
   };    
   //корректировка не нужна просто сравниваем значения
   if (touttable[num]>tt) return 0; //таймаут не истек;
           else return 1;   

}
char long_toutexpired(char num){
  if(toutexpired(num)){
    longtouttable[num]-=0x2000;
    settout(num,0x2000);
  }
  if(longtouttable[num]<0)return 1;//таймаут истек;
    return 0;//таймаут не истек;
}