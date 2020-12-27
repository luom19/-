/*
 * ��ͷ�ļ������ֲ���������Ƭ�������ݱ�������ӻ��޸����׼ǵó���Ҫ�����װ��ն�Ӧ�ĸ�ʽд��֮�⣬
 * ��Ҫ�޸ĺ궨��ScoreNumber��MaxScore���Լ�������tempo�����������׵�bpm�ٶ�
 */
#ifndef PIANODATASHEET_H_
#define PIANODATASHEET_H_

//Ĭ�ϵ�P1�˿ڣ����ڰ���ѡ��
#define HighDefaultFlag 0xf0//BIT4+BIT5+BIT6+BIT7
#define LowDefaultFlag 0x0f//BIT0+BIT1+BIT2+BIT3
#define InterruptPort2 0x2d//BIT0+BIT2+BIT3+BIT5
#define PWMPort BIT1//TA1���������
#define LinkPort BIT4//���鵥Ƭ�����ӵĶ˿�

//���ھ�����̵�����ѡ���Ǿ�������к�
#define Line1 0//0b0000
#define Line2 1//0b0001
#define Line3 2//0b0010
#define Line4 3//0b0011
#define Row1 0//0b0000
#define Row2 4//0b0100
#define Row3 8//0b1000
#define Row4 12//0b1100

//���ھ�����̵�����ѡ���Ƕ�Ӧ���кŶ�Ӧ�Ķ˿�
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
#define KeyDefault 16//Ĭ�ϵ����ռ�ֵ

//�������ֲ�������60bpm�¶�Ӧ������ѭ������
#define Half 8192
#define One 16384
#define Two 32768
#define Dot 24576
#define Four 65535
#define Quarter 4096
#define TQuarter 12288
#define NQuarter 36864

//����ϵͳ��һЩ״̬����
#define Cycle 1//���ֲ�����������ѭ��
#define List 2//���ֲ��������б�ѭ��
#define Piano 1//ȫ�֣�����
#define MusicPlay 2//ȫ�֣����ֲ�����
#define Start 1//���ֲ�����������
#define Pause 2//���ֲ���������ͣ

//��Ƶ���йص�ֵ����
#define Low 0//����
#define Middle 1//����
#define High 2//����


//�������йص�CCR0ֵ����
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


//һЩ�������йصĲ���
#define ScoreNumber 4//�����������
#define MaxScore Score4//������ױ��
//���ױ��
#define Score1 0//����1�����ո�
#define Score2 1//����2�������
#define Score3 2//����3����ֻ�ϻ�
#define Score4 3//����4���������¼����������

//ÿ������Ӧ��TA1CCR0ֵ��������Ϊ������������Ϊ�˶ȣ�������A=442HzΪ�м�˶�6��C������ʮ��ƽ���ɰ�������
const unsigned int Freq[3][12]=
{
LDo,LUDo,LRe,LURe,LMi,LFa,LUFa,LSo,LUSo,LLa,LULa,LTi,
Do,UDo,Re,URe,Mi,Fa,UFa,So,USo,La,ULa,Ti,
HDo,HUDo,HRe,HURe,HMi,HFa,HUFa,HSo,HUSo,HLa,HULa,HTi
};
const unsigned int empty=1;//ռ�ձ����Ϊ1-1/32=96.8%>95%�����������б�֤

//�������
//ÿһ�����׶���ΪƵ�ʺͶ�Ӧ�ĳ���ѭ��������������ΪΪ�˱�֤ѭ���������ᳬ��unsigned int��������long unsigned int
//ĩβ0�����ж����׽���
//���ո�����
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

//���������
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

//��ֻ�ϻ�����
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

//�������¼������������
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


//��������ͬ���ķ������������������

//���׵��ٶȣ���bpm��
unsigned int tempo[ScoreNumber]={60,60,80,75};

#endif /* PIANODATASHEET_H_ */
