/*
 * ��ͷ�ļ������ֲ���������Ƭ���Ĺ��ܿ⣬����ɾ����
 * ����������ף���Ҫ��������ĸ�ʽ�޸�PlayMusic���������ʽΪ�����������ӵ��ǵ�k�����ף�
 * else if(*Score==Scorek)
    {
        //��ѭ�������ڲ���ÿ����
        for(i=PlusScoreFlag;ScorekFreq[i]!=0;i++)
            {
                TA1CCR0=ScorekFreq[i];
                TA1CCR1=empty;
                temp=ScorekTimes[i];
                //���ѭ��������ע�⻹Ҫ���ǵ��ٶȵı仯
                MaxCycleTimek=(long unsigned int)((double)temp*((double)60/(double)tempo[*Score]));
                //�������еĵ�i+1����
                for(j=0;j<MaxCycleTimek;j++)//���ϴο�ʼ���ŵ��ֳ���ʼ����
                {
                     while(*PlayFlag==Pause)//�����ͣ��,��ͨ���������ö˿�2��ֹ��������
                     {
                         Port2Reset();
                         if(*Key==K16)//�����ʱ�����л�ģʽ�������ͣ״̬����
                         {
                             *PlayFlag=Start;
                             break;
                         }
                     }
                     Port2StartBuzz();//�ָ��˿�2
                     if((*Key==K16)||(*Score!=Scorek)) break;//����л�ģʽ�����л��˲��ŵ���������˳�ѭ��
                };
                Port2Reset();//�ָ�P2״̬
                if((*Key==K16)||(*Score!=Scorek)) break;//����л�ģʽ�����л��˲��ŵ���������˳�ѭ��
                DelayBetweenNote();//�������ӳ٣��ν�
            };
    }
 *���⣬��Ҫ���ⶨ��һ��PlayMusic�����еı�����������ΪMaxCycleTimek;
 */
#ifndef PIANOFUNCTIONLIB_H_
#define PIANOFUNCTIONLIB_H_

//�������
void Keydelay()
{
    unsigned int i;
    for (i=1000;i>0;i--);
}

//�����������õĶ��ӳ�
void Shortdelay()
{
    unsigned int i;
    for(i=0x0100;i>0;i--);
}

//����֮��Ķ����ӳ�
void DelayBetweenNote()
{
    unsigned int i;
    for(i=0x00F0;i>0;i--);
}

//����֮��Ľϳ��ӳ�
void DelayBetweenScore()
{
    unsigned int i;
    for(i=0xF000;i>0;i--);
}

//�رտ��Ź�
void CloseWatchDog()
{
    //�رտ��Ź�
    WDTCTL = WDTPW + WDTHOLD;
}

//�趨����P1�˿��������Ӿ�����̣����ڿ��Ƹ��ٵķ���
void Port1set()
{
    //�趨P1Ϊ���������������
    P1SEL&=~(HighDefaultFlag+LowDefaultFlag);
    P1SEL2&=~(HighDefaultFlag+LowDefaultFlag);
    //�趨P1.0~P1.3Ϊ�������
    P1DIR|=LowDefaultFlag;
    //�趨P1.4~P1.7Ϊ���빦��
    P1DIR&=~HighDefaultFlag;
    //����˿ڳ�ʼ��Ϊ�ߵ�ƽ
    P1OUT|=LowDefaultFlag;

}

//P2��PWM�Ĵ�������
void Port2PWMset()
{
    //ѡ��TA1����ʱ��ΪACLK��ʹ���ϵ縴λ���ã���32768Hz
    TA1CTL |=TASSEL0;
    //����TA1�Ƚ���1��PWM���Ϊģʽ2�� ������CCR1ֵ��ת����CCR0ֵ��0
    TA1CCTL1|=OUTMOD1;
    //������������ʽ��ʹ��������0��ʼ������������TA1CCR0���ִ�0������
    TA1CTL |=TACLR+MC0;
}

