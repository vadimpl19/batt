//#define uart1_ex
#define ver 1
#define subver 4


//��������� �������� �� ������ � ������������ ����
#define AF 2
#define CF 3

#define	FCres 0 /* ��������� ����� ����������                   */
#define	FClink 1 /* ��������� ����������������� �����           */


#define	FCtest 2/* ���� �����                                   */

#define	FCgetbat 4 /* ������ ���������� � ���. ��������� ������� */
#define FCsetprofile 0x05  /* ������ ���������� � ���. ��������� ������� */
#define FCsetactivation 0x06 /* ������� � ����� ��������� */
#define FCsetbyprofile 0x07  /* ������� � ����� ������ �� ������� */
#define FCresetfrmcnt 0x08  /* ����� �������� ������ */
#define FCgetitems 0x09  /* �������� ������ ������� �� ������� */
#define FCcalibr 0x0a  /* ��������� ���������� */

//#define	FCgetind 0x1b 



#define	FCexept  15/*- exception �� �������                     */

#define	ex_no_support  1/*- ������������� ������� �� ��������������  */





#include <iom128.h>
#include "ina90.h"
//#include "led.h"
#include "types.h"
#include "hwr.h"
#include "byte_stuff.h"
#include "coms.h"
#include "hist.h"
#include "adc.h"
#include "timeservice.h"
#include "func_handle.h"
//#include "extRAM\RAMtest.h"
//#include "ADCm\adc.h"
extern thist hist;
extern int curoffset;
char frmcnt; //����� ���������� ������������� �����
char * forsend;//��������� �� ����� ��� ��������;
char work_mode=0;//����� ������ 0- ����� ���������
                        //       1- ���� �� ������� ��������� ���������, ��� ����.
                         //      10 - ����� ������� �� �������

extern UINT getcrc(UCHAR *puchMsg, UINT usDataLen);
char adr=2; //��� ����� ����� ����������

