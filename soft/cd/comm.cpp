#define NO_WIN32_LEAN_AND_MEAN

#include <sys\stat.h>
#include <WindowsX.h>
#include <windows.h>
#include <registry.hpp>
#include <io.h>
#include <assert.h>
#include <stdio.h>
#include "comm.h"
/////////////////////////////////////////////////////////////////////////////////
int comopen(char * com,DWORD  speed,unsigned long* dwError){ //открытие com-порта с именем com
/////////////////////////////////////////////////////////////////////////////////
DCB dcb;
  COMMTIMEOUTS ct;
  HANDLE handle; //COM port handle
  void * hCom;  BOOL fSuccess;  handle=::CreateFile(com,		GENERIC_READ|GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		0,
		NULL);
  if (handle==INVALID_HANDLE_VALUE)
           {
           handle=0;
           return 0;
           }

  GetCommState(handle,&dcb);
  dcb.BaudRate=speed;
  dcb.ByteSize=8;
  dcb.fDtrControl=DTR_CONTROL_ENABLE;
  dcb.fInX=0;
  dcb.fOutX=0;
  dcb.fNull=0;
  dcb.fOutxCtsFlow=0;
  dcb.StopBits=ONESTOPBIT;
  dcb.fParity=0;
  dcb.Parity=0;
  dcb.fRtsControl=RTS_CONTROL_ENABLE;
  dcb.fAbortOnError=0;
  dcb.fDsrSensitivity=0;
  dcb.fErrorChar=0;
  dcb.fOutxCtsFlow=0;
  dcb.fOutxDsrFlow=0;
  dcb.fTXContinueOnXoff=0;
  if (!SetCommState(handle,&dcb))
		goto m_fail;

  GetCommTimeouts(handle,&ct);
  ct.ReadIntervalTimeout=55;
  ct.ReadTotalTimeoutConstant=250;
  ct.ReadTotalTimeoutMultiplier=0;
  ct.WriteTotalTimeoutConstant=1000;
  ct.WriteTotalTimeoutMultiplier=1000;
  if (!SetCommTimeouts(handle,&ct))
		goto m_fail;
  if (!SetupComm(handle,3072,3072)) goto m_fail;

  EscapeCommFunction(handle,CLRRTS);
  return (int)handle;
m_fail:  FileClose((int)handle);  return 0;}


