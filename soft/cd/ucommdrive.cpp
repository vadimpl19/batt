//---------------------------------------------------------------------------
#include <vcl.h>
#include <windows.h>
#include <stdio.h>
#include <inifiles.hpp>
#pragma hdrstop

#include "comm.h"
#include "hwr.h"
#include "byte_stuff.h"
#include "constants.h"
#include "ucommdrive.h"
//---------------------------------------------------------------------------
//   Important note about DLL memory management when your DLL uses the
//   static version of the RunTime Library:
//
//   If your DLL exports any functions that pass String objects (or structs/
//   classes containing nested Strings) as parameter or function results,
//   you will need to add the library MEMMGR.LIB to both the DLL project and
//   any other projects that use the DLL.  You will also need to use MEMMGR.LIB
//   if any other projects which use the DLL will be performing new or delete
//   operations on any non-TObject-derived classes which are exported from the
//   DLL. Adding MEMMGR.LIB to your project will change the DLL and its calling
//   EXE's to use the BORLNDMM.DLL as their memory manager.  In these cases,
//   the file BORLNDMM.DLL should be deployed along with your DLL.
//
//   To avoid using BORLNDMM.DLL, pass string information using "char *" or
//   ShortString parameters.
//
//   If your DLL uses the dynamic version of the RTL, you do not need to
//   explicitly add MEMMGR.LIB as this will be done implicitly for you
//---------------------------------------------------------------------------

#pragma argsused
extern unsigned short i_radio;
char ExeName[1024]="";//полное имя файла dll-ки

//данные потока
unsigned long thid;
HANDLE thhdl;
struct _tdata
{
  int port;
  TQueue *myqu;
  bool thact;
}*RunPar=NULL;
/*
int iSave(char *filename)
{//функция сохранения настроек dll-ки
 TIniFile *file=new TIniFile(filename);
 file->WriteInteger("commdrive","i_radio",i_radio);
 delete file;
 return 0;
}

int iLoad(char *filename)
{//функция загрузки настроек dll-ки
 TIniFile *file=new TIniFile(filename);
 i_radio=file->ReadInteger("commdrive","i_radio",i_radio);
 delete file;
 return 0;
}

int WINAPI DllEntryPoint(HINSTANCE hinst, unsigned long reason, void* lpReserved)
{
 char IniName[1024]="";
 GetModuleFileName(hinst,ExeName,1023);
 for (unsigned int i=0;i<strlen(ExeName)-3;i++) IniName[i]=ExeName[i];
 strcat(IniName,"ini");
 switch(reason){
  case DLL_PROCESS_ATTACH:
  //  MessageBox(0,"PROC_ATTACH",NULL,MB_OK);
  iLoad(IniName);
  break;
  case DLL_THREAD_ATTACH:
//  MessageBox(0,"THREAD_ATTACH",NULL,MB_OK);
  break;
  case DLL_PROCESS_DETACH:
//  MessageBox(0,"PROC_DETACH",NULL,MB_OK);
  iSave(IniName);
  break;
  case DLL_THREAD_DETACH:
//  MessageBox(0,"THREAD_DETACH",NULL,MB_OK);
  break;
  default:
//  MessageBox(0,"UNKNOWN",NULL,MB_OK);
  break;
 }
 return 1;
}
//---------------------------------------------------------------------------

*/
int ch1=0;
short bl_size=1000;
unsigned int delay;
DWORD speed=115200;
unsigned short i_radio=0xffff;
short repc=10;
///////////////////////////////////////////////////////////////////////////////////
DWORD CALLBACK SendResThread(void *dt) //процесс коммуникации по com-порту со стендом
///////////////////////////////////////////////////////////////////////////////////

