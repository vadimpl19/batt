void iniuart0(unsigned int speed,char par); //��������� UART0
void iniuart1(unsigned int speed,char par);//��������� UART1
void req0handle();// ��������� �������� ������ �� UART0
void req1handle();// ��������� �������� ������ �� UART1

//void delayed_func();

#define maxit 10
typedef struct {
  char cnt;// ����� ���������, �������� � �������
  int curr[maxit];//��� ��������.
  long dur[maxit];//������������  � �������������
  char act_cur; //��������� ��� ���������,��
  char act_cur_level; //����� ��������� ������� �����,��
  long act_time;//��������� ����� ��������� � ������ ��
  int period;//������ ������ ������ ����� ��� ������� �� �������

}tprofile;
extern tprofile profile;
void read_settings();// ������ ���������� � ��� �� eeprom

extern char stepcnt;//������� ����� ������������ �������� �������
extern char work_mode;//����� ������ 0- ����� ���������
                        //       1- ���� �� ������� ��������� ���������, ��� ����.
                         //      10 - ����� ������� �� �������
extern char * curbuf;//��������� �� ������� ����������� ����������� ������� ����� (prbuf0 ��� prbuf1)
#define prbufsize 900
#define framenum 5 /*�������� �� ������ ������ �� ����� ��������� ������ */
extern char prbuf0[prbufsize];//��� ������ ��� ���������� ����������� �������, ����������� ����������
extern char prbuf1[prbufsize];
//extern int offset1,offset0,curoffset;
extern int curoffset;//������� �������� � ������, � ����� �������� ����� �������� ����� ������
