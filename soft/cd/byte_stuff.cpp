#define  byte_stuff

#include "byte_stuff.h"

#define DLE 0x55
#define SOT 0x0F
#define EOT 0xF0
terrstat errstat;
int makefrm(char * outbuff,char * frm, int len, int maxlen)
{
  tsenctx ctx;
  int i;
  char ch;
  inisend(len, frm,&ctx);
  for (i=0;i<maxlen;i++)
  {
    if (getnextch(&ch,&ctx)){return i;} //кадр успешно сформирован
    else outbuff[i]=ch;
  }
  return 0; //кадр не влез в выходной буфер
}

void inirec(trecctx * recctx)
{
  CLI
  recctx->lrec=0;
  recctx->recst=0;
  EI
}
void inisend(int l, char * bufpoint,tsenctx * senctx)
{
  CLI
  senctx->l=l;
  senctx->senptr=bufpoint;
  senctx->senst=0;
  send_begin
  EI
}

char getnextch(char *nextch, tsenctx * senctx)
{
  switch (senctx->senst)
  {
    case 0: {*nextch=DLE;senctx->senst=1;return 0;}
    case 1: {*nextch=SOT;senctx->senst=2;return 0;}
    case 2: {
              *nextch=*(senctx->senptr);
              if (*nextch==DLE)
              {
                senctx->senst=3;
                senctx->l--;
                senctx->senptr++;
                return 0;
              }
              senctx->l--;
              senctx->senptr++;
is_last:      if (senctx->l<=0){senctx->senst=4; return 0;}
              return 0;
            }
    case 3:{*nextch=DLE;senctx->senst=2;goto is_last;}
    case 4:{*nextch=DLE;senctx->senst=5;return 0;}
    case 5:{*nextch=EOT;senctx->senst=6;return 0;}
    default: return 1;
  }
}

int recfrm_bs(trecctx * recctx, char *source, int len, int * curroffs)
{
  int r;
  inirec(recctx);
  for (;* curroffs<len;(*curroffs)++)
  {
    r=recnextch(source[* curroffs],recctx);
    if(r==0)return 0;
  }
  return 1;
}

char recnextch(char nextch,trecctx * recctx)
{
  switch (recctx->recst)
  {
    case 0: if (nextch==DLE){recctx->recst=1;return 1;}
            else return 2;
    case 1: switch (nextch)
                {
                  case SOT:
                  {
                    recctx->lrec=0;
                    recctx->recst=2;
                    return 1;
                  }
                  case EOT:
                  {
                    if (recctx->lrec==0){recctx->recst=0; return 2;}
                    else {recctx->recst=3;return 0;
                  }
               }
               case DLE: if (recctx->lrec!=0)
                         {
                           recctx->recst=2;
                           recctx->rbuf[recctx->lrec]=DLE;
                           recctx->lrec++; return 1;
                         }
                         else
                         {
                           recctx->recst=0;
                           return 2;
                         }
               default:  recctx->recst=0;
                         return 2;
             }
     case 2: //прием тела кадра
                if (nextch==DLE){recctx->recst=1;return 1;}
                else    if (recctx->lrec<(rbuf_size-1)){recctx->rbuf[recctx->lrec]=nextch;
                                                   recctx->lrec++;return 1;}
                        else {recctx->recst=0;return 1;}

     default:   recctx->recst=0;
                return 2;
  }
}
