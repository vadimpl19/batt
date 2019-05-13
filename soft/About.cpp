//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "About.h"
//--------------------------------------------------------------------- 
#pragma resource "*.dfm"
TAboutBox *AboutBox;
//--------------------------------------------------------------------- 
__fastcall TAboutBox::TAboutBox(TComponent* AOwner)

	: TForm(AOwner)
{

UINT count;

}
//---------------------------------------------------------------------
void __fastcall TAboutBox::Label4Click(TObject *Sender) //открытие браузера по ссылке
{
HINSTANCE res= ShellExecute(Application->Handle,"open","http://source-ltd.org.ru/","","",SW_NORMAL);
}
//---------------------------------------------------------------------------

void __fastcall TAboutBox::Label4MouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
Label4->Font->Style=TFontStyles()<< fsBold << fsUnderline;

}
//---------------------------------------------------------------------------

void __fastcall TAboutBox::Panel1MouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
Label4->Font->Style=TFontStyles();
}
//---------------------------------------------------------------------------

