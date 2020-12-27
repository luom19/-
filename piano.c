/*
 *���ļ������ֲ���������Ƭ���ĺ��ĳ������й��ܿ�����ݱ�ͷ�ļ��������á�
 *�����ɾ���ף���Ҫ�ڱ��ļ��ĵ�68�ж����߼���һ��ScorekFreq[PlusScoreFlag]==0
 */
#include<msp430.h>
#include<PianoDatasheet.h>//����ͷ�ļ���������Ҫ���ܺ�����д������
#include<PianoFunctionLib.h>//����ͷ�ļ���������Ƭ�������ݱ����涨���˴��������������Խ����Զ����������ɾ

//ȫ�ֱ����������ڸ�����Ķ�����PianoDatasheet.h�У�
//����ģʽ������ѡ�񰴼���Ӧ�İ˶ȣ�Ĭ��Ϊ���İ˶�
unsigned int FreqChoice=Middle;
//����ѡ�������̰���ֵ��ȫ�ֱ�����0~15����K1~K16��16��ʾĬ������ֵ
unsigned int Key=KeyDefault;
//��ʾϵͳ���ܹ���ģʽ��Ĭ��ģʽΪ���٣�Piano��ʾ���٣�MusicPlay��ʾ���ֲ�����
unsigned int Mode=Piano;
//���ֲ�����ģʽ��ѡ��������ŵı���
int Score=Score1;
//���ֲ�����ģʽ������ѡ�񲥷��б�˳��ı�����CycleΪ����ѭ����ListΪ�б�ѭ��
unsigned int PlayMode=Cycle;
//���ֲ�����ģʽ�����ڱ�ʾ�Ƿ񲥷ŵı�����Start��ʾ���ţ�Pause��ʾ��ͣ
unsigned int PlayFlag=Start;
//���ֲ��ź����ķ���ֵ�������ж��Ƿ��Ƿ�����һ�����ֲ��˳��ĺ���
unsigned int PlusScoreFlag=0;

int main(void)
{
    //�رտ��Ź�.
    CloseWatchDog();

    //��ؼĴ�����ʼ����
    //�˿�1��������
    Port1set();
    //�˿�1�ж�����
    Port1InterruptSet();
    //�˿�2��������
    Port2set();
    //�˿�2PWM��������
    Port2PWMset();
    //�˿�2�ж�����
    Port2InterruptSet();

    //���ж�����
    _EINT();

    //��ѭ��
    while(1)
    {

       if(Mode==Piano)//��ʱΪ������ģʽ
       {
           if(Key!=KeyDefault)
           {
               FreqChoice=DoAfterChoose(FreqChoice,Key);//��ʾѡ��˶ȣ���ͨ���ж�ѡ�񰴼�ֵ
               if(Key==K16) Mode++;//�������K16����ϵͳ����ģʽ�л�
               Key=KeyDefault;
           }
       }
       else if(Mode==MusicPlay)//��ʱΪ��Ƶ������ģʽ��Mode==MusicPlay
       {
           PlusScoreFlag=PlayMusic(&Score,&PlayFlag,&Key,&Mode,PlusScoreFlag);//���ֲ��ź��������ű��ΪScore�����ײ���ʱ���״̬ȫ�ֱ�������Score��Key��PlayFlag��Mode�ı仯�����ı�״̬
           if(Key==K16)//��������˾�����̵�K16�����ͻ��л�ģʽ�������ֲ���ģʽ���˳�
           {
               Key=KeyDefault;//��ΪĬ������ֵ
               Mode--;
           }
           else//��ʱ������������������һ���������л�����������Ŀ
           {
               if((Score1Freq[PlusScoreFlag]==0)||(Score2Freq[PlusScoreFlag]==0)||(Score3Freq[PlusScoreFlag]==0)||(Score4Freq[PlusScoreFlag]==0))//������ʱ����������������һ������
               {
                   switch(PlayMode)
                   {
                   case Cycle:break;//����ǵ���ѭ����ֱ���ز�
                   case List:Score++;if(Score>MaxScore) Score=Score1;break;//������б�ѭ���򲥷���һ��
                   }
               }
               PlusScoreFlag=0;//���֮ǰ���ֳ�
               DelayBetweenScore();
           }
       }
    }
}

//P1�˿ڵ��ж�
#pragma  vector=PORT1_VECTOR
__interrupt  void port1_ISR( )
{
    if(P1IN !=LowDefaultFlag)//������ʱ����һ������
    {
        Keydelay();//����
        if(P1IN != LowDefaultFlag)
        {
            Key=ChooseKey();//ѡ�񰴼����ö����Ʊ���0b0000~0b1111��ʾK1~K16
        }
    }
    P1IFG &= 0;//����жϱ�־λ
}

//P2�˿ڵ��ж�
#pragma  vector=PORT2_VECTOR
__interrupt  void port2_ISR( )
{
    Keydelay();//����
    if((P2IFG&BIT0)!=0)//�����P2.0�ϵ��жϣ���K1���£��л���ͣ�򲥷�״̬
    {
        PlayFlag++;
        if (PlayFlag>Pause)
        {
            PlayFlag=Start;
        }
    }
    else if((P2IFG&BIT2)!=0)//�����P2.2�ϵ��жϣ���K2���£���ı䲥��ģʽ
    {
        PlayMode++;
        if(PlayMode>List)
        {
            PlayMode=Cycle;
        }
    }
    else if((P2IFG&BIT3)!=0)//�����P2.3�ϵ��жϣ���K3����,����һ��
    {
        Score++;
        if(Score>MaxScore)
        {
            Score=Score1;
        }
    }
     else  if((P2IFG&BIT5)!=0)//�����P2.5�ϵ��жϣ���K4���£�����һ��
     {
         Score--;
         if(Score<Score1)
         {
             Score=MaxScore;
         }
     }
    P2IFG &= 0;//����жϱ�־λ
}