trecctx rec0ctx;
#ifdef uart1_ex   
trecctx  rec1ctx;
#endif
void setcur(char i);
void iniuart0(unsigned int speed,char par){
_ID

//DDRE_Bit2=1; //���������� ��� ���������� ������������ �� �����
txen0ini
SEND0OFF;
 UCSR0A=2; //���������� ���  U2X
 UCSR0B = (1<<RXEN0)|(1<<TXEN0);
 UCSR0C=((1<<1)|(1<<2));//���������� 8��� ������ � 1 ����
 switch (par){
   case none:{ 
     UCSR0C&=~((1<<UPM01)|(1<<UPM00));
     break;
   };  
   case even:{ 
     UCSR0C|= 1<<UPM01;
     UCSR0C&=~(1<<UPM10);
     break;
   };  
   case odd:{ 
     UCSR0C|= 1<<UPM01;
     UCSR0C|=1<<UPM00;
     break;
   };  
 };
/* ������� tccr0
 7 =1 - �� ����� PWM
 6,3 = zero - ������� ����
 5,4 =zero - �� ������������ ����� ���������
 2,1,zero - ������������
*/
  switch (speed){
    case 48:{
//      TCCR0CH=CTC124_0;// CTC ���� ������������ 1024;
      UBRR0L=383-256; 
      UBRR0H = (unsigned char)(383>>8);
      UBRR0L = (unsigned char)383;
      break;
    }case 96:{
//      TCCR0CH=CTC124_0; // CTC ���� ������������ 1024;
      UBRR0H = 0;
      UBRR0L = 191;
      break;
    }case 192:{
//      TCCR0CH=CTC256_0; // CTC ���� ������������ 256;
      UBRR0H = 0;
      UBRR0L = 95;
      break;
    }case 384:{
//      TCCR0CH=CTC256_0;
      UBRR0H = 0;
      UBRR0L = 47;    
      break;
    }
    case 576: {
//      TCCR0CH=CTC256_0; 
      UBRR0H = 0;
      UBRR0L = 31;
      break;
    }
    case 1152: {
//      TCCR0CH=CTC256_0; 
      UBRR0H = 0;
      UBRR0L = 15;
      break;
    }
    default: { //57600
//      TCCR0CH=CTC256_0; 
      UBRR0H = 0;
      UBRR0L = 31;
      break;
   };                 
  };

//  TCNT0CH=0;
//  OCIE0CH=1;//��������� ���������� �� �������  �� COMP !!!!!!
  inirec(&rec0ctx);
//  redon2
  UCSR0B|=(1<<RXCIE0); //��������� ���������� �� ���������
_IE  
};
#ifdef uart1_ex   
void iniuart1(unsigned int speed,char par){
_ID

//DDRE_Bit2=1; //���������� ��� ���������� ������������ �� �����
txen1ini
SEND1OFF;
 UCSR1A=2; //���������� ���  U2X
 UCSR1B = (1<<RXEN1)|(1<<TXEN1);
 UCSR1C=((1<<1)|(1<<2));//���������� 8��� ������ � 1 ����
 switch (par){
   case none:{ 
     UCSR1C&=~((1<<UPM11)|(1<<UPM10));
     break;
   };  
   case even:{ 
     UCSR1C|= 1<<UPM11;
     UCSR1C&=~(1<<UPM10);
     break;
   };  
   case odd:{ 
     UCSR1C|= 1<<UPM11;
     UCSR1C|=1<<UPM10;
     break;
   };  
 };
/* ������� tccr0
 7 =1 - �� ����� PWM
 6,3 = zero - ������� ����
 5,4 =zero - �� ������������ ����� ���������
 2,1,zero - ������������
*/
  switch (speed){
    case 48:{
//      TCCR0CH=CTC124_0;// CTC ���� ������������ 1024;
      UBRR1L=383-256; 
      UBRR1H = (unsigned char)(383>>8);
      UBRR1L = (unsigned char)383;
      break;
    }case 96:{
//      TCCR1CH=CTC124_0; // CTC ���� ������������ 1024;
      UBRR1H = 0;
      UBRR1L = 191;
      break;
    }case 192:{
//      TCCR1CH=CTC256_0; // CTC ���� ������������ 256;
      UBRR1H = 0;
      UBRR1L = 95;
      break;
    }case 384:{
//      TCCR1CH=CTC256_0;
      UBRR1H = 0;
      UBRR1L = 47;    
      break;
    }
    case 576: {
//      TCCR1CH=CTC256_0; 
      UBRR1H = 0;
      UBRR1L = 31;
      break;
    }
    case 1152: {
//      TCCR1CH=CTC256_0; 
      UBRR1H = 0;
      UBRR1L = 15;
      break;
    }
    default: { //57600
//      TCCR1CH=CTC256_0; 
      UBRR1H = 0;
      UBRR1L = 31;
      break;
   };                 
  };
  inirec(&rec1ctx);
  UCSR1B|=(1<<RXCIE1); //��������� ���������� �� ���������
  _IE  
};
#endif //uart1
//trecctx rec0ctx,rec1ctx;
#pragma vector=USART0_TXC_vect
__interrupt void tx0end_isr() {

//      red3^=1;
      UCSR0B|=(1<<RXCIE0);//��������� ���������� �� ���������
      UCSR1B|=(1<<RXCIE1);//��������� ���������� �� ���������
      UCSR0B&=~(1<<TXCIE0); //���������  ���������� �� ���������� ������������ ����. �����
      EI
//      UCSR0B|=(1<<RXCIE0);//��������� ���������� �� ���������
      SEND0OFF
      inirec(&rec0ctx);
}
#pragma vector=USART0_RXC_vect
__interrupt void rx0_isr() {
char r;
UCSR0B&=~(1<<RXCIE0);//��������� ���������� �� ���������
    EI


r=recnextch(UDR0,&rec0ctx);
if (r==10) { //������ ����� ������ �����
  TCNT1=0; 
  OCR1A = 0xffff;//68
  TIFR = (1<<OCF1A); //�������� ��������� ����������.
  //PORTF_Bit6 = 1;//KT1
//  TIMSK |= (1<<OCIE1A); //��������� ���������� �� �������.
}

   CLI
UCSR0B|=(1<<RXCIE0); //��������� ���������� �� ���������
if (!r){//������� ����

  UCSR0B&=~(1<<RXCIE0);//��������� ���������� �� ���������
//  red1^=1;
};
};
#ifdef uart1_ex   
#pragma vector=USART1_RXC_vect
__interrupt void rx1_isr() {
char r;
UCSR1B&=~(1<<RXCIE1);//��������� ���������� �� ���������
    EI
//gron1  
r=recnextch(UDR1,&rec1ctx);

if (r==10) { //������ ����� ������ �����
  TCNT3=0;
  OCR3A = 0xffff;//68 us
  ETIFR = (1<<OCF3A); //�������� ��������� ����������.
//  TIMSK |= (1<<OCIE3A); //��������� ���������� �� �������.
//PORTF_Bit6 = 1;//KT2
}

   CLI
UCSR1B|=(1<<RXCIE1); //��������� ���������� �� ���������
if (!r){//������� ����
//  if (rec1ctx.lrec!=9) redon2;
 UCSR1B&=~(1<<RXCIE1);//��������� ���������� �� ���������
// gron2
};

};
#endif //uart1
//unsigned char first0,cnt0,first1,cnt1;
//unsigned int size0,size1;
 




