

//extern int bufcnt;
void adcini();//��������� ���
void adcstart();//������ �� ��������� ���� 8-�� �������
//void setrgstate(char chn);
typedef struct {
  char state;
  int v;//���������� � ������������
  int curr;//��� � �������� ����������
  long time;//����� ��������� � ������ �s
  long begt;//�����  ������ ����. ����� ���������
  long endt;//���� �����. ���������
  int charge_hi;//������ �����, ������� 16 ��������
  unsigned long charge;//������ �����
}tbatt;
extern tbatt batt[4];
