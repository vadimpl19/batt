#ifndef ucommd_h
#define ucommd_h
//����� �������� ����� ������� ���������
#define DEF_DELAY 10
//������������ ������ ����� ������ �� ��������
#define blsize 220
#include "cd\byte_stuff.h"
//------------------------------------------------------------------------------
//--------------------------���������� �������----------------------------------
//------------------------------------------------------------------------------
int sendfrm(int h,short adr,short fc, char * ASDU,int len);
/*
  h- ��������� ����������
  adr - ����� ����������� �������
  fc - ��� ������������� �������
  buf - ���� �� �������� (ASDU)
  len - ��� ������
  FR_OK                         - ��� ������� �������� ��� ��� ������
  ERR_SEND_WRITE_PORT           - �� ������� �������� � ����
  ERR_SEND_PORT_IS_CLOSED       - ���� ������
  ERR_SEND_BAD_FC               - �������� ��� �������
*/

int recfrm(int h,trecctx *recctx);
/*
������� ������ ����� �� com-�����,
����������
FR_OK                   - ������� ����. (�� � ��������� recctx);
ERR_REC_NO_RESPOND      - ������ - ��� �����.
ERR_REC_PORT_IS_CLOSED  - ������, ���� �� ������.
ERR_REC_CRC             - ������, �� ������� �RC
ERR_REC_LENGTH          - ������, �� ������� ������
*/

int SendPacket(short adr,short fc,char* packet,int lght);
/*
�������� ����� ������ � ��������������
adr     - ����� ����������
fc      - ��� �������
packet  - ������
lght    - ����� ������

������ ����� �������, ���������� � init � ������� ���
� ������� �������, ���������� � init
���������� 1 ���� ����� �������
*/

int RecPacket(short adr,short fc,char* packet);
/*
��������� ����� ������
adr    - ����� ���������
fc     - ��� �������
packet - ����� ��� ������

������� ����� � ������� ������� ��������� � init
���������� -1 ���� ������ ������
��� ����� �������� ������ ���� ������� ������
*/
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

extern "C" int  init(char * chnum, int repcount,int systime);
/* ������� ������������� ��������
ch1num - ��� ���-����� ����� � �����������, ������������
        ��������������� � PC
repcount - ������������ ���������� �������� �� ��������� ������
           �����. �������� �������� 1-9. ������������� - 3
blsize - ������������ ������ ����� ������ �� ��������.
         �������� ��������, ����  32-1024
systime - ����� ������� ������� �� ������
������� ����������
ERR_CANT_OPEN_PORT1 ���� �� �������� ����
*/

extern "C" void  close_ports();//������� ��������� �����

extern "C" void  ErrLine(unsigned int ErrCode,char *line);
//������� � line ���������� ���������� ��� ������ ErrCode,
//�������� ���� ��� ������� � ������� ����������

struct _request         //������ �� �����/��������
{
  bool ask;             //������������ �� ��������� �������
  unsigned short fc;    //��� �������
  unsigned char adr;    //����� ����������
  unsigned char heating_time; //����� �� ������� ����� ����������� ������� � �������*10
                         //������ ������������ ������ ������ ASDU �� ������ ������� ��������
  unsigned char res;    //���������
                        //  0 -��� ��
                        // 0x10 ERR_REC_NO_RESPOND �� ���� �� ������� � �����
  int lenght;           //�������� ��� ��� ������. � ����� ����. �����, � ��� ������ ����� �����

  char *Data;           //��� �������� �������� ���� �������, � ��� ������-�������� ������
                        //����� ���� ��������� ����. ������������ ���� ������ �� �� ���� ��������
  int reclen;            //���������� �������� ����, -1 ���� ��� TOUT
  int senlen;           //���������� ������ �� �������� � ������ sen data
  char sendata[blsize];  //������ �� ��������. ������������ ���� ������ � ������� GetData
};
///////////////////////////////////////////////////////////////////////////////////
int GetData(_request* req); //������� ������� � ��������� ������ �� �������
// �� ���������� ������ req->ask ������������ � 0
// req->res- ��� ����������
// req->reclen - ����� ��������� �����
///////////////////////////////////////////////////////////////////////////////////

extern "C" void  SendRec(_request *nrec);
/*
������ ������ �� ���������� ��������
���� ������� � constants.h
*/

extern "C" void  CancelQue(void);
/*
����������� ����� �������������� �������
� ������� ������� ��������
*/
#endif
