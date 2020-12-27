/*
 * 本头文件是音乐播放器主单片机的数据表，如果增加或修改乐谱记得除了要把乐谱按照对应的格式写好之外，
 * 还要修改宏定义ScoreNumber和MaxScore，以及在数组tempo中增加新乐谱的bpm速度
 */
#ifndef PIANODATASHEET_H_
#define PIANODATASHEET_H_

//默认的P1端口，用于按键选择
#define HighDefaultFlag 0xf0//BIT4+BIT5+BIT6+BIT7
#define LowDefaultFlag 0x0f//BIT0+BIT1+BIT2+BIT3
#define InterruptPort2 0x2d//BIT0+BIT2+BIT3+BIT5
#define PWMPort BIT1//TA1的输出引脚
#define LinkPort BIT4//两块单片机连接的端口

//用于矩阵键盘的行列选择，是具体的行列号
#define Line1 0//0b0000
#define Line2 1//0b0001
#define Line3 2//0b0010
#define Line4 3//0b0011
#define Row1 0//0b0000
#define Row2 4//0b0100
#define Row3 8//0b1000
#define Row4 12//0b1100

//用于矩阵键盘的行列选择，是对应行列号对应的端口
#define L1 0xf1//BIT4+BIT5+BIT6+BIT7+BIT0
#define L2 0xf2//BIT4+BIT5+BIT6+BIT7+BIT1
#define L3 0xf4//BIT4+BIT5+BIT6+BIT7+BIT2
#define L4 0xf8//BIT4+BIT5+BIT6+BIT7+BIT3
#define R1 0x1f//BIT0+BIT1+BIT2+BIT3+BIT4
#define R2 0x2f//BIT0+BIT1+BIT2+BIT3+BIT5
#define R3 0x4f//BIT0+BIT1+BIT2+BIT3+BIT6
#define R4 0x8f//BIT0+BIT1+BIT2+BIT3+BIT7
#define K16 0b1111//K16
#define K15 0b1110//K15
#define K14 0b1101//K14
#define K13 0b1100//K13
#define KeyDefault 16//默认的悬空键值

//用于音乐播放器，60bpm下对应音长的循环次数
#define Half 8192
#define One 16384
#define Two 32768
#define Dot 24576
#define Four 65535
#define Quarter 4096
#define TQuarter 12288
#define NQuarter 36864

//整个系统的一些状态参数
#define Cycle 1//音乐播放器：单曲循环
#define List 2//音乐播放器：列表循环
#define Piano 1//全局：钢琴
#define MusicPlay 2//全局：音乐播放器
#define Start 1//音乐播放器：播放
#define Pause 2//音乐播放器：暂停

//与频段有关的值定义
#define Low 0//低音
#define Middle 1//中音
#define High 2//高音


//与音名有关的CCR0值定义
#define LDo 248
#define LUDo 234
#define LRe 221
#define LURe 208
#define LMi 197
#define LFa 186
#define LUFa 175
#define LSo 165
#define LUSo 156
#define LLa 147
#define LULa 138
#define LTi 131
#define Do 124
#define UDo 117
#define Re 110
#define URe 104
#define Mi 98
#define Fa 92
#define UFa 87
#define So 82
#define USo 78
#define La 73
#define ULa 69
#define Ti 65
#define HDo 61
#define HUDo 58
#define HRe 55
#define HURe 51
#define HMi 48
#define HFa 46
#define HUFa 43
#define HSo 41
#define HUSo 38
#define HLa 36
#define HULa 34
#define HTi 32


//一些跟乐谱有关的参数
#define ScoreNumber 4//存的乐谱总量
#define MaxScore Score4//最大乐谱编号
//乐谱编号
#define Score1 0//乐谱1：生日歌
#define Score2 1//乐谱2：虫儿飞
#define Score3 2//乐谱3：两只老虎
#define Score4 3//乐谱4：九州缥缈录·乱世歌行

//每个音对应的TA1CCR0值，横坐标为音名，纵坐标为八度，总体以A=442Hz为中间八度6（C调）的十二平均律半音序列
const unsigned int Freq[3][12]=
{
LDo,LUDo,LRe,LURe,LMi,LFa,LUFa,LSo,LUSo,LLa,LULa,LTi,
Do,UDo,Re,URe,Mi,Fa,UFa,So,USo,La,ULa,Ti,
HDo,HUDo,HRe,HURe,HMi,HFa,HUFa,HSo,HUSo,HLa,HULa,HTi
};
const unsigned int empty=1;//占空比最低为1-1/32=96.8%>95%，声音质量有保证

//乐谱相关
//每一首乐谱都分为频率和对应的持续循环次数，这是因为为了保证循环次数不会超过unsigned int，区分了long unsigned int
//末尾0用于判断乐谱结束
//生日歌乐谱
const unsigned int Score1Freq[]=
{
 Do,Do,Re,Do,Fa,Mi,
 Do,Do,Re,Do,So,Fa,
 Do,Do,HDo,La,Fa,Mi,Re,
 ULa,ULa,La,Fa,So,Fa,0
};
const long unsigned int Score1Times[]=
{Half,Half,One,One,One,Two,
 Half,Half,One,One,One,Two,
 Half,Half,One,One,One,One,One,
 Half,Half,One,One,One,Two,0
};

//虫儿飞乐谱
const unsigned int Score2Freq[]=
{
 La,La,La,Ti,HDo,La,So,
 Fa,Fa,Fa,So,La,La,Mi,Mi,
 Re,La,So,Re,La,So,
 Re,La,So,Fa,Fa,0};
