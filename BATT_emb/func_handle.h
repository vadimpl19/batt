
#define	FCres 0 /* ��������� ����� ����������                   */
#define	FClink 1 /* ��������� ����������������� �����           */



#define	FCexept  15/*- exception �� �������                     */

#define	ex_no_support  1/*- ������������� ������� �� ��������������  */


//void gotofac(); //��������� ����� � �������� ����� �� ��������� �������
//void setfac(char tst,char subtst);
//int set_but_req(char but_no,char cnt);
//int set_fac_req(char tst,char subtst);
//int set_mode_req(char mode,float* power);
//void setmode(char mode,float power);

void performcmd();//���������� ������� �� ����;
extern char cmd_active;
extern UCHAR ledstate;
extern UCHAR l_avg;
extern UCHAR l_cnt;
extern UCHAR l_max;
extern int l_samples;
void getledstate();
