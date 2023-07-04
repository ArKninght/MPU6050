/*
 * my_iic.h
 *
 *  Created on: 2023年7月3日
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
#define READ_SDA        GPIO_getInputPinValue(GPIO_PORT_P6,GPIO_PIN4)  //输入SDA


void IIC_Init(void);                //初始化IIC的IO口
void IIC_Start(void);               //发送IIC开始信号
void IIC_Stop(void);                //发送IIC停止信号
void IIC_Send_Byte(uint8_t txd);         //IIC发送一个字节
uint8_t IIC_Read_Byte(unsigned char ack);//IIC读取一个字节
uint8_t IIC_Wait_Ack(void);              //IIC等待ACK信号
void IIC_Ack(void);                 //IIC发送ACK信号
void IIC_NAck(void);                //IIC不发送ACK信号



#endif /* MY_I2C_H_ */
