<<<<<<< HEAD
# 航行器控制中心

#### 介绍
{**以下是码云平台说明，您可以替换此简介**
码云是开源中国推出的基于 Git 的代码托管平台（同时支持 SVN）。专为开发者提供稳定、高效、安全的云端软件开发协作平台
无论是个人、团队、或是企业，都能够用码云实现代码托管、项目管理、协作开发。企业项目请看 [https://gitee.com/enterprises](https://gitee.com/enterprises)}


该航控 基于国产 RT-Thread 实时操作系统，目前完成外设驱动及数据采集，后续为姿态算法 与 抗洋流算法.

#### 软件架构
软件架构说明
```c

RT-Thread 
├──STM32F407ZGT6                  
│   └──Peripherals
│       ├── RGB [IO]   
│       ├── KEY [IO] 
│       ├── BUZZER [IO]             
│       ├── OLED [Software SPI]       
│       ├── Voltage Detection [ADC]             
│       ├── Wifi [UART]             
│       ├── Bluetooth [UART]       
│       ├── Nine axis gyroscope [UART]
│       ├── USB to serial port [CP2102 UART Bridge]
│       ├── OV2640 Camera [unfinished]
│       └── Be continued     
├── hardware
├── README.md  
├── docs           //documents      
└── Be continued  

```

#### 安装教程

1. KEIL5
2. STM32F4XX package
3. RT-Thread

#### 使用说明

1. NULL available
2. NULL available
3. NULL available
=======
# 13th-NXP-JMU双车会车2018

#### 介绍
2018 JMU双车会车所有资料

#### 软件架构
软件架构说明


#### 安装教程

1. xxxx
2. xxxx
3. xxxx

#### 使用说明

1. xxxx
2. xxxx
3. xxxx
>>>>>>> d023a4061f82c081799404d46ece40211858601f

#### 参与贡献

1. Fork 本仓库
2. 新建 Feat_xxx 分支
3. 提交代码
4. 新建 Pull Request


#### 码云特技

1. 使用 Readme\_XXX.md 来支持不同的语言，例如 Readme\_en.md, Readme\_zh.md
2. 码云官方博客 [blog.gitee.com](https://blog.gitee.com)
3. 你可以 [https://gitee.com/explore](https://gitee.com/explore) 这个地址来了解码云上的优秀开源项目
4. [GVP](https://gitee.com/gvp) 全称是码云最有价值开源项目，是码云综合评定出的优秀开源项目
5. 码云官方提供的使用手册 [https://gitee.com/help](https://gitee.com/help)
<<<<<<< HEAD
6. 码云封面人物是一档用来展示码云会员风采的栏目 [https://gitee.com/gitee-stars/](https://gitee.com/gitee-stars/)


=======
6. 码云封面人物是一档用来展示码云会员风采的栏目 [https://gitee.com/gitee-stars/](https://gitee.com/gitee-stars/)
>>>>>>> d023a4061f82c081799404d46ece40211858601f
