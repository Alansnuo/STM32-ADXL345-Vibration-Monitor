/**
 * @file W25Q64.h
 * @brief W25Q64 SPI Flash 驱动接口
 * @note  底层 SPI 由 MySPI 提供
 */
#ifndef __W25Q64_H
#define __W25Q64_H


#include "MySPI.h"
#include "W25Q64_Ins.h"

/**
 * @brief  初始化, 内部调用 MySPI_Init
 */
void W25Q64_Init(void);
/**
 * @brief  读 JEDEC ID
 * @param  MID 出参, 厂商 ID
 * @param  DID 出参, 设备 ID
 */
void W25Q64_ReadID(uint8_t *MID, uint16_t *DID);
/**
 * @brief  页编程, 单次最多 256 字节且不可跨页
 * @param  Address 起始地址
 * @param  DataArray 待写数据
 * @param  Count 字节数, 0~256
 */
void W25Q64_PageProgram(uint32_t Address, uint8_t *DataArray, uint16_t Count);
/**
 * @brief  扇区擦除, 4KB
 * @param  Address 扇区内任意地址
 */
void W25Q64_SectorErase(uint32_t Address);
/**
 * @brief  读取数据, 地址自动递增
 * @param  Address 起始地址
 * @param  DataArray 接收缓冲
 * @param  Count 字节数
 */
void W25Q64_ReadData(uint32_t Address, uint8_t *DataArray, uint32_t Count);

#endif
