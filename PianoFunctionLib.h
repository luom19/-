/*
 * 本头文件是音乐播放器主单片机的功能库，不可删除。
 * 如果增加乐谱，需要按照下面的格式修改PlayMusic函数。其格式为：（假设增加的是第k份乐谱）
 * else if(*Score==Scorek)
    {
        //主循环，用于播放每个音
        for(i=PlusScoreFlag;ScorekFreq[i]!=0;i++)
            {
                TA1CCR0=ScorekFreq[i];
                TA1CCR1=empty;
                temp=ScorekTimes[i];
                //最大循环次数，注意还要考虑到速度的变化
                MaxCycleTimek=(long unsigned int)((double)temp*((double)60/(double)tempo[*Score]));
                //播放其中的第i+1个音
                for(j=0;j<MaxCycleTimek;j++)//从上次开始播放的现场开始播放
                {
                     while(*PlayFlag==Pause)//如果暂停了,则通过反复重置端口2防止发出声音
                     {
                         Port2Reset();
                         if(*Key==K16)//如果此时按下切换模式，则把暂停状态撤销
                         {
                             *PlayFlag=Start;
                             break;
                         }
                     }
                     Port2StartBuzz();//恢复端口2
                     if((*Key==K16)||(*Score!=Scorek)) break;//如果切换模式或者切换了播放的乐谱序号退出循环
                };
                Port2Reset();//恢复P2状态
                if((*Key==K16)||(*Score!=Scorek)) break;//如果切换模式或者切换了播放的乐谱序号退出循环
                DelayBetweenNote();//乐曲间延迟，衔接
            };
    }
 *另外，需要额外定义一个PlayMusic函数中的变量，并命名为MaxCycleTimek;
 */
#ifndef PIANOFUNCTIONLIB_H_
#define PIANOFUNCTIONLIB_H_

//软件防抖
void Keydelay()
{
    unsigned int i;
    for (i=1000;i>0;i--);
}

//给按键发音用的短延迟
void Shortdelay()
{
    unsigned int i;
    for(i=0x0100;i>0;i--);
}

//音符之间的短暂延迟
void DelayBetweenNote()
{
    unsigned int i;
    for(i=0x00F0;i>0;i--);
}

//乐曲之间的较长延迟
void DelayBetweenScore()
{
    unsigned int i;
    for(i=0xF000;i>0;i--);
}

//关闭看门狗
void CloseWatchDog()
{
    //关闭看门狗
    WDTCTL = WDTPW + WDTHOLD;
}

//设定整个P1端口用来连接矩阵键盘，用于控制钢琴的发音
void Port1set()
{
    //设定P1为基本输入输出功能
    P1SEL&=~(HighDefaultFlag+LowDefaultFlag);
    P1SEL2&=~(HighDefaultFlag+LowDefaultFlag);
    //设定P1.0~P1.3为输出功能
    P1DIR|=LowDefaultFlag;
    //设定P1.4~P1.7为输入功能
    P1DIR&=~HighDefaultFlag;
    //输入端口初始化为高电平
    P1OUT|=LowDefaultFlag;

}

//P2的PWM寄存器设置
void Port2PWMset()
{
    //选择TA1计数时钟为ACLK，使用上电复位设置，即32768Hz
    TA1CTL |=TASSEL0;
    //设置TA1比较器1的PWM输出为模式2： 计数到CCR1值翻转，到CCR0值置0
    TA1CCTL1|=OUTMOD1;
    //设置增计数方式，使计数器从0开始计数，计数到TA1CCR0后又从0计数。
    TA1CTL |=TACLR+MC0;
}

//端口2初始化
void Port2Reset()
{
    //此时P2.1不输出PMW波形
    P2SEL2|=PWMPort;
    //置为低电平默认值
    P2OUT&=~PWMPort;
}

//设定P2用PWM波形控制蜂鸣器
void Port2set()
{
    //置P2.1为定时器TA1的PWM输出引脚
    P2SEL |=PWMPort;
    P2DIR |=PWMPort;
    //设置P2.4用于连接第二块单片机
    P2SEL&=~LinkPort;
    P2SEL2&=~LinkPort;
    P2DIR|=LinkPort;
    P2OUT|=LinkPort;
    Port2Reset();
}

//设定P2输出控制蜂鸣器的信号
void Port2StartBuzz()
{
    //P2.1和P2.4为比较器1的PWM输出引脚
    P2SEL2 &=~PWMPort;
}

