void iniuart0(unsigned int speed,char par);
void iniuart1(unsigned int speed,char par);
void req0handle();
void req1handle();

void delayed_func();

#define maxit 10
typedef struct {
  char cnt;
  int curr[maxit];
  long dur[maxit];//длительность  в миллисекундах
  char act_cur; //требуемый ток активации,мА
  char act_cur_level; //порог зажигания красной лампы,мА
  long act_time;//требуемое время активации в сотнях мс
  int period;//период выдачи наверх точек при разряде по профилю

}tprofile;
void read_settings();// чтение параметров в ОЗУ из eeprom
extern tprofile profile;
extern char stepcnt;
extern char work_mode;//режим работы 0- режим активации
                        //       1- одна из батарей завершила активацию, ток снят.
                         //      10 - режим прогона по профилю
extern char * curbuf;
#define prbufsize 900
#define framenum 5 /*смещение от начала буфера то байта нумерации кадров */
extern char prbuf0[prbufsize];
extern char prbuf1[prbufsize];
//extern int offset1,offset0,curoffset;
extern int curoffset;
