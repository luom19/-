/*
 *本文件是数码管驱动单片机的核心程序，其中功能库和数据表头文件必须引用。
 *当前硬件条件下不支持扩展。
 */
#include<msp430.h>
#include<ShowDatasheet.h>
#include<ShowFunctionLib.h>

//存储显示模式的变量
unsigned int ModeFlag=Pano;//播放模式，默认为系统的默认状态（钢琴）
unsigned int ShowFlag=Show;//是否显示，默认为显示
unsigned int PlayModeBuffer=Cycl;//缓存播放模式

int main(void)
{
    CloseWatchDog();//关闭看门狗

    //相关寄存器设置：
    //P1.0~P1.3用于控制LG3641BH的S1~S4
    Port1SetLG3641BH();
    //P1.4~P1.6中断基本设置
    Port1InterruptSet();
    //P2.0~P2.2用于控制74HC595的DS，SHCP和STCP
    Port2Set74HC595();

    //总中断允许
    _EINT();
    P1IFG=0;

    //默认状态为钢琴、且显示
     SetLEDtoPANODot(&ShowFlag,&ModeFlag);

    while(1)
    {
        if(ShowFlag==Pause)//如果此时要求不显示
        {
            SetLEDClear();//清空数码管
        }
        else if(ShowFlag==Show)//如果此时要求显示
        {
            switch(ModeFlag)
            {
            case Pano:SetLEDtoPANODot(&ShowFlag,&ModeFlag);break;//显示Pano.
            case List:SetLEDtoLISTDot(&ShowFlag,&ModeFlag);break;//显示List.
            case Cycl:SetLEDtoCYCLDot(&ShowFlag,&ModeFlag);break;//显示Cycl.
            }
        }
    }
}

//P1端口的中断
#pragma  vector=PORT1_VECTOR
__interrupt  void port1_ISR( )
{
    Keydelay();
    if((P1IFG&Sign)!=0)//表示系统模式变化
    {
        if((ModeFlag==Cycl)||(ModeFlag==List)) ModeFlag=Pano;//如果在音乐播放器模式，则调整为钢琴模式
        else if(ModeFlag==Pano) ModeFlag=PlayModeBuffer;//如果在钢琴模式，则调整为音乐播放器之前存储的状态
    }
    else if((P1IFG&PlayModeChange)!=0)//表示音乐播放器模式的变化
    {
        if((ModeFlag==Cycl)||(ModeFlag==List))//检测处在音乐播放器模式才执行，否则不执行
        {
            if(ModeFlag==Cycl) ModeFlag=List;
            else if(ModeFlag==List) ModeFlag=Cycl;
            PlayModeBuffer=ModeFlag;//把状态传给缓存
        }
    }
    else if((P1IFG&ShowModeChange)!=0)//表示显示模式的变化
    {
        ShowFlag++;
        if(ShowFlag>Pause) ShowFlag=Show;
    }
    P1IFG &= 0;//清除中断标志位
}

