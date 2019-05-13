void iniuart0(unsigned int speed,char par);
void iniuart1(unsigned int speed,char par);
void req0handle();
void req1handle();

void delayed_func();

#define maxit 10
typedef struct {
  char cnt;
  int curr[maxit];
  long dur[maxit];//������������  � �������������
  char act_cur; //��������� ��� ���������,��
  char act_cur_level; //����� ��������� ������� �����,��
  long act_time;//��������� ����� ��������� � ������ ��
  int period;//������ ������ ������ ����� ��� ������� �� �������

}tprofile;
void read_settings();// ������ ���������� � ��� �� eeprom
extern tprofile profile;
extern char stepcnt;
extern char work_mode;//����� ������ 0- ����� ���������
                        //       1- ���� �� ������� ��������� ���������, ��� ����.
                         //      10 - ����� ������� �� �������
extern char * curbuf;
#define prbufsize 900
#define framenum 5 /*�������� �� ������ ������ �� ����� ��������� ������ */
extern char prbuf0[prbufsize];
extern char prbuf1[prbufsize];
//extern int offset1,offset0,curoffset;
extern int curoffset;
