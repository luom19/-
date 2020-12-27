/*
 *本文件是音乐播放器主单片机的核心程序，其中功能库和数据表头文件必须引用。
 *如果增删乐谱，需要在本文件的第68行额外逻辑或一个ScorekFreq[PlusScoreFlag]==0
 */
#include<msp430.h>
#include<PianoDatasheet.h>//自制头文件，各个主要功能函数都写在其中
#include<PianoFunctionLib.h>//自制头文件，是主单片机的数据表，里面定义了大量常数，并可以进行自定义的数据增删

//全局变量：（关于各个宏的定义在PianoDatasheet.h中）
//钢琴模式下用于选择按键对应的八度，默认为中心八度
unsigned int FreqChoice=Middle;
//用于选择矩阵键盘按键值的全局变量，0~15代表K1~K16，16表示默认悬空值
unsigned int Key=KeyDefault;
//表示系统的总工作模式，默认模式为钢琴，Piano表示钢琴，MusicPlay表示音乐播放器
unsigned int Mode=Piano;
//音乐播放器模式下选择乐谱序号的变量
int Score=Score1;
//音乐播放器模式下用于选择播放列表顺序的变量，Cycle为单曲循环，List为列表循环
unsigned int PlayMode=Cycle;
//音乐播放器模式下用于表示是否播放的变量，Start表示播放，Pause表示暂停
unsigned int PlayFlag=Start;
//音乐播放函数的返回值，用于判断是否是放完了一首音乐才退出的函数
unsigned int PlusScoreFlag=0;

int main(void)
{
    //关闭看门狗.
    CloseWatchDog();

    //相关寄存器初始化：
    //端口1基本设置
    Port1set();
    //端口1中断设置
    Port1InterruptSet();
    //端口2基本设置
    Port2set();
    //端口2PWM波形设置
    Port2PWMset();
    //端口2中断设置
    Port2InterruptSet();

    //总中断允许
    _EINT();

    //主循环
    while(1)
    {

       if(Mode==Piano)//此时为电子琴模式
       {
           if(Key!=KeyDefault)
           {
               FreqChoice=DoAfterChoose(FreqChoice,Key);//表示选择八度，并通过中断选择按键值
               if(Key==K16) Mode++;//如果按下K16，则系统工作模式切换
               Key=KeyDefault;
           }
       }
       else if(Mode==MusicPlay)//此时为音频播放器模式，Mode==MusicPlay
       {
           PlusScoreFlag=PlayMusic(&Score,&PlayFlag,&Key,&Mode,PlusScoreFlag);//音乐播放函数，播放编号为Score的乐谱并随时监测状态全局变量参量Score、Key、PlayFlag和Mode的变化，来改变状态
           if(Key==K16)//如果按下了矩阵键盘的K16按键就会切换模式，从音乐播放模式中退出
           {
               Key=KeyDefault;//置为默认悬空值
               Mode--;
           }
           else//此时表明是正常结束播放一首乐曲或切换了上下首曲目
           {
               if((Score1Freq[PlusScoreFlag]==0)||(Score2Freq[PlusScoreFlag]==0)||(Score3Freq[PlusScoreFlag]==0)||(Score4Freq[PlusScoreFlag]==0))//表明此时是正常结束播放了一首乐曲
               {
                   switch(PlayMode)
                   {
                   case Cycle:break;//如果是单曲循环，直接重播
                   case List:Score++;if(Score>MaxScore) Score=Score1;break;//如果是列表循环则播放下一首
                   }
               }
               PlusScoreFlag=0;//清除之前的现场
               DelayBetweenScore();
           }
       }
    }
}

//P1端口的中断
#pragma  vector=PORT1_VECTOR
__interrupt  void port1_ISR( )
{
    if(P1IN !=LowDefaultFlag)//表明此时按了一个按键
    {
        Keydelay();//防抖
        if(P1IN != LowDefaultFlag)
        {
            Key=ChooseKey();//选择按键，用二进制编码0b0000~0b1111表示K1~K16
        }
    }
    P1IFG &= 0;//清除中断标志位
}

//P2端口的中断
#pragma  vector=PORT2_VECTOR
__interrupt  void port2_ISR( )
{
    Keydelay();//防抖
    if((P2IFG&BIT0)!=0)//如果是P2.0上的中断，则K1按下，切换暂停或播放状态
    {
        PlayFlag++;
        if (PlayFlag>Pause)
        {
            PlayFlag=Start;
        }
    }
    else if((P2IFG&BIT2)!=0)//如果是P2.2上的中断，则K2按下，则改变播放模式
    {
        PlayMode++;
        if(PlayMode>List)
        {
            PlayMode=Cycle;
        }
    }
    else if((P2IFG&BIT3)!=0)//如果是P2.3上的中断，则K3按下,则下一首
    {
        Score++;
        if(Score>MaxScore)
        {
            Score=Score1;
        }
    }
     else  if((P2IFG&BIT5)!=0)//如果是P2.5上的中断，则K4按下，则上一首
     {
         Score--;
         if(Score<Score1)
         {
             Score=MaxScore;
         }
     }
    P2IFG &= 0;//清除中断标志位
}




