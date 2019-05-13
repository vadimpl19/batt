#ifndef byte_stuff_h
#define byte_stuff_h
/* ������ ��������� �������� ����-��������� �� ����� � �������� */
#include "hwr.h"
typedef struct  {
  int lrec;
  char recst;
  unsigned char rbuf[rbuf_size];
}trecctx;
typedef struct  {
  int l;
  char * senptr;
  char senst;
}tsenctx;
typedef struct  {
  int all,sync,lenmin,lenmax,crc,len;
}terrstat;


void inisend(int l, char * bufpoint,tsenctx * senctx);
/* ������������� �������� ��������.
    l- ����� ������������� �����
    bufpoint - ����������� ��� ������������ ����
    senctx - �������� �������� ( ���������� ���������� ��� ���������
              ����� ��������� ��� ������� getnextch )

    ��� ���� ��� ������� ����� ��������
� ������� ���������� ������ send_begin, ������� ������ ���� ��������� �������,
� ����� hwr.h
*/

char getnextch(char *nextch, tsenctx * senctx);
/* ���������� �������
������� ������ ������������ ��� ������ �� ������ ����������� ����������� �� UART.
nextch - ���������� � ������� ������������ ��������� ���� ��� ��������
������� ���������� 0, ���� ���� ���� �� �������� � 1 - ���� ��� ���
�������� */

void inirec(trecctx * recctx);
/* ������� ���������� ������� ������,
recctx - ��������� ���������� ����� ������, ����� ����������� ����� � ��.
          ��������� ���� ( ���������� ���������� ��� ���������
          ����� ��������� ��� ������� recfrm )
*/

//char recfrm(char nextch);
char recnextch(char nextch,trecctx * recctx);
/* ������� �������� ������ �� ������������� (��� ���������� ������ � �����
hwr.h ������ ���� ���������� ��������� rbuf_size - ������ ������ ������.)
���������� 0- ������ ��������� ����
           1- ���� ����� �����
           2 - ��� ����, ������� �������������.
� ������ ��������� ������ �����   � ���������� ���������� lrec ������������
������ ��������� �����. ��� ���� ��������� � ������� rbuf.
����������� ����� recfrm �������� � ����, ��� ����� ������������ ����� ���-
������� ����� � �������� lrec � rbuf ������ ������������. */

int makefrm(char * outbuff,char * frm, int len, int maxlen);

/* ������������ ��� �������� �������� ����� �� �������������� ���� ����������
   ( ��� ���������� inisend � getnextch, ������� ������ ��� ������ ��� �������,
   ����� ���������������� ���� - ��� ���������� � ����� ���� ���� ������ �������).
   outbuff - ��������� �� ����� ��� ����� ����������� �������� ����
   frm - ���� �� �������� ( ��� ��� ����-���������)
   len - ����� ����� �� ��������.
   maxlen - ����� ��������� ������, ������� ������ ���������.
   ��������!!! ������ ��������� ������ ����� ������������ ������� ��������
        ������� �����*2 + 4 !!!!  ������������ �����!!!!!!!

*/

int recfrm_bs(trecctx * recctx, char *source, int len,int *curroffs);
/* ���������� �������� ����-��������� �� ������
   ���������� 0 - ���� ������
              1 - ���� �� ������
   ����� ����� ��������� ��������� �������� ���������� ������
   recctx - ��������� ��� ��������� �����
   source - �������� �� com ����� ������������������ ����
   len - ���������� �������� ����
*/
void inierrorstat();//��������� ���������� ������
void seterrorcrc();//���������� ������ �RC.
void seterrorlen();//���������� ������ �� ������� �����.
#endif
