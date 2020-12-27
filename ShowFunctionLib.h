/*
 *��ͷ�ļ��������������Ƭ���Ĺ��ܿ⣬����ɾ����
 *���������õ������Ӳ���������£�

 *74HC595���ܣ�
 *DS�������������ţ��Ƚ���λ�����λ��
 *STCP������ת���е��������ţ�����������λ�Ĵ����е���������洢��
 *SHCP���������ݣ��������ذ���λ�Ĵ��������ݺ���һλ�����µ������ͽ���λ�Ĵ�����
 *Qn����������˿ڣ�

 *LG3641BH���ܣ�
 *����������ܣ�Sa~Sh�͵�ƽʱ��Ӧ�ܽ������ߵ�ƽʱ��
 *��S1~S4�������أ����ݱ������Ӧ��λ�������Ǳ���ע�Ᵽ�ָߵ�ƽ�������õķ����ǲ���ɨ�跨��
 *����ܸ����ܽŵ�Լ�����ƣ�����λ���ҵ���ֱ���S1~S4���ƣ�
     A��
     ����
 F�� |  |��B
     ���� ��G
 E�� |  | ��C .��H
     ����
     D��
*�ر�أ������ֹ��ܿ�����ֲ������ƽ̨��������������Ҫ����74HC595�͹���������ܵĵط���
*������ֲʱ����ע�⣬���ʹ�õ��ǹ���������ܣ�������ʾ��ĸ�����ֵı��붼����ȡ����
*/
#ifndef SHOWFUNCTIONLIB_H_
#define SHOWFUNCTIONLIB_H_

void CloseWatchDog()
{
    //�رտ��Ź�
    WDTCTL = WDTPW + WDTHOLD;
}

//��ʱ
void delay()
{
    unsigned int i;
    for (i=0;i<0x0100;i++);
}

//�������
void Keydelay()
{
    unsigned int i;
    for (i=1000;i>0;i--);
}

//���������ɨ����ʾ���ӳ�
void ShowDelay()
{
    unsigned int i;
    for(i=10;i>0;i--);
}

//����P1ʹ������Կ���LG3641BH
void Port1SetLG3641BH()
{
    P1SEL&=~(S1+S2+S3+S4);
    P1SEL2&=~(S1+S2+S3+S4);
    P1DIR|=(S1+S2+S3+S4);
    P1OUT&=~(S1+S2+S3+S4);
}

//����P2ʹ������Կ���74HC595
void Port2Set74HC595()
{
    P2SEL&=~(DS+STCP+SHCP);
    P2SEL2&=~(DS+STCP+SHCP);
    P2DIR|=(DS+STCP+SHCP);
    P2OUT&=~(DS+STCP+SHCP);
}

//�趨P1.4~P1.7�йص��жϹ���
//P1.4����һ��Ƭ����P2.0���������ڼ��ģʽ�仯���ź�
//P1.5����չ���K2�������ڲ���ģʽ�仯��ʱ����ʾ�仯
//P1.6����չ��K6���������ڿ���������Ƿ���ʾ
void Port1InterruptSet()
{
    //P1�ж��������
    P1SEL&=~(Sign+PlayModeChange+ShowModeChange);
    P1SEL2&=~(Sign+PlayModeChange+ShowModeChange);
    P1REN |=Sign+PlayModeChange+ShowModeChange;
    P1DIR&=~(Sign+PlayModeChange+ShowModeChange);
    P1OUT |=Sign+PlayModeChange+ShowModeChange;
    P1IE |= Sign+PlayModeChange+ShowModeChange;
    P1IES &=~(Sign+PlayModeChange+ShowModeChange);
    P1IFG &=0;
}

//��74HC595��һλ��Ϊ1
void SetBit1()
{
    P2OUT|=DS;
    P2OUT|=SHCP;
    ShowDelay();
    P2OUT&=~(DS+SHCP);
    ShowDelay();
}

//��74HC595��һλ��Ϊ0
void SetBit0()
{
    P2OUT&=~DS;
    P2OUT|=SHCP;
    ShowDelay();
    P2OUT&=~(DS+SHCP);
    ShowDelay();
}

//��λ�Ĵ�������������洢
void DSgotoQn()
{
    P2OUT|=STCP;
    ShowDelay();
    P2OUT&=~STCP;
    ShowDelay();
}

//��74HC595��Qnֵ���뵽����ܶ�Ӧ��PINλ��
void SetLEDBIT(unsigned int PIN)
{
    P1OUT|=PIN;
    ShowDelay();
    P1OUT&=~PIN;
}

