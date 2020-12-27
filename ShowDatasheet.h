/*
 * 本头文件是数码管驱动单片机的数据表，当前硬件条件下不具备扩展空间，但是可以作为接线的指导。
 * 当然，本部分也可以用来修改更好的排线方式。但是修改排线必须在数据表中修改对应的宏定义。
 */
#ifndef SHOWDATASHEET_H_
#define SHOWDATASHEET_H_

//P2对应端口控制74HC595
#define DS BIT0
#define SHCP BIT1
#define STCP BIT2

//P1对应端口控制LG3641BH的各位
#define S1 BIT0
#define S2 BIT1
#define S3 BIT2
#define S4 BIT3

//扩展板上用于控制整个系统的按键
#define Sign BIT4
#define PlayModeChange BIT5
#define ShowModeChange BIT6

//显示状态的标志
#define Show 1
#define Pause 2

//显示模式
#define Pano 1
#define Cycl 2
#define List 3

#endif /* SHOWDATASHEET_H_ */
