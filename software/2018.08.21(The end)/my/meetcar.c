#include "include.h"
/*******************************************
* ��    �ܣ�ֱ���ᳵʶ��
* ��    ������Ϊֱ��(���߷���С) && ���߷�����Դ� && ����ƽ������Դ�  && ���߰��ݵ�϶�
********************************************/

//--------------------ͨѶ--------------------//
extern uint8 CMD_in[5];  //ͨѶ����
extern uint8 MSG_in[4];  //ͨѶ����
extern uint8 MSG_out[4]; //ͨѶ����
extern uint8 last_send_signal; //�ϴη����źż�д�������ж��Ƿ���ԹضϷ�����һ������flag��
extern uint8 OK_send_flag;
extern uint8 send_to_other_car_flag; //�������ⷢ�͵�flag
extern MEET_CAR_NUMBER_e car_number; //ǰ���󳵱�־λ
extern uint8 recv_data_p;

extern uint8 to_the_side;
extern CAR_STATUS_e car_mode;  //����״̬
extern uint8 edge[60][2];
extern uint8 center_line[60];
extern uint8 Cam2Mag_Weight;

extern uint8 img[CAMERA_H][CAMERA_W];

extern uint16 Servo_Duty;
//************************�ᳵ��************************//

//---------------------ƽ����-------------------//
extern int16 Servo_Turn;
extern uint16 smoothness_left;
extern uint16 smoothness_right;
extern uint16 smoothness_sum;

//---------------------���߷���-------------------//
extern uint16 meet_edge_left[19];  //����������
extern uint32 variance_sum_left;   //���������ۼ���
extern uint16 variance_aver_left;  //����ƽ����
extern uint16 variance_left;       //����

//---------------------���߷���-------------------//
extern uint16 meet_edge_right[19];//�ᳵ����������
extern uint32 variance_sum_right;   //���������ۼ���
extern uint16 variance_aver_right;  //����ƽ����
extern uint16 variance_right;       //����

//---------------------���߷���-------------------//
extern uint16 variance_sum_center;   //���������ۼ���
extern uint16 variance_aver_center;  //����ƽ����
extern uint16 variance_center;       //����

//---------------------���߰���-----------------//
extern uint16 corner_dian_r;
extern uint16 corner_dian_l;
extern uint16 corner_meet_rn;
extern uint16 corner_meet_ln;

//---------------------����-----------------//
extern uint16 Pulse_Counter_R;
extern uint16 Pulse_Counter_L;
extern uint16 Length_L;  //���㳤��
extern uint16 Length_R;
extern uint16 long_count_cjx;

//---------------------��־λ������-----------------//
extern int16 Servo_Turn;
extern uint8 meet_flag;         //�ᳵ״̬λ
extern int16 meet_turn;  

extern uint8 Meet_ON_OFF;       //�ᳵ�ܿ���
extern uint8 Meet_Action_flag;  //�ᳵ��־λ
extern uint8 real_stop_flag;     //����ͣ����־λ

extern uint8 FootWalk_Flag;      //�����߱�־λ
extern uint8 FootWalk_ON_OFF;   //�����߿���
extern uint8 WhiteDot_Count;  //�����ߺںںڰװװ���ʼ�׵�
extern uint8 WhiteDot_CountLn;  //�����ߺںںڰװװ���ʼ�׵�


//---------------------Բ���ᳵ��־λ������-----------------//

