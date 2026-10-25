/**
 * @file W25Q64.c
 * @brief W25Q64 SPI Flash 读写与擦除实现
 * @note  页编程不可跨页; 写/擦除后须等待忙
 */

#include "W25Q64.h"
/**
 * @brief  初始化, 挂接底层 SPI
 */
void W25Q64_Init(void)
{
	MySPI_Init();					/* 初始化底层 SPI */
}

/**
 * @brief  读 JEDEC ID
 * @param  MID 出参, 厂商 ID
 * @param  DID 出参, 设备 ID
 */
void W25Q64_ReadID(uint8_t *MID, uint16_t *DID)
{
	MySPI_Start();
	MySPI_SwapByte(W25Q64_JEDEC_ID);			/* 发读 ID 指令 */
	*MID = MySPI_SwapByte(W25Q64_DUMMY_BYTE);
	*DID = MySPI_SwapByte(W25Q64_DUMMY_BYTE);	/* DID 高 8 位 */
	*DID <<= 8;
	*DID |= MySPI_SwapByte(W25Q64_DUMMY_BYTE);	/* DID 低 8 位 */
	MySPI_Stop();
}

/**
 * @brief  写使能
 */
void W25Q64_WriteEnable(void)
{
	MySPI_Start();
	MySPI_SwapByte(W25Q64_WRITE_ENABLE);
	MySPI_Stop();
}

/**
 * @brief  等待芯片空闲
 *         轮询状态寄存器 WIP 位, 带超时保护
 */
void W25Q64_WaitBusy(void)
{
	uint32_t Timeout;
	MySPI_Start();
	MySPI_SwapByte(W25Q64_READ_STATUS_REGISTER_1);
	Timeout = 100000;							/* 超时计数 */
	while ((MySPI_SwapByte(W25Q64_DUMMY_BYTE) & 0x01) == 0x01)	/* WIP 为 1 表示忙 */
	{
		Timeout --;
		if (Timeout == 0)
		{
			break;								/* 超时则不再等待 */
		}
	}
	MySPI_Stop();
}

/**
 * @brief  页编程
 * @param  Address 起始地址
 * @param  DataArray 待写数据
 * @param  Count 字节数, 0~256, 不可跨页
 */
void W25Q64_PageProgram(uint32_t Address, uint8_t *DataArray, uint16_t Count)
{
	uint16_t i;
	
	W25Q64_WriteEnable();
	
	MySPI_Start();
	MySPI_SwapByte(W25Q64_PAGE_PROGRAM);
	MySPI_SwapByte(Address >> 16);				/* 地址 23~16 位 */
	MySPI_SwapByte(Address >> 8);				/* 地址 15~8 位 */
	MySPI_SwapByte(Address);					/* 地址 7~0 位 */
	for (i = 0; i < Count; i ++)
	{
		MySPI_SwapByte(DataArray[i]);			/* 逐字节写入 */
	}
	MySPI_Stop();
	
	W25Q64_WaitBusy();
}

/**
 * @brief  扇区擦除, 4KB
 * @param  Address 扇区内任意地址
 */
void W25Q64_SectorErase(uint32_t Address)
{
	W25Q64_WriteEnable();
	
	MySPI_Start();
	MySPI_SwapByte(W25Q64_SECTOR_ERASE_4KB);
	MySPI_SwapByte(Address >> 16);				/* 地址 23~16 位 */
	MySPI_SwapByte(Address >> 8);				/* 地址 15~8 位 */
	MySPI_SwapByte(Address);					/* 地址 7~0 位 */
	MySPI_Stop();
	
	W25Q64_WaitBusy();
}

/**
 * @brief  读取数据
 * @param  Address 起始地址
 * @param  DataArray 接收缓冲
 * @param  Count 字节数
 */
void W25Q64_ReadData(uint32_t Address, uint8_t *DataArray, uint32_t Count)
{
	uint32_t i;
	MySPI_Start();
	MySPI_SwapByte(W25Q64_READ_DATA);
	MySPI_SwapByte(Address >> 16);				/* 地址 23~16 位 */
	MySPI_SwapByte(Address >> 8);				/* 地址 15~8 位 */
	MySPI_SwapByte(Address);					/* 地址 7~0 位 */
	for (i = 0; i < Count; i ++)
	{
		DataArray[i] = MySPI_SwapByte(W25Q64_DUMMY_BYTE);	/* 逐字节读取 */
	}
	MySPI_Stop();
}
