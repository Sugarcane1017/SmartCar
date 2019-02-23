#ifndef __INCLUDE_H__
#define __INCLUDE_H__

#include  "common.h"

/*
 * Include �û��Զ����ͷ�ļ�
 */
#include  "MK60_wdog.h"
#include  "MK60_gpio.h"     //IO�ڲ���
#include  "MK60_uart.h"     //����
#include  "MK60_SysTick.h"
#include  "MK60_lptmr.h"    //�͹��Ķ�ʱ��(��ʱ)
#include  "MK60_i2c.h"      //I2C
#include  "MK60_ftm.h"      //FTM
#include  "MK60_pit.h"      //PIT
#include  "MK60_adc.h"      //ADC
#include  "MK60_dac.h"      //DAC
#include  "MK60_dma.h"      //DMA
#include  "MK60_FLASH.h"    //FLASH
#include  "MK60DZ10.h"

	 
#include  "VCAN_computer.h"
#include  "VCAN_OV7725_Eagle.h"
#include  "VCAN_OV7725_REG.h"
#include  "VCAN_camera.h"       //����ͷ��ͷ�ļ�
#include  "LQ_OLED.h"

#include  "debug.h"          
#include  "general.h"          
#include  "init.h"  
#include  "isr.h"  
#include  "key.h"  
#include  "magnetic.h"  
#include  "camera.h"
#include  "control.h"
#include  "message.h"
#include  "meetcar.h"
#include  "fuzzy.h"


#endif  //__INCLUDE_H__