extern uint16 var_left;
extern uint16 var_right;
extern uint16 var_middle;
extern ROAD_STATUS_e road_flag;
extern uint8 delay_run_flag;
extern uint8 one_car_mode;
extern uint8 first_meet_flag;
extern int16 camera_integral_center;
extern MEET_PLACE_e meet_choose;
extern uint8 zz_flag;
extern uint8 meet_seq;
extern uint8 polarization_ON_OFF; 
//---------------------------�ᳵ--------------------------------//
/*******************************************
* �� �� ����First_Meet
* ��    �ܣ���㷢������
* ���������none
* �� �� ֵ��none
* Ŀ    �ģ��رհ�������ᳵ��ʶ����ʱ��ŷ���
********************************************/
void First_Meet()   //��һ��(����)�ᳵ   ��ʱ�ᳵ
{
	static uint16 delay_count=0;//��ʱ4s����
	static uint8 first_meet_count=0;
	static uint8 first_run_flag=0;
	static uint8 MEET_STATUS=0;
	if(Meet_ON_OFF==1){MEET_STATUS=1;}
	if(first_meet_flag==0 && car_mode==run)
	{
		if(delay_run_flag==0)
		{
			delay_count++;
			LED_ALL_ON();
			last_send_signal='R';
			MSG_out[0]='M';
			MSG_out[1]='R';
			MSG_out[2]='R';
			MSG_out[3]='.';
			buzzer_bibi(3,2);
			send_to_other_car_flag=1;//���Ϳ���flag
			OK_send_flag=0;
		}
		if(delay_count>=100)
		{
			delay_run_flag=1;
		}
		if(delay_run_flag==1)
		{
			LED_ALL_OFF();
			to_the_side=1; 
			first_meet_count++;
			if(first_run_flag==0)//����һ��������RUN
			{
				first_run_flag=1;
			}
			if(first_meet_count<=40)
			{
				Cam2Mag_Weight=0;  //�ر�����ͷ
				Meet_ON_OFF=0;     //ǿ�ƹرջᳵ
				FootWalk_ON_OFF=0;
			}
			else if(first_meet_count>40 && first_meet_count<150)//����ȫ�����ᳵ��  ������
			{
				Cam2Mag_Weight=flash_read(servo_sector , 76, uint8)+((float)(flash_read(servo_sector , 80, uint8))*(0.1));;  //��������ͷ
				to_the_side=0;
				Meet_ON_OFF=0;     //ǿ�ƹرջᳵ
				FootWalk_ON_OFF=0;
			}
			else 
			{
				if(MEET_STATUS==1){Meet_ON_OFF=1;}
				else {Meet_ON_OFF=0;}
				first_meet_flag=1;//һ��ֻ��һ��
				to_the_side=0;
				Cam2Mag_Weight=flash_read(servo_sector , 76, uint8)+((float)(flash_read(servo_sector , 80, uint8))*(0.1));;  //��������ͷ 
			}
		}
		
	}
	
}
/*******************************************
* �� �� ����Straight_Meet_Judge
* ��    �ܣ�ֱ���ᳵ���ж�
* ���������none
* �� �� ֵ��none
* Ŀ    �ģ��ж�ֱ���ᳵ����������ֹ����
********************************************/
void Straight_Meet_Judge()
{
	static uint8 Meet_Action_flag_count=0;
	if(variance_center<=50)    //�ӽ�ֱ��
	{
		if(variance_left>critical_val && variance_left<500 &&variance_right>critical_val && variance_right<500)   
		{
			if(smoothness_left>critical_val && smoothness_left<400 && smoothness_right>critical_val &&smoothness_right<400&&smoothness_sum<800)  //ֱ����ֱ���ᳵ����  ����
			{   
				if(corner_meet_rn>=2 && corner_meet_rn<=5 && corner_meet_ln>=2 && corner_meet_ln<=5)
				{
					Meet_Action_flag_count++;
					if(Meet_Action_flag_count>=2)  //���� ��η�����
					{
						Meet_Action_flag=1;
						Meet_Action_flag_count=0;
					}
				}
				else{Meet_Action_flag=0;}//����
			}
			else{Meet_Action_flag=0;Meet_Action_flag_count=0;}
		}
		else{Meet_Action_flag=0;Meet_Action_flag_count=0;}
	}
}