const long unsigned int Score2Times[]=
{One,Half,Half,One,One,Two,Two,
 One,Half,Half,One,One,Dot,Half,Two,
 One,One,Two,One,One,Two,
 One,One,Dot,Half,Four,0
};

//两只老虎乐谱
const unsigned int Score3Freq[]=
{Do,Re,Mi,Do,Do,Re,Mi,Do,
 Mi,Fa,So,Mi,Fa,So,
 So,La,So,Fa,Mi,Do,
 So,La,So,Fa,Mi,Do,
 Do,LSo,Do,Do,LSo,Do,0};
const long unsigned int Score3Times[]=
{One,One,One,One,One,One,One,One,
 One,One,Two,One,One,Two,
 TQuarter,Quarter,TQuarter,Quarter,One,One,
 TQuarter,Quarter,TQuarter,Quarter,One,One,
 One,One,Two,One,One,Two,0};

//九州缥缈录乱世歌行乐谱
const unsigned int Score4Freq[]=
{
 La,So,Mi,La,So,Re,La,So,Mi,Re,Mi,So,Mi,
 La,So,Mi,La,Ti,HDo,HDo,Ti,La,So,La,
 La,So,Mi,La,So,Re,La,So,Mi,Re,Mi,So,Mi,
 La,Ti,HDo,Mi,HDo,Ti,So,HDo,Ti,La,So,La,

 HDo,Ti,La,So,Mi,So,La,So,Mi,So,Mi,
 Do,Re,Do,Re,Re,Do,Mi,Do,Re,So,So,
 Mi,So,HDo,Ti,La,So,Mi,So,La,So,La,HRe,HDo,
 La,Ti,HDo,La,HMi,HRe,Ti,So,Mi,La,So,La,

 La,Ti,So,Mi,Re,So,Mi,
 Re,Mi,Re,Mi,Re,Do,Re,Do,Re,So,So,
 La,Ti,So,Mi,Re,Do,Re,So,Mi,
 HDo,Ti,La,So,Mi,So,La,La,

 La,So,Mi,La,So,Re,La,So,Mi,Re,Mi,So,Mi,
 La,So,Mi,La,Ti,HDo,HDo,Ti,La,So,La,
 La,So,Mi,La,So,Re,La,So,Mi,Re,Mi,So,Mi,
 La,Ti,HDo,Mi,HDo,Ti,So,HDo,Ti,La,So,La,

 La,So,Mi,La,So,Re,La,So,Mi,Re,Mi,So,Mi,
 La,So,Mi,La,Ti,HDo,HDo,Ti,La,So,La,
 La,So,Mi,La,So,Re,La,So,Mi,Re,Mi,So,Mi,
 La,Ti,HDo,Mi,HDo,Ti,So,HDo,Ti,La,So,La,

 HDo,Ti,La,So,Mi,So,La,So,Mi,So,Mi,
 Do,Re,Do,Re,Re,Do,Mi,Do,Re,So,So,
 Mi,So,HDo,Ti,La,So,Mi,So,La,So,La,HRe,HDo,
 La,Ti,HDo,La,HMi,HRe,Ti,So,Mi,La,So,La,0
};
const unsigned int Score4Times[]=
{
 Half,Half,One,Half,Half,One,Half,Half,Half,Half,Half,Half,One,
 Half,Half,One,Half,Half,Dot,Half,Half,Half,Half,Dot,
 Half,Half,One,Half,Half,One,Half,Half,Half,Half,Half,Half,One,
 Half,Half,One,Half,Half,Dot,Half,One,Half,Quarter,Quarter,Two,

 One,Half,Half,One,Half,Half,Half,Half,Half,Half,Dot,
 Half,One,Half,Half,One,One,Half,Half,Half,Half,One,
 Half,Half,One,Half,Half,One,Half,Half,Half,Half,Half,Half,One,
 Half,Half,One,Half,Half,Dot,Half,Half,Half,Half,Quarter,NQuarter,

 Dot,Half,One,One,One,One,Dot,
 Half,One,Half,Half,Half,Dot,Half,Half,Half,Half,Two,
 Dot,Half,One,One,Half,Half,Half,Half,Two,
 One,Half,Half,Half,Half,Half,Half,Four,

 Half,Half,One,Half,Half,One,Half,Half,Half,Half,Half,Half,One,
 Half,Half,One,Half,Half,Dot,Half,Half,Half,Half,Dot,
 Half,Half,One,Half,Half,One,Half,Half,Half,Half,Half,Half,One,
 Half,Half,One,Half,Half,Dot,Half,One,Half,Quarter,Quarter,Two,

 Half,Half,One,Half,Half,One,Half,Half,Half,Half,Half,Half,One,
 Half,Half,One,Half,Half,Dot,Half,Half,Half,Half,Dot,
 Half,Half,One,Half,Half,One,Half,Half,Half,Half,Half,Half,One,
 Half,Half,One,Half,Half,Dot,Half,One,Half,Quarter,Quarter,Two,

 One,Half,Half,One,Half,Half,Half,Half,Half,Half,Dot,
 Half,One,Half,Half,One,One,Half,Half,Half,Half,One,
 Half,Half,One,Half,Half,One,Half,Half,Half,Half,Half,Half,One,
 Half,Half,One,Half,Half,Dot,Half,Half,Half,Half,Quarter,Four,0
};


//还可以用同样的方法继续添加其他乐谱

//乐谱的速度，按bpm计
unsigned int tempo[ScoreNumber]={60,60,80,75};

#endif /* PIANODATASHEET_H_ */
