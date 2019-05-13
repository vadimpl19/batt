//#define jtagen 1
//#include "base.h"
#include <ina90.h>

#include <iom128.h>
long int summ[8]; //сумма значений
#include "types.h"
#include "adc.h"
#include "hwr.h"
#include "timeservice.h"
#include "coms.h"
extern char work_mode;
long int summcnt[8]; //число проссуммированных значений
int maxsummcnt[8];//максимальное число просс. значений 

char chn;//номер текущего канала;
//#define defADMUX 0x40
#define defADMUX 0x00
//#define maxscnt 1152
#define maxscnt 83
int samplecnt=maxscnt;
long sumadc=0;
int results[8];
//unsigned char adcbuf[maxbufcnt+1];
//int bufcnt=0;
tbatt batt[4];
char rdy;//флаг что интегрирование измерения завершено - нужен для лучшей синхронизации выдачи с замерами

//////////////////////////////////////////////////////////////////////////////////////////
#pragma vector=ADC_vect
__interrupt void ADC_isr(){
//////////////////////////////////////////////////////////////////////////////////////////  
// работаем по одиноч. запускам
  char oldch;
  int res=ADCL;
  res|=ADCH<<8;
  oldch=chn;
  chn++; 
  ADMUX=chn|defADMUX;
  if(chn==8)     ADCSR_ADSC=0;  //завершили замер
  else ADCSR_ADSC=1;  //взвели бит запуска АЦП
  summ[oldch]+=res;
  results[oldch]=res;
  summcnt[oldch]++;
  
#ifdef jtagen
 if(oldch>4) goto continuel;
#endif  
  if(summcnt[oldch]>maxsummcnt[oldch]){
     
     char num=oldch>>1;
     tbatt *b;
     b=&batt[num];
     if(oldch&1){ //это напряжение
     b->v=((summ[ oldch]*4)/summcnt[oldch]);  
//     }else      b->curr=((summ[ oldch])/summcnt[oldch]*1690/2);//для шунта 16,9 Ом
       }else      b->curr=(summ[ oldch]*2*1000)/(summcnt[oldch]*169);//для шунта 16,9 Ом
     //ramb[currents+oldch]=resl; 
     
     summcnt[oldch]=0;  
     summ[oldch]=0;

  }
continuel:  
#ifdef jtagen
  if(oldch==3){
#else    
  if(oldch==7){
#endif    
     ADCSR_ADSC=0;  //завершили замер
     for(int i=0;i<4;i++){
         tbatt *b;      
         b=&batt[i];
       if((b->state==1)||(b->state==10)){
         unsigned long l=b->charge+results[i*2];
         if(l<b->charge)b->charge_hi++;
         b->charge=l;
       }
     } 
     //red1=1;
     return;
  } 

} 
extern char * curbuf;
extern char* forsend;
typedef struct{
  long time;//время от начала работы в данном режиме в сотнях мс
  int curr[4];
  int v[4];
}titem;
long nextsampletime=0;
/////////////////////////////////////////////////////////////////////////////////////////////////////
void ini_addsamples(){//инициализация глобальных переменных, необходимых
     //для корректной работы функции addsamples
/////////////////////////////////////////////////////////////////////////////////////////////////////
  curtime=0;
  nextsampletime=0;
  curbuf=prbuf0;
  forsend=prbuf1;
  prbuf1[framenum]=255;
  prbuf0[framenum+1]=0;//флаг переполнения сброшен
  //offset0=framenum+2;//начало непоср. данных
  curoffset=framenum+2;
  // offset1=0;//означает пустоту неисп. буфера;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
void addsamples(){// добавление элемента в буфер для передачи
/////////////////////////////////////////////////////////////////////////////////////////////////////
//  return; 
  if(work_mode!=10)return;
  if(curtime<nextsampletime)return;
  nextsampletime=nextsampletime+profile.period;
  char * p;
  int  *pi;
  titem * it;
  if((curoffset+sizeof(titem))>(prbufsize-2)){
    //складывать некуда, взводим флаг переполнения
      curbuf[framenum+1]=1;
      return;
    /*
    //пора менять буфер
    if(curbuf==prbuf0){
       offset0=curoffset;
       curbuf=prbuf1;
       if(offset1!=0){//буфер не пуст, взведем флаг переполнения в пред. буфер
         prbuf0[framenum+1]=1;
       }
       offset1=framenum+2;
       curoffset=offset1;
    }else{
      offset1=curoffset;
      curbuf=prbuf0;
       if(offset0!=0){//буфер не пуст, взведем флаг переполнения в пред. буфер
         prbuf1[framenum+1]=1;
       }
       offset0=framenum+2;
       curoffset=offset0;
    }
    */
  }
  it=(titem*)&curbuf[curoffset];
  it->time=curtime;
  for(int i=0;i<4;i++){
     it->curr[i]=batt[i].curr;
     it->v[i]=batt[i].v;
  }
  curoffset+=sizeof(titem);

  
}
//////////////////////////////////////////////////////////////////////////////////////////  
void adcini(){// инициализация ацп
//////////////////////////////////////////////////////////////////////////////////////////  
  for(char i=0;i<8;i++){
  //  maxsummcnt[i]=16;
      maxsummcnt[i]=32;
  }  
  chn=0;
//  ADMUX=defADMUX;
  ADMUX=defADMUX;
  ADCSR=7;//прескалер 128; НА кварце 14,745 это 115,2 КГц то есть на 10мс нужно 1152отсчета
  ADCSR_ADEN=1;//разрешение AD
  ADCSR_ADIE=1;//разрешили прерывания
  ADCSR_ADSC=1;  //взвели бит запуска АЦП
}  
//////////////////////////////////////////////////////////////////////////////////////////  
void adcstart(){// инициализация ацп
//////////////////////////////////////////////////////////////////////////////////////////  
  chn=0;
  ADMUX=chn|defADMUX;
  ADCSR_ADSC=1;  //взвели бит запуска АЦП
  //red1=0;//зажгли кр. лампу
}  

//////////////////////////////////////////////////////////////////////////////////////////  
void adc_recountled(){
//////////////////////////////////////////////////////////////////////////////////////////  

}
//typedef enum {false=0,true=1}bool;
