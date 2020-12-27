/*
 *本头文件是数码管驱动单片机的功能库，不可删除。
 *本部分利用到的相关硬件功能如下：

 *74HC595功能：
 *DS：串行输入引脚（先进高位后进低位）
 *STCP：串行转并行的输入引脚，在上升沿移位寄存器中的数据送入存储；
 *SHCP：接受数据，在上升沿把移位寄存器的数据后移一位并把新的数据送进移位寄存器；
 *Qn：并行输出端口；

 *LG3641BH功能：
 *共阳极数码管，Sa~Sh低电平时对应管脚亮，高电平时灭；
 *在S1~S4的上升沿，数据被读入对应的位；（但是必须注意保持高电平，因此最好的方法是采用扫描法）
 *数码管各个管脚的约定名称：（四位从右到左分别由S1~S4控制）
     A↓
     ——
 F→ |  |←B
     —— ←G
 E→ |  | ←C .←H
     ——
     D↑
*特别地，本部分功能可以移植到其他平台或至少是其他需要驱动74HC595和共阳极数码管的地方。
*但是移植时必须注意，如果使用的是共阴极数码管，所有显示字母或数字的编码都必须取反。
*/
#ifndef SHOWFUNCTIONLIB_H_
#define SHOWFUNCTIONLIB_H_

void CloseWatchDog()
{
    //关闭看门狗
    WDTCTL = WDTPW + WDTHOLD;
}

//延时
void delay()
{
    unsigned int i;
    for (i=0;i<0x0100;i++);
}

//软件防抖
void Keydelay()
{
    unsigned int i;
    for (i=1000;i>0;i--);
}

//用于数码管扫描显示的延迟
void ShowDelay()
{
    unsigned int i;
    for(i=10;i>0;i--);
}

//设置P1使得其可以控制LG3641BH
void Port1SetLG3641BH()
{
    P1SEL&=~(S1+S2+S3+S4);
    P1SEL2&=~(S1+S2+S3+S4);
    P1DIR|=(S1+S2+S3+S4);
    P1OUT&=~(S1+S2+S3+S4);
}

//设置P2使得其可以控制74HC595
void Port2Set74HC595()
{
    P2SEL&=~(DS+STCP+SHCP);
    P2SEL2&=~(DS+STCP+SHCP);
    P2DIR|=(DS+STCP+SHCP);
    P2OUT&=~(DS+STCP+SHCP);
}

//设定P1.4~P1.7有关的中断功能
//P1.4和另一单片机的P2.0相连，用于监测模式变化的信号
//P1.5和扩展板的K2相连，在播放模式变化的时候显示变化
//P1.6和扩展板K6相连，由于控制数码管是否显示
void Port1InterruptSet()
{
    //P1中断相关设置
    P1SEL&=~(Sign+PlayModeChange+ShowModeChange);
    P1SEL2&=~(Sign+PlayModeChange+ShowModeChange);
    P1REN |=Sign+PlayModeChange+ShowModeChange;
    P1DIR&=~(Sign+PlayModeChange+ShowModeChange);
    P1OUT |=Sign+PlayModeChange+ShowModeChange;
    P1IE |= Sign+PlayModeChange+ShowModeChange;
    P1IES &=~(Sign+PlayModeChange+ShowModeChange);
    P1IFG &=0;
}

//把74HC595的一位置为1
void SetBit1()
{
    P2OUT|=DS;
    P2OUT|=SHCP;
    ShowDelay();
    P2OUT&=~(DS+SHCP);
    ShowDelay();
}

//把74HC595的一位置为0
void SetBit0()
{
    P2OUT&=~DS;
    P2OUT|=SHCP;
    ShowDelay();
    P2OUT&=~(DS+SHCP);
    ShowDelay();
}

//移位寄存器的数据送入存储
void DSgotoQn()
{
    P2OUT|=STCP;
    ShowDelay();
    P2OUT&=~STCP;
    ShowDelay();
}

//把74HC595的Qn值输入到数码管对应的PIN位中
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

//逐位扫描的方法驱动数码管显示对应的模式代号
//设置数码管显示List.
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

//设置数码管显示CYCL.
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

//设置数码管显示Pano.
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

//清除数码管显示
void SetLEDClear()
{
    P1OUT&=~(S1+S2+S3+S4);
}

#endif /* SHOWFUNCTIONLIB_H_ */
