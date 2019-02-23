#include "include.h"

//--------------------ͨѶ--------------------//
extern uint8 CMD_in[5];  //ͨѶ����
extern uint8 MSG_in[4];  //ͨѶ����
extern uint8 MSG_out[4]; //ͨѶ����
extern uint8 last_send_signal; //�ϴη����źż�д�������ж��Ƿ���ԹضϷ�����һ������flag��
extern uint8 send_to_other_car_flag; //�������ⷢ�͵�flag
extern MEET_CAR_NUMBER_e car_number; //ǰ���󳵱�־λ
extern uint8 recv_data_p;
//--------------------ͨѶ--------------------//
extern uint8 Meet_ON_OFF;
extern int16 Servo_Turn;
extern uint8 meet_flag;         //�ᳵ״̬λ
extern int16 meet_turn;  

extern CAR_STATUS_e car_mode;  //����״̬
extern uint8 check_send_flag;
extern MEET_PLACE_e meet_choose;
extern uint8 to_the_side;
extern uint8 one_car_mode;
extern uint8 FootWalk_ON_OFF;   //�����߿���
extern uint8 first_meet_flag;
extern uint8 OK_send_flag;
extern ring_missage ring_info;
extern ROAD_STATUS_e road_flag;
extern uint8 meet_ring_number;
extern uint8 meet_seq;
extern uint8 meet_ring_seq;
extern uint16 ring_size;
extern uint8 ring_size_plus;
extern uint8 yy_flag;
void Check_Communication()
{
	if(check_send_flag==1)
	{
		MSG_out[0]='M';
		MSG_out[1]='I';
		MSG_out[2]='I';
		MSG_out[3]='.';
		uart_putbuff(UART3,MSG_out,sizeof(MSG_out));
	}
	
	
}
void Communication_In()
{

	char buff=0 ;
	if(UART_S1_REG(UARTN[UART3]) & UART_S1_RDRF_MASK)   //�������ݼĴ�����
	{
		uart_getchar (UART3,&buff);
		MSG_in[recv_data_p]=buff;
		if(MSG_in[0]=='M')//��ȷ��ͷ�ֽ�
		{
			recv_data_p++;
		}
		else {recv_data_p=0;}
		if(recv_data_p==4)  //����4��
		{
			recv_data_p=0;//����
			if(MSG_in[0]=='M'&& MSG_in[3]=='.')//��ͷ�ֽ�������ַ�У��   ---> ������ȷ
			{
				recv_data_p=0;//����
				if(MSG_in[1]!='O'&& MSG_in[1]==MSG_in[2])  //�����ź�Ϊ��O��Ӧ�𣩣�Ϊ������Ϣ
				{
					switch(MSG_in[1])
					{
						case 'G':  // �󳵽��յ���) ǰ������ᳵ��    ��ʼ����ǰ��(���յ�)
						{
							if(first_meet_flag==1 && meet_flag!=5)
							{
								last_send_signal='O';
								MSG_out[0]='M';
								MSG_out[1]='O';
								MSG_out[2]='G';
								MSG_out[3]='.';
								OK_send_flag=1;//���Ϳ���flag
								send_to_other_car_flag=0;//ֹͣ�㲥
								one_car_mode=1;
								FootWalk_ON_OFF=1;
								car_mode=run;
                                                                meet_ring_seq=7;
                                                                meet_seq=7;								
							}
							break;   
							
						}
						case 'I':  // �󳵽��յ���) ǰ������ᳵ��    ��ʼ����ǰ��
						{
							if(check_send_flag==0)
							{
								MSG_in[0]=0;
								MSG_in[1]=0;
								MSG_in[2]=0;
								MSG_in[3]=0;
								MSG_out[0]=0;
								MSG_out[1]=0;
								MSG_out[2]=0;
								MSG_out[3]=0;
								gpio_set(PTD15,1);
								
							}
							gpio_turn(PTD15);    // LED����
							
							break;
						}
						case 'A':  // �󳵽��յ���) ǰ������ᳵ��    ��ʼ����ǰ��(���յ�)
						{
							last_send_signal='O';
							MSG_out[0]='M';
							MSG_out[1]='O';
							MSG_out[2]='A';
							MSG_out[3]='.';
							OK_send_flag=1;//���Ϳ���flag
							send_to_other_car_flag=0;//ֹͣ�㲥
							car_number=after_car;
							buzzer_bibi(1,1);  
							break;
							
							
						}
						case 'B': //  (ǰ�����յ���) 79 70  �󳵵���ᳵ�� (ǰ���յ�)
						{
							last_send_signal='O';
							MSG_out[0]='M';
							MSG_out[1]='O';
							MSG_out[2]='B';
							MSG_out[3]='.';
							OK_send_flag=1;//���Ϳ���flag
							send_to_other_car_flag=0;//ֹͣ�㲥
							to_the_side=1;  
							car_mode=run; 
							meet_flag=1;
							buzzer_bibi(1,1);
							break; 
							
							
							
						}
						case 'C': // ����CC���л�ӦOC (�󳵽��յ���) 79 71    ��ʾ������
						{
							last_send_signal='O';
							MSG_out[0]='M';
							MSG_out[1]='O';
							MSG_out[2]='C';
							MSG_out[3]='.';
							OK_send_flag=1;//���Ϳ���flag
							send_to_other_car_flag=0;
							car_number=after_car;
							meet_flag=3;    
							buzzer_bibi(1,1);
							break; 
							
							
						}
						
						case 'D': // ����DD���л�ӦOD  69 (�󳵽��յ���)   �󳵵�֪ǰ���Ѿ������յ�
						{
							last_send_signal='O';
							MSG_out[0]='M';
							MSG_out[1]='O';
							MSG_out[2]='D';
							MSG_out[3]='.';
							OK_send_flag=1;//���Ϳ���flag
							send_to_other_car_flag=0;//ֹͣ�㲥
							to_the_side=2;  
							car_mode=run;//ǰ������
							meet_flag=4;    
							buzzer_bibi(1,1);
							break; 
							
							
						}
						
						case 'R': // ����EE���л�ӦOE  69 (ǰ�����յ���)    ң��������
						{
							last_send_signal='O';
							MSG_out[0]='M';
							MSG_out[1]='O';
							MSG_out[2]='R';
							MSG_out[3]='.';
							OK_send_flag=1;//���Ϳ���flag
							send_to_other_car_flag=0;//ֹͣ�㲥
							if(Meet_ON_OFF==1)
							{
								car_mode=run;
								buzzer_bibi(1,1);
							}
							break;
						}
						
						case 'X': // ����EE���л�ӦOE  69 (ǰ�����յ���)   ң����ͣ��
						{
							last_send_signal='O';
							MSG_out[0]='M';
							MSG_out[1]='O';
							MSG_out[2]='X';
							MSG_out[3]='.';
							OK_send_flag=1;//���Ϳ���flag
							send_to_other_car_flag=0;//ֹͣ�㲥
							car_number=after_car;

							buzzer_bibi(1,2);  
							break; 
						}
						case 'Y': // ����EE���л�ӦOE  69 (ǰ�����յ���)   ң����ͣ��
						{
							last_send_signal='O';
							MSG_out[0]='M';
							MSG_out[1]='O';
							MSG_out[2]='Y';
							MSG_out[3]='.';
							OK_send_flag=1;//���Ϳ���flag
                                                        yy_flag=1;
							car_mode=run;
                                                        
							meet_seq=3;
							send_to_other_car_flag=0;//ֹͣ�㲥
							break;
							
						}
						case 'Z': // ����EE���л�ӦOE  69 (ǰ�����յ���)   ң����ͣ��
						{
							last_send_signal='O';
							MSG_out[0]='M';
							MSG_out[1]='O';
							MSG_out[2]='Z';
							MSG_out[3]='.';
							OK_send_flag=1;//���Ϳ���flag
							send_to_other_car_flag=0;//ֹͣ�㲥
							meet_seq=2;
							meet_flag=2;
							FootWalk_ON_OFF=1;
							Meet_ON_OFF=0;
							break; 
						}
						
						default:
						{
							break;
						}
					}
				}
				else if(MSG_in[1]=='O') //���յ��Է����ҷ������źŵĻ�Ӧ
				{
					switch(MSG_in[2])
					{
						
						case 'A'://(ǰ�����յ���)
						{
							if(last_send_signal=='A')
							{
								send_to_other_car_flag=0;//ֹͣ�㲥
								
							}
							break;
							
						}
						case 'B'://(�󳵽��յ���)
						{
							if(last_send_signal=='B')
							{
								
								send_to_other_car_flag=0;//ֹͣ�㲥
								
							}
							break;
						}
						case 'C'://(ǰ�����յ���)
						{
							if(last_send_signal=='C')
							{
								send_to_other_car_flag=0;//ֹͣ�㲥
								
							}
							break;
						}
						
						case 'D'://(ǰ�����յ���)
						{
							if(last_send_signal=='D')
							{
								send_to_other_car_flag=0;//ֹͣ�㲥
								
							}
							break;
						}
						
						case 'E'://(�󳵽��յ���)
						{
							if(last_send_signal=='E')
							{
								send_to_other_car_flag=0;//ֹͣ�㲥
							}
							break;
						}
						case 'R'://(�󳵽��յ���)
						{
							if(last_send_signal=='R')
							{
								send_to_other_car_flag=0;//ֹͣ�㲥
							}
							break;
						}
						
						case 'G'://(�󳵽��յ���)
						{
							if(last_send_signal=='G')
							{
								send_to_other_car_flag=0;//ֹͣ�㲥
							}
							break;
						}
						case 'X'://(�󳵽��յ���)
						{
							if(last_send_signal=='X')
							{
								send_to_other_car_flag=0;//ֹͣ�㲥
							}
							break;
						}
						case 'Y'://(�󳵽��յ���)
						{
							if(last_send_signal=='Y')
							{
								send_to_other_car_flag=0;//ֹͣ�㲥
							}
							break;
						}
						case 'Z'://(�󳵽��յ���)
						{
							if(last_send_signal=='Z')
							{
								send_to_other_car_flag=0;//ֹͣ�㲥
							}
							break;
						}
						default:
						{
							break;
						}
						
					}
				}
				
			}
			else {recv_data_p=0;}
		}
	}
	
}

void Communication_Out()  
{
	static uint8 send_count=0;
	if(send_to_other_car_flag==1)
	{
		uart_putbuff(UART3,MSG_out,sizeof(MSG_out));
		
	}
	if(OK_send_flag==1)
	{
		uart_putbuff(UART3,MSG_out,sizeof(MSG_out));
		send_count+=1;
		if(send_count==8)
		{
			OK_send_flag=0;
			send_count=0;
		}
		
	}
}
