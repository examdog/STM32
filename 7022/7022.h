#ifndef __7022_h
#define __7022_h
/*���⹦�ܼĴ����������*/
#define Proofread_EN()  write7022(0xc9,0x00005A);//ʹ��дУ��
#define Proofread_DIS() write7022(0xc9,0x000050);//ʹ��дУ��

/*У������Ĵ���*/
#define w_ModeCfg 0x01
#define w_EMUCfg  0x03
#define w_ModuleCFG 0x31
#define w_PGACtrl 0x02
#define w_Iregion 0x37
#define w_PgainA  0x04
#define w_PgainB  0x05
#define w_PgainC  0x06
#define w_QgainA  0x07
#define w_QgainB  0x08
#define w_QgainC  0x09
#define w_SgainA  0x0a
#define w_SgainB  0x0b
#define w_SgainC  0x0c
#define w_PhSregApq0 0x0D 
#define w_PhSregBpq0 0x0e
#define w_PhSregCpq0 0x0f
#define w_PhSregApq1 0x10
#define w_PhSregBpq1 0x11
#define w_PhSregCpq1 0x12
#define w_PoffsetA 0x13
#define w_PoffsetB 0x14
#define w_PoffsetC 0x15
#define w_QPhscal  0x16
#define w_UgainA   0x17
#define w_UgainB   0x18
#define w_UgainC   0x19
#define w_IgainA   0x1a
#define w_IgainB   0x1b
#define w_IgainC   0x1c
#define w_Istarup  0x1d
#define w_Hfconst  0x1e
#define w_FailVoltage 0x1f
#define w_GainADC7 0x20
#define w_QoffsetA 0x21
#define w_QoffsetB 0x22
#define w_QoffsetC 0x23
#define w_UaRmsoffse 0x24
#define w_UbRmsoffse 0x25
#define w_UcRmsoffse 0x26
#define w_IaRmsoffse 0x27
#define w_IbRmsoffse 0x28
#define w_IcRmsoffse 0x29
#define w_UoffsetA   0x2a
#define w_UoffsetB   0x2b
#define w_UoffsetC   0x2c 
#define w_IoffsetA   0x2d
#define w_IoffsetB   0x2e
#define w_IoffsetC   0x2f
#define w_EMUIE      0x30
#define w_ModuleCFG  0x31
#define w_AllGain    0x32
#define w_HFDouble   0x33
#define w_LineGain   0x34
#define w_PinCtrl    0x35
#define w_Pstart     0x36
#define w_Iregion    0x37
/****************************************/
#define ID 0x7122A0
#define r_Pa 0x01   //A���й�����
#define r_Pb 0x02   //B���й�����
#define r_Pc 0x03   //C���й�����
#define r_Pt 0x04   //�����й�����

#define  r_Qa 0x05
#define  r_Qb 0x06
#define  r_Qc 0x07
#define  r_Qt 0x08
#define r_Sa 0x09   //A�����ڹ���
#define r_Sb 0x0A   //B�����ڹ���
#define r_Sc 0x0B   //C�����ڹ���
#define r_St 0x0C   //����ʵ�ڹ���

#define r_URmsa 0x0D    //A���ѹ��Чֵ
#define r_URmsb 0x0E    //B���ѹ��Чֵ
#define r_URmsc 0x0F    //C���ѹ��Чֵ

#define r_IRmsa 0x10    //A�������Чֵ
#define r_IRmsb 0x11    //B�������Чֵ
#define r_IRmsc 0x12    //C�������Чֵ
#define r_IRmst 0x13    //ABC�����ʸ���͵���Чֵ

#define r_Pfa 0x14  //A�๦������
#define r_Pfb 0x15  //B�๦������
#define r_Pfc 0x16  //C�๦������
#define r_Pft 0x17  //���๦������

#define r_Pga 0x18  //A��������ѹ�н�
#define r_Pgb 0x19  //B��������ѹ�н�
#define r_Pgc 0x1A  //C��������ѹ�н�
#define r_Pgt 0x1B  //������ǣ�����๦��������Ӧ

#define r_Freq 0x1C //��Ƶ��

#define r_Epa 0x1E  //A���й�����
#define r_Epb 0x1F  //B���й�����
#define r_Epc 0x20  //C���й�����
#define r_Eqt 0x25  //�����޹�����(�����ֲ����)
#define r_Ept 0x21  //�����й�����

#define r_RSPIDData 0x28    //��һ��spi����������

#define r_URmst 0x2B    //ABC�����ѹʸ���͵���Чֵ

#define r_SFlag 0x2C    //��Ŷ��ࡢ����SIG�ȱ�־״̬

#define r_WSPIData1 0x2D    //��һ��spiд�������
#define r_WSPIData2 0x2E    //ͬ��

#define r_EFlag 0x30    //���ܼĴ����Ĺ���״̬

#define r_Epa2 0x31 //A���й����ܣ��������
#define r_Epb2 0x32 //B���й����ܣ���������
#define r_Epc2 0x33 //C���й����ܣ���������
#define r_Ept2 0x34 //�����й����ܣ���������

#define r_PFlag 0x3D    //�й����ʷ�������Ϊ0������Ϊ1
#define r_ChkSum1 0x043D03  //У������У��Ĵ��������������£�
//#define r_ChkSum1 0x16BD03    //��������У��Ĵ���(����������)
/*******************�����ó���******************************************/
#define EC 3200
#define I  5
#define U  220
#define P  1100
#define P_P 549
#define t13 8192
#define t15 32768
#define t16 65536
#define t20 1048576
#define t23 8388608 
#define t24 16777216
#define Na 1.2
#define Nb 1.2
#define Nc 1.2
#define hf 7
#define K  0.138
/************************************************************/
void delay_us(int us);
int Read7022(unsigned char COM);
void write7022(unsigned char Com,int Data);
void SPI_IO_Ini(void);
void Correction7022(void);  
void Read_reg(void);
void For_Blance(void);
void Proofread(void);
int Detection_of_phase_squence(void);
#endif
