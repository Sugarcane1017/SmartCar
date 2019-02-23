#include "include.h"



uint8 img[CAMERA_H][CAMERA_W]; 
uint8 imgbuff[CAMERA_SIZE];//����ͷ����
uint8 send_picture[CAMERA_SIZE];
uint8 sending_flag=0;//����ͷ�������


float S_P; //���P
float S_D; //���D
float M_L_P=M_P; //����P
float M_L_I=M_I; //����D
float M_R_P=M_P; //�ҵ��P 
float M_R_I=M_I; //�ҵ��D
float C_P; //cameraP
float C_D; //cameraD
float Cam2Mag_Weight;//����ͷ�Ե��Ȩ��//10Ϊ��ֵ

volatile MENU_LIST_e MENU =picture; //�˵�
volatile CAR_STATUS_e car_mode = stop;  //����״̬
volatile ROAD_STATUS_e road_flag=straight; // ����λ�ã�Բ����ʮ�֣������ֱ����

to_speed speed_expect={0}; //��š�����ͷ�����ٶ�

ring_missage ring_info={0};

uint8 buzzer_time=0;//������
uint8 buzzer_count=0;//������
uint8 buzzer_number=0;//������

uint8 page =1; // LCD ҳ
uint8 row=1;  // LCD ��
uint8 unit=1;//��λ

uint16 integer=0,decimal=0;//������С�����֣�����flash��

uint16 var_left=0; //��һ�������ֵ
uint16 var_right=0;
uint16 var_middle=0;
uint16 var_left_last=0;
uint16 var_right_last=0;
uint16 var_middle_last=0;

uint8 var_max[3]={0,0,0}; //��һ�����ֵ
uint8 var_min[3]={0,0,0};//��һ����Сֵ

int16 Cam_duty=0;//ƫ��*P D//�����
int16 Mag_duty=0;//ƫ��*P D//�����

int16 Servo_Offset=0;

int16 deviation=0;  //���ƫ��
int16 last_deviation=0; //�ϴε��ƫ��

uint8 L_bubble=0; //ADʵ�ʲɼ�ֵ��0~255��
uint8 R_bubble=0; 
uint8 M_bubble=0;

uint8 BM_L;   //��1   Ϊ��ת  
uint8 BM_R;   //��0   Ϊ��ת

int16 Get_SpeedL=0; //�������ɼ������ٶ�
int16 Get_SpeedR=0;

uint16 normal_speed; //��������ٶ�
uint16 min_speed=200; //��С�����ٶ�//Բ���ٶ�
moty_duty run_duty={0};//����ftm����ٶ�
  
int16 Servo_Duty_Last=Servo_Duty_Md; //������
int16 Servo_Duty=Servo_Duty_Md;

uint8 A_Car=1;
uint8 edge[60][2]; //����ͷ����
uint8 center_line[60]; // ����ͷ���ߣ��ߣ�
int16 camera_center=0; // ����ͷ���ߣ�ƫ��ֵ��//��Զ��Ȩ��
int16 camera_last_center=0; 
int16 camera_integral_center=0; //����ͷ����һ�λ���
//int16 camera_integral_center_2=0;  //����ͷ���߶��λ���
            //Բ�������д��
float Circle_W_In=7.5;                //�жϵ�Բ��  ����ͷȨ��
int8 edge_der1[2][40]={0};//����һ�ε���
int8 edge_der2[2][40]={0};//���ض��ε���
uint8 edge_start[80][2]={0};  //���ذ�ɫ��������
uint8 circle_edge_start[4];//Բ�������־��������0,2,������1,3
uint8 Line_sum[2];
uint8 straight_go_flag;
uint8 Circle_fill_line_flag=0;;
uint8 circle_point[2]={0};//Բ�������־��������0,,������1
uint8 ring_pass_number=0;


uint8 edge_sum_left;//���غ�ɫ����
uint8 edge_sum_right;//���غ�ɫ����
uint16 edge_black[2];
uint16 edge_Int_R=0;//���شֲڶ�
uint16 edge_Int_L=0;//���شֲڶ�


uint8 camera_integral_flag=0;//Բ������
uint8 Om_turn_flag=0;

uint8 system_clock=0;//��ʱ
uint8 system_old_clock=0; //��ʱ
uint8 camera_frequency=0;//��֡����
uint8 camera_count=0;//��֡����

uint8 fitting_over_flag=1;
uint8 Circle_ON_OFF=0;
MEET_PLACE_e meet_choose;
uint8 meet_ring_number;


uint8 Circle_go_flag=0;

MEET_CAR_NUMBER_e car_number=un_know; //ǰ���󳵱�־λ
//**********************************�ᳵ��******************************//

//---------------------ƽ����-------------------//
uint16 smoothness_left=0;
uint16 smoothness_right=0;
uint16 smoothness_sum=0;

//---------------------���߷���-------------------//
uint16 meet_edge_left[19]={0};  //����������
uint32 variance_sum_left=0;   //���������ۼ���
uint16 variance_aver_left=0;  //����ƽ����
uint16 variance_left=0;       //����

//---------------------���߷���-------------------//
uint16 meet_edge_right[19]={0};//�ᳵ����������
uint32 variance_sum_right=0;   //���������ۼ���
uint16 variance_aver_right=0;  //����ƽ����
uint16 variance_right=0;       //����

//---------------------���߷���-------------------//
uint16 variance_sum_center=0;   //���������ۼ���
uint16 variance_aver_center=0;  //����ƽ����
uint16 variance_center=0;       //����

