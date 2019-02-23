#ifndef MAGNETIC_H_H
#define MAGNETIC_H_H

#include "include.h"



/*************�����������š�����*************/
#define work_mode    1
/*************�����������š�����*************/
/************************************/


//ADC0_SE9







//>>>>>>>>>>>>1�ų�<<<<<<<<<<<<<<//
#if work_mode == 1

#define M_I 6
#define M_P 40
#define add_bias 1
#define circle_line_in 45


#define critical_val   180   //ֱ���ᳵ�ж��ٽ�ֵ
#define AD_right ADC0_SE13
#define AD_middle ADC0_SE9
#define AD_left ADC1_SE11

#define Servo_Duty_Md 1100// for��  1
#define Servo_Duty_Lf 1260// for��
#define Servo_Duty_Rt 930//for��


//>>>>>>>>>>>>2�ų�<<<<<<<<<<<<<<//
#else

#define M_I 6
#define M_P 42
#define add_bias -2             //��ƫ��
#define circle_line_in 44       //Բ����������


#define critical_val   200     //ֱ���ᳵ�ж��ٽ�ֵ
/**************[��] [��] [��] []**************************/


#define AD_right ADC0_SE13  
#define AD_middle ADC0_SE12
#define AD_left ADC1_SE11

#define Servo_Duty_Md 1480//1480for����  2
#define Servo_Duty_Lf 1670//1670for����
#define Servo_Duty_Rt 1290//1290for����


#endif


void magnetic_information();
uint8 Bubble(uint8 *v);
void ad_collect();
void magnetic_circle();
void Insurance_Mag();

#endif