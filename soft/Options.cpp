//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Options.h"
#include "uMainForm.h"
#include <inifiles.hpp>
#include "stendu.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CSPIN"
#pragma resource "*.dfm"
TParameters *Parameters;
//---------------------------------------------------------------------------
__fastcall TParameters::TParameters(TComponent* Owner)
        : TForm(Owner)
{
}

/////////////////////////////////////////////////////////////////////////////////
void __fastcall TParameters::FormCreate(TObject *Sender){
/////////////////////////////////////////////////////////////////////////////////
  //�������� ����������� � ���-����� �������
  ast s=ExtractFilePath(Application->ExeName);
  TIniFile* inif=new TIniFile(s+"par.ini");
  CSpinEdit1->Value=inif->ReadInteger("params","stend_com",1);
  delete inif;
  init(CSpinEdit1->Value);

}
//---------------------------------------------------------------------------
/////////////////////////////////////////////////////////////////////////////////
void __fastcall TParameters::Button2Click(TObject *Sender){
/////////////////////////////////////////////////////////////////////////////////
  ast s=ExtractFilePath(Application->ExeName);
 TIniFile* inif=new TIniFile(s+"\\par.ini");
  inif->WriteInteger("params","stend_com",CSpinEdit1->Value);
  delete inif;
  init(CSpinEdit1->Value);   //���������� ����� ������ � ���- ������
}
//---------------------------------------------------------------------------

tprofile profile;
char work_mode;//������� ����� ������ �����
/////////////////////////////////////////////////////////////////////////////////
void __fastcall TParameters::savebClick(TObject *Sender){ //��������� ������� � ����������
/////////////////////////////////////////////////////////////////////////////////
//������� ����������� ������ � ���������
 if(RichEdit1->Lines->Count>10){
   alert("���������� �����>10");
   return;
 }
 ast s,s2;
 for(int i=0;i<RichEdit1->Lines->Count;i++){
    s=RichEdit1->Lines->Strings[i];
    int p=s.Pos(";");
    if (s.Length()==0){
      profile.dur[i]=0;
      profile.curr[i]=0;
    }
    if(p==0){
      s="������ � ������ "+IntToStr(i+1);
      alert(s.c_str());
      return;
    };
    try{
        s2=s.SubString(0,p-1);
       profile.curr[i]=StrToInt(s2);
       s2=s.SubString(p+1,100);
       profile.dur[i]=StrToInt(s2);
    }catch(Exception &exception){
      s="������ � ������"+IntToStr(i+1);
      alert(s.c_str());
      return;
    };
  }
    profile.cnt=RichEdit1->Lines->Count;
  //��������� ���������
  double d;
  try{
        d=StrToFloat(period->Text);
    }catch(Exception &exception){
      s="������ ��� ����� ������� ����� ����������.";
      alert(s.c_str());
      return;
    };
   profile.period=d*10+0.5;
   period->Text=FloatToStrF(profile.period/10.0,ffFixed,8,1);
   profile.act_cur=act_cur_e->Value;
   profile.act_cur_level=act_cur_level_e->Value;

   try{
        d=StrToFloat(act_time->Text);
    }catch(Exception &exception){
      s="������ ��� ����� ������� ���������.";
      alert(s.c_str());
      return;
    };
   profile.act_time=d*10+0.5;
   act_time->Text=FloatToStrF(profile.act_time/10.0,ffFixed,8,1);
  if(!connectb->connect_r){
    s="��� ����� � �����������. �������� �� �������������";
    alert(s.c_str())
    return;
  }
  loadb->Enabled=false;
  saveb->Enabled=false;
  trequest req;
  req.fc=FCsetprofile;
  req.adr=connectb->req.adr;
  req.senlen=sizeof(profile);
  memcpy(req.sendata,&profile,req.senlen);
  req.active=true;
  SendRec(&req);
  while(req.active){
     Application->ProcessMessages();
  }
  if(req.res!=0){
     s="������ ��� ��������� ������";
      alert(s.c_str());

  }else{
     Visible=false;
  }
  loadb->Enabled=true;
  saveb->Enabled=true;
}






void __fastcall TParameters::Button1Click(TObject *Sender)
{
 ast s;
  Button1->Enabled=false;
  loadb->Enabled=false;
  saveb->Enabled=false;
  trequest req;
  req.fc=FCcalib;
  req.adr=connectb->req.adr;
  req.senlen=0;
  req.active=true;
  SendRec(&req);
  while(req.active){
     Application->ProcessMessages();
  }
  if(req.res!=0){
     s="������ ��� ��������� ������";
      alert(s.c_str());

  }else{
     Application->MessageBoxA("���������� ������������","",0);
  }
  loadb->Enabled=true;
  saveb->Enabled=true;
  Button1->Enabled=true;
}
//---------------------------------------------------------------------------

