/*
 * ��ͷ�ļ��������������Ƭ�������ݱ���ǰӲ�������²��߱���չ�ռ䣬���ǿ�����Ϊ���ߵ�ָ����
 * ��Ȼ��������Ҳ���������޸ĸ��õ����߷�ʽ�������޸����߱��������ݱ����޸Ķ�Ӧ�ĺ궨�塣
 */
#ifndef SHOWDATASHEET_H_
#define SHOWDATASHEET_H_

//P2��Ӧ�˿ڿ���74HC595
#define DS BIT0
#define SHCP BIT1
#define STCP BIT2

//P1��Ӧ�˿ڿ���LG3641BH�ĸ�λ
#define S1 BIT0
#define S2 BIT1
#define S3 BIT2
#define S4 BIT3

//��չ�������ڿ�������ϵͳ�İ���
#define Sign BIT4
#define PlayModeChange BIT5
#define ShowModeChange BIT6

//��ʾ״̬�ı�־
#define Show 1
#define Pause 2

//��ʾģʽ
#define Pano 1
#define Cycl 2
#define List 3

#endif /* SHOWDATASHEET_H_ */