{
  _tdata *mydat=(_tdata*)dt;
  _request *rq;
  char ofst[2],Frame[255];
  int offset,offsetst,tmp,chc=repc;
  while(mydat->thact)
  {
    if(mydat->myqu->Count()<1)Sleep(10);
    else
    {
      rq=(_request*)mydat->myqu->Peek();
      switch(rq->fc)
      {
	case TEST_CONNECTION:
	  break;
	case TEST_VOLTAGE:
	case TEST_TERMO:
//	case TEST_INPUT:
	case TEST_LOOP:
	case TEST_CALIBR:
	case POWER_ON:
	case POWER_OFF:
	case TEST_NWORK:
	case TEST_CYCLS:
	case STOP_ALL:
	case REPEAT_TEST:
	case SAVE_PARAM:
//	case TNW3:
//	case TNW4:
	  rq->res=SendPacket(rq->adr,rq->fc,rq->Data,rq->lenght);
	  break;
	case GET_VOLTAGE:
//	case GET_INPUT:
	case GET_LOOP:
	case GET_CALIBR:
	case GET_NWORK:
	case GET_TERMO:
//	case GET_TNW4:
//	case GET_TNW3:
	case GET_CYCL:
	case GET_REST:
	case REQ_NUM:
/*
	  offset=0;
	  chc=repc;
	  while(chc)
	  {
	    ofst[0]=((rq->lenght-offset)>bl_size ? bl_size:rq->lenght)&0x0ff;
	    ofst[1]=((rq->lenght-offset)>bl_size ? bl_size>>8:rq->lenght>>8)&0x0ff;
	    sendfrm(ch1,rq->adr,rq->fc,ofst,2);
	    if((tmp=RecPacket(rq->adr,rq->fc,rq->Data+offset))==-1)
	    {
	      chc--;
	      rq->res=ERR_REC_NO_RESPOND;
	    }
	    else offset+=tmp;
	    if(offset>=rq->lenght)break;
	  }
	  if(chc<1)rq->lenght=-1;
	  else rq->res=FR_OK;
*/
	  rq->senlen=0;
	  GetData(rq);
	  break;
	case BURN_FILE:
	  chc=repc;
	  while(chc)
	  {
	    sendfrm(ch1,rq->adr,rq->fc,rq->Data,rq->lenght);
	    if((tmp=RecPacket(rq->adr,rq->fc,rq->Data))==-1)
	    {
              chc--;
              rq->res=ERR_REC_NO_RESPOND;
            }
            else
            {
              rq->lenght=1;
              rq->res=FR_OK;
              break;
            }
          }
          break;
        case LOAD_FILE:
          offsetst=(unsigned char)rq->Data[0]+(unsigned char)rq->Data[1]*256;
          offset=0;
          while(rq->lenght>0)
          {
            Frame[0]=offsetst+offset&0x0ff;
            Frame[1]=(offsetst+offset>>8)&0x0ff;
            memcpy(&Frame[2],&rq->Data[2]+offset,rq->lenght>bl_size-2 ? bl_size-2:rq->lenght);
            if((rq->res=SendPacket(rq->adr,rq->fc,Frame,rq->lenght>bl_size ? bl_size:rq->lenght))==FR_OK)
              rq->lenght-=(rq->lenght>bl_size-2 ? bl_size-2:rq->lenght);
            else break;
            offset+=bl_size-2;
          }
          break;
        case FILE_CRC:
          rq->res=SendPacket(rq->adr,rq->fc,rq->Data,rq->lenght);
          if(rq->Data[0]==0)rq->res=0;
          else rq->res=ERR_REC_CRC;
          break;
        default:
          rq->res=ERR_SEND_BAD_FC;
          rq->lenght=-1;
      }
      rq->ask=false;
      mydat->myqu->Pop();
    }
  }
  return 0;
}
///////////////////////////////////////////////////////////////////////////////////
int SendPacket(short adr,short fc,char* packet,int lght)
// посылка пакета с подтверждением о доставке.
// количество повторов - repc
// таймаут - delay
// возвращает код ошибки, 0 если все ок
///////////////////////////////////////////////////////////////////////////////////
{
  unsigned short hh,hh1,mm,mm1,ss,ss1,ms,ms1;
  unsigned long tmp,ret;
  char chance=repc;
  trecctx resdat;
  while(chance)
  {
    if((ret=sendfrm(ch1,adr,fc,packet,lght))!=FR_OK)
    {
      chance--;
      continue;
    }
    TDateTime TCT,TBD=TBD.CurrentTime();
    TBD.DecodeTime(&hh,&mm,&ss,&ms);
    for(;;)
    {
      if((ret=recfrm(ch1,&resdat))==FR_OK)
        {
          if(resdat.rbuf[3]>=0x0f0)continue; //прием сообщений об ошибках. не слишком мудро их выбрасывать
          if(resdat.rbuf[3]!=(fc|0x80))continue;
          packet[0]=resdat.rbuf[4];//перекладывает первые 2 байта ASDU в packet зачем???
          packet[1]=resdat.rbuf[5];

          if(resdat.rbuf[AF]==adr)return 0;
        }
      else Sleep(10);
      TCT=TCT.CurrentTime();
      TCT.DecodeTime(&hh1,&mm1,&ss1,&ms1);
      tmp=(ms1-ms)+1000*((ss1-ss)+60*((mm1-mm)+60*(hh1-hh)));
      if(tmp>delay)
          break;
    }
    chance--;
  }
  return ret;
}
///////////////////////////////////////////////////////////////////////////////////
int GetData(_request* req){ //посылка запроса и получение данных по запросу
// по завершению работы req->ask сбрасывается в 0
// req->res- код завершения дублируется в выводе функции
// req->reclen - длина принятого кадра
///////////////////////////////////////////////////////////////////////////////////
  int chc=repc;
  while(chc){
            sendfrm(ch1,req->adr,req->fc,req->sendata,0);
//            if((tmp=RecPacket(rq->adr,rq->fc,rq->Data+offset))==-1)
            if((req->reclen=RecPacket(req->adr,req->fc,req->Data))==-1)
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
///////////////////////////////////////////////////////////////////////////////////
int RecPacket(short adr,short fc,char* packet)// прием кадра из линии
// возвращает длину ASDU (данные без длины СRC adr и fc) либо -1 при таймауте
////////////////////////////////////////////////////////////////////////////////////
{
  unsigned short hh,hh1,mm,mm1,ss,ss1,ms,ms1;
  unsigned long tmp;
  trecctx recdat;
  TDateTime TCT,TBD=TBD.CurrentTime();
  TBD.DecodeTime(&hh,&mm,&ss,&ms);
  for(;;)
  {
    if(recfrm(ch1,&recdat)==FR_OK){
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
    if(tmp>delay)
        break;
  }
  return -1;
}

int init(char * chnum, int repcount,int systime)
{
static bool first_entry=true;
 int errcode;
 unsigned long dwError=0;
// if ((blsize>1000)||(blsize<10)) return ERR_INI_BLSIZE+0x100*ERR_INI_BLSIZE;
 bl_size=blsize; //задали значение глобальной переменной
 repc=repcount;
 delay=systime;
 if(RunPar){
    RunPar->thact=0;
    unsigned long EXCD,ll;

      ll=GetExitCodeThread(thhdl,&EXCD);
//  while(GetExitCodeThread(thhdl,&EXCD)==STILL_ACTIVE){
    GetExitCodeThread(thhdl,&EXCD);
    while(EXCD!=0){
       Sleep(10);
       GetExitCodeThread(thhdl,&EXCD);
    }
  }
 if(ch1) {
     FileClose(ch1);ch1=0;
 }
 ch1=comopen(chnum,speed,&dwError);
 errcode=FR_OK;//по умолчанию всё ОК
 if(!ch1) errcode=ERR_INI_PORT;
 else{
       thid=1;
          if(!RunPar)RunPar=new _tdata;
          RunPar->port=(int)ch1;
          RunPar->myqu=new TQueue;
          RunPar->thact=1;
          thhdl=CreateThread(0,0,SendResThread,RunPar,0,&thid);
          first_entry=false;

 }
 return errcode;
}

void close_ports()
{
  RunPar->thact=0;
  ch1=0;
}

typedef unsigned char UCHAR;
typedef unsigned int UINT;
extern "C" UINT getcrc(UCHAR *puchMsg, UINT usDataLen);
/////////////////////////////////////////////////////////////////////////////////////////////////////////
int recfrm(int h,trecctx *recctx)
/////////////////////////////////////////////////////////////////////////////////////////////////////////
{
  int cnt,r,crc,curoffs;
  char buf[rbuf_size*2+4];
  if(!h) return ERR_REC_PORT_IS_CLOSED;
  cnt=FileRead(h,buf,sizeof(buf));
  curoffs=0;
  if(recfrm_bs(recctx,buf,cnt,&curoffs))
        return ERR_REC_NO_RESPOND; //ни чего не приняли.
  while(!(recctx->rbuf[CF]&0x80))
  {
    if(recfrm_bs(recctx,buf,cnt,&curoffs)) return ERR_REC_NO_RESPOND; //ни чего не приняли.
  }
  if (recctx->lrec!=(recctx->rbuf[1]*0x100+(unsigned char)recctx->rbuf[0]))return ERR_REC_LENGTH;
  crc=getcrc((UCHAR *)recctx->rbuf, recctx->lrec);
  if (crc) return ERR_REC_CRC;
  return FR_OK;
}

int sendfrm(int h,short adr,short fc, char * ASDU,int len)
{
  char  trash[3072];//временное вместилище
  char  tmpb1[sbuf_size+6];
  char  tmpb2[(sbuf_size+6)*2+4];
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
  if(lw==-1)return ERR_SEND_WRITE_PORT;
  else return FR_OK;
}

void SendRec(_request *nrec)
{
  nrec->ask=1;
  nrec->res=0x0ff;
  RunPar->myqu->Push((void*)nrec);
}

void CancelQue(void)
{
  unsigned long EXCD;
  GetExitCodeThread(thhdl,&EXCD);
  TerminateThread(thhdl,EXCD);
  delete RunPar->myqu;
  RunPar->myqu=new TQueue;
  thhdl=CreateThread(0,0,SendResThread,RunPar,0,&thid);
}

void Err1Line(unsigned short ErrCode, char *line)
{//в line добавляем символьное имя ошибки ErrCode
 switch (ErrCode){
  ////////////  2  //////////////
  case FR_OK:
  strcat(line,"FR_OK");
  break;
  case FR_CANCELED:
  strcat(line,"FR_CANCELED");
  break;
  ////////////  3  //////////////
  case ERR_SEND_WRITE_PORT:
  strcat(line,"ERR_SEND_WRITE_PORT");
  break;
  case ERR_SEND_PORT_IS_CLOSED:
  strcat(line,"ERR_SEND_PORT_IS_CLOSED");
  break;
  case ERR_SEND_BAD_FC:
  strcat(line,"ERR_SEND_BAD_FC");
  break;
  ////////////  4  //////////////
  case ERR_REC_NO_RESPOND:
  strcat(line,"ERR_REC_NO_RESPOND");
  break;
  case ERR_REC_PORT_IS_CLOSED:
  strcat(line,"ERR_REC_PORT_IS_CLOSED");
  break;
  case ERR_REC_CRC:
  strcat(line,"ERR_REC_CRC");
  break;
  case ERR_REC_LENGTH:
  strcat(line,"ERR_REC_LENGTH");
  break;
  ////////////  1  //////////////
  case ERR_TST_LENGTH:
  strcat(line,"ERR_TST_LENGTH");
  break;
  ////////////  2  //////////////
  case ERR_INI_PORT:
  strcat(line,"ERR_INI_PORT");
  break;
  case ERR_INI_BLSIZE:
  strcat(line,"ERR_INI_BLSIZE");
  break;
  ////////////  4  //////////////
  default:
  strcat(line,"UNKNOWN ERROR");
  break;
 }
}

extern "C" void ErrLine(unsigned int ErrCode,char *line)
{
 unsigned short err1;
 err1=ErrCode&0x00ff;
 strcpy(line,"Устр. 1 : ");
 Err1Line(err1,line);
}
