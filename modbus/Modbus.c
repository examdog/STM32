#include "modbus.h"
#include <stdio.h>
#include <string.h>
#include "7022.h"
#include<stdlib.h>
#include<math.h> 
#include "extern.h"
#include "flash.h"
#include "RTC_Time.h"
struct commstruct comm1,comm2,comm3,comm4;
//union int2char commchg;
const int comm_delay[3]=
{
    4*EVERY_BYTE_TIME9600,2*EVERY_BYTE_TIME9600,EVERY_BYTE_TIME9600*4
};

struct data_map
{
    int def;
    int * rampoint;
};
int Pp_1,Pp_2,Pp_3,Prp_1,Prp_2,Prp_3,Pn_1,Pn_2,Pn_3,Prn_1,Prn_2,Prn_3;
char DEVICD_ID[30]="dk_103";
int interval=60;
int q=1,w=2,e=3;
extern int balance_p,balance_i;
extern unsigned char Begin_B;
extern unsigned char first_open;

/***********************/

/***********************/
u16 verify_parameter[12];//12个校表参数 起始地址56
int Year=12,Month=12,Day=12,Hour=12,Min=12,Sec=12;
struct data_map  UIPQFS[29]={
														 {0,&Pft},
														 {0,&Pft},	
                             {0,&UA},
                             {0,&UB},
                             {0,&UC},
                             {0,&IA},
                             {0,&IB},
                             {0,&IC},
                             {0,&PA},
                             {0,&PB},
                             {0,&PC},
														 {0,&F}, 
                             {0,&Pfa},
                             {0,&Pfb},
                             {0,&Pfc},
                                              
                             {0,&Year},
														 {0,&Month},
														 {0,&Day},
														 {0,&Hour},
														 {0,&Min},
														 {0,&Sec},
														 {0,&Pft},
														 {0,&Pft},

														 {0,&interval},															 
                           
                            };

const unsigned char auchCRCHi[] =
{
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
    0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
    0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01,
    0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81,
    0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01,
    0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
    0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
    0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01,
    0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
    0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01,
    0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
    0x40
};
const char auchCRCLo[] =
{
    0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06, 0x07, 0xC7, 0x05, 0xC5, 0xC4,
    0x04, 0xCC, 0x0C, 0x0D, 0xCD, 0x0F, 0xCF, 0xCE, 0x0E, 0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09,
    0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9, 0x1B, 0xDB, 0xDA, 0x1A, 0x1E, 0xDE, 0xDF, 0x1F, 0xDD,
    0x1D, 0x1C, 0xDC, 0x14, 0xD4, 0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3,
    0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3, 0xF2, 0x32, 0x36, 0xF6, 0xF7,
    0x37, 0xF5, 0x35, 0x34, 0xF4, 0x3C, 0xFC, 0xFD, 0x3D, 0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A,
    0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38, 0x28, 0xE8, 0xE9, 0x29, 0xEB, 0x2B, 0x2A, 0xEA, 0xEE,
    0x2E, 0x2F, 0xEF, 0x2D, 0xED, 0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26,
    0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60, 0x61, 0xA1, 0x63, 0xA3, 0xA2,
    0x62, 0x66, 0xA6, 0xA7, 0x67, 0xA5, 0x65, 0x64, 0xA4, 0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F,
    0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB, 0x69, 0xA9, 0xA8, 0x68, 0x78, 0xB8, 0xB9, 0x79, 0xBB,
    0x7B, 0x7A, 0xBA, 0xBE, 0x7E, 0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5,
    0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71, 0x70, 0xB0, 0x50, 0x90, 0x91,
    0x51, 0x93, 0x53, 0x52, 0x92, 0x96, 0x56, 0x57, 0x97, 0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C,
    0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E, 0x5A, 0x9A, 0x9B, 0x5B, 0x99, 0x59, 0x58, 0x98, 0x88,
    0x48, 0x49, 0x89, 0x4B, 0x8B, 0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,
    0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42, 0x43, 0x83, 0x41, 0x81, 0x80,
    0x40
};




unsigned short int CRC16(unsigned char *puchMsg,unsigned short int  usDataLen)
{
    unsigned char uchCRCHi = 0xFF ;
    unsigned char uchCRCLo = 0xFF ;
    unsigned uIndex ;
    while (usDataLen--)
    {
        uIndex = uchCRCHi ^ *puchMsg++ ;
        uchCRCHi = uchCRCLo ^ auchCRCHi[uIndex];
        uchCRCLo = auchCRCLo[uIndex] ;
    }
    return (uchCRCHi << 8 | uchCRCLo) ;
}

