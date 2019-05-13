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

    ast name;// название пирбора. используется при выводе сообщений.
    unsigned char ver;
    unsigned char subver;//версия и подверсия встроенного по платы
    bool startthr;//флаг активации потока после заполнения всех полей tdevice в конструкторе базового класса
    bool connect;
    tstate state;
    int portnum;
    int thh;//хэндл потока
//    char adr;  используется адрес в структуре
    unsigned long thid;

    int lasterr;

  private:
    bool wait_forendop_req;
    bool wait_forendop_rdy;//переменная обозначающая конец поллинга окончания пред. команды
                           //не важно с каким результатом.
    void wait_forendop_body();
    void virtual perform_answ_for_endop(){};
  public:
      char statear[20];//массив данных с платы. жестко идентифицирован только 1-й байт
    __property bool startthr_r={read=startthr};
    __property bool rec_active={read=req.active};
    __property bool connect_r={read=connect};
    trequest req;
    char config[100];
    bool connecting_req; //запрос на установление коннекта
    bool closingth_req;// запрос на закрытие потока (сбрасывается в потоке перед выходом)
    void __fastcall thrbody();//тело потока в контексте класса;
    void resetconnect();//сброс коннекта (вызыыв из потока)
    void connecting();//проверка связи (вызыыв из потока)

   tboard();
   int wait_forendop();//ожидание окончания обработки команды
                        //как побочный эффект - состояние индикатора
   int setreq_wait_forendop();//постановка запроса на ожидание окончания обработки команды

};

class tconnectb:public tboard { //класс платы
  private:
  public:

    tconnectb();
//    int ~tind();

    int sendstopall();//выключить все реле по команде стоп
                     //коды завершения
                     //1=в обработке
    int load_config();//посылка запроса на отключение питания по 220в с сохранением остальных параметров коммутации
    poweron();
    bool is_poweron();
};

extern tconnectb *connectb;
int poweroff();//посылка запроса на отключение питания по 220в с сохранением остальных параметров коммутации
#endif