//---------------------���߰���-----------------//
uint16 corner_dian_r=0;
uint16 corner_dian_l=0;
uint16 corner_meet_rn=0;
uint16 corner_meet_ln=0;

//---------------------����-----------------//
uint16 Pulse_Counter_R=0;
uint16 Pulse_Counter_L=0;
uint16 Length_L=0;  //���㳤��
uint16 Length_R=0;

//---------------------��־λ������-----------------//
int16 Servo_Turn=0;
uint8 meet_flag=0;         //�ᳵ״̬λ
int16 meet_turn=0;  


uint8 Meet_ON_OFF=0;       //�ᳵ�ܿ���
uint8 Meet_Action_flag=0;  //�ᳵ��־λ


uint8 FootWalk_Flag=0;      //�����߱�־λ
uint8 FootWalk_ON_OFF=0;   //�����߿���
uint8 WhiteDot_Count=0;  //�����ߺںںڰװװ���ʼ�׵�

uint8 WhiteDot_CountLn=0;  //�����ߺںںڰװװ���ʼ�׵�
uint8 real_stop_flag=0;    //����ͣ����־λ

//--------------------ͨѶ--------------------//
uint8 CMD_in[5]={0};  //ͨѶ����
uint8 MSG_in[4]={0};  //ͨѶ����
uint8 MSG_out[4]={0}; //ͨѶ����
uint8 last_send_signal='O'; //�ϴη����źż�д�������ж��Ƿ���ԹضϷ�����һ������flag��
uint8 send_to_other_car_flag=0; //�������ⷢ�͵�flag
uint8 recv_data_p=0;
uint8 check_send_flag=1; //У��zigbee�����Ƿ�������



uint16 white_num=0;
uint8 white_proportion=0;   //�׵�ռ��
uint8 ramp_flag=0;
int16 ramp_count=0;
uint8 to_the_side=0;//����
uint8 side_high[160]={0};//0-60
uint8 delay_run_flag=0;
uint8 one_car_mode=0;
uint8 first_meet_flag=0;
uint8 OK_send_flag=0;

int16 var_camera_center=0;
int16 var_last_camera_center=0;

uint16 temp_time_c=0;
uint8 Mag_insurance; //��ű���
uint8 Circle_size=0;//0��1С2��
uint16 ring_size=0;

uint8 Go_back_flag=0;
uint8 meet_ring_seq=0;
uint8 meet_seq=6;
uint8 meet_zk_count=0;
uint8 yy_flag=0;
uint8 zz_flag=0;
uint8 ring_size_plus=0;

int16 Servo_dir_n[20]={0};
int16  Servo_dir=0;
uint8 Insurance_flag=0;
uint8 Insurance_dir=3;

uint16 long_count_cjx;
uint16 add_deviation_cjx;

//--------------------ʮ��--------------------//
uint16 crossl_f=0;
uint16 crossr_f=0;
uint16 crossl_b=0;
uint16 crossr_b=0;

uint8 death_time_flag=0;
uint8 polarization_ON_OFF=0;  //ֱ���ᳵƫ�ÿ���

void ware_test()
{   

	static int16 t_list[8]= {0};
	t_list[0] = Cam_duty;//edge_sum_left;//edge_Int_R+edge_Int_L;//camera_center;
	t_list[1] = Mag_duty;//edge_Int_R;//(edge_sum_left-edge_sum_right)*7;
	t_list[2] = 180;//Servo_Offset;
	t_list[3] = white_proportion*2;//-(Servo_Duty-Servo_Duty_Md);
	t_list[4] = var_left+var_right+var_middle;//corner_meet_rn;//edge_start[1];//
	t_list[5] = var_left;
	t_list[6] = var_middle;//camera_forecast_center;//
	t_list[7] = var_right;//camera_center;
	
        
        
	vcan_sendware(t_list,sizeof(t_list));
}




void buzzer_once()
{
buzzer_time=5;
buzzer_number=5;
buzzer_count=1;

}  
void buzzer_bibi(uint8 t,uint8 l)
{
buzzer_time=l*5;
buzzer_number=l*5;
buzzer_count=t*2;

}  
void buzzer_ring()
{
  
if(buzzer_count>=1)
{  
	if(buzzer_number>=1)
	{	
          if(buzzer_count%2==1)   {gpio_set(PTB23,0);}
          else                    {gpio_set(PTB23,1);}
          buzzer_number--;	
	}
	else
	{
          buzzer_number=buzzer_time;
          buzzer_count--;
	}
}
else
{
  gpio_set(PTB23,1);
  buzzer_time=0;
  buzzer_count=0;
}

}


void time_count()
{

 static uint8 system_count=0;
  
  system_count++;
  
  if(system_count>=201) 
  { 
    
    camera_frequency=camera_count;//��ǰ��ʾ֡��
    camera_count=0;
    system_count=0;
    system_clock++;
  }
  if(system_clock==61)
  {
    system_clock=0;
  }
}

void dma_count()
{
  camera_count++;
}


void LED_ALL_ON()
{
  	//LED
        gpio_set (PTC0,0);    
	gpio_set (PTD15,0);    
	gpio_set(PTE26,0);   
	gpio_set (PTA17,0);    
}

void LED_ALL_OFF()
{
        gpio_set (PTC0,1);    
	gpio_set (PTD15,1);    
	gpio_set(PTE26,1);   
	gpio_set (PTA17,1);    
}