unsigned char ack_inst_3_reg(struct commstruct * thiscomm,int read_startaddress, int read_len)//命令3标准应答，回复parm_table寄存器的值
{
    int b;
    u16 temp[30];  
	  union int2char commchg;
	  read_startaddress+=1;
    thiscomm->sendbuf[0] = MyAddress;
    thiscomm->sendbuf[1] = thiscomm->receivebuf[1]; 
	thiscomm->sendbuf[2]=read_len*2;
	  if(read_startaddress<25)
		{
      for (b = 0; b < read_len; b++)
    {   
        {
          commchg.i=*UIPQFS[read_startaddress+b].rampoint;
          thiscomm->sendbuf[3 + b*2] = commchg.asd.high;
          thiscomm->sendbuf[3 + b * 2+1] = commchg.asd.low;

        }
    }
		thiscomm->sendlength = 3 + read_len * 2 + 1 + 1;
		commchg.i = CRC16(&(thiscomm->sendbuf[0]), 3 + read_len * 2);
    thiscomm->sendbuf[3 + read_len * 2 ] = commchg.asd.high;
    thiscomm->sendbuf[3 + read_len * 2  + 1] = commchg.asd.low;
	}
	  else if((read_startaddress>=25)&&(read_startaddress<=55))
	{
		
		for(b=0;b<30;b++)
		temp[b]=*(u16*)(sn_add+b*2);
		for(b=0;b<30;b++)
		thiscomm->sendbuf[3+b]=temp[b];
		
		thiscomm->sendlength = 3 + read_len * 2 + 1 + 1;
		commchg.i = CRC16(&(thiscomm->sendbuf[0]), 3 + read_len * 2);
    thiscomm->sendbuf[3 + read_len * 2 ] = commchg.asd.high;
    thiscomm->sendbuf[3 + read_len * 2  + 1] = commchg.asd.low;
	}
    else if(read_startaddress>55)
		{
			
			}
    
    thiscomm->timer = comm_delay[0];
    thiscomm->commstate = SENDPRE;//准备发送
    return 0;

}



unsigned char chk_inst_error(unsigned char *commbuf,unsigned char  commLen)//检查命令和命令长度
{
    if( (commbuf[1] == 0x03)
            ||((commbuf[1] == 0x06) && (commLen == 8))
            ||(commbuf[1] == 0x10)||(commbuf[1] == 0x04)
      )
    {
        return 0;
    }

    return 1;
}



    
void deal_inst_3(struct commstruct * thiscomm)
{
    union int2char commchg;
    int read_startaddress, read_len;
    commchg.i=0;
    commchg.asd.high = thiscomm->receivebuf[2];
    commchg.asd.low = thiscomm->receivebuf[3];
    read_startaddress = commchg.i;
    commchg.asd.high = thiscomm->receivebuf[4];
    commchg.asd.low = thiscomm->receivebuf[5];
    read_len = commchg.i;

    if (!(read_startaddress < 0 || read_startaddress >= MDB_MEMADDR_MAX
            || read_len < 1 || read_len > MAX_READ_LEN))
    {
        if (read_startaddress < MDB_REGADDR_MAX)
        {
            if(!ack_inst_3_reg(thiscomm,read_startaddress, read_len))//换成485的结构体
            {
                return;//正常处理完，可以返回
            }
        }
       
    }

//异常处理

//出界应答

    thiscomm->sendbuf[0] = MyAddress;
    thiscomm->sendbuf[1] = thiscomm->receivebuf[1] | 0x80;
    thiscomm->sendbuf[2] = 0x82;//82．非法的数据位置。
    commchg.i = CRC16(&(thiscomm->sendbuf[0]),3);
    thiscomm->sendbuf[3] = commchg.asd.high;
    thiscomm->sendbuf[4] = commchg.asd.low;
    thiscomm->sendlength = 5;
    //thiscomm->timer = comm_delay[0];
    thiscomm->commstate = SENDPRE;//准备发送
    return;
}




