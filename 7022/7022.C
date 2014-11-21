#include "stm32f10x.h"
#include "7022.h"
#include <stdio.h>
#include "extern.h"
#define IQR GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14)
/****************************/
double Ua=0,Ub,Uc,Ia,Ib,Ic,Pa,Pb,Pc;
int UA,UB,UC,IA,IB,IC,PA,PB,PC,Pft,F;
int Uag,Ubg,Ucg,Iag,Ibg,Icg,Pag,Pbg,Pcg,Qag,Qbg,Qcg,Sag,Sbg,Scg,Qaph,Qbph,Qcph,Paph,Pbph,Pcph,Ept,Eqt,Est;
double temp=0,Pfa,Pfb,Pfc;

/******************/
#define Chip_ID 0x7122A0

void Correction7022()
{
while(Read7022(0)!=0x7122A0);
Proofread_EN();
  write7022(w_ModeCfg+0x80,0xb9Ff);//模式配置  
  write7022(w_EMUCfg+0x80,0xf884);
  write7022(w_ModuleCFG+0x80,0x3427);//模拟模块使能 
  write7022(w_Hfconst+0x80,0x7); 
	
  write7022(w_UgainA+0x80,verify_parameter[0]);
  write7022(w_UgainB+0x80,verify_parameter[1]);
  write7022(w_UgainC+0x80,verify_parameter[2]);
  write7022(w_IgainA+0x80,verify_parameter[3]);
  write7022(w_IgainB+0x80,verify_parameter[4]);
  write7022(w_IgainC+0x80,verify_parameter[5]);
  write7022(w_PgainA+0X80,verify_parameter[6]);
  write7022(w_PgainB+0X80,verify_parameter[7]);
  write7022(w_PgainC+0X80,verify_parameter[8]);
  write7022(w_QgainA+0X80,verify_parameter[6]);
  write7022(w_QgainB+0X80,verify_parameter[7]);
  write7022(w_QgainC+0X80,verify_parameter[8]);
  write7022(w_SgainA+0X80,verify_parameter[6]);
  write7022(w_SgainB+0X80,verify_parameter[7]);
  write7022(w_SgainC+0X80,verify_parameter[8]);  
  write7022(w_PhSregApq1+0x80,verify_parameter[9]);//65082
  write7022(w_PhSregApq0+0x80,verify_parameter[9]);//65082
  write7022(w_PhSregBpq1+0x80,verify_parameter[10]);//65157
  write7022(w_PhSregBpq0+0x80,verify_parameter[10]);//65157
  write7022(w_PhSregCpq1+0x80,verify_parameter[11]);//65088
  write7022(w_PhSregCpq0+0x80,verify_parameter[11]); //65088
  write7022(w_QPhscal+0x80,0x0);
  /*
  write7022(w_PGACtrl,);
     
  write7022(w_PoffsetA,);
  write7022(w_PoffsetB,);
  write7022(w_PoffsetC,);
  
  write7022(w_QoffsetA,);
  write7022(w_QoffsetB,);
  write7022(w_QoffsetC,);
  
  write7022(w_UaRmsoffse);
  write7022(w_UbRmsoffse);
  write7022(w_UcRmsoffse);
  
  write7022(w_IaRmsoffse);
  write7022(w_IbRmsoffse);
  write7022(w_IcRmsoffse);
  
  write7022(w_Pstart); 
  */
  Proofread_DIS();
}

