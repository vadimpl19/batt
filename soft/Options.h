//---------------------------------------------------------------------------

#ifndef OptionsH
#define OptionsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Mask.hpp>
#include "CSPIN.h"
#include <Grids.hpp>
#include <ValEdit.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TParameters : public TForm
{
__published:	// IDE-managed Components
        TGroupBox *GroupBox1;
        TButton *Button2;
        TCSpinEdit *CSpinEdit1;
        TLabel *Label1;
        TRichEdit *RichEdit1;
        TLabel *D;
        TLabel *Label2;
        TLabel *Label3;
        TGroupBox *GroupBox2;
        TCSpinEdit *act_cur_e;
        TLabel *Label4;
        TLabel *Label5;
        TEdit *act_time;
        TLabel *Label6;
        TCSpinEdit *act_cur_level_e;
        TButton *saveb;
        TButton *loadb;
        TEdit *period;
        TLabel *Label7;
        TButton *Button1;
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall savebClick(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TParameters(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TParameters *Parameters;
extern char work_mode;//������� ����� ������ �����
#define maxit 10
#pragma pack(push,1)
typedef struct {
  char cnt;
  __int16 curr[maxit]; // ���� ��� ������� ���� �� �������
  __int32 dur[maxit];//������������  � �������������
  char act_cur; //��������� ��� ���������,��
  char act_cur_level; //����� ��������� ������� �����,��
  __int32 act_time;//��������� ����� ��������� � ������ ��
  __int16 period;//������ ����� ���������� � ������ ��

}tprofile;
#pragma pack(pop)
extern tprofile profile;
//---------------------------------------------------------------------------
#endif
