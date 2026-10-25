/**
 * @file MyI2C.h
 * @brief 软件 I2C 底层, 引脚与具体从机解耦
 * @note  SDA 须配置为开漏
 */

#ifndef __MYI2C_H
#define __MYI2C_H

#include "main.h"

/* 软件 I2C 1 引脚; 以后加第二条总线时, 复制一组并改编号 */
#define MYI2C1_SCL_PORT     GPIOF
#define MYI2C1_SCL_PIN      GPIO_PIN_8
#define MYI2C1_SDA_PORT     GPIOE
#define MYI2C1_SDA_PIN      GPIO_PIN_5

/**
 * @brief  发送起始信号
 */
void MyI2C_Start(void);

/**
 * @brief  发送停止信号
 */
void MyI2C_Stop(void);

/**
 * @brief  发送一个字节, 高位先发
 * @param  Byte 待发送字节
 */
void MyI2C_SendByte(uint8_t Byte);

/**
 * @brief  接收一个字节
 * @retval 读到的字节
 */
uint8_t MyI2C_ReceiveByte(void);

/**
 * @brief  发送应答位
 * @param  AckBit 0 应答, 1 非应答
 */
void MyI2C_SendAck(uint8_t AckBit);

/**
 * @brief  接收应答位
 * @retval 0 应答, 1 非应答
 */
uint8_t MyI2C_ReceiveAck(void);

#endif
