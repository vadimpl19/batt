void iniuart0(unsigned int speed,char par); //инициация UART0
void iniuart1(unsigned int speed,char par);//инициация UART1
void req0handle();// обработка принятых кадров от UART0
void req1handle();// обработка принятых кадров от UART1

//void delayed_func();

#define maxit 10
typedef struct {
  char cnt;// число элементов, заданных в профиле
  int curr[maxit];//ток элемента.
  long dur[maxit];//длительность  в миллисекундах
  char act_cur; //требуемый ток активации,мА
  char act_cur_level; //порог зажигания красной лампы,мА
  long act_time;//требуемое время активации в сотнях мс
  int period;//период выдачи наверх точек при разряде по профилю

}tprofile;
extern tprofile profile;
void read_settings();// чтение параметров в ОЗУ из eeprom

extern char stepcnt;//текущий номер исполняемого элемента профиля
extern char work_mode;//режим работы 0- режим активации
                        //       1- одна из батарей завершила активацию, ток снят.
                         //      10 - режим прогона по профилю
extern char * curbuf;//указатель на текущий заполняемый измеренными данными буфер (prbuf0 или prbuf1)
#define prbufsize 900
#define framenum 5 /*смещение от начала буфера то байта нумерации кадров */
extern char prbuf0[prbufsize];//два буфера для заполнения измеренными данными, заполняются поочередно
extern char prbuf1[prbufsize];
//extern int offset1,offset0,curoffset;
extern int curoffset;//текущее смещение в буфере, с этого смещения будут положены новые данные