/*******************************************
* �� �� ����Meet_Action
* ��    �ܣ�ֱ���ᳵ���ж�
* ���������none
* �� �� ֵ��none
* Ŀ    �ģ��ж�ֱ���ᳵ������������ֹ����
********************************************/
void Meet_Action()
{
	if(car_number==un_know  && meet_flag==0)//Ϊ  ǰ��ʱ��⵽ ֹͣ
	{
                Cam2Mag_Weight=0;
		gpio_set (PTC0, 0);    // LED����
		last_send_signal='A';
		MSG_out[0]='M';        //��B�������Ѿ�����
		MSG_out[1]='A';        //��B�������Ѿ�����65
		MSG_out[2]='A';        //��B�������Ѿ�����65
		MSG_out[3]='.';        //��B�������Ѿ�����
		send_to_other_car_flag=1;
		OK_send_flag=0;
		car_number=front_car;  //��Ϊǰ��
                
                if(polarization_ON_OFF==1)  //�����ش�  ����ƫ��
                {
                  to_the_side=1;
                }
		car_mode=meet_reversal;      //ͣ���ȴ�
		Meet_ON_OFF=0;         //�ر�ֱ���ᳵ�ж�
	}
	
	if(car_number==after_car && meet_flag==0)
	{ 
                Cam2Mag_Weight=0;
		gpio_set (PTC0, 0);    // LED����
		car_mode=meet_reversal;
		meet_flag=1;    
		Meet_ON_OFF=0;      //�ر�ֱ���ᳵ�ж�
	}
	
}

/*******************************************
* �� �� ����Out_Straight_Meet
* ��    �ܣ���ֱ���ᳵ������
* ���������none
* �� �� ֵ��none
* Ŀ    �ģ��������Ǿ��룬���0.8M����Ż��� 
********************************************/
void Out_Straight_Meet()// ����֪���ᳵ������ʾ������  �������ɼ����� 
{
  static uint8 clear_zero_flag=0;
	//--------------�������ɼ� �����Ҫ���м�ᳵ��  meet_flag ��Ϊ2 ----------//
	if(meet_flag==1 && meet_choose==meet_straight)  // �󳵳��ᳵ��
	{
		Length_L+=(Pulse_Counter_L*20/1165);
		Length_R+=(Pulse_Counter_R*20/1165);
		Cam2Mag_Weight=0;	
		if(car_number==after_car )  // ��ʾ��һ����
		{
			if(real_stop_flag==1)
			{
				last_send_signal='B';
				MSG_out[0]='M';        //��B�������Ѿ�����
				MSG_out[1]='B';        //��B�������Ѿ�����
				MSG_out[2]='B';        //��B�������Ѿ�����
				MSG_out[3]='.';        //��B�������Ѿ�����
				send_to_other_car_flag=1;
				OK_send_flag=0;
				car_mode=run;  //����
			}
			to_the_side=1;
		}
		
		if(((Length_R+Length_L)/2) >=90)
		{
			to_the_side=0;
			buzzer_bibi(3,3);
			Cam2Mag_Weight=flash_read(servo_sector , 76, uint8)+((float)(flash_read(servo_sector , 80, uint8))*(0.1));  //����ͷ
			Length_L=0; 
			Length_R=0;  //�Ǿ�������
			meet_flag=2;  //    �����յ�ᳵ���� 
			FootWalk_ON_OFF=1;   //�򿪰�����
		}  
	}  
	
	//--------------�������ɼ� �����Ҫ���յ�ᳵ��  meet_flag ��Ϊ5 ----------//
	if(meet_flag==4)  // 
	{
          
            if(clear_zero_flag==0)
            {
              Length_L=0;
              Length_R=0;
              clear_zero_flag=1;   
            }
		Length_L+=(Pulse_Counter_L*20/1165);
		Length_R+=(Pulse_Counter_R*20/1165);
		Cam2Mag_Weight=0;
		if(car_number==after_car)  // ǰ����ʾ��һ����
		{
			car_mode=run;  //����  //�ر�����ͷ
		}
		if(((Length_R+Length_L)/2) >long_count_cjx)    
		{
			to_the_side=0;
			Cam2Mag_Weight=flash_read(servo_sector , 76, uint8)+((float)(flash_read(servo_sector , 80, uint8))*(0.1));  //����ͷ
			buzzer_bibi(3,3);
		}
		if(((Length_R+Length_L)/2) >130)    
		{
			to_the_side=0;
			meet_flag=5;  //    �����յ�ᳵ���� 
			car_mode=meet_reversal;  
			
		}   
	}
}

