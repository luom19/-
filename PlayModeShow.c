/*
 *���ļ��������������Ƭ���ĺ��ĳ������й��ܿ�����ݱ�ͷ�ļ��������á�
 *��ǰӲ�������²�֧����չ��
 */
#include<msp430.h>
#include<ShowDatasheet.h>
#include<ShowFunctionLib.h>

//�洢��ʾģʽ�ı���
unsigned int ModeFlag=Pano;//����ģʽ��Ĭ��Ϊϵͳ��Ĭ��״̬�����٣�
unsigned int ShowFlag=Show;//�Ƿ���ʾ��Ĭ��Ϊ��ʾ
unsigned int PlayModeBuffer=Cycl;//���沥��ģʽ

int main(void)
{
    CloseWatchDog();//�رտ��Ź�

    //��ؼĴ������ã�
    //P1.0~P1.3���ڿ���LG3641BH��S1~S4
    Port1SetLG3641BH();
    //P1.4~P1.6�жϻ�������
    Port1InterruptSet();
    //P2.0~P2.2���ڿ���74HC595��DS��SHCP��STCP
    Port2Set74HC595();

    //���ж�����
    _EINT();
    P1IFG=0;

    //Ĭ��״̬Ϊ���١�����ʾ
     SetLEDtoPANODot(&ShowFlag,&ModeFlag);

    while(1)
    {
        if(ShowFlag==Pause)//�����ʱҪ����ʾ
        {
            SetLEDClear();//��������
        }
        else if(ShowFlag==Show)//�����ʱҪ����ʾ
        {
            switch(ModeFlag)
            {
            case Pano:SetLEDtoPANODot(&ShowFlag,&ModeFlag);break;//��ʾPano.
            case List:SetLEDtoLISTDot(&ShowFlag,&ModeFlag);break;//��ʾList.
            case Cycl:SetLEDtoCYCLDot(&ShowFlag,&ModeFlag);break;//��ʾCycl.
            }
        }
    }
}

//P1�˿ڵ��ж�
#pragma  vector=PORT1_VECTOR
__interrupt  void port1_ISR( )
{
    Keydelay();
    if((P1IFG&Sign)!=0)//��ʾϵͳģʽ�仯
    {
        if((ModeFlag==Cycl)||(ModeFlag==List)) ModeFlag=Pano;//��������ֲ�����ģʽ�������Ϊ����ģʽ
        else if(ModeFlag==Pano) ModeFlag=PlayModeBuffer;//����ڸ���ģʽ�������Ϊ���ֲ�����֮ǰ�洢��״̬
    }
    else if((P1IFG&PlayModeChange)!=0)//��ʾ���ֲ�����ģʽ�ı仯
    {
        if((ModeFlag==Cycl)||(ModeFlag==List))//��⴦�����ֲ�����ģʽ��ִ�У�����ִ��
        {
            if(ModeFlag==Cycl) ModeFlag=List;
            else if(ModeFlag==List) ModeFlag=Cycl;
            PlayModeBuffer=ModeFlag;//��״̬��������
        }
    }
    else if((P1IFG&ShowModeChange)!=0)//��ʾ��ʾģʽ�ı仯
    {
        ShowFlag++;
        if(ShowFlag>Pause) ShowFlag=Show;
    }
    P1IFG &= 0;//����жϱ�־λ
}