void  deal_inst_6(struct commstruct * thiscomm)
{
	  union int2char commchg;
    int write_startaddress,data;
    commchg.i=0;
    commchg.asd.high = thiscomm->receivebuf[2];
    commchg.asd.low = thiscomm->receivebuf[3];
    write_startaddress = commchg.i;
	
	  commchg.asd.high = thiscomm->receivebuf[4];
    commchg.asd.low = thiscomm->receivebuf[5];
		data = commchg.i;
	  if(write_startaddress==24)//修改采集间隔 单位分钟
		{
			interval=data;
			FLASH_Unlock();
			FLASH_ClearFlag(FLASH_FLAG_EOP|FLASH_FLAG_PGERR|FLASH_FLAG_WRPRTERR);
			FLASH_ErasePage(interval_add);
      FLASH_ProgramHalfWord(sn_add ,interval);  //flash  为一个字节存储，16位数据必须地址加2
			FLASH_Lock();
			}

	}


	
void deal_inst_16(struct commstruct * thiscomm)
{
	  union int2char commchg;
    int write_startaddress,len;
	  char i=0;

    commchg.i=0;
    commchg.asd.high = thiscomm->receivebuf[2];
    commchg.asd.low = thiscomm->receivebuf[3];
    write_startaddress = commchg.i+1;
	  commchg.asd.high = thiscomm->receivebuf[4];
    commchg.asd.low = thiscomm->receivebuf[5];
		len = commchg.i;
	  if((write_startaddress>=25)&&(write_startaddress<55))//每个寄存器存一个字母
		{

		for(i=0;i<len*2;i++)
			{
				DEVICD_ID[i]=thiscomm->receivebuf[7+i];
			}
	  FLASH_Unlock();
		FLASH_ClearFlag(FLASH_FLAG_EOP|FLASH_FLAG_PGERR|FLASH_FLAG_WRPRTERR);
		FLASH_ErasePage(sn_add);
	  for(i=0;i<len*2+1;i++)
		FLASH_ProgramHalfWord(sn_add+i*2,DEVICD_ID[i]);  //flash  为一个字节存储，16位数据必须地址加2
		FLASH_Lock();
		for(i=0;i<5;i++)
		thiscomm->sendbuf[i]=thiscomm->receivebuf[i];
		thiscomm->sendlength = 5+1 + 1;
		commchg.i = CRC16(&(thiscomm->sendbuf[0]), 5);
    thiscomm->sendbuf[5 * 2 ] = commchg.asd.high;
    thiscomm->sendbuf[5  + 1] = commchg.asd.low;
		thiscomm->commstate = SENDPRE;//准备发送
		thiscomm->timer = comm_delay[0];
   
		/*
	  for(i=0;i<len+1;i++)
		temp[i]=*(u16*)(sn_add+i*2);
		for(i=0;i<len+1;i++)
		thiscomm->sendbuf[i]=temp[i];
		
    thiscomm->sendlength = len;
    thiscomm->timer = comm_delay[0];
    thiscomm->commstate = SENDPRE;//准备发送
			*/
		}
		
		else if((write_startaddress>=55))
		{
			for(i=0;i<len;i++)
			{
				commchg.asd.high = thiscomm->receivebuf[7+i*2];
        commchg.asd.low  = thiscomm->receivebuf[7+i*2+1];
				verify_parameter[write_startaddress+i-55]=commchg.i;
			}
				FLASH_Unlock();
				FLASH_ClearFlag(FLASH_FLAG_EOP|FLASH_FLAG_PGERR|FLASH_FLAG_WRPRTERR);
				FLASH_ErasePage(verify_data_add);
				for(i=0;i<12;i++)
				FLASH_ProgramHalfWord(verify_data_add+i*2,verify_parameter[i]);  //flash  为一个字节存储，16位数据必须地址加2
				FLASH_Lock();
			for(i=0;i<5;i++)
		thiscomm->sendbuf[i]=thiscomm->receivebuf[i];
		thiscomm->sendlength = 5+1 + 1;
		commchg.i = CRC16(&(thiscomm->sendbuf[0]), 5);
    thiscomm->sendbuf[5 * 2 ] = commchg.asd.high;
    thiscomm->sendbuf[5  + 1] = commchg.asd.low;
		thiscomm->commstate = SENDPRE;//准备发送
		thiscomm->timer = comm_delay[0];
			
			IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
				  IWDG_SetReload(0);   
	  IWDG_ReloadCounter(); 
			}
			else
			{
					  commchg.asd.high = thiscomm->receivebuf[4];
    commchg.asd.low = thiscomm->receivebuf[5];

				for(i=0;i<len;i++)
				{
					commchg.asd.high = thiscomm->receivebuf[7+i*2];
					commchg.asd.low = thiscomm->receivebuf[7+i*2+1];
					*UIPQFS[write_startaddress++].rampoint=commchg.i;
					}			
					initdate();
		for(i=0;i<5;i++)
		thiscomm->sendbuf[i]=thiscomm->receivebuf[i];
		thiscomm->sendlength = 5+1 + 1;
		commchg.i = CRC16(&(thiscomm->sendbuf[0]), 5);
    thiscomm->sendbuf[5 * 2 ] = commchg.asd.high;
    thiscomm->sendbuf[5  + 1] = commchg.asd.low;
		thiscomm->commstate = SENDPRE;//准备发送
		thiscomm->timer = comm_delay[0];
			}
    return;
	}  

  void dealcommmsg(struct commstruct * thiscomm)//对接到的数据包进行处理，准备发送
{
    unsigned int chkcrc;
    union int2char commchg;

    if (thiscomm->commstate == DEAL)//处理程序
    {
        //长度检测和CRC 校验
        if (thiscomm->receivepoint < 4)//数据不足
        {
            thiscomm->commstate = WAITCOMM;
            USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);
            return;
        }
        commchg.i=0;
        chkcrc = CRC16(&(thiscomm->receivebuf[0]), (unsigned int)(thiscomm->receivepoint - 2));
        commchg.asd.low = thiscomm->receivebuf[thiscomm->receivepoint - 1];
        commchg.asd.high = thiscomm->receivebuf[thiscomm->receivepoint - 2];//高位
        if (commchg.i != chkcrc)//校验错
        {
            thiscomm->commstate = WAITCOMM;
            USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);
            return;
        }

        if((thiscomm->receivebuf[0] != MyAddress) && (thiscomm->receivebuf[0] != 0))
        {
            thiscomm->commstate = WAITCOMM;
            USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);
            return;
        }//地址不匹配不予处理

        if(chk_inst_error(&(thiscomm->receivebuf[0]),thiscomm->receivepoint))//命令不支持，或帧长度不对
        {
            thiscomm->sendbuf[0] = MyAddress;//准备应答
            thiscomm->sendbuf[1] = thiscomm->receivebuf[1] | 0x80;
            thiscomm->sendbuf[2] = 0x81;//81．非法的功能码
            commchg.i = CRC16(&(thiscomm->sendbuf[0]), 3);
            thiscomm->sendbuf[3] = commchg.asd.high;
            thiscomm->sendbuf[4] = commchg.asd.low;
            thiscomm->sendlength = 5;
            thiscomm->timer = comm_delay[0];
            thiscomm->commstate = SENDPRE;//准备发送
            return;
        }

        switch(thiscomm->receivebuf[1])//处理通讯命令
        {
        case 3:
          {
            deal_inst_3(thiscomm);
          }
            break;
				case 6:
          {
            deal_inst_6(thiscomm);           
          }
            break;
       	case 16:
          {
            deal_inst_16(thiscomm);           
          }
            break;
        
        default:  { thiscomm->commstate = WAITCOMM;
       
        }
        break;
        }
        return;
    }
}



