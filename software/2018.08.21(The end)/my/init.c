#include "include.h"


extern uint8 imgbuff[CAMERA_SIZE];

extern float S_P;
extern float S_D;
extern float M_L_P; //����P
extern float M_L_I; //����D
extern float M_R_P; //�ҵ��P 
extern float M_R_I; //�ҵ��D
extern float C_P;
extern float C_D;

extern uint16 normal_speed;
extern uint8 Circle_ON_OFF;
extern uint8 Meet_ON_OFF;
extern float Cam2Mag_Weight;
extern MEET_PLACE_e meet_choose;
extern uint8 meet_ring_number;
extern uint8 meet_seq;
extern uint16 long_count_cjx;

extern uint16 add_deviation_cjx;

extern uint8 polarization_ON_OFF;
/* ����ͷ��ʼ����Ҫ���õ��� 
VCAN_OV7725_Eagle.h {//��������ͷ�������}
VCAN_SCCB.h {//SCCB �ܽ�����}
*/

void init()
{
	
	DisableInterrupts;
	set_vector_handler(PORTA_VECTORn,PORTA_IRQHandler); //����PORTD�жϺ���
	set_vector_handler(DMA4_VECTORn,DMA4_IRQHandler);   //����DMA4�жϺ���
	camera_init(imgbuff);
	//enable_irq(PORTA_IRQn);   //ʹ��PORTA
	set_irq_priority(PORTA_IRQn,1);  // �������ȼ�
	set_irq_priority(DMA4_IRQn,5);
	
	//���
	FTM_PWM_init(FTM0, FTM_CH0, 10000, 0);  //���PTC1  Ƶ��10000    //���� 
	FTM_PWM_init(FTM0, FTM_CH1, 10000, 0);//���PTC2  Ƶ��10000     //������
	FTM_PWM_init(FTM0, FTM_CH2, 10000, 0); //���PTC3  Ƶ��10000     //������
	FTM_PWM_init(FTM0, FTM_CH3, 10000, 0);  //���PTC4  Ƶ��10000     //����
	
	//������
	lptmr_pulse_init(LPT0_ALT2,0xFFFF,LPT_Rising);    
	FTM_QUAD_Init(FTM2);    //��ʼ�� FTM2 Ϊ��������ģʽ
	port_init_NoALT(PTA11,PULLUP);
	lptmr_pulse_clean();
	FTM_QUAD_clean(FTM2);
	//����������תIO
	gpio_init (PTD10, GPI,1);    //��ʼ�� ������
	port_init(PTD10,  ALT1 | PULLUP);
	gpio_init (PTD12, GPI,1);    //��ʼ�� ������
	port_init(PTD12,  ALT1 | PULLUP);
	
	//Ӳ���Ϸ�
	set_vector_handler(HardFault_VECTORn ,HardFault);
	
	//LED
	gpio_init (PTC0, GPO,1);    //��ʼ�� LED
	gpio_init (PTD15, GPO,1);    //��ʼ�� LED
	gpio_init (PTE26, GPO,1);    //��ʼ�� LED
	gpio_init (PTA17, GPO,1);    //��ʼ�� LED
	
	//    ����
	gpio_init(PTD1,GPI,1);
	port_init(PTD1,  ALT1 | PULLUP);//boma1
	gpio_init(PTD4,GPI,1);
	port_init(PTD4,  ALT1 | PULLUP);//boma2
	gpio_init(PTD6,GPI,1);
	port_init(PTD6, ALT1 | PULLUP);//boma3
	gpio_init(PTD9,GPI,1);
	port_init(PTD9, ALT1 | PULLUP);//boma4
	gpio_init(PTD11,GPI,1);
	port_init(PTD11, ALT1 | PULLUP);//boma5
	gpio_init(PTD13,GPI,1);
	port_init(PTD13, ALT1 | PULLUP);//boma6
	
	//����
	gpio_init(PTC10,GPI,1);//��
	port_init (PTC10,  ALT1|PULLUP );
	gpio_init(PTC13,GPI,1);//��
	port_init (PTC13,  ALT1|PULLUP );
	gpio_init(PTC19,GPI,1);//��
	port_init (PTC19,  ALT1|PULLUP );
	gpio_init(PTC6,GPI,1);//��
	port_init (PTC6,  ALT1|PULLUP );
	gpio_init(PTC8,GPI,1);//��
	port_init (PTC8,  ALT1|PULLUP );
	
	gpio_init(PTC11,GPI,1);//����
	port_init (PTC11,  ALT1|PULLUP );
	
	LCD_Init();
	LCD_Print(36,2,"Welcome");
	Dis_Num(37,4,work_mode,3);
	DELAY_MS(1000);
	LCD_Fill(0x00);
	
	//zigbeeͨ�Ŵ����ж�
	uart_init(UART3,9600); 
	set_vector_handler(UART3_RX_TX_VECTORn,UART3_IRQHandler);
	uart_rx_irq_en(UART3);
	set_irq_priority(UART3_RX_TX_IRQn,2);	
	
	//���������ж�
//	set_irq_priority(UART0_RX_TX_IRQn,7);
	
	
	//AD
	pit_init_ms(PIT1,5);
	set_vector_handler(PIT1_VECTORn,PIT1_IRQHandler);
	set_irq_priority(PIT1_IRQn,3);
	
	adc_init(ADC0_SE9);
	adc_init(ADC0_SE13);
	adc_init(ADC0_SE12);
	adc_init(ADC1_SE11);
	adc_init(ADC1_SE10);
	adc_init(ADC1_SE13);
	adc_init(ADC1_SE12);
	
	pit_init_ms(PIT0,10); //���������ж�
	set_vector_handler(PIT0_VECTORn,PIT0_IRQHandler);
	set_irq_priority(PIT0_IRQn,6);
	enable_irq(PIT0_IRQn );
	
	pit_init_ms(PIT2,20);
	set_vector_handler(PIT2_VECTORn,PIT2_IRQHandler);
	set_irq_priority(PIT2_IRQn,4);
	//enable_irq(PIT2_IRQn );
	
	//    ������
	gpio_init(PTB23,GPO,1);
	port_init (PTB23,  ALT1|ODO|PULLUP );
	
	gpio_init(PTD7,GPI,0);//��
	port_init (PTD7,  ALT1|PULLDOWN );
	gpio_init(PTD8,GPI,0);//��
	port_init (PTD8,  ALT1|PULLDOWN );
	
	/////////////////////////////////////////////////////////
	
	
	//	
	//	flash_erase_sector(servo_sector);
	//	
	//	
	//	flash_write(servo_sector, 0, 5);
	//	flash_write(servo_sector, 4, 7);
	//
	//	flash_write(servo_sector, 8, 20);
	//	flash_write(servo_sector, 12, 0);
	//	
	//
	//	flash_write(servo_sector, 16, 70);
	//
	//	flash_write(servo_sector, 48, 9);
	//	flash_write(servo_sector, 52, 0);  
	//	
	//	flash_write(servo_sector, 56, 17);
	//	flash_write(servo_sector, 60, 0);  
	//	
	//	flash_write(servo_sector, 64, 200);
	//	
	//	flash_write(servo_sector, 68,1);
	//	
	//	flash_write(servo_sector, 72, 1);
	//	
	//	flash_write(servo_sector, 76, 4);
	//	flash_write(servo_sector, 80, 0);  
	//	flash_write(servo_sector, 84, 1);
	//	flash_write(servo_sector, 88, 1); 
	//	
	
	
	////////////////////////////////////////////////////////////
	
	
	//FLASH��ȡ��ʼ��
	S_P=flash_read(servo_sector , 0, uint8)+((float)(flash_read(servo_sector , 4, uint8))*(0.1));
	S_D=flash_read(servo_sector , 8, uint8)+((float)(flash_read(servo_sector , 12, uint8))*(0.1));
	
	long_count_cjx=flash_read(servo_sector , 16, uint16);
	add_deviation_cjx=flash_read(servo_sector , 24, uint16);
	
	//	M_R_I=flash_read(servo_sector , 32, uint8)+((float)(flash_read(servo_sector , 36, uint8))*(0.1));
	//	M_R_P=flash_read(servo_sector , 40, uint8)+((float)(flash_read(servo_sector , 44, uint8))*(0.1));
	C_P=flash_read(servo_sector , 48, uint8)+((float)(flash_read(servo_sector , 52, uint8))*(0.1));
	C_D=flash_read(servo_sector , 56, uint8)+((float)(flash_read(servo_sector , 60, uint8))*(0.1));
	normal_speed=flash_read(servo_sector , 64, uint16);	
	Circle_ON_OFF=flash_read(servo_sector , 72, uint16);	
	Meet_ON_OFF=flash_read(servo_sector , 68, uint16);
	Cam2Mag_Weight=flash_read(servo_sector , 76, uint8)+((float)(flash_read(servo_sector , 80, uint8))*(0.1));
	meet_choose=flash_read(servo_sector ,84, uint16);
	meet_ring_number=flash_read(servo_sector ,88, uint16);
	
        polarization_ON_OFF=flash_read(servo_sector , 92, uint16);
	if(meet_ring_number>=10 || meet_choose>=3)
	{
		meet_choose=no_meet;
		meet_ring_number=0;
		flash_updata();
	}
	if(Meet_ON_OFF==0)
	{
		meet_choose=no_meet;
	}
	//	else if(meet_choose==meet_circle)
	//	{
	//		meet_seq=5;
	//	}
	EnableInterrupts;
	
	
}