//C:11000110
void SetLEDSDtoC()
{
    SetBit1();
    SetBit1();
    SetBit0();
    SetBit0();
    SetBit0();
    SetBit1();
    SetBit1();
    SetBit0();
    DSgotoQn();
}

//Y:10010001
void SetLEDSDtoY()
{
    SetBit1();
    SetBit0();
    SetBit0();
    SetBit1();
    SetBit0();
    SetBit0();
    SetBit0();
    SetBit1();
    DSgotoQn();
}

//L.:01000111
void SetLEDSDtoLDot()
{
    SetBit0();
    SetBit1();
    SetBit0();
    SetBit0();
    SetBit0();
    SetBit1();
    SetBit1();
    SetBit1();
    DSgotoQn();
}

//L:11000111
void SetLEDSDtoL()
{
    SetBit1();
    SetBit1();
    SetBit0();
    SetBit0();
    SetBit0();
    SetBit1();
    SetBit1();
    SetBit1();
    DSgotoQn();
}

//I:11111011
void SetLEDSDtoI()
{
    SetBit1();
    SetBit1();
    SetBit1();
    SetBit1();
    SetBit1();
    SetBit0();
    SetBit1();
    SetBit1();
    DSgotoQn();
}

//S:10011011
void SetLEDSDtoS()
{
    SetBit1();
    SetBit0();
    SetBit0();
    SetBit1();
    SetBit1();
    SetBit0();
    SetBit1();
    SetBit1();
    DSgotoQn();
}

//T.:00000111
void SetLEDSDtoTDot()
{
    SetBit0();
    SetBit0();
    SetBit0();
    SetBit0();
    SetBit0();
    SetBit1();
    SetBit1();
    SetBit1();
    DSgotoQn();
}

//P:10001100
void SetLEDSDtoP()
{
    SetBit1();
    SetBit0();
    SetBit0();
    SetBit0();
    SetBit1();
    SetBit1();
    SetBit0();
    SetBit0();
    DSgotoQn();
}

//A:10001000
void SetLEDSDtoA()
{
    SetBit1();
    SetBit0();
    SetBit0();
    SetBit0();
    SetBit1();
    SetBit0();
    SetBit0();
    SetBit0();
    DSgotoQn();
}

//N:10101011
void SetLEDSDtoN()
{
    SetBit1();
    SetBit0();
    SetBit1();
    SetBit0();
    SetBit1();
    SetBit0();
    SetBit1();
    SetBit1();
    DSgotoQn();
}

//O.:00100011
void SetLEDSDtoODot()
{
    SetBit0();
    SetBit0();
    SetBit1();
    SetBit0();
    SetBit0();
    SetBit0();
    SetBit1();
    SetBit1();
    DSgotoQn();
}

//��λɨ��ķ��������������ʾ��Ӧ��ģʽ����
//�����������ʾList.
void SetLEDtoLISTDot(volatile unsigned int *ShowFlag,volatile unsigned int *ModeFlag)
{
    while((*ShowFlag==Show)&&(*ModeFlag==List))
    {
        SetLEDSDtoL();
        SetLEDBIT(S4);
        SetLEDSDtoI();
        SetLEDBIT(S3);
        SetLEDSDtoS();
        SetLEDBIT(S2);
        SetLEDSDtoTDot();
        SetLEDBIT(S1);
    }
}

//�����������ʾCYCL.
void SetLEDtoCYCLDot(volatile unsigned int *ShowFlag,volatile unsigned int *ModeFlag)
{
    while((*ShowFlag==Show)&&(*ModeFlag==Cycl))
    {
        SetLEDSDtoC();
        SetLEDBIT(S4);
        SetLEDSDtoY();
        SetLEDBIT(S3);
        SetLEDSDtoC();
        SetLEDBIT(S2);
        SetLEDSDtoLDot();
        SetLEDBIT(S1);
    }
}

//�����������ʾPano.
void SetLEDtoPANODot(volatile unsigned int *ShowFlag,volatile unsigned int *ModeFlag)
{
    while((*ShowFlag==Show)&&(*ModeFlag==Pano))
    {
        SetLEDSDtoP();
        SetLEDBIT(S4);
        SetLEDSDtoA();
        SetLEDBIT(S3);
        SetLEDSDtoN();
        SetLEDBIT(S2);
        SetLEDSDtoODot();
        SetLEDBIT(S1);
    }
}

//����������ʾ
void SetLEDClear()
{
    P1OUT&=~(S1+S2+S3+S4);
}

#endif /* SHOWFUNCTIONLIB_H_ */
