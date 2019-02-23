#include "common.h"
#include "include.h"

extern uint8  *ov7725_eagle_img_buff;
extern uint8 imgbuff[CAMERA_SIZE];
extern uint8 img[CAMERA_H][CAMERA_W];
extern CAR_STATUS_e car_mode;

extern int16 Get_SpeedL;
extern int16 Get_SpeedR;

extern uint8 camera_open_flag;
extern moty_duty run_duty;

extern uint8 buzzer_time;
extern uint8 buzzer_count;
extern uint8 buzzer_number;

extern uint8 edge_sum_left;
extern uint8 edge_sum_right;
extern uint16 edge_black[2];
extern int16 Servo_Duty;
extern uint8 meet_flag;

extern uint8 system_clock;
extern uint8 camera_times;

extern uint8 send_picture[CAMERA_SIZE];
extern uint8 sending_flag;

extern uint8 Circle_ON_OFF;
extern uint8 Meet_ON_OFF;
extern uint8 Meet_Action_flag;
extern uint8 FootWalk_ON_OFF;   //�����߿���

extern uint8 check_send_flag;
extern MEET_PLACE_e meet_choose;
extern uint8 meet_ring_number;
extern uint8 ring_pass_number;

extern int16 ramp_count;
extern uint8 delay_run_flag;
extern uint8 one_car_mode;

extern  ROAD_STATUS_e road_flag;

void PORTA_IRQHandler()
{
	
	uint8 n=24;
	if(PORTA_ISFR & (1<<n))  
	{
		PORTA_ISFR |=1<<n;         //���VSYNC��־λ
		disable_irq(PORTA_IRQn);   //�ر��ж�
		PORTA_ISFR = 1<<PTA19;      //���PCLK��־λ
		DMA_IRQ_CLEAN(DMA_CH4);
		DMA_EN(DMA_CH4);
		DMA_IRQ_EN(DMA_CH4);
		DMA_DADDR(DMA_CH4) =(uint32)ov7725_eagle_img_buff;
		PORTA_ISFR = 1<<PTA19;       
	}
}

void DMA4_IRQHandler()
{
	
	DMA_IRQ_CLEAN(DMA_CH4);
	DMA_IRQ_DIS(DMA_CH4);
	DMA_DIS(DMA_CH4);
	
	img_extract(img, imgbuff, CAMERA_SIZE);             //��ѹ
	
	/*������⴦��*/
	
	cover_image();//����ǰ10��//ǰհ70��80cm  
	find_edge();//ɨ����//����start����  
	find_circle_point();
	/*�������Ż�*/
	
	/*�µ�����*/

	get_white_proportion();
	Edge_sum();//��ڵ� 
	/*�㷨*/
	Camera_center();   //������ƫ�� 
	/*Բ�������㷨*/
	if(Circle_ON_OFF==1)  
	{
		// Edge_sum();//�ڱߣ�Բ����//��Ҫ�Ż�       
		Circle_deal_last();
		//    magnetic_circle();
	}
	
	if(FootWalk_ON_OFF==1)
	{
		FootWalk_scanning();//��ֱɨ��
	}
	
	/* �㳵�����㷨  */
	if(meet_choose!=no_meet)
	{
		First_Meet();
		if(meet_choose==meet_straight && Meet_ON_OFF==1)
		{
			Smoothness_Judge();
			variance_judge_left();//�����  �����ж�   
			variance_judge_right();//�ұ���  �����ж�  

			sunken_edge();
			if(one_car_mode==0)
			{
				if(car_mode!=stop)  //ͣ��״̬��ʶ��ᳵ��
				{
					Straight_Meet_Judge();//�㳵�ж�
				}				
			}
		}
	}
	else {delay_run_flag=1;}
	if(Meet_Action_flag==1 )
	{
		Meet_Action();//�㳵�߼�
	}
	
	
	/*��������*/
	//	dma_count();
        variance_judge_center();//����  �����ж�   
	draw_center_line();
	draw_car_line();//����λ��  //ֱ������
	Three_line_mode();
	
	/***************************/
	img_compress(imgbuff, img, CAMERA_SIZE);  
	if(sending_flag==0)
	{
		memcpy(send_picture,imgbuff,CAMERA_SIZE);
	}
	
	PORTA_ISFR  |= (1 << 24);
	enable_irq(PORTA_IRQn);
	
	
	
	
}


void PIT0_IRQHandler()
{
	if(boma5==1)
	{
		buzzer_ring();
	}
	if(boma3==0)
	{
		check_send_flag=0;
		
	}
        if(check_send_flag==0)
	{
                Communication_Out();
	}
	
	PIT_Flag_Clear(PIT0);
}


void PIT1_IRQHandler()//����ж�//5ms�ɼ�10��
{
	
	//��������
	time_count();
	ad_collect();
//        if(road_flag==circle)
//        {
//          Insurance_Mag();
//        }
	OUT_STOP();
	//�Ƕȴ���  
	if(Circle_ON_OFF==1)
	{
		magnetic_circle();
	}
	
	//�Ƕ��ϴ�  
	servo_control_AD();
	
	
	PIT_Flag_Clear(PIT1);//���жϱ�־λ
	
	
}



void PIT2_IRQHandler()//pi�ж�10ms
{
        if(ramp_count>0){ramp_count--;}
	
	Counter_collect();//�������ɼ�  
	if(Meet_ON_OFF==1 && meet_choose==meet_circle)
	{
		circle_reverse();
	}
	road_speed_control(); //·�ͱ任�����ٶ�
	

        Go_back(50);//flag1�ɵ���0����
        
	Out_Straight_Meet();//���س�ȥ
	PI_control();    

	if(delay_run_flag==1)//��ʱ�ϴ�
	{
		FTM_updata(run_duty);//�ٶȴ������ 
	}
	
	PIT_Flag_Clear(PIT2);//���жϱ�־λ
	
	
	
	
}


void UART3_IRQHandler()
{
	Communication_In();
}



void HardFault()
{
	car_mode=error;
	printf("hardfault");
}