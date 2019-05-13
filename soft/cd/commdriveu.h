//---------------------------------------------------------------------------

#ifndef commdriveuH
#define commdriveuH
//общая задержка перед началом измерений
#define DEF_DELAY 10
//максимальный размер блока данных на передачу
//#define blsize 220
#define blsize 500
//#define recblsize 240
#define recblsize 2000
#include "cd\byte_stuff.h"
extern int ch_stend; //хэндл рабочего порта
extern short repc;
extern int stend_portn;
extern void * thhdl;
extern unsigned int tout;// таймаут на ответ;

//extern "C" int  init(char * chnum, int repcount,int tout);
extern "C" int  init(int portnum);
/* функция инициализации драйвера все параметры уже должны быть в глобальных переменных
stend_portn - номер сом-порта связи с устройством, подключенным
        непосредственно к PC
repc - максимальное количество запросов до генерации ошибки
           связи. Диапазон значений 1-9. Рекомендуемое - 3
tout - время реакции системы на запрос
Функция возвращает
ERR_CANT_OPEN_PORT1 если не открылся порт
*/

extern "C" void  close_port();//функция закрывает порт

extern "C" void  ErrLine(unsigned int ErrCode,char *line);
//функция в line записывает символьное имя ошибки ErrCode,

struct trequest         //запрос на прием/передачу
{
  bool active;// ask;             //сбрасывается по отработке запроса
  unsigned short fc;    //код функции
  unsigned char adr;    //адрес получателя
//  unsigned char heating_time; //время на прогрев перед исполнением команды в минутах*10
                         //всегда отправляется первым байтом ASDU не считая команды загрузки
  unsigned char res;    //результат
                        //  0 -все ок
                        // 0x10 ERR_REC_NO_RESPOND ни чего не приняли в ответ
  int reclen;            //количество принятых байт, -1 если был TOUT
  int senlen;           //количество данных на передачу в буфере sen data
  char sendata[blsize];  //данные на передачу. используется пока только в функции GetData
  char recdata[recblsize];  //данные на передачу. используется пока только в функции GetData
};

extern "C" void  CancelQue(void);
/*
Пересоздает поток обрабатывающий запросы
и удаляет очередь запросов
*/
void  SendRec(trequest *req);
/*
ставит запрос на выполнение операции
коды комманд в constants.h
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