void dealcommmsg2(struct commstruct * thiscomm)//对接到的数据包进行处理，准备发送
{
    unsigned int chkcrc;
    union int2char commchg;
    commchg.i=0;
    if (thiscomm->commstate == DEAL)//处理程序
    {
        //长度检测和CRC 校验
        if (thiscomm->receivepoint < 4)//数据不足
        {
            thiscomm->commstate = WAITCOMM;
            USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
            return;
        }

        chkcrc = CRC16(&(thiscomm->receivebuf[0]), (unsigned int)(thiscomm->receivepoint - 2));
        commchg.asd.low = thiscomm->receivebuf[thiscomm->receivepoint - 1];
        commchg.asd.high = thiscomm->receivebuf[thiscomm->receivepoint - 2];//高位
        if (commchg.i != chkcrc)//校验错
        {
            thiscomm->commstate = WAITCOMM;
            USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
            return;
        }

        if((thiscomm->receivebuf[0] != MyAddress) && (thiscomm->receivebuf[0] != 0))
        {
            thiscomm->commstate = WAITCOMM;
            USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
            return;
        }//地址不匹配不予处理

        if(chk_inst_error(&(thiscomm->receivebuf[0]),thiscomm->receivepoint))//命令不支持，或帧长度不对
        {
            thiscomm->sendbuf[0] = MyAddress;//准备应答
            thiscomm->sendbuf[1] = thiscomm->receivebuf[1] | 0x80;
            thiscomm->sendbuf[2] = 0x81;//81．非法的功能码
            commchg.i = CRC16(&(thiscomm->sendbuf[0]), 3);
            thiscomm->sendbuf[3] = commchg.asd.high;
            thiscomm->sendbuf[4] = commchg.asd.low;
            thiscomm->sendlength = 5;
            thiscomm->timer = comm_delay[0];
            thiscomm->commstate = SENDPRE;//准备发送
            return;
        }

        switch(thiscomm->receivebuf[1])//处理通讯命令
        {
        case 3:
          {
            deal_inst_3(thiscomm);
            
          }
            break;
        case 6:
          {
            deal_inst_6(thiscomm);           
          }
            break;
       	case 16:
          {
            deal_inst_16(thiscomm);           
          }
            break;
        default:   {thiscomm->commstate = WAITCOMM; USART_ITConfig(USART2, USART_IT_TXE, ENABLE);}break;
        }
        return;
    }
}
double Degree_Max=0,Degree_Min=0,Degree_temp=0,Degree,zanshi;
int Max_C=0;//最大值更新次数
void dealcommmsg3(struct commstruct * thiscomm)//对接到的数据包进行处理，准备发送
{
    unsigned int chkcrc;
    union int2char commchg;
    commchg.i=0;
    if (thiscomm->commstate == DEAL)//处理程序
    {
        //长度检测和CRC 校验
        if (thiscomm->receivepoint < 4)//数据不足
        {
            thiscomm->commstate = WAITCOMM;
            USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
            return;
        }

        chkcrc = CRC16(&(thiscomm->receivebuf[0]), (unsigned int)(thiscomm->receivepoint - 2));
        commchg.asd.low = thiscomm->receivebuf[thiscomm->receivepoint - 1];
        commchg.asd.high = thiscomm->receivebuf[thiscomm->receivepoint - 2];//高位
        if (commchg.i != chkcrc)//校验错
        {
            thiscomm->commstate = WAITCOMM;
            USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
            return;
        }

        if((thiscomm->receivebuf[0] != MyAddress) && (thiscomm->receivebuf[0] != 0))
        {
            thiscomm->commstate = WAITCOMM;
            USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
            return;
        }//地址不匹配不予处理

        if(chk_inst_error(&(thiscomm->receivebuf[0]),thiscomm->receivepoint))//命令不支持，或帧长度不对
        {
            thiscomm->sendbuf[0] = MyAddress;//准备应答
            thiscomm->sendbuf[1] = thiscomm->receivebuf[1] | 0x80;
            thiscomm->sendbuf[2] = 0x81;//81．非法的功能码
            commchg.i = CRC16(&(thiscomm->sendbuf[0]), 3);
            thiscomm->sendbuf[3] = commchg.asd.high;
            thiscomm->sendbuf[4] = commchg.asd.low;
            thiscomm->sendlength = 5;
            thiscomm->timer = comm_delay[0];
            thiscomm->commstate = SENDPRE;//准备发送
            return;
        }

        switch(thiscomm->receivebuf[1])//处理通讯命令
        {
        case 3:
          {
            deal_inst_3(thiscomm);
            
          }
            break;
        
        default:   {thiscomm->commstate = WAITCOMM; USART_ITConfig(USART3, USART_IT_TXE, ENABLE);}break;
        }
        return;
    }
}
///////////////////////////////////////////////////////////////////////////
//通讯程序
void send_commmsg(struct commstruct * thiscomm,u8  datatype)//done为0，error为1/*封包发送准备发送*/
{
    int i;
  //  if(thiscomm->commstate==WAITCOMM)
  //  {
        for(i=0; i<5; i++)
        {
//            thiscomm->sendbuf[i]=comm_array[datatype][i];/*功能码，起始地址，数据长度*/
        }
        thiscomm->sendlength=8;
        thiscomm->timer = comm_delay[0];
        thiscomm->commstate = SENDPRE;//准备发送
   // }
}

