////---------------------------------------------------------------------------

#ifndef uMainFormH
#define uMainFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include <ActnList.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include <Graphics.hpp>
#include <ComCtrls.hpp>
#include <Dialogs.hpp>
#include <math.h>
#include <CheckLst.hpp>
#include <Mask.hpp>
#include "CSPIN.h"
#include <Grids.hpp>
#include <ValEdit.hpp>
#define ast AnsiString
//#include "cd\ucommdrive.h"
#include "commdriveu.h"
//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components
        TTimer *Timer1;
        TRichEdit *RichEdit1;
        TStatusBar *StatusBar1;
        TSaveDialog *SaveDialog1;
        TOpenDialog *OpenDialog1;
        TProgressBar *ProgressBar1;
        TPopupMenu *PopupMenu1;
        TMenuItem *N1;
        TTimer *touttimer;
        TGroupBox *GroupBox1;
        TGroupBox *GroupBox2;
        TGroupBox *batbox1;
        TLabel *Label6;
        TLabel *Label7;
        TEdit *batv1;
        TEdit *batc1;
        TMainMenu *MainMenu1;
        TMenuItem *N2;
        TMenuItem *N3;
        TLabel *Label8;
        TLabel *Label9;
        TEdit *batt1;
        TEdit *batch1;
        TGroupBox *batbox3;
        TLabel *Label18;
        TLabel *Label19;
        TLabel *Label20;
        TLabel *Label21;
        TEdit *batv3;
        TEdit *batc3;
        TEdit *batt3;
        TEdit *batch3;
        TGroupBox *batbox4;
        TLabel *Label22;
        TLabel *Label23;
        TLabel *Label24;
        TLabel *Label25;
        TEdit *batv4;
        TEdit *batc4;
        TEdit *batt4;
        TEdit *batch4;
        TLabel *Label1;
        TLabel *batst1;
        TMenuItem *N4;
        TGroupBox *batbox2;
        TLabel *Label10;
        TLabel *Label11;
        TLabel *Label12;
        TLabel *Label13;
        TEdit *batv2;
        TEdit *batc2;
        TEdit *batt2;
        TEdit *batch2;
        TLabel *batst3;
        TLabel *batst2;
        TLabel *batst4;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Label4;
        TSpeedButton *ActivB;
        TSpeedButton *byProfileB;
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall SaveDataCSV(TObject *Sender);

        void __fastcall N1Click(TObject *Sender);
        void __fastcall BitBtn1Click(TObject *Sender);

        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall FormActivate(TObject *Sender);
        void __fastcall FormDestroy(TObject *Sender);
        void __fastcall touttimerTimer(TObject *Sender);
        void __fastcall N2Click(TObject *Sender);
        void __fastcall N4Click(TObject *Sender);
        void __fastcall ActivBClick(TObject *Sender);
        void __fastcall byProfileBClick(TObject *Sender);
private:        // User declarations
        void __fastcall SendFileTD();
        void __fastcall PSLINI(bool Save);
//        void processanswer();//// обработка прин€того ответа от стенда
        void __fastcall TMainForm::process_addmsg();//добавление сообщений из очереди в RichEdit
        void __fastcall TMainForm::process_devstate();
        int f_current;
        void stop();// сброс запроса на останов и активайи€ кнопок
        int state;//переменна€ состо€ни€ дл€ текущей проверки
        int chkres_connectb();// типовой кусок автомата выполнени€ теста, провер€ющий результат команды плате коннекторов
        int chkres_indboard();// типовой кусок автомата выполнени€ теста, провер€ющий результат команды плате коннекторов
        int chkres_epm();
        int chkres_osc();
        int chkres_volt();
        int chkerr_indboard();
        void __fastcall TMainForm::getbatt();//запрос состо€ни€ батарей
        int getledstate_req();//запрос на coсто€ние светодиода
        int getind(); //запрос состо€ни€ индикацииж
        int setself(bool begin_self);//запрос на установку флага ееprom на загрузку в режиме самотестировани€
        int __fastcall TMainForm::process_nu();//обработка всех тестов в Ќ”
        int __fastcall TMainForm::setfr_u1();

        int __fastcall TMainForm::set_u1();
        int __fastcall TMainForm::fac10();
        int __fastcall TMainForm::fac40();
        int __fastcall TMainForm::fac4142();
      //  int __fastcall TMainForm::fac43();
        int __fastcall TMainForm::fac4344(bool is_fac43);
        int __fastcall TMainForm::fac45();
        int __fastcall TMainForm::fac46();
        int __fastcall TMainForm::fac47();
        int __fastcall TMainForm::fac4849(bool is_fac48);
        int __fastcall TMainForm::fac50();
        int __fastcall TMainForm::fac535a();
        int __fastcall TMainForm::fac60();
        int __fastcall TMainForm::adjlevel();
        void __fastcall TMainForm::getresfr(float freqa);
        int __fastcall TMainForm::adjres();//подстройка резонансной частоты
        int __fastcall TMainForm::selftest();//стирание пам€ти ошибок и selftets
        int __fastcall TMainForm::fac5152(bool repeatt);
        int __fastcall TMainForm::fac70();
        int __fastcall TMainForm::pedal();
        int __fastcall TMainForm::power_chk();
        int __fastcall TMainForm::tstelect();
        int __fastcall TMainForm::loadmpu(char mpunum);// загрузка программы в процессоры
        bool selftestactive;//флаг активности теста самопроверки дл€ обхода станд. обработки ошибок платы инд.

public:		// User declarations
        trequest MainRQ;
        void settout(int tout);
        bool toutexpired;
        void alert(const AnsiString & str);
        bool stopreq;//запрос на на останов выполнени€;
        int __fastcall TMainForm::TestU();
//        TRTLCriticalSection Sect1;
         TQueue *  msg_q;
         bool __fastcall sendparam(TObject *Sender);
				 bool __fastcall sendparamcalib(char inout,char point);//посылка команды установки режима калибровки сопротивлений
																															 //в этой проге не нужна
				 void __fastcall ETtype_reload();//загрузка контекстных параметров дл€ преобразовател€
				__fastcall TMainForm(TComponent* Owner);
				void __fastcall TMainForm::enableallb();

};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
extern trequest stopr;

//---------------------------------------------------------------------------
void ProcessASK(trequest onend);
//void __fastcall addmsg(const AnsiString & s,TColor color);
 void __fastcall addmsg(char *s,TColor color);
#define alert( str) Application->MessageBoxA(str,"¬нимание",0);
#endif
