//---------------------------------------------------------------------------

#ifndef stenduH
#define stenduH
#include "cd\commdriveu.h"
#include "common.h"




#define FCgetbat 0x04
#define FCsetprofile 0x05
#define FCsetactivation 0x06
#define FCsetbyprofile 0x07

#define FCgetitems 0x09
#define FCcalib 0x0a

#define	FCgetind 0x1b






//---------------------------------------------------------------------------
enum tstate {error,ini_st,idle,perform_cmd_st};
class tboard  {
  protected:

    ast name;// �������� �������. ������������ ��� ������ ���������.
    unsigned char ver;
    unsigned char subver;//������ � ��������� ����������� �� �����
    bool startthr;//���� ��������� ������ ����� ���������� ���� ����� tdevice � ������������ �������� ������
    bool connect;
    tstate state;
    int portnum;
    int thh;//����� ������
//    char adr;  ������������ ����� � ���������
    unsigned long thid;

    int lasterr;

  private:
    bool wait_forendop_req;
    bool wait_forendop_rdy;//���������� ������������ ����� �������� ��������� ����. �������
                           //�� ����� � ����� �����������.
    void wait_forendop_body();
    void virtual perform_answ_for_endop(){};
  public:
      char statear[20];//������ ������ � �����. ������ ��������������� ������ 1-� ����
    __property bool startthr_r={read=startthr};
    __property bool rec_active={read=req.active};
    __property bool connect_r={read=connect};
    trequest req;
    char config[100];
    bool connecting_req; //������ �� ������������ ��������
    bool closingth_req;// ������ �� �������� ������ (������������ � ������ ����� �������)
    void __fastcall thrbody();//���� ������ � ��������� ������;
    void resetconnect();//����� �������� (������ �� ������)
    void connecting();//�������� ����� (������ �� ������)

   tboard();
   int wait_forendop();//�������� ��������� ��������� �������
                        //��� �������� ������ - ��������� ����������
   int setreq_wait_forendop();//���������� ������� �� �������� ��������� ��������� �������

};

class tconnectb:public tboard { //����� �����
  private:
  public:

    tconnectb();
//    int ~tind();

    int sendstopall();//��������� ��� ���� �� ������� ����
                     //���� ����������
                     //1=� ���������
    int load_config();//������� ������� �� ���������� ������� �� 220� � ����������� ��������� ���������� ����������
    poweron();
    bool is_poweron();
};

extern tconnectb *connectb;
int poweroff();//������� ������� �� ���������� ������� �� 220� � ����������� ��������� ���������� ����������
#endif