//�˿�2��ʼ��
void Port2Reset()
{
    //��ʱP2.1�����PMW����
    P2SEL2|=PWMPort;
    //��Ϊ�͵�ƽĬ��ֵ
    P2OUT&=~PWMPort;
}

//�趨P2��PWM���ο��Ʒ�����
void Port2set()
{
    //��P2.1Ϊ��ʱ��TA1��PWM�������
    P2SEL |=PWMPort;
    P2DIR |=PWMPort;
    //����P2.4�������ӵڶ��鵥Ƭ��
    P2SEL&=~LinkPort;
    P2SEL2&=~LinkPort;
    P2DIR|=LinkPort;
    P2OUT|=LinkPort;
    Port2Reset();
}

//�趨P2������Ʒ��������ź�
void Port2StartBuzz()
{
    //P2.1��P2.4Ϊ�Ƚ���1��PWM�������
    P2SEL2 &=~PWMPort;
}

//�趨P1.4~P1.7�йص��жϹ���
void Port1InterruptSet()
{
    //P1�ж��������
        P1OUT &=~HighDefaultFlag;
        P1REN |=HighDefaultFlag;
        P1IE |= LowDefaultFlag+HighDefaultFlag;
        P1IES &=~(LowDefaultFlag+HighDefaultFlag);
        P1IFG &=~(LowDefaultFlag+HighDefaultFlag);
}

void Port2InterruptSet()
{
    //P2�ж��������
        P2SEL&=~InterruptPort2;
        P2SEL2&=~InterruptPort2;
        P2DIR&=~InterruptPort2;
        P2OUT |=InterruptPort2;
        P2REN |=InterruptPort2;
        P2IE |= InterruptPort2;
        P2IES &=~InterruptPort2;
        P2IFG &=~InterruptPort2;
}

//K16����ʱ��P2.4�����һ���½�-�����ź������жϣ��Է��½��ش�����
void LinkPortInterruptFlag()
{
    P2OUT&=~LinkPort;
    Shortdelay();
    P2OUT|=LinkPort;
}

//ѡ�񰴼����ڵ���
unsigned int SwitchKeyLine()
{
    //ѡ�񰴼��еı�������Ĭ��Ϊ����ֵ
    unsigned int key=16;

    P1OUT=0;
    //����P1.4~P1.7���
    P1DIR|=HighDefaultFlag;
    //����P1.0~P1.3����
    P1DIR&=~LowDefaultFlag;
    //����P1.4~P1.7�ߵ�ƽ
    P1OUT|=HighDefaultFlag;

    //����Ӧ�а�������ʱ����Ӧ��P1IN������ߵ�ƽ������Ϊ�͵�ƽ��ѡ������ߵ�ƽ
    switch(P1IN)
    {
        case L1:key=Line1;break;
        case L2:key=Line2;break;
        case L3:key=Line3;break;
        case L4:key=Line4;break;
    }
    return key;
}

//ѡ�񰴼����ڵ���
unsigned int SwitchKeyRow(unsigned int key)
{
    //��P1Ϊ�͵�ƽĬ��ֵ
    P1OUT=0;
    //����P1.0~P1.3���
    P1DIR|=LowDefaultFlag;
    //����P1.4~P1.7����
    P1DIR&=~HighDefaultFlag;
    //����P1.0~P1.3�ߵ�ƽ
    P1OUT|=LowDefaultFlag;

    //ɨ���ж�Ӧֵ
    switch(P1IN)
    {
        case R1:key+=Row1;break;
        case R2:key+=Row2;break;
        case R3:key+=Row3;break;
        case R4:key+=Row4;break;
    }

    return key;
}

//ѡ�񰴼������������ڶ�Ӧ������Ƶ��
unsigned int ChooseKey()
{
    //ѡ�񰴼��ı�����Ĭ��ֵ����
    unsigned int key=KeyDefault;
    //ѡ�񰴼���
    key=SwitchKeyLine();
    //ѡ�񰴼���
    key=SwitchKeyRow(key);
    //�����K16�����һ�鵥Ƭ��һ�������ź������ܹ��任���������
    if(key==K16) LinkPortInterruptFlag();

    return key;
}

