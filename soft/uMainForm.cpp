//коды функций для обработчика таймера
//#define start_nu 1
//#define metrtime 0
//#define show_autorisation 1 /* показываем диалог */


//#define maxcommand 3
#include <vcl.h>
#include <stdio.h>
#pragma hdrstop

#include <inifiles.hpp>
#include "stdlib.h"
#include "cd\byte_stuff.h"
//#include "cd\ucommdrive.h"
#include "commdriveu.h"
#include "logs.h"
#include "uMainForm.h"
#include "About.h"
#include "Options.h"
#include "constants.h"

#include "stendu.h"
#pragma package(smart_init)
#pragma link "CSPIN"
#pragma resource "*.dfm"

#define RedOrGreen(s1,t1,b1) if((s1>=b1)&&(s1<t1)){this->RichEdit1->SelAttributes->Color=clGreen;\
this->Edit1->Color=clGreen;}\
else {ErrRes=true;this->RichEdit1->SelAttributes->Color=clRed;this->Edit1->Color=clRed;}

#define RequestBUF blsize+10

bool repeatFAC43= false;
bool repeatFAC44=false;
bool PortOK=false;
TMainForm *MainForm;

#pragma pack(push,1)
typedef struct{
  __int32 time;//время от начала работы в данном режиме
  __int16 curr[4];
  __int16 v[4];
}titem;
#pragma pack(pop)
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
				: TForm(Owner)
{
 f_current=-1;
 stopreq=false;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormCreate(TObject *Sender)
{
	String str;
	int res;
         //DecimalSeparator='.';
        msg_q=new TQueue();
	this->MainRQ.fc=0;

//	IBaseDir= ExtractFilePath(Application->ExeName);
        //inilog("com.log");

//         set_combClick((TObject*)0);//инициализация сом-порта
        //создаем критическую секцию
//        InitializeCriticalSection(&Sect1);
        connectb=new tconnectb();
        Timer1->Enabled=true;
}
class tqitem{
   public:
   //AnsiString s;
   char str[5000];
   TColor color;
};
//void __fastcall addmsg(const AnsiString & s,TColor color){
 void __fastcall addmsg(char *s,TColor color){
//    EnterCriticalSection(&MainForm->Sect1);
       tqitem * q=new tqitem();
//       q->s=s;
       strcpy(q->str,s);
       q->color=color;
       MainForm->msg_q->Push(q);

//    LeaveCriticalSection(&MainForm->Sect1);
}
void __fastcall TMainForm::process_addmsg(){
   if(msg_q->Count()>0){                        //почему здесь возникает Exception?
     tqitem * q=(tqitem*)MainForm->msg_q->Pop();
     RichEdit1->SelAttributes->Color=q->color;
     RichEdit1->Lines->Add(q->str);

     delete q;
  }
}
void __fastcall TMainForm::process_devstate(){
}

//---------------------------------------------------------------------------
bool __fastcall TMainForm::sendparam(TObject *Sender)
{
	if(PortOK){
		CancelQue();
		return true;
	}
	return false;
};
char lastp,lastinout;
trequest stopr;
unsigned char datastop[255];
void __fastcall TMainForm::SaveDataCSV(TObject *Sender)
{
	this->SaveDialog1->Execute();
}

void __fastcall TMainForm::enableallb(){
}
//---------------------------------------------------------------------------
//extern "C" UINT getcrc_ini(UCHAR *puchMsg, UINT usDataLen, UINT iniCRC);

void __fastcall TMainForm::N1Click(TObject *Sender)
{
  this->RichEdit1->Clear();
}
void __fastcall TMainForm::BitBtn1Click(TObject *Sender)
{
	AboutBox->ShowModal();
}

//**********************************************************

//****************************************************************************




void __fastcall TMainForm::Timer1Timer(TObject *Sender)
{
  MainForm->Timer1->Enabled=false;
  process_addmsg();
  //process_devstate();
  getbatt();

  MainForm->Timer1->Enabled=true;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormActivate(TObject *Sender)
{
         AnsiString ASG="Федя";
//        memcpy(MainU.Name,ASG.c_str(),ASG.Length());

}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormDestroy(TObject *Sender)
{
closelog();
delete  connectb;
delete RunParam->myqu;
delete RunParam;
//FreeLibrary(dllp);
}

void TMainForm::settout(int tout){
   touttimer->Enabled=false;
   toutexpired=false;
   touttimer->Interval=tout;
   touttimer->Enabled=true;
}



void __fastcall TMainForm::touttimerTimer(TObject *Sender)
{
toutexpired=true;
touttimer->Enabled=false;
}
//---------------------------------------------------------------------------


#pragma pack(push,1)
typedef struct {
  char state;
  __int16 v;//напряжение в милливольтах int
  __int16 curr;//ток в десятках микроампер
  long time;//время активации в сотнях мs
  long begt;//время  начала посл. цикла активации
  long endt;//ремя оконч. активации
  __int16 charge_hi;//снятый заряд, верхние 16 разрядов
  unsigned long charge;//снятый заряд
}tbatt;
#pragma pack(pop)

tbatt batt[4];
char st[5][40]={"Отсутствует бат.","Активация","Ожидание","Готово","Неверн. состояние"};
char * getstate(unsigned int num){
  if(num>3)return st[4];
  return st[batt[num].state];

}
AnsiString *itemtostr(titem* p){
 static ast s;
 s=FloatToStrF(p->time/10.0,ffFixed,5,1);
 for(int i=0;i<4;i++){
   s+="; "+FloatToStrF(p->v[i]/1000.0,ffFixed,5,3);
   s+="; "+FloatToStrF(p->curr[i]/100.0,ffFixed,5,1);
 }
 s+="\n";
 return &s;
}
////////////////////////////////////////////////////////////////////////////////////
Extended getcharge(int num){//расчет отобранной емкости в миллиампер-часах
////////////////////////////////////////////////////////////////////////////////////
Extended res=batt[num].charge_hi;
res=res*(2^32);
res=res+batt[num].charge;
res*=1.666666e-3/3600*2*1000/169/100;
return res;
}
char frmcnt=0;
void __fastcall TMainForm::getbatt(){
  //return;//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  if(connectb->req.active){
     return ;
  }
  int i=1;

  if((connectb->req.fc==FCgetbat)&&(connectb->req.res==0)){
     work_mode=connectb->req.recdata[0];
     memcpy(&batt[0],&connectb->req.recdata[1],sizeof(tbatt)*4);
     //прорисовка состояния батарей
      if(batt[0].state!=0)batbox1->Visible=true;
    else batbox1->Visible=false;
    if(batt[1].state!=0)batbox2->Visible=true;
    else batbox2->Visible=false;
    if(batt[2].state!=0)batbox3->Visible=true;
    else batbox3->Visible=false;
    if(batt[3].state!=0)batbox4->Visible=true;
    else batbox4->Visible=false;

    batv1->Text=FloatToStrF(batt[0].v/1000.0,ffFixed,5,3);
    batv2->Text=FloatToStrF(batt[1].v/1000.0,ffFixed,5,3);
    batv3->Text=FloatToStrF(batt[2].v/1000.0,ffFixed,5,3);
    batv4->Text=FloatToStrF(batt[3].v/1000.0,ffFixed,5,3);

    batc1->Text=FloatToStrF(batt[0].curr/100.0,ffFixed,5,1);
    batc2->Text=FloatToStrF(batt[1].curr/100.0,ffFixed,5,1);
    batc3->Text=FloatToStrF(batt[2].curr/100.0,ffFixed,5,1);
    batc4->Text=FloatToStrF(batt[3].curr/100.0,ffFixed,5,1);

    batt1->Text=FloatToStrF(batt[0].time/10.0,ffFixed,5,2);
    batt2->Text=FloatToStrF(batt[1].time/10.0,ffFixed,5,2);
    batt3->Text=FloatToStrF(batt[2].time/10.0,ffFixed,5,2);
    batt4->Text=FloatToStrF(batt[3].time/10.0,ffFixed,5,2);

    batch1->Text=FloatToStrF(getcharge(0),ffFixed,8,4);
    batch2->Text=FloatToStrF(getcharge(1),ffFixed,8,4);
    batch3->Text=FloatToStrF(getcharge(2),ffFixed,8,4);
    batch4->Text=FloatToStrF(getcharge(3),ffFixed,8,4);

    batst1->Caption=getstate(0);
    batst2->Caption=getstate(1);
    batst3->Caption=getstate(2);
    batst4->Caption=getstate(3);
  }
  if(connectb->req.fc==FCgetitems)
    if(connectb->req.res==0){
    frmcnt++;
    if(connectb->req.reclen>2){
     //получили данные
     titem * p;
     if(connectb->req.recdata[2]!=0)addmsg("Было переполнение буфера на передачу в устройстве. Часть данных потеряна!",clRed);
     int recoffs=3;
     ast s="";
     while(recoffs<connectb->req.reclen){
       p=(titem*)&connectb->req.recdata[recoffs];
       s=s+*itemtostr(p);
       recoffs+=sizeof(titem);
     }

     addmsg(s.c_str(),clGreen);
     addcsv(s);
     #define vlev 300
     //добавили строчку в csv и в окно ввода
    batt[0].v=p->v[0];
    batt[1].v=p->v[1];
    batt[2].v=p->v[2];
    batt[3].v=p->v[3];

    batt[0].curr=p->curr[0];
    batt[1].curr=p->curr[1];
    batt[2].curr=p->curr[2];
    batt[3].curr=p->curr[3];
    if(batt[0].v>vlev)batbox1->Visible=true;
    else batbox1->Visible=false;
    if(batt[1].v>vlev)batbox2->Visible=true;
    else batbox2->Visible=false;
    if(batt[2].v>vlev)batbox3->Visible=true;
    else batbox3->Visible=false;
    if(batt[3].v>vlev)batbox4->Visible=true;
    else batbox4->Visible=false;

    batc1->Text=FloatToStrF(p->curr[0]/100.0,ffFixed,5,1);
    batc2->Text=FloatToStrF(p->curr[1]/100.0,ffFixed,5,1);
    batc3->Text=FloatToStrF(p->curr[2]/100.0,ffFixed,5,1);
    batc4->Text=FloatToStrF(p->curr[3]/100.0,ffFixed,5,1);
    batst1->Caption="раб. по профилю";
    batst2->Caption="раб. по профилю";
    batst3->Caption="раб. по профилю";
    batst4->Caption="раб. по профилю";
    batv1->Text=FloatToStrF(p->v[0]/1000.0,ffFixed,5,3);
    batv2->Text=FloatToStrF(p->v[1]/1000.0,ffFixed,5,3);
    batv3->Text=FloatToStrF(p->v[2]/1000.0,ffFixed,5,3);
    batv4->Text=FloatToStrF(p->v[3]/1000.0,ffFixed,5,3);
    }
  }
  if(work_mode==10){
    connectb->req.fc=FCgetitems;
    connectb->req.senlen=1;
    connectb->req.sendata[0]=frmcnt;
    connectb->req.active=true;
    SendRec(&connectb->req);
    return ;
  }else{
    connectb->req.fc=FCgetbat;
    connectb->req.senlen=0;
    connectb->req.active=true;
    SendRec(&connectb->req);
    return ;
  }
//	}

}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N2Click(TObject *Sender)
{
Parameters->Visible=true;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N4Click(TObject *Sender)
{
// AboutBox->Visible=true;
 AboutBox->ShowModal();
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::ActivBClick(TObject *Sender)
{
AnsiString s;
if(!ActivB->Down) return;
  closecsv();
  ActivB->Enabled=false;
  byProfileB->Enabled=false;
  trequest req;
  req.fc=FCsetactivation;
  req.adr=connectb->req.adr;
  req.senlen=0;
  req.active=true;
  SendRec(&req);
  while(req.active){
     Application->ProcessMessages();
  }
  if(req.res!=0){
     s="Ошибка при пересылке данных";
      alert(s.c_str());
     ActivB->Down=false;
  }else work_mode=0;//перешли в режим активации

  ActivB->Enabled=true;
  byProfileB->Enabled=true;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::byProfileBClick(TObject *Sender)
{
AnsiString s;
if(!byProfileB->Down) return;
  if(inicsv()<=0){
    Application->MessageBoxA("Ошибка создания файла csv","ошибка");
    ActivB->Down=true;
    return;
  }  
  ActivB->Enabled=false;
  byProfileB->Enabled=false;
  trequest req;
  req.fc=FCsetbyprofile;
  req.adr=connectb->req.adr;
  req.senlen=0;
  req.active=true;
  SendRec(&req);
  while(req.active){
     Application->ProcessMessages();
  }
  if(req.res!=0){
     s="Ошибка при пересылке данных";
      alert(s.c_str());
     byProfileB->Down=false;
  }else work_mode=10;//перешли в режим работы по профилю
  frmcnt=0;
  ActivB->Enabled=true;
  byProfileB->Enabled=true;
}
//---------------------------------------------------------------------------