tsenctx sen0ctx;
#pragma vector=USART0_UDRE_vect
__interrupt void tx0_isr()
{char ch;
  UCSR0B&=~(1<<UDRIE0); //��������� ���������� �� ����������� ������� 7.07
  EI
  
  if (!getnextch(&ch, &sen0ctx)){
  
    UDR0=ch;
    addh((sen0ctx.senst<<8)+ch);
   // gronw
   }else  {
      addh(0xbbbb);
      UCSR0B&=~(1<<UDRIE0); //��������� ���������� �� �����������
      UCSR0B|=(1<<TXCIE0); //���������  ���������� �� ���������� ������������ ����. �����
      //redonw
//      SEND0OFF
//      redonw
//      UCSR0B|=(1<<RXCIE0);//��������� ���������� �� ���������
      return; //������� 7.07
  }
  CLI
  UCSR0B|=(1<<UDRIE0); //��������� ���������� �� ����������� ������� 7.07
};

short chkfrm(char adr,trecctx *ctx){//�������� ������������ ��������� �����
/*
���������� 0 - ��� 0�
1 - �� ������� �����
2 - ��� ���� �� ��� 1-� �������
3 - ��� ���� �� �� �������
4 - ������ �RC
*/

//redon3
//gron4
if (ctx->lrec!=(ctx->rbuf[0]+((int)(ctx->rbuf[1])<<8))) return 1;

if (ctx->rbuf[AF]!=adr) return 2;
//redon3
if ((ctx->rbuf[CF]&0x80)!=0) return 3;

if(getcrc((UCHAR *)(ctx->rbuf), ctx->lrec)) return 4;
//redon2
return 0;
}

typedef struct {
     int len;
     char adr;
     char cf;
     char asdu[sbuf_size-2];
}tsbuf;
tsbuf sbuf;


void _copy(char * source,char *dest,UINT len){
while (len) {*dest=*source; dest++;source++;len--;};
}

void sendexept(){
int crc;
       // addh(0xaaa1); 
       sbuf.len=rec0ctx.rbuf[0]+ (rec0ctx.rbuf[1]<<8);
       sbuf.len++;
       sbuf.adr=adr;
       sbuf.cf=0x80|FCexept;
       sbuf.asdu[0]=ex_no_support;
       _copy(&rec0ctx.rbuf[3],&sbuf.asdu[1],rec0ctx.lrec-5);  
       crc=getcrc((UCHAR *)&sbuf, sbuf.len-2);
       sbuf.asdu[sbuf.len-6]=crc>>8;
       sbuf.asdu[sbuf.len-5]=crc&0xff; 
       inisend(sbuf.len,(char *)&sbuf,&sen0ctx);
       SEND0ON 
       UCSR0B|=(1<<UDRIE0); //��������� ���������� �� �����������
}

