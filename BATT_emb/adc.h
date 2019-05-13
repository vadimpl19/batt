

//extern int bufcnt;
void adcini();//инициация ацп
void adcstart();//запуск на измерение всех 8-ми каналов
//void setrgstate(char chn);
typedef struct {
  char state;
  int v;//напряжение в милливольтах
  int curr;//ток в десятках микроампер
  long time;//время активации в сотнях мs
  long begt;//время  начала посл. цикла активации
  long endt;//ремя оконч. активации
  int charge_hi;//снятый заряд, верхние 16 разрядов
  unsigned long charge;//снятый заряд
}tbatt;
extern tbatt batt[4];
