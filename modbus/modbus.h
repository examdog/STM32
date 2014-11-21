#ifndef __modbus_h
#define __modbus_h
#include "stm32f10x.h"
#include "Base_Config.h"
#include "AT45DB.H"

#define MAX_READ_LEN 125 
#define MAX_RECEIVE_LEN (MAX_READ_LEN*2+5)//255个
#define SENDBUF_LEN 300
#define MyAddress 1
#define MDB_MEMADDR_MAX 101
#define MDB_REGADDR_MAX 120
#define EVERY_BYTE_TIME9600  10 //1ms 一个字节 0.1MS进一次中断 
extern int Max_C;//最大值更新次数
extern int UA,UB,UC,IA,IB,IC,PA,PB,PC,Pfa,Pfb,Pfc,Pft,F;
extern const int comm_delay[3];
extern unsigned char DF_buffer[264];
extern char flag;
union int2char
{
    unsigned int i;
    struct
    {
        unsigned char low;
        unsigned char high;
    }asd ;
};


enum commstat {WAITCOMM,RECEIVE,DEAL,SENDPRE,SEND,SENDEND};

struct commstruct
{
    unsigned char receivebuf[MAX_RECEIVE_LEN],receivepoint,sendbuf[SENDBUF_LEN];
    int sendlength,sendpoint;
    enum commstat commstate;
    short int delay_ctrl,timer;
};
extern struct commstruct comm1,comm2,comm3,comm4;
extern double Degree_Max,Degree_Min,Degree_temp,Degree;
extern struct commstruct comm1,comm2,comm3,comm4;
void dealcommmsg(struct commstruct * thiscomm);
void dealcommmsg2(struct commstruct * thiscomm);
void dealcommmsg3(struct commstruct * thiscomm);
extern void send_commmsg(struct commstruct * thiscomm,u8  datatype);//done为0，error为1/*封包发送准备发送*/

#endif
