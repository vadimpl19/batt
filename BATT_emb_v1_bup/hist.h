void inihist(UINT start_adr,UINT maxadr);
void addh(int h);
typedef struct thist {
     int len;
     char adr;
     char cf;
     int harr[1];
     int crc;
}thist;

#ifndef its_hist_source
extern thist hist ;
#endif