inisendfrm(int len,char * sbuf){
int crc;
       sbuf[0]=len&0xff;
       sbuf[1]=len>>8;
       sbuf[2]=adr;
       crc=getcrc((UCHAR *)sbuf, len-2);
       sbuf[len-2]=crc>>8;
       sbuf[len-1]=crc&0xff;  
       inisend(len,sbuf,&sen0ctx);
       SEND0ON 
       UCSR0B|=(1<<UDRIE0); //��������� ���������� �� �����������
       inirec(&rec0ctx);//�������������� �����. ����� ����������!!!
}


extern unsigned int FileSIZE[32];
extern unsigned char FSTATUS[32];

char sendbuf[200];
char prbufcur;//����� ��� ������ ��� ���
int curoffset=0;
char * curbuf;

char prbuf0[prbufsize];
char prbuf1[prbufsize];
int offset1,offset2;
tprofile profile;     

void setch(int absad,char ch){

 if( *(( unsigned int __eeprom *)(absad))==ch)return;//����� �� ����������, ������ �� �����
 
  while(EECR & (1<<EEWE));    /* Wait for completion of previous write */
__disable_interrupt();
/* Set up address and data registers */
EEAR = absad;
EEDR = ch;
/* Write logical one to EEMWE */
EECR |= (1<<EEMWE);
/* Start eeprom write by setting EEWE */
EECR |= (1<<EEWE);   
__enable_interrupt();
//  while(EECR & (1<<EEWE));    
}
////////////////////////////////////////////////////////////////////////////////////////////
void read_settings(){// ������ ���������� � ���
/////////////////////////////////////////////////////////////////////////////////////////////
  char * p=(char *)&profile;
  char ch;
  for(int i=0;i<sizeof(tprofile);i++ ){
     ch=*(( unsigned char __eeprom *)i);
     *p=ch;
     p++;
     __watchdog_reset();
  };
  if(profile.cnt==0xff){ //eeprom ������, ������ ��������� �� ���������
     profile.cnt=2;
     profile.curr[0]=100;
     profile.curr[1]=0;
     profile.dur[0]=50;
     profile.dur[1]=50;
     profile.act_cur=100;
     profile.act_cur_level=90;
     profile.act_time=600;
  }
}
  
  

////////////////////////////////////////////////////////////////////////////////////////////
void wr_settings(){// ������ ���������� � eeprom 
/////////////////////////////////////////////////////////////////////////////////////////////
  char * p=(char *)&profile;
  __watchdog_reset();
  for(int i=0;i<sizeof(tprofile);i++){
     setch(i,*p++);
     __watchdog_reset();
  }
}
      
