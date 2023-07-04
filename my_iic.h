/*
 * my_iic.h
 *
 *  Created on: 2023��7��3��
 *      Author: 15976
 */


#ifndef MY_I2C_H_
#define MY_I2C_H_

#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <delay.h>

#define SDA_IN()  GPIO_setAsInputPin(GPIO_PORT_P6,GPIO_PIN4)
#define SDA_OUT() GPIO_setAsOutputPin(GPIO_PORT_P6,GPIO_PIN4)


#define IIC_SCL_High()  GPIO_setOutputHighOnPin(GPIO_PORT_P6,GPIO_PIN5) //SCL_High
#define IIC_SCL_Low()   GPIO_setOutputLowOnPin(GPIO_PORT_P6,GPIO_PIN5) //SCL_Low
#define IIC_SDA_High()  GPIO_setOutputHighOnPin(GPIO_PORT_P6,GPIO_PIN4) //SDA_High
#define IIC_SDA_Low()   GPIO_setOutputLowOnPin(GPIO_PORT_P6,GPIO_PIN4) //SDA_Low
#define READ_SDA        GPIO_getInputPinValue(GPIO_PORT_P6,GPIO_PIN4)  //����SDA


void IIC_Init(void);                //��ʼ��IIC��IO��
void IIC_Start(void);               //����IIC��ʼ�ź�
void IIC_Stop(void);                //����IICֹͣ�ź�
void IIC_Send_Byte(uint8_t txd);         //IIC����һ���ֽ�
uint8_t IIC_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
uint8_t IIC_Wait_Ack(void);              //IIC�ȴ�ACK�ź�
void IIC_Ack(void);                 //IIC����ACK�ź�
void IIC_NAck(void);                //IIC������ACK�ź�



#endif /* MY_I2C_H_ */
