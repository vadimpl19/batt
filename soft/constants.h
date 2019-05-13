
//*******************************************************************
  // Список идентификационных номеров всех возможных преобразователей серии ET-71xx.
  const unsigned char ET7186_id = 0xA0;
  const unsigned char ET7187_id = 0xA1;
  /* --- */


  const unsigned char TargetID =  ET7187_id;//Данное ПО для ET7187.
//*******************************************************************

//определим смещение до адреса и контрольного поля
#define AF 2
#define CF 3

//Коды комманд
#define TEST_CONNECTION 0x00    //прозвон устройства
#define RESERV          0x70    //резерв
#define BURN_FILE       0x30    //прожиг файла
#define LOAD_FILE       0x40    //загрузка файла и ПК
#define FILE_CRC        0x50    //проверка файла
#define STOP_ALL        0x60    //Stop All Actions

//Коды запросов комманд (ET7122)
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!Внимание!!!!!!!!!!!!!!!!!!!!!
// при добавлении новых команд не забываем  прописывать их коды (и TEST и GET)
// в драйвере передачи ucommdrive
// а также код TEST__ в модуле MAIN в устройстве
#define TEST_VOLTAGE    0x10    //запуск измерений напряжения
#define TEST_CONVERTER  0x11    //запуск проверки преобразователя
#define TEST_LOOP       0x12    //запуск проверки цепи
#define TEST_CALIBR     0x13    //калибровка
#define TEST_LED        0x13
#define POWER_ON        0x14    //подача питания на преобразователь
#define POWER_OFF       0x15    //отключение питания
#define TEST_NWORK      0x16    //проверка в НУ
#define TEST_CYCLS      0x17    //проверка электроциклов
#define REPEAT_TEST     0x18    //Циклические тесты.
#define REQ_NUM         0x19    //запрос заводского номера
#define SAVE_PARAM      0x1a    //запись параметров калибровки
#define TEST_TERMO      0x1b    //проверка в термокамере



//Коды запросов данных (RecResult)
#define GET_VOLTAGE     0x20    //запрос данных напряжения
#define GET_CONVERTER   0x21    //запрос параметров преобразователя
#define GET_LOOP        0x22    //запрос параметров цепи
#define GET_CALIBR      0x23    //результаты калибровки
#define GET_LED      		0x23    
#define GET_NWORK       0x26    //результат проверки НУ
#define GET_CYCL        0x27    //результат проверки циклов
#define GET_REST        0x28    //Get current value
#define GET_TERMO       0x2b    //проверка в термокамере




//коды подфункций для циклического теста
#define SET_CPOINT      0x18    //установка точки калибровки сопротивлений

//Коды возврата функции BurnFile
#define BURN_CMPLT      0x00    //прожиг закончен
#define BURN_INPROCESS  0x01    //прожиг идет
#define BURN_WRONGFILE  0x02    //файл отсутствует
#define BURN_ERROR      0x03    //ошибка прожига

/*ОТВЕТЫ ФУНКЦИЙ*/
#define FR_OK                           0x00   /*функция выполнена успешно        */
#define FR_CANCELED                     0xC0   /*действие отменено                */
/*ОШИБКИ ФУНКЦИИ ПОСЫЛКИ КАДРА sendfrm*/
#define ERR_SEND_WRITE_PORT             -1   /*не удалось записать в порт       */
#define ERR_SEND_PORT_IS_CLOSED         -2   /*порт закрыт                      */
#define ERR_SEND_BAD_FC                 -3   /*неверный код функции             */
/*ОШИБКИ ФУНКЦИИ ПРИЁМА КАДРА recfrm*/
#define ERR_REC_NO_RESPOND              -10   /*устройство не отвечает           */
#define ERR_REC_PORT_IS_CLOSED          -11   /*порт закрыт                      */
#define ERR_REC_CRC                     -12   /*в полученом кадре не сошлось CRC */
#define ERR_REC_LENGTH                  -13   /*в кадре не сошлась длинна        */


/*ОШИБКИ ФУНКЦИИ ИНИЦИАЛИЗАЦИИ ПОРТОВ init*/
#define ERR_INI_PORT                    -20   /*не удалось открыть порт          */
#define ERR_INI_BLSIZE                  -21   /*размер блока не попадает в 10-1000 байт */
#define ERR_INI_repeat                  -22   /*повторный вход в процедуру инициализации недождавшись ответа */
/*ОШИБКИ ФУНКЦИИ L7*/
#define ERR_TOO_LONG                  -31   /*принятых данных больше чем ожидалось */
#define ERR_NO_CONNECT                -32   /*принятых данных больше чем ожидалось */

/*ОШИБКИ возвращаемые tind*/
#define ERR_REQ_ACTIVE                  -40   /*уже есть активный запрос, попытка поставить еще */
#define ERR_NO_CONNECT                -32   /*принятых данных больше чем ожидалось */

enum commands{GET_INFO=1,SET_KEY=0x1a,GET_IND=0x1b};
