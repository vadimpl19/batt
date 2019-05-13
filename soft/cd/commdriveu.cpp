//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
#pragma hdrstop

#include "commdriveu.h"
#include "constants.h"
#include "comm.h"
#include "logs.h"
#include "options.h"
//void __fastcall addmsg(const AnsiString & s,TColor color);//тело определено в uMainFort.h
 void __fastcall addmsg(char *s,TColor color);
extern "C" UINT getcrc(UCHAR *puchMsg, UINT usDataLen);
int GetData(trequest* req); //посылка запроса и получение данных по запросу
//---------------------------------------------------------------------------
short repc=3;
//данные потока
unsigned long thid;
HANDLE thhdl=0;

tdata2*RunParam=NULL;
int ch_stend=0;//хэндл рабочего порта
int stend_portn=8;
unsigned int tout=1000;// таймаут на ответный кадр в мс;
///////////////////////////////////////////////////////////////////////////////////
DWORD CALLBACK SendResThread(void *dt) //процесс коммуникации по com-порту со стендом
///////////////////////////////////////////////////////////////////////////////////

{
  tdata2 *mydat=(tdata2*)dt;
  trequest *rq;

  char ofst[2],Frame[255];
  char mess[250];
  int offset,offsetst,tmp;
  bool first=true;
  unsigned long dwError;
repeatl:
  sprintf(mess,"COM%d",stend_portn);
  ch_stend=comopen(mess,115200,&dwError);
  if(ch_stend<=0){
    if(first){
       sprintf(mess,"Ошибка открытия порта (COM%d)",stend_portn);
       addmsg(mess,clRed);
       first=false;
       }
    if(!mydat->thact)
        return 0;
    Sleep(500);
    if(!mydat->thact)
         return 0;
    goto repeatl;
  }
  sprintf(mess,"Порт стенда открыт (COM%d)",stend_portn);
  addmsg(mess,clGray);
  while(mydat->thact)
  {
    if(mydat->myqu->Count()<1)Sleep(10);
    else
    {
      rq=(trequest*)mydat->myqu->Peek();
//	  rq->senlen=0;
      char msgbuf[1000];
//      sprintf(msgbuf,"запрос fc=%x adr=%d",rq->fc,rq->adr);
//      if(!((rq->fc==1)&&(rq->adr==1)))addmsg(msgbuf,clBlue);
      GetData(rq);
      rq->active=false;
//      if(!((rq->fc==1)&&(rq->adr==1)))addmsg("завершили запрос",clGray);
      mydat->myqu->Pop();
    }
  }
  mydat->thact=false;
  return 0;
}
/////////////////////////////////////////////////////////////////////////////////
int sendfrm(int h,short adr,short fc, char * ASDU,int len){//посылка кадра, h- хэндл порта
                                                //fc код функции
                                                //ASDU - информация для передачи
                                                //len - длина ASDU
//функция подготавливает кадр к отправке и засовывает в сом-порт
/////////////////////////////////////////////////////////////////////////////////
  char  trash[3072];//временное вместилище
  char  tmpb1[blsize+6];
  char  tmpb2[(blsize+6)*2+4];
  UINT crc;
  int lw;
  if(!h) return ERR_SEND_PORT_IS_CLOSED; //порт закрыт
  if (fc>0x7F) return ERR_SEND_BAD_FC;//неверный код функции;
  PurgeComm((HANDLE)h,PURGE_RXCLEAR);//перед отправкой очистим буфер приёма порта от возможного мусора
  tmpb1[0]=(len+6)&0xff;
  tmpb1[1]=(len+6)>>8;
  tmpb1[2]=adr;
  tmpb1[3]=fc; //|0x80;
  memcpy((void*)(&tmpb1[4]),(void*)ASDU,len);
  crc=getcrc((UCHAR *)tmpb1, len+4);
  tmpb1[len+4]=(crc>>8)&0xff;
  tmpb1[len+5]=(crc)&0xff;
  len=makefrm(tmpb2,tmpb1, len+6, sizeof(tmpb2));
  lw=FileWrite((int)h, (void *)tmpb2,len);
  AnsiString s="send:";
  unsigned char ii;
  char buf[10];
  for(int i=0;i<len;i++){
    ii=tmpb2[i];
    sprintf(buf," %02X",ii);
    s=s+buf;                       //printf
  };
  addstr(s);
  if(lw==-1)return ERR_SEND_WRITE_PORT;
  else return FR_OK;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
int recfrm(int h,trecctx *recctx){// функция приема кадра
                                   // h- хендл открытого com-порта
                                   //recctx - структура автомата приема
/////////////////////////////////////////////////////////////////////////////////////////////////////////
static bool disconnected=false;
  int cnt,r,crc,curoffs;
  char buf[rbuf_size*2+4];
  if(!h) return ERR_REC_PORT_IS_CLOSED;
repeatl:
  cnt=FileRead(h,buf,sizeof(buf));
  if(cnt==-1){
    if(!disconnected)    addmsg("отвалился сом-порт - скорее всего отсытковывали устройство,подключите устройство и переинициируйте связь  нажав кнопку 'задать'",clRed);
   // init(Parameters->CSpinEdit1->Value);   //
   disconnected=true;
   return ERR_NO_CONNECT;
  }
  if((cnt!=0)&&cnt){
     AnsiString s="                             rec L= ";
    unsigned char ii;
    char buft[10];
    sprintf(buft," %03d",cnt);
    s=s+buft+" :";
    for(int i=0;i<cnt;i++){
      ii=buf[i];
      sprintf(buft," %02X",ii);
      s=s+buft;                       //printf
    };
    addstr(s);
  }
  curoffs=0;
  if(recfrm_bs(recctx,buf,cnt,&curoffs))
        return ERR_REC_NO_RESPOND; //ни чего не приняли.
/*
  while(!(recctx->rbuf[CF]&0x80))
  {
    if(recfrm_bs(recctx,buf,cnt,&curoffs))
        return ERR_REC_NO_RESPOND; //ни чего не приняли.
  }
  */
  if((recctx->rbuf[CF]&0x80)==0)goto repeatl;//приняли кадр от мастера - уходит на повтор

  if (recctx->lrec!=(recctx->rbuf[1]*0x100+(unsigned char)recctx->rbuf[0]))
        return ERR_REC_LENGTH;
  crc=getcrc((UCHAR *)recctx->rbuf, recctx->lrec);
  if (crc)
     return ERR_REC_CRC;
  return FR_OK;
}

///////////////////////////////////////////////////////////////////////////////////
int RecPacket(short adr,short fc,char* packet){
// прием кадра из линии
// возвращает длину ASDU (данные без длины СRC adr и fc) либо -1 при таймауте
////////////////////////////////////////////////////////////////////////////////////

  unsigned short hh,hh1,mm,mm1,ss,ss1,ms,ms1;
  unsigned long tmp;
  int res;
  trecctx recdat;
  TDateTime TCT,TBD=TBD.CurrentTime();
  TBD.DecodeTime(&hh,&mm,&ss,&ms);
  for(;;)
  {
    res=recfrm(ch_stend,&recdat);
    if(res==FR_OK){
      if(recdat.rbuf[AF]==adr)
      {
        if(recdat.rbuf[3]>0x0f0)continue;
        if(recdat.rbuf[3]!=(fc|0x80))continue;
             if(recdat.rbuf[AF]!=adr)continue;
        memcpy(packet,&(recdat.rbuf[4]),recdat.lrec-6);
        return recdat.lrec-6;
      }}
    else Sleep(10);
    TCT=TCT.CurrentTime();
    TCT.DecodeTime(&hh1,&mm1,&ss1,&ms1);
    tmp=(ms1-ms)+1000*((ss1-ss)+60*((mm1-mm)+60*(hh1-hh)));
    if(tmp>tout)
        break;
  }
  return -1;
}
///////////////////////////////////////////////////////////////////////////////////
int GetData(trequest* req){ //посылка запроса и получение данных по запросу
// по завершению работы req->ask сбрасывается в 0
// req->res- код завершения дублируется в выводе функции
// req->reclen - длина принятого кадра
///////////////////////////////////////////////////////////////////////////////////
  int chc=repc;
  if(req->adr==2){
    chc++;
  }
  while(chc){
            sendfrm(ch_stend,req->adr,req->fc,req->sendata,req->senlen);
//            if((tmp=RecPacket(rq->adr,rq->fc,rq->Data+offset))==-1)
//            Sleep(500);
            if((req->reclen=RecPacket(req->adr,req->fc,req->recdata))==-1)
            {
              chc--;
              req->res=ERR_REC_NO_RESPOND;
            }
            else {
               req->res=FR_OK;
               return   req->res    ;
            }
  }
  return req->res;
}
bool entered_init=false;
///////////////////////////////////////////////////////////////////////////////////
int init(int portnum){ //инициация процесса коммуникации по com-порту
///////////////////////////////////////////////////////////////////////////////////
 Sleep(10);
 while(entered_init)return ERR_INI_repeat; //защита от повторного вхождения.
 entered_init=true;

 int errcode;
// unsigned long dwError=0;
// repc=repcount;
// tout=touta;
 if(RunParam){
    RunParam->thact=0;
    unsigned long EXCD;

      GetExitCodeThread(thhdl,&EXCD);
//  while(GetExitCodeThread(thhdl,&EXCD)==STILL_ACTIVE){
    GetExitCodeThread(thhdl,&EXCD);
    while(EXCD!=0){
       Sleep(10);
       GetExitCodeThread(thhdl,&EXCD);
    }
  }
   if(ch_stend) {
     FileClose(ch_stend);ch_stend=0;
 }
 stend_portn=portnum;
       thid=1;
          if(!RunParam)RunParam=new tdata2;
          RunParam->port=(int)ch_stend;
          RunParam->myqu=new TQueue;
          RunParam->thact=1;
          thhdl=CreateThread(0,0,SendResThread,RunParam,0,&thid);



 errcode=FR_OK;//по умолчанию всё ОК
 if(!ch_stend) errcode=ERR_INI_PORT;
 else{
 }
 entered_init=false;
 return errcode;
}

#pragma package(smart_init)
/////////////////////////////////////////////////////////////////////////////////
void SendRec(trequest *nrec){ //постановка запроса в буфер запросов (FIFO)
/////////////////////////////////////////////////////////////////////////////////
  if(RunParam!=NULL){
    nrec->active=1;
    nrec->res=0x0ff;
    RunParam->myqu->Push((void*)nrec);
  }  
}