void Proofread()
{
	
    Ua=Read7022(r_URmsa); 
    temp=Ua/t13;
    temp=(U/temp-1);
    Uag=(int)(temp*t15);    
      
   Ub=Read7022(r_URmsb); 
	 temp=Ub/t13;
   temp=(U/temp-1);
	 if(temp>0)
   Ubg=(int)(temp*t15);
   else
  		Ubg=(int)(t16+temp*t15);
   UB=(int)temp;
    
   Uc=Read7022(r_URmsc); 
   temp=Uc/t13;
   temp=(U/temp-1);
   Ucg=(int)(temp*t15);   
   UC=(int)temp;
   
    
  
   Ia=Read7022(r_IRmsa); 
   temp=Ia/t13/Na;
   temp=(I/temp-1);
	 if(temp<0)
	 Iag=(int)(t16+temp*t15);
	 else
   Iag=(int)(temp*t15);   
   IA=(int)temp;
   
  
   Ib=Read7022(r_IRmsb); 
   temp=Ib/t13/Nb;
   temp=(I/temp-1);
	 if(temp<0)
		 Ibg=(int)(t16+temp*t15);
	 else
   Ibg=(int)(temp*t15);   
   IB=(int)temp;
   
   
  
   Ic=Read7022(r_IRmsc); 
   temp=Ic/t13/Nc;
   temp=(I/temp-1);
	 if(temp<0)
		 Icg=(int)(t16+temp*t15);
	 else
   Icg=(int)(temp*t15);
   IC=(int)temp;
    
    
    /************功率增益*****************/
  
   Pa=Read7022(r_Pa);
   temp=Pa*K;
   temp=P/temp-1;
   if(temp>0)
     Pag=(int)(temp*t15);
   else
     Pag=(int)(t16+temp*t15);  
   PA=(int)temp;
   PA=Read7022(r_Pa)*K;
   temp=(double)(PA-P_P)/P_P/1.732;
	 
   Pb=Read7022(r_Pb);
   temp=Pb*K;
   temp=P/temp-1;
   if(temp>0)
     Pbg=(int)(temp*t15);
   else
     Pbg=(int)(t16+temp*t15);  
   PB=(int)temp;
   
 
   Pc=Read7022(r_Pc);
   temp=Pc*K;
   temp=P/temp-1;
   if(temp>0)
     Pcg=(int)(temp*t15);
   else
     Pcg=(int)(t16+temp*t15);
   PC=(int)temp;
   
	 
   
   
/**************功率因数************************/    
	   temp=Read7022(r_Pfa);   
   if(temp>t23)
     temp=(int)(temp-t24);
   Pfa=temp/t23*100;

	 temp=Read7022(r_Pfb);   
   if(temp>t23)
     temp=(int)(temp-t24);
   Pfb=temp/t23*100;
	 
	 temp=Read7022(r_Pfc);   
   if(temp>t23)
     temp=(int)(temp-t24);
   Pfc=temp/t23*100;
	}

void Read_reg(void)
{
  int temp;
  {
		F=Read7022(0);
    F=(int)(Read7022(r_Freq)/t13);     
    IA=(int)((double)Read7022(r_IRmsa)/t13/Na*100);
    IB=(int)((double)Read7022(r_IRmsb)/t13/Nb*100);
    IC=(int)((double)Read7022(r_IRmsc)/t13/Nc*100);
		
		UA=(int)((double)Read7022(r_URmsa)/t13*100);
    UB=(int)((double)Read7022(r_URmsb)/t13*100);
    UC=(int)((double)Read7022(r_URmsc)/t13*100);
			
		PA=Read7022(r_Pa);
			if(PA>t23) PA=PA-t24;
			PA=(int)(PA*K);   
    PB=Read7022(r_Pb);
			if(PB>t23) PB=PB-t24;
			PB=(int)(PB*K);    
    PC=Read7022(r_Pc);
			if(PC>t23) PC=PC-t24;
			PC=(int)(PC*K);
		
		
  temp=Read7022(r_Pfa);   
   if(temp>t23)
     temp=(temp-t24);
   Pfa=(double)(temp/t23*100);

	 temp=Read7022(r_Pfb);   
   if(temp>t23)
     temp=(temp-t24);
   Pfb=(double)(temp/t23*100);
	 
	 temp=Read7022(r_Pfc);   
   if(temp>t23)
     temp=(temp-t24);
   Pfc=(double)(temp/t23*100);

	 
    temp=Read7022(0x21);
	  temp=(int)(temp/2*3);
    ALL_DATA[5]=IA>>8;
		ALL_DATA[6]=IA;
    ALL_DATA[7]=IB>>8;
		ALL_DATA[8]=IB;
		ALL_DATA[9]=IC>>8;
		ALL_DATA[10]=IC;
		
		ALL_DATA[11]=UA>>8;
		ALL_DATA[12]=UA;
    ALL_DATA[13]=UB>>8;
		ALL_DATA[14]=UB;
		ALL_DATA[15]=UC>>8;
		ALL_DATA[16]=UC;
 
    ALL_DATA[17]=PA>>8;
		ALL_DATA[18]=PA;
    ALL_DATA[19]=PB>>8;
		ALL_DATA[20]=PB;
		ALL_DATA[21]=PC>>8;
		ALL_DATA[22]=PC;
		
		ALL_DATA[23]=temp>>16;
		ALL_DATA[24]=temp>>8;
		ALL_DATA[25]=temp;
		
  }
}
//返回参数：0~3为1 A B C 合相有功反向
//          4~6为1 A B C 电压失压
//           7    电压相序错
//           8    电流相序错
//           9    有功负
//           10   无功负
int Detection_of_phase_squence(void)
{
	int temp=0;
	temp=(Read7022(r_SFlag)&0xFF)<<4|(Read7022(r_PFlag)&0x07);//标志状态
	return temp;
}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	





	
	
	
	
	
	
	
	
	
	
	


