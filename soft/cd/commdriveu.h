//---------------------------------------------------------------------------

#ifndef commdriveuH
#define commdriveuH
//����� �������� ����� ������� ���������
#define DEF_DELAY 10
//������������ ������ ����� ������ �� ��������
//#define blsize 220
#define blsize 500
//#define recblsize 240
#define recblsize 2000
#include "cd\byte_stuff.h"
extern int ch_stend; //����� �������� �����
extern short repc;
extern int stend_portn;
extern void * thhdl;
extern unsigned int tout;// ������� �� �����;

//extern "C" int  init(char * chnum, int repcount,int tout);
extern "C" int  init(int portnum);
/* ������� ������������� �������� ��� ��������� ��� ������ ���� � ���������� ����������
stend_portn - ����� ���-����� ����� � �����������, ������������
        ��������������� � PC
repc - ������������ ���������� �������� �� ��������� ������
           �����. �������� �������� 1-9. ������������� - 3
tout - ����� ������� ������� �� ������
������� ����������
ERR_CANT_OPEN_PORT1 ���� �� �������� ����
*/

extern "C" void  close_port();//������� ��������� ����

extern "C" void  ErrLine(unsigned int ErrCode,char *line);
//������� � line ���������� ���������� ��� ������ ErrCode,

struct trequest         //������ �� �����/��������
{
  bool active;// ask;             //������������ �� ��������� �������
  unsigned short fc;    //��� �������
  unsigned char adr;    //����� ����������
//  unsigned char heating_time; //����� �� ������� ����� ����������� ������� � �������*10
                         //������ ������������ ������ ������ ASDU �� ������ ������� ��������
  unsigned char res;    //���������
                        //  0 -��� ��
                        // 0x10 ERR_REC_NO_RESPOND �� ���� �� ������� � �����
  int reclen;            //���������� �������� ����, -1 ���� ��� TOUT
  int senlen;           //���������� ������ �� �������� � ������ sen data
  char sendata[blsize];  //������ �� ��������. ������������ ���� ������ � ������� GetData
  char recdata[recblsize];  //������ �� ��������. ������������ ���� ������ � ������� GetData
};

extern "C" void  CancelQue(void);
/*
����������� ����� �������������� �������
� ������� ������� ��������
*/
void  SendRec(trequest *req);
/*
������ ������ �� ���������� ��������
���� ������� � constants.h
*/
class tdata2
{
  public:
  int port;
  TQueue *myqu;
  bool thact;
};
extern  tdata2 *RunParam; 
//---------------------------------------------------------------------------
#endif