/*******************************************
* �� �� ����sunken_edge
* ��    �ܣ�ɨ����߰���
* ���������none
* �� �� ֵ��none
* Ŀ    �ģ�ֱ���ᳵ�������԰�������㣬��ֹ������Ԫ������ 
********************************************/
void sunken_edge()   //���߰���
{
	corner_meet_ln=0;
	corner_meet_rn=0;
	corner_dian_r=0;
	corner_dian_l=0;
	//-----------------------------���ᳵ�����ߵ�----------------------------------//
	for(int i =0; i<19; i++)   //
	{
		corner_dian_r=abs(meet_edge_right[i+1]-meet_edge_right[i]);
		
		if(corner_dian_r>=6)
		{corner_meet_rn++;}
		
		corner_dian_l=abs(meet_edge_left[i]-meet_edge_left[i+1]);
		
		if(corner_dian_l>=6)
		{corner_meet_ln++;}	
	}
	//-----------------------------���ᳵ�����ߵ�----------------------------------//
}

/*******************************************
* �� �� ����variance_judge_center
* ��    �ܣ����߷���
* ���������none
* �� �� ֵ��none
* Ŀ    �ģ��ж��Ƿ���Ϊֱ�� 
********************************************/
void variance_judge_center()//���߷����ж�
{
	uint8 n=17;     //��������
	variance_sum_center=0;   //���������ۼ���
	variance_aver_center=0;  //����ƽ����
	variance_center=0;       //����
	for(int i=13;i<30;i++)   //��Ч�ж�����   //  >������<   >13-30(��Ч��)<   >������<
	{
		variance_sum_center+=center_line[i];  //�����ۼ�
	}
	variance_aver_center = variance_sum_center/n;  //��ȡƽ�� 
	for(int i=13;i<30;i++)
	{
		variance_center+=(  (abs(center_line[i]-variance_aver_center))  *  (abs(center_line[i]-variance_aver_center)) );
	}
	variance_center/=(n);
	
}

/*******************************************
* �� �� ����Smoothness_Judge
* ��    �ܣ�����ƽ�����ж�
* ���������none
* �� �� ֵ��none
* Ŀ    �ģ��жϱ����Ƿ�ֲ�
********************************************/
void Smoothness_Judge()//���ƽ����
{ 
	uint16 temp_l=0,temp_r=0;
	smoothness_left=0;
	smoothness_right=0;
	smoothness_sum=0;
	for(int i=11;i<=30;i++)   //��Ч�ж�����
	{
		if(edge[i][0]!=0)
		{		
			temp_l=abs(edge[i][0]-edge[i+1][0]);
		}
		if(edge[i][1]!=159)
		{
			temp_r=abs(edge[i][1]-edge[i+1][1]);
		}
		smoothness_left +=(temp_l*temp_l);  
		smoothness_right+=(temp_r*temp_r);
	}
	smoothness_sum=smoothness_left+smoothness_right;
}

