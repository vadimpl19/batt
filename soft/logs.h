//---------------------------------------------------------------------------

#ifndef logsH
#define logsH
void inilog(AnsiString s);
void addstr(AnsiString s);
void closelog();

int inicsv();// инициация файла csv, возвращает дескриптор файла
void addcsv(AnsiString s); //добавить стоку s в csv-файл
void closecsv();// закрытие лог- файла
//---------------------------------------------------------------------------
#endif
