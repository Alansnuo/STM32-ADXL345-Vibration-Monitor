/**
 * @file MyI2C.c
 * @brief 软件 I2C 底层实现, GPIO 模拟时序
 * @note  SDA 须为开漏; 位延时把 SCL 控制在 60~80kHz
 */

#include "MyI2C.h"

/**
 * @brief  位延时, 约 6~8us
 *         不能用 HAL_Delay, 并需留足 SDA 开漏上拉的上升时间
 */
static void MyI2C_Delay(void)
{
    for(volatile uint32_t i = 0; i < 100U; i++) { }
}

/**
 * @brief  写 SCL 电平
 * @param  BitValue 0 低, 非 0 高
 */
void MyI2C_W_SCL(uint8_t BitValue)
{
    HAL_GPIO_WritePin(MYI2C1_SCL_PORT, MYI2C1_SCL_PIN, BitValue ? GPIO_PIN_SET : GPIO_PIN_RESET);
    MyI2C_Delay();
}

/**
 * @brief  写 SDA 电平
 * @param  BitValue 0 低, 非 0 高
 */
void MyI2C_W_SDA(uint8_t BitValue)
{
    HAL_GPIO_WritePin(MYI2C1_SDA_PORT, MYI2C1_SDA_PIN, BitValue ? GPIO_PIN_SET : GPIO_PIN_RESET);
    MyI2C_Delay();
}

/**
 * @brief  读 SDA 电平
 * @retval 0 低, 非 0 高
 */
uint8_t MyI2C_R_SDA(void)
{
    uint8_t BitValue;
    BitValue = HAL_GPIO_ReadPin(MYI2C1_SDA_PORT, MYI2C1_SDA_PIN);
    MyI2C_Delay();
    return BitValue;
}

/* ---------- I2C 协议层 ---------- */
/**
 * @brief  发送起始信号
 */
void MyI2C_Start(void)
{
	MyI2C_W_SDA(1);							/* 释放 SDA */
	MyI2C_W_SCL(1);							/* 释放 SCL */
	MyI2C_W_SDA(0);							/* SCL 高时拉低 SDA */
	MyI2C_W_SCL(0);							/* 占用总线 */
}

/**
 * @brief  发送停止信号
 */
void MyI2C_Stop(void)
{
	MyI2C_W_SDA(0);							/* 拉低 SDA */
	MyI2C_W_SCL(1);							/* 释放 SCL */
	MyI2C_W_SDA(1);							/* SCL 高时释放 SDA */
}

/**
 * @brief  发送一个字节, 高位先发
 * @param  Byte 待发送字节
 */
void MyI2C_SendByte(uint8_t Byte)
{
	uint8_t i;
	for (i = 0; i < 8; i ++)
	{
		MyI2C_W_SDA(!!(Byte & (0x80 >> i)));/* 取第 i 位, 归一化为 0/1 */
		MyI2C_W_SCL(1);						/* 释放 SCL, 从机采样 */
		MyI2C_W_SCL(0);						/* 拉低 SCL, 准备下一位 */
	}
}

/**
 * @brief  接收一个字节
 * @retval 读到的字节
 */
uint8_t MyI2C_ReceiveByte(void)
{
	uint8_t i, Byte = 0x00;					/* 累加接收字节 */
	MyI2C_W_SDA(1);							/* 接收前释放 SDA */
	for (i = 0; i < 8; i ++)
	{
		MyI2C_W_SCL(1);						/* 从机在 SCL 高期间送数 */
		if (MyI2C_R_SDA()){Byte |= (0x80 >> i);}	/* 读 SDA 并置位 */
		MyI2C_W_SCL(0);						/* 拉低 SCL, 从机换下一位 */
	}
	return Byte;
}

/**
 * @brief  发送应答位
 * @param  AckBit 0 应答, 1 非应答
 */
void MyI2C_SendAck(uint8_t AckBit)
{
	MyI2C_W_SDA(AckBit);					/* 把应答位放到 SDA */
	MyI2C_W_SCL(1);							/* 释放 SCL, 从机读取 */
	MyI2C_W_SCL(0);
}

/**
 * @brief  接收应答位
 * @retval 0 应答, 1 非应答
 */
uint8_t MyI2C_ReceiveAck(void)
{
	uint8_t AckBit;
	MyI2C_W_SDA(1);							/* 接收前释放 SDA */
	MyI2C_W_SCL(1);							/* 从机在 SCL 高期间送应答 */
	AckBit = MyI2C_R_SDA();
	MyI2C_W_SCL(0);
	return AckBit;
}