void  variance_judge_left()//�����  �����ж�   
{
	uint8 n=19;               //��������
	
	variance_sum_left=0;   //���������ۼ���
	variance_aver_left=0;  //����ƽ����
	variance_left=0;       //����
	for(int i=11;i<30;i++)   //��Ч�ж�����   //  >������<   >11-30(��Ч��)<   >�ᳵ������<
	{
		meet_edge_left[i-11]=edge[i][0];  //���ݽ�ά
		// if(meet_edge_left[i-13]==0){n--;}
	}
	
	for(int i=11;i<30;i++)   //��Ч�ж�����   //  >������<   >11-30(��Ч��)<   >�ᳵ������<
	{
		variance_sum_left+=meet_edge_left[i-11];  //�����ۼ�
	}
	variance_aver_left = variance_sum_left/n;
	
	for(int i=0;i<19;i++)
	{
		variance_left+=(  (abs(meet_edge_left[i]-variance_aver_left)) * (abs(meet_edge_left[i]-variance_aver_left))  );
	}
	// variance_left-=((variance_aver_left*variance_aver_left)*(17-n));//��ȥ��ֵ
	variance_left/=(n);
	
}


void  variance_judge_right()//�ұ���  �����ж�   
{
	uint8 n=19;               //��������
	
	variance_sum_right=0;   //���������ۼ���
	variance_aver_right=0;  //����ƽ����
	variance_right=0;       //����
	
	for(int i=11;i<30;i++)   //��Ч�ж�����   //  >������<   >11-30(��Ч��)<   >������<
	{
		meet_edge_right[i-11]=edge[i][1];  //���ݽ�ά
		//  if(meet_edge_right[i-13]==79){meet_edge_right[i-13]=0;n--;}
	}
	
	for(int i=11;i<30;i++)   //��Ч�ж�����   //  >������<   >11-30(��Ч��)<   >������<
	{
		variance_sum_right+=meet_edge_right[i-11];  //�����ۼ�
	}
	variance_aver_right = variance_sum_right/n;//����ƽ��
	
	for(int i=0;i<19;i++)
	{
		variance_right+=(  (abs(meet_edge_right[i]-variance_aver_right)) * (abs(meet_edge_right[i]-variance_aver_right))  );//��ֵ��ƽ��
	}
	// variance_right-=(  ((variance_aver_right)*(variance_aver_right)) * (17-n));//��ȥ��ֵ
	variance_right/=(n);
	
	
	
}

