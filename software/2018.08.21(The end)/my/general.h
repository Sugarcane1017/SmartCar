#ifndef H_GENERAL_H
#define H_GENERAL_H
#include "include.h"

typedef enum
{
	
	normaliz=1,
	flash=2,   
	car_run=3,
	picture=4,
	mode_screen=5,
}
MENU_LIST_e; //�˵�

typedef enum
{
	meet_reversal=4,
	reversal=3,
	run=2,
	stop=1,
	error=0,
}
CAR_STATUS_e;  //����״̬ 


typedef enum
{
	in_contorl=0, //AD������ͷ������
	enforce_left=1, //ǿ����
	enforce_right=2, //ǿ����
	
}
TURN_STATUS_e; //ǿ�ƴ��

typedef enum
{   
	straight=1, //ֱ��
	corner=2, //���
	circle=3, //Բ��
	cross=4, //ʮ��
	meet=5,//�㳵
	ramp=6,
}
ROAD_STATUS_e;  //����״̬



typedef enum
{
	no_ring=0, //����û��Բ��
	near_ring=1, //����Բ��
	reach_ring_point=2, //����Բ��ֱ�������
	at_ring=3, //�ڻ���
//	out_ring=4, //����
	ring_meet=4,
}
RING_FLAG_e;


typedef enum
{
	no_meet=0,
	meet_straight=1,
	meet_circle=2,
}
MEET_PLACE_e;



typedef struct A
{
	int16 goal_speed_L;
	int16 goal_speed_R;
}to_speed;


typedef struct R
{
	RING_FLAG_e ring_flag;
	TURN_STATUS_e ring_turn;
}ring_missage;

typedef enum
{
	un_know=0,
	front_car=1,
	after_car=2,
}
MEET_CAR_NUMBER_e;


void ware_test();
void buzzer_once();
void buzzer_bibi(uint8 t,uint8 l);
void buzzer_ring();
void time_count();
void dma_count();
void LED_ALL_ON();
void LED_ALL_OFF();
#define servo_sector (FLASH_SECTOR_NUM-1)
#define magnetic_sector (FLASH_SECTOR_NUM-2)





#endif