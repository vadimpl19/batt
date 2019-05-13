
//*******************************************************************
  // ������ ����������������� ������� ���� ��������� ���������������� ����� ET-71xx.
  const unsigned char ET7186_id = 0xA0;
  const unsigned char ET7187_id = 0xA1;
  /* --- */


  const unsigned char TargetID =  ET7187_id;//������ �� ��� ET7187.
//*******************************************************************

//��������� �������� �� ������ � ������������ ����
#define AF 2
#define CF 3

//���� �������
#define TEST_CONNECTION 0x00    //������� ����������
#define RESERV          0x70    //������
#define BURN_FILE       0x30    //������ �����
#define LOAD_FILE       0x40    //�������� ����� � ��
#define FILE_CRC        0x50    //�������� �����
#define STOP_ALL        0x60    //Stop All Actions

//���� �������� ������� (ET7122)
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!��������!!!!!!!!!!!!!!!!!!!!!
// ��� ���������� ����� ������ �� ��������  ����������� �� ���� (� TEST � GET)
// � �������� �������� ucommdrive
// � ����� ��� TEST__ � ������ MAIN � ����������
#define TEST_VOLTAGE    0x10    //������ ��������� ����������
#define TEST_CONVERTER  0x11    //������ �������� ���������������
#define TEST_LOOP       0x12    //������ �������� ����
#define TEST_CALIBR     0x13    //����������
#define TEST_LED        0x13
#define POWER_ON        0x14    //������ ������� �� ���������������
#define POWER_OFF       0x15    //���������� �������
#define TEST_NWORK      0x16    //�������� � ��
#define TEST_CYCLS      0x17    //�������� �������������
#define REPEAT_TEST     0x18    //����������� �����.
#define REQ_NUM         0x19    //������ ���������� ������
#define SAVE_PARAM      0x1a    //������ ���������� ����������
#define TEST_TERMO      0x1b    //�������� � �����������



//���� �������� ������ (RecResult)
#define GET_VOLTAGE     0x20    //������ ������ ����������
#define GET_CONVERTER   0x21    //������ ���������� ���������������
#define GET_LOOP        0x22    //������ ���������� ����
#define GET_CALIBR      0x23    //���������� ����������
#define GET_LED      		0x23    
#define GET_NWORK       0x26    //��������� �������� ��
#define GET_CYCL        0x27    //��������� �������� ������
#define GET_REST        0x28    //Get current value
#define GET_TERMO       0x2b    //�������� � �����������




//���� ���������� ��� ������������ �����
#define SET_CPOINT      0x18    //��������� ����� ���������� �������������

//���� �������� ������� BurnFile
#define BURN_CMPLT      0x00    //������ ��������
#define BURN_INPROCESS  0x01    //������ ����
#define BURN_WRONGFILE  0x02    //���� �����������
#define BURN_ERROR      0x03    //������ �������

/*������ �������*/
#define FR_OK                           0x00   /*������� ��������� �������        */
#define FR_CANCELED                     0xC0   /*�������� ��������                */
/*������ ������� ������� ����� sendfrm*/
#define ERR_SEND_WRITE_PORT             -1   /*�� ������� �������� � ����       */
#define ERR_SEND_PORT_IS_CLOSED         -2   /*���� ������                      */
#define ERR_SEND_BAD_FC                 -3   /*�������� ��� �������             */
/*������ ������� ��Ȩ�� ����� recfrm*/
#define ERR_REC_NO_RESPOND              -10   /*���������� �� ��������           */
#define ERR_REC_PORT_IS_CLOSED          -11   /*���� ������                      */
#define ERR_REC_CRC                     -12   /*� ��������� ����� �� ������� CRC */
#define ERR_REC_LENGTH                  -13   /*� ����� �� ������� ������        */


/*������ ������� ������������� ������ init*/
#define ERR_INI_PORT                    -20   /*�� ������� ������� ����          */
#define ERR_INI_BLSIZE                  -21   /*������ ����� �� �������� � 10-1000 ���� */
#define ERR_INI_repeat                  -22   /*��������� ���� � ��������� ������������� ������������ ������ */
/*������ ������� L7*/
#define ERR_TOO_LONG                  -31   /*�������� ������ ������ ��� ��������� */
#define ERR_NO_CONNECT                -32   /*�������� ������ ������ ��� ��������� */

/*������ ������������ tind*/
#define ERR_REQ_ACTIVE                  -40   /*��� ���� �������� ������, ������� ��������� ��� */
#define ERR_NO_CONNECT                -32   /*�������� ������ ������ ��� ��������� */

enum commands{GET_INFO=1,SET_KEY=0x1a,GET_IND=0x1b};
