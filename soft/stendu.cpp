#define id_set_relays 0x12
#include <vcl.h>
#pragma hdrstop

#include "stendu.h"
#include <fstream.h>
#include <stdio.h>
#include "constants.h"
#include "options.h"
#include "uMainForm.h"

tconnectb *connectb;
void __fastcall addmsg(char * s,TColor color);

///////////////////////////////////////////////////////////////////////////////////
DWORD CALLBACK boardthread(void *dt){ //процесс коммуникации по com-порту
///////////////////////////////////////////////////////////////////////////////////
 tboard * dev=(tboard*)dt;
  while(!dev->startthr_r)Sleep(10);//ждем отработки конструктора дочернего класса;
  while(!dev->closingth_req){
   dev->thrbody();
   Sleep(10);
  }
  return 0;
}
///////////////////////////////////////////////////////////////////////////////////
void __fastcall tboard::thrbody(){//тело потока работы с удаленным устройством
///////////////////////////////////////////////////////////////////////////////////
   if(connecting_req){
      resetconnect();

   };

   switch (state){
     case ini_st:
     /*
        if(ch_stend<=0){

             Sleep(500);
             return;

        }
      */  
        if(!connect)
           connecting();
        if(connect)state=idle;
     break;
     case idle:
        if(wait_forendop_req)wait_forendop_body();

     break;
     default: state=ini_st;
   }
}
///////////////////////////////////////////////////////////////////////////////////
void tboard::wait_forendop_body(){   //функция ожидания окончания отработки запроса, в данном проекте не используется
///////////////////////////////////////////////////////////////////////////////////
repeatl:
    wait_forendop_rdy=false;
    req.adr=req.adr;
    req.fc=FCgetind;
    req.senlen=0;
    req.res=0;
        SendRec(&req);
        int cnt=0;
        while(req.active){
           Sleep(50);
           cnt++;
           if(cnt>200){
             addmsg("Сбой в работе wait_forendop_body - отсутствие ответа на запрос. Поставим заново.",clRed);
             goto repeatl;
           }
        }
        if(req.res!=0){//ошибка cвязи
           lasterr=req.res;
           req.res=ERR_NO_CONNECT;
           req.active=false;//c
           connecting_req=true;
           wait_forendop_req=false;
           wait_forendop_rdy=true;
           return;
        };
        if (req.reclen>sizeof(statear)){
          lasterr=ERR_TOO_LONG;
          wait_forendop_rdy=true;
          wait_forendop_req=false;

          return;
        };
        memcpy(statear,req.recdata,req.reclen);
        perform_answ_for_endop();
        if(req.recdata[0]&0x80)goto repeatl;
          wait_forendop_rdy=true;
          wait_forendop_req=false;

}

///////////////////////////////////////////////////////////////////////////////////
void tboard::resetconnect(){//сбросить установленный коннект с устройством
///////////////////////////////////////////////////////////////////////////////////
   connect=false;
   state=ini_st;
   Sleep(200);
}
///////////////////////////////////////////////////////////////////////////////////
tboard::tboard(){
///////////////////////////////////////////////////////////////////////////////////
   startthr=false;
   req.active=false;
   req.res=0;
   closingth_req=false;
   wait_forendop_req=false;
   connect=false;
   state=ini_st;
   thh=(int)CreateThread(0,0,boardthread,this,0,&thid);


};
///////////////////////////////////////////////////////////////////////////////////
tconnectb::tconnectb(){
///////////////////////////////////////////////////////////////////////////////////
req.adr=2;
name="Плата активации батарей";

startthr=true;
};
///////////////////////////////////////////////////////////////////////////////////
void tboard::connecting(){   //процедура установления связи.вызывается в потоке класса
///////////////////////////////////////////////////////////////////////////////////
  trequest   reqc;
  char mess[250];
  char mess2[250];
     //for(int i=0;i<repc;i++){
        reqc.adr=req.adr;
        reqc.fc=GET_INFO;
        reqc.senlen=0;
        reqc.active=true;
        SendRec(&reqc);
        while(reqc.active)Sleep(50);
        if(reqc.res!=0){
           lasterr=reqc.res;
           if(req.active){
             req.res=ERR_NO_CONNECT;
             req.active=false;//c
           }
           return;

        }; //ошибка при коннекте
        if (reqc.reclen>sizeof(config)){lasterr=ERR_TOO_LONG; return;};
        //memcpy(config,reqc.recdata,reqc.reclen);
//        if(req.adr!=1)
        ver=reqc.recdata[2];
        subver=reqc.recdata[3];
        work_mode=reqc.recdata[4];
        memcpy(&profile,&reqc.recdata[5],sizeof(tprofile));
        Parameters->act_cur_e->Value=profile.act_cur;
        Parameters->act_cur_level_e->Value=profile.act_cur_level;
        Parameters->act_time->Text=FloatToStrF(profile.act_time/10.0,ffFixed,8,1);

        Parameters->period->Text=FloatToStrF(profile.period/10.0,ffFixed,8,1);
        Parameters->act_time->Text=FloatToStrF(profile.act_time/10.0,ffFixed,8,1);
        Parameters->RichEdit1->Clear();
        ast s;
        for(int i=0;i<profile.cnt;i++){
           s=IntToStr(profile.curr[i])+";"+IntToStr(profile.dur[i]);
           Parameters->RichEdit1->Lines->Add(s);
        }

        MainForm->GroupBox1->Enabled=true;
        MainForm->GroupBox2->Enabled=true;
        if(work_mode==10){
             MainForm->byProfileB->Down=true;
        }else{
            MainForm->ActivB->Down=true;
        }
//        EnterCriticalSection(&MainForm->Sect1);

        sprintf(mess," : Связь установлена. Версия ПО %d.%d",ver,subver);
        strcpy(mess2,name.c_str());
        strcat(mess2,mess);
        addmsg(mess2,clGreen);
        // получим сотояние устройства
        /*
        reqc.fc=fc_getind;
        reqc.senlen=0;
        reqc.res=0;
        reqc.active=true;
        SendRec(&reqc);
        while(reqc.active)Sleep(50);
        if(reqc.res!=0){
           lasterr=reqc.res;
           if(req.active){
             req.res=ERR_NO_CONNECT;
             req.active=false;//c
           }
           return;

        }; //ошибка при коннекте
        memcpy(statear,reqc.recdata,reqc.reclen);
        perform_answ_for_endop();
        */
        connect=true;
        connecting_req=false;

}
///////////////////////////////////////////////////////////////////////////////////
int tconnectb::sendstopall(){   //отрубить все по команде стоп
///////////////////////////////////////////////////////////////////////////////////
}


///////////////////////////////////////////////////////////////////////////////////
int tboard::setreq_wait_forendop(){//постановка запроса на ожидание окончания обработки команды
///////////////////////////////////////////////////////////////////////////////////
   if(wait_forendop_req)return ERR_REQ_ACTIVE;//ужев обработке
   if (req.active)return ERR_REQ_ACTIVE;// уже активен какой то запрос
   wait_forendop_rdy=false;
   wait_forendop_req=true;
   return 0;//
}
///////////////////////////////////////////////////////////////////////////////////
int tboard::wait_forendop(){//ожидание окончания обработки команды
///////////////////////////////////////////////////////////////////////////////////
   if(wait_forendop_req)return 1;//в обработке
   if (!wait_forendop_rdy)return 1;//
  return req.res;
}



#pragma package(smart_init)