//设定P1.4~P1.7有关的中断功能
void Port1InterruptSet()
{
    //P1中断相关设置
        P1OUT &=~HighDefaultFlag;
        P1REN |=HighDefaultFlag;
        P1IE |= LowDefaultFlag+HighDefaultFlag;
        P1IES &=~(LowDefaultFlag+HighDefaultFlag);
        P1IFG &=~(LowDefaultFlag+HighDefaultFlag);
}

void Port2InterruptSet()
{
    //P2中断相关设置
        P2SEL&=~InterruptPort2;
        P2SEL2&=~InterruptPort2;
        P2DIR&=~InterruptPort2;
        P2OUT |=InterruptPort2;
        P2REN |=InterruptPort2;
        P2IE |= InterruptPort2;
        P2IES &=~InterruptPort2;
        P2IFG &=~InterruptPort2;
}

//K16按下时在P2.4上输出一个下降-上升信号用于中断（对方下降沿触发）
void LinkPortInterruptFlag()
{
    P2OUT&=~LinkPort;
    Shortdelay();
    P2OUT|=LinkPort;
}

//选择按键所在的列
unsigned int SwitchKeyLine()
{
    //选择按键列的变量，且默认为悬空值
    unsigned int key=16;

    P1OUT=0;
    //设置P1.4~P1.7输出
    P1DIR|=HighDefaultFlag;
    //设置P1.0~P1.3输入
    P1DIR&=~LowDefaultFlag;
    //设置P1.4~P1.7高电平
    P1OUT|=HighDefaultFlag;

    //当对应行按键按下时，对应的P1IN会产生高电平，否则为低电平，选择这个高电平
    switch(P1IN)
    {
        case L1:key=Line1;break;
        case L2:key=Line2;break;
        case L3:key=Line3;break;
        case L4:key=Line4;break;
    }
    return key;
}

//选择按键所在的行
unsigned int SwitchKeyRow(unsigned int key)
{
    //置P1为低电平默认值
    P1OUT=0;
    //设置P1.0~P1.3输出
    P1DIR|=LowDefaultFlag;
    //设置P1.4~P1.7输入
    P1DIR&=~HighDefaultFlag;
    //设置P1.0~P1.3高电平
    P1OUT|=LowDefaultFlag;

    //扫描行对应值
    switch(P1IN)
    {
        case R1:key+=Row1;break;
        case R2:key+=Row2;break;
        case R3:key+=Row3;break;
        case R4:key+=Row4;break;
    }

    return key;
}

//选择按键，并返回现在对应的音高频段
unsigned int ChooseKey()
{
    //选择按键的变量，默认值悬空
    unsigned int key=KeyDefault;
    //选择按键列
    key=SwitchKeyLine();
    //选择按键行
    key=SwitchKeyRow(key);
    //如果是K16则给另一块单片机一个触发信号让它能够变换数码管内容
    if(key==K16) LinkPortInterruptFlag();

    return key;
}

//根据扫描按键的值返回当前选择的八度的函数
unsigned int DoAfterChoose(unsigned int Freqchoice,unsigned int key)
{
    unsigned int FreqChoice=Freqchoice;
    //恢复P1端口现场
    P1DIR|=LowDefaultFlag;
    //设定P1.4~P1.7为输入功能
    P1DIR&=~HighDefaultFlag;
    //输入端口初始化为高电平
    P1OUT|=LowDefaultFlag;

    //这些按键是用于选择频率范围的
    if(key>=K13)
    {
        switch(key)
        {
        //K16用于切换模式，在这里对应什么都不需要做
        case K16:break;
        //K13~K15用于选择频率：
        case K13:FreqChoice=0;break;//K13
        case K14:FreqChoice=1;break;//K14
        case K15:FreqChoice=2;break;//K15
        default:break;
        }
    }
    //其余按键是演奏用的
    else
    {
        //启动蜂鸣器
        Port2StartBuzz();
        TA1CCR0=Freq[FreqChoice][key];
        TA1CCR1=empty;
        while(P1IN!=LowDefaultFlag)
        {
            Shortdelay();
        }
        //恢复P2端口
        Port2Reset();
    }

    return FreqChoice;

}

