//---------------------------------------------------------------------------

#ifndef logsH
#define logsH
void inilog(AnsiString s);
void addstr(AnsiString s);
void closelog();

int inicsv();// ��������� ����� csv, ���������� ���������� �����
void addcsv(AnsiString s); //�������� ����� s � csv-����
void closecsv();// �������� ���- �����
//---------------------------------------------------------------------------
#endif