//����ɨ�谴����ֵ���ص�ǰѡ��İ˶ȵĺ���
unsigned int DoAfterChoose(unsigned int Freqchoice,unsigned int key)
{
    unsigned int FreqChoice=Freqchoice;
    //�ָ�P1�˿��ֳ�
    P1DIR|=LowDefaultFlag;
    //�趨P1.4~P1.7Ϊ���빦��
    P1DIR&=~HighDefaultFlag;
    //����˿ڳ�ʼ��Ϊ�ߵ�ƽ
    P1OUT|=LowDefaultFlag;

    //��Щ����������ѡ��Ƶ�ʷ�Χ��
    if(key>=K13)
    {
        switch(key)
        {
        //K16�����л�ģʽ���������Ӧʲô������Ҫ��
        case K16:break;
        //K13~K15����ѡ��Ƶ�ʣ�
        case K13:FreqChoice=0;break;//K13
        case K14:FreqChoice=1;break;//K14
        case K15:FreqChoice=2;break;//K15
        default:break;
        }
    }
    //���ఴ���������õ�
    else
    {
        //����������
        Port2StartBuzz();
        TA1CCR0=Freq[FreqChoice][key];
        TA1CCR1=empty;
        while(P1IN!=LowDefaultFlag)
        {
            Shortdelay();
        }
        //�ָ�P2�˿�
        Port2Reset();
    }

    return FreqChoice;

}

//���ֲ��ź���
unsigned int PlayMusic(int *Score,unsigned int *PlayFlag,unsigned int *Key,unsigned int *Mode,unsigned int PlusScoreFlag)
{
    unsigned int i;
    long unsigned int j;
    long unsigned int temp;
    //ÿ������ѭ������
    long unsigned int MaxCycleTime1,MaxCycleTime2,MaxCycleTime3,MaxCycleTime4;
    //��ֹ�Ӹ���ģʽ�ո��л�����������
    TA1CCR0=0;
    TA1CCR1=0;
    Port2StartBuzz();

    //���������1
    if(*Score==Score1)
    {
        //��ѭ�������ڲ���ÿ����
        for(i=PlusScoreFlag;Score1Freq[i]!=0;i++)
            {
                TA1CCR0=Score1Freq[i];
                TA1CCR1=empty;
                temp=Score1Times[i];
                //���ѭ��������ע�⻹Ҫ���ǵ��ٶȵı仯
                MaxCycleTime1=(long unsigned int)((double)temp*((double)60/(double)tempo[*Score]));
                //�������еĵ�i+1����
                for(j=0;j<MaxCycleTime1;j++)//���ϴο�ʼ���ŵ��ֳ���ʼ����
                {
                     while(*PlayFlag==Pause)//�����ͣ��,��ͨ���������ö˿�2��ֹ��������
                     {
                         Port2Reset();
                         if(*Key==K16)//�����ʱ�����л�ģʽ�������ͣ״̬����
                         {
                             *PlayFlag=Start;
                             break;
                         }
                     }
                     Port2StartBuzz();//�ָ��˿�2
                     if((*Key==K16)||(*Score!=Score1)) break;//����л�ģʽ�����л��˲��ŵ���������˳�ѭ��
                };
                Port2Reset();//�ָ�P2״̬
                if((*Key==K16)||(*Score!=Score1)) break;//����л�ģʽ�����л��˲��ŵ���������˳�ѭ��
                DelayBetweenNote();//�������ӳ٣��ν�
            };
    }
    else if(*Score==Score2)//���������2��ע��ͬ��
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
    else if(*Score==Score3)//���������3��ע��ͬ��
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
    else if(*Score==Score4)//���������4��ע��ͬ��
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
    //������ͬ���ķ�ʽ��Ӳ���������������¼���������չ����������

    return i;
}

#endif /* PIANOFUNCTIONLIB_H_ */