/*******************************************
* �� �� ����FootWalk_scanning
* ��    �ܣ���ֱɨ�� ����������  
* ���������none
* �� �� ֵ��none
* Ŀ    �ģ�ɨ�������  ����յ�ᳵ
********************************************/
void FootWalk_scanning()
{
	uint8 i=0,j=0;   //�ӿ�汾
	for(i=45;i>=11;i--)
	{
                WhiteDot_Count=0;//--
		WhiteDot_CountLn=0;
		for(j=40;j<120;j++)
		{
			if(img[i][j]==0 && img[i][j+1]==0 && img[i][j+2]==0 && img[i][j+3]==1 && img[i][j+4]==1 && img[i][j+5]==1 )  //�ٺٺٰװװ�
			{
				WhiteDot_Count++;  //�����
				j+=4;
			}
                   
			if(WhiteDot_Count>=6)
			{
                                WhiteDot_CountLn++; //������
				gpio_set (PTA17, 0);    // LED����
				//FootWalk_Flag=1;
			}
                        
                        //--
                        if(WhiteDot_CountLn>=3)   //��������Ϊ��ȷʶ��
                        {
                          FootWalk_Flag=1;
                          buzzer_once();
                        }
                        //--
		} 
	}
          //���߷���edge[i][0]+edge[i][1]  �ӱ���ɨ��
        /*uint8 i=0,j=0; 
	for(i=50;i>=11;i--)
	{
		WhiteDot_CountLn=0;
		for(j=edge[i][0];j<edge[i][1];j++)
		{
			if(img[i][j]==0 && img[i][j+1]==0 && img[i][j+2]==0 && img[i][j+3]==1 && img[i][j+4]==1 && img[i][j+5]==1 )  //�ٺٺٰװװ�
			{
				WhiteDot_CountLn++;
				j+=4;
			}
			if(WhiteDot_CountLn>=5)
			{
				gpio_set (PTA17, 0);    // LED����
				FootWalk_Flag=1;
                                buzzer_once();
			}
		} 
	}*/
             
        /*  //ԭʼ����
        uint8 i=0,j=0; 
	for(i=18;i>=11;i--)
	{
		WhiteDot_CountLn=0;
		for(j=40;j<120;j++)
		{
			if(img[i][j]==0 && img[i][j+1]==0 && img[i][j+2]==0 && img[i][j+3]==1 && img[i][j+4]==1 && img[i][j+5]==1 )  //�ٺٺٰװװ�
			{
				WhiteDot_CountLn++;
				j+=4;
			}
			if(WhiteDot_CountLn>=6)
			{
				gpio_set (PTA17, 0);    // LED����
				FootWalk_Flag=1;
			}
		} 
	}
        */
	
	if(FootWalk_Flag == 1&& one_car_mode==0)
	{
		Cam2Mag_Weight=0;
		if(meet_flag==2)   //˭���  �յ�ᳵ��   END����
		{ 
			gpio_set (PTC0, 1);    // LEDϨ��
			last_send_signal='C';
			MSG_out[0]='M';        //��B�������Ѿ�����
			MSG_out[1]='C';        //��B�������Ѿ�����67
			MSG_out[2]='C';        //��B�������Ѿ�����67
			MSG_out[3]='.';        //��B�������Ѿ�����
			send_to_other_car_flag=1;
			OK_send_flag=0;
                        Cam2Mag_Weight=0;
			car_number=front_car;       //��Ϊǰ��
			to_the_side=2;
			car_mode=meet_reversal;
			meet_flag=3;
		}
		
		if(car_number==after_car && meet_flag==3)//�󳵵����յ�ᳵ��
		{ 
			gpio_set (PTC0, 1);  // LEDϨ��
			last_send_signal='D';
			MSG_out[0]='M';        //��B�������Ѿ�����
			MSG_out[1]='D';        //��B�������Ѿ�����67
			MSG_out[2]='D';        //��B�������Ѿ�����67
			MSG_out[3]='.';        //��B�������Ѿ�����
			send_to_other_car_flag=1;
			OK_send_flag=0;
                        Cam2Mag_Weight=0;
			meet_flag=4;
			to_the_side=2;
			car_mode=stop;
		}         
	}
	if(FootWalk_Flag == 1&& one_car_mode==1)
	{
		Length_L+=(Pulse_Counter_L*20/1165);
		Length_R+=(Pulse_Counter_R*20/1165);
                OK_send_flag=0;
		if(((Length_R+Length_L)/2) >=100)    
		{
			car_mode=meet_reversal;  		
		}   
	}
}



void circle_reverse()
{
	if(real_stop_flag==1 && car_number==front_car  && meet_seq==4 ) //��ǰ��������
	{
		last_send_signal='X';
		MSG_out[0]='M';        
		MSG_out[1]='X';        
		MSG_out[2]='X';        
		MSG_out[3]='.';        
		send_to_other_car_flag=1;
		OK_send_flag=0;
		
	}
	if(car_number==after_car && real_stop_flag==1 &&meet_seq==1) //(�󳵶���)
	{
		last_send_signal='Y';
		MSG_out[0]='M';        
		MSG_out[1]='Y';        
		MSG_out[2]='Y';       
		MSG_out[3]='.';        
		send_to_other_car_flag=1;
		OK_send_flag=0;
	}
	

	
	if(car_number==front_car && zz_flag==1)  //��ǰ��������
	{
		
			last_send_signal='Z';
			MSG_out[0]='M';       
			MSG_out[1]='Z';     
			MSG_out[2]='Z';       
			MSG_out[3]='.';       
			send_to_other_car_flag=1;
			OK_send_flag=0;
			car_number=un_know;
			meet_flag=2;
			FootWalk_ON_OFF=1;
			Meet_ON_OFF=0;
			camera_circle_clear();


	}
}