void setrg(UINT address,UINT rg){
  setch(address*2,rg&0xff);
   while(EECR & (1<<EEWE));    /* Wait for completion of previous write */
  setch(address*2+1,rg>>8);
  while(EECR & (1<<EEWE));    /* Wait for completion of previous write */
};
//#define answerb_size 100
//char answerb[answerb_size];
char oldportg=0;
char need_portgsel;
///////////////////////////////////////////////////////////////////////////////////////
void sendack(char retcode){
///////////////////////////////////////////////////////////////////////////////////////
//          answerb[3]=FCset_relays+0x80;
   sendbuf[3]=rec0ctx.rbuf[CF]|0x80 ;
   sendbuf[4]=retcode;
   inisendfrm(5+2,sendbuf);
}
int senlen=0;//����� ����� �� �������� � ������ forsend
void ini_workbyprofile();
void ini_activation();
///////////////////////////////////////////////////////////////////////////////////////
void req0handle(){
///////////////////////////////////////////////////////////////////////////////////////
//char senbuf[]="abcd";
//int r;
//gr3^=1;
//int s;
//char res;

if (rec0ctx.recst==3) { //��� ������ ���� 3

  if(chkfrm(adr,&rec0ctx)) goto errfrm0 ;
  switch (rec0ctx.rbuf[CF]){
     //------------------------------------------------------------------------  
  
  case FClink: //��������� �����     
          //answerb[0]=adr;
          sendbuf[3]=FClink+0x80;
          sendbuf[4]=1;
          sendbuf[5]=0;
          sendbuf[6]=ver;
          sendbuf[7]=subver;
          sendbuf[8]=work_mode;
          memcpy(&sendbuf[9],&profile,sizeof(tprofile));
          inisendfrm(9+2+sizeof(tprofile),sendbuf);
          break;
       
/*     
     case FCget_hist:{
      
          sendbuf[3]=FCset_ref+0x80;
          for (s=0;s<sizeof(hist.harr)/2;s++){
            sendbuf[4+s*2]=hist.harr[s];
            sendbuf[4+s*2+1]=hist.harr[s]>>8;
          }          
          inisendfrm(sizeof(hist),(char *)&sendbuf);
          break;
     }
*/          
     case FCgetbat://������ ����. �������
    {
      sendbuf[3]=FCgetbat+0x80;      
//      sendbuf[4]=0;
      sendbuf[4]=work_mode;
      memcpy(&sendbuf[5],batt,sizeof(tbatt)*4);
         inisendfrm(4+2+sizeof(tbatt)*4,(char *)&sendbuf);

     }
     break;
  case FCsetprofile://������ ������������
     sendack(0);
     inirec(&rec0ctx);//�������������� �����. ������� ������, ����� �� �������� ������ ������ ��������� wr_settings
     __watchdog_reset();
     memcpy(&profile,&rec0ctx.rbuf[CF+1],sizeof(tprofile));
     wr_settings();
     if(work_mode!=10)ini_activation();
     else ini_workbyprofile();
     return;
  case FCsetactivation://������� � ����� ���������
     sendack(0);
     ini_activation();
     break;
  case FCsetbyprofile://������� � ����� ������� �� �������
     sendack(0);
     ini_workbyprofile();
     stepcnt=0;
     break;
  case FCresetfrmcnt://
     sendack(0);
     frmcnt=0;
     break;
  case FCgetitems:
    if((senlen!=0)&&(frmcnt==rec0ctx.rbuf[4])){
      //���� ���������;
      inisendfrm(senlen,forsend);
    }else{
      //������ ������ ������
      frmcnt=rec0ctx.rbuf[4];
      if(forsend==prbuf0){
        forsend=prbuf1; //�������� � 1-��, ��������� 0-�
        curbuf=prbuf0;
        senlen=curoffset+1;
//        offset0=0;//���������� ������� ����������� ������
//         offset1=framenum+2;
        curoffset=  framenum+2;
        
      }else{
        forsend=prbuf0;
        curbuf=prbuf1;
        senlen=curoffset+1;
        curoffset=  framenum+2;
      }
       curbuf[framenum+1]=0;//�������� ���� ������������
      forsend[CF]=0x80+FCgetitems;
      forsend[framenum]=frmcnt;
       inisendfrm(senlen,(char *)forsend);
       
    }
    
    break;
  case FCcalibr://��������� ��������� ����������
     sendack(0);
     inirec(&rec0ctx);//�������������� �����. ������� ������, ����� �� �������� ������ ������ ��������� 
     __watchdog_reset();
     calibration();
    return;
    

  default: sendexept();  
  }
  inirec(&rec0ctx);//�������������� �����. ����� ����������!!!
  return;
errfrm0:   
   inirec(&rec0ctx);//�������������� �����. ����� ����������!!!
   UCSR0B|=(1<<RXCIE0); //��������� ���������� �� ���������
   
   
}
};

