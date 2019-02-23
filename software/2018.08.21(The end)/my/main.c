/*!
����ں�����ͷ
Բ������������أ�����ͷ�жϹ�����Ȧ������ͷ��������ͷ��ţ�����ͷ�ջش��

//7.27  ����
*/

#include "common.h"
#include "include.h"

extern MENU_LIST_e MENU;
extern uint8 var_max[3];
extern uint8 var_min[3];
extern uint8 imgbuff[CAMERA_SIZE];
extern uint8 img[CAMERA_H][CAMERA_W];
extern uint8 send_picture[CAMERA_SIZE];
extern uint8 sending_flag;
extern uint8 fitting_over_flag;
/*!
*  @brief      main����
*  @since      v5.0
*  @note       ���� LED �����Ƿ�����
������Ч����LED0��LED1ͬʱ������˸
*/
void main()
{    
	
	
	
	init();
	Boma_OLED();
	while(MENU==normaliz)
	{  
		magnetic_information();
		Boma_OLED();
		if(MENU!=normaliz)
		{
			flash_erase_sector(magnetic_sector);
			flash_write(magnetic_sector, 0, var_max[0]);
			flash_write(magnetic_sector , 4, var_max[1]);
			flash_write(magnetic_sector , 8, var_max[2]);
			
			flash_write(magnetic_sector, 12, var_min[0]);
			flash_write(magnetic_sector , 16, var_min[1]);
			flash_write(magnetic_sector , 20, var_min[2]);
		}
	}
	
	var_max[0]=flash_read(magnetic_sector , 0, uint8);
	var_max[1]=flash_read(magnetic_sector , 4, uint8);
	var_max[2]=flash_read(magnetic_sector , 8, uint8);
	
	var_min[0]=flash_read(magnetic_sector , 12, uint8);
	var_min[1]=flash_read(magnetic_sector , 16, uint8);
	var_min[2]=flash_read(magnetic_sector , 20, uint8);
	
	
	//������һ���ٿ�����AD�ɼ��Ͷ������
	DisableInterrupts;
	FTM_PWM_init(FTM1, FTM_CH0, 100,Servo_Duty_Md);
	enable_irq(PIT1_IRQn );
	enable_irq(PORTA_IRQn);
	enable_irq(PIT2_IRQn );
	EnableInterrupts;
	
	buzzer_bibi(1,1);
	while(1)
	{
		
		
		Boma_OLED();
		key_control();
		Check_Communication();
//		if(sending_flag==0)
//		{
//			sending_flag=1;
//			vcan_sendimg(send_picture,CAMERA_SIZE);
//		}
//		ware_test();
		
		
	}
}