//音乐播放函数
unsigned int PlayMusic(int *Score,unsigned int *PlayFlag,unsigned int *Key,unsigned int *Mode,unsigned int PlusScoreFlag)
{
    unsigned int i;
    long unsigned int j;
    long unsigned int temp;
    //每个音的循环次数
    long unsigned int MaxCycleTime1,MaxCycleTime2,MaxCycleTime3,MaxCycleTime4;
    //防止从钢琴模式刚刚切换过来的声音
    TA1CCR0=0;
    TA1CCR1=0;
    Port2StartBuzz();

    //如果是乐谱1
    if(*Score==Score1)
    {
        //主循环，用于播放每个音
        for(i=PlusScoreFlag;Score1Freq[i]!=0;i++)
            {
                TA1CCR0=Score1Freq[i];
                TA1CCR1=empty;
                temp=Score1Times[i];
                //最大循环次数，注意还要考虑到速度的变化
                MaxCycleTime1=(long unsigned int)((double)temp*((double)60/(double)tempo[*Score]));
                //播放其中的第i+1个音
                for(j=0;j<MaxCycleTime1;j++)//从上次开始播放的现场开始播放
                {
                     while(*PlayFlag==Pause)//如果暂停了,则通过反复重置端口2防止发出声音
                     {
                         Port2Reset();
                         if(*Key==K16)//如果此时按下切换模式，则把暂停状态撤销
                         {
                             *PlayFlag=Start;
                             break;
                         }
                     }
                     Port2StartBuzz();//恢复端口2
                     if((*Key==K16)||(*Score!=Score1)) break;//如果切换模式或者切换了播放的乐谱序号退出循环
                };
                Port2Reset();//恢复P2状态
                if((*Key==K16)||(*Score!=Score1)) break;//如果切换模式或者切换了播放的乐谱序号退出循环
                DelayBetweenNote();//乐曲间延迟，衔接
            };
    }
    else if(*Score==Score2)//如果是乐谱2，注释同上
    {
        for(i=PlusScoreFlag;Score2Freq[i]!=0;i++)
            {
                TA1CCR0=Score2Freq[i];
                TA1CCR1=empty;
                temp=Score2Times[i];
                MaxCycleTime2=(long unsigned int)((double)temp*((double)60/(double)tempo[*Score]));
                for(j=0;j<MaxCycleTime2;j++)
                {
                     while(*PlayFlag==Pause)
                     {
                         Port2Reset();
                         if(*Key==K16)
                         {
                             *PlayFlag=Start;
                             break;
                         }
                     }
                     Port2StartBuzz();
                     if((*Key==K16)||(*Score!=Score2)) break;
                };
                Port2Reset();
                if((*Key==K16)||(*Score!=Score2)) break;
                DelayBetweenNote();
            };
    }
    else if(*Score==Score3)//如果是乐谱3，注释同上
    {
        for(i=PlusScoreFlag;Score3Freq[i]!=0;i++)
            {
                TA1CCR0=Score3Freq[i];
                TA1CCR1=empty;
                temp=Score3Times[i];
                MaxCycleTime3=(long unsigned int)((double)temp*((double)60/(double)tempo[*Score]));
                for(j=0;j<MaxCycleTime3;j++)
                {
                     while(*PlayFlag==Pause)
                     {
                         Port2Reset();
                         if(*Key==K16)
                         {
                             *PlayFlag=Start;
                             break;
                         }
                     }
                     Port2StartBuzz();
                     if((*Key==K16)||(*Score!=Score3)) break;
                };
                Port2Reset();
                if((*Key==K16)||(*Score!=Score3)) break;
                DelayBetweenNote();
            };
    }
    else if(*Score==Score4)//如果是乐谱4，注释同上
    {
        for(i=PlusScoreFlag;Score4Freq[i]!=0;i++)
            {
                TA1CCR0=Score4Freq[i];
                TA1CCR1=empty;
                temp=Score4Times[i];
                MaxCycleTime4=(long unsigned int)((double)temp*((double)60/(double)tempo[*Score]));
                for(j=0;j<MaxCycleTime4;j++)
                {
                    while(*PlayFlag==Pause)
                     {
                         Port2Reset();
                         if(*Key==K16)
                         {
                             *PlayFlag=Start;
                             break;
                         }
                     }
                     Port2StartBuzz();
                     if((*Key==K16)||(*Score!=Score4)) break;
                };
                Port2Reset();
                if((*Key==K16)||(*Score!=Score4)) break;
                DelayBetweenNote();
            };
    }
    /*else if(*Score==Score5)*/
    //可以用同样的方式在硬件条件允许的情况下继续往下扩展其他的乐谱

    return i;
}

#endif /* PIANOFUNCTIONLIB_H_ */
