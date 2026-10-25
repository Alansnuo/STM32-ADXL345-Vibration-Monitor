# 基于 STM32 与 ADXL345 的电机振动监测与故障预警系统

以 STM32U575 为主控、ADXL345 为振动传感器，对电机运行状态做实时采集与本地显示，
并通过振动特征与阈值判断给出故障预警。

> **当前阶段**：显示、触摸、LVGL 界面框架与 FreeRTOS 任务框架已跑通；
> ADXL345 采集、特征提取与预警逻辑尚未实现（见文末进度）。

## 1. 目标功能

| 模块 | 内容 |
|---|---|
| 振动采集 | ADXL345 三轴加速度，定时采样 |
| 特征提取 | RMS、峰值、峰峰值、峭度等时域指标 |
| 故障预警 | 阈值分级（正常 / 注意 / 报警）+ 趋势判断 |
| 本地显示 | LCD 实时波形、数值、状态与告警页 |
| 数据记录 | W25Q64 保存历史特征与告警事件 |
| 调试输出 | USART1 printf 日志 |

## 2. 硬件平台

| 项目 | 型号 / 参数 | 接口 |
|---|---|---|
| MCU | STM32U575ZIT6Q，LQFP144，160 MHz（MSI→PLL） | — |
| 液晶屏 | ST7789，320×240（横屏），RGB565 | SPI2 + GPDMA1 |
| 电容触摸 | FT6336U | 软件 I2C |
| 外部存储 | W25Q64（规划） | SPI |
| 振动传感器 | ADXL345（待接入） | SPI / I2C |
| 调试串口 | USART1，115200 8N1 | — |

已确认的引脚分配（其余见 `Project.ioc`）：

| 信号 | 引脚 |
|---|---|
| LCD_CS / LCD_DC / LCD_RESET | PD6 / PD4 / PD5 |
| 触摸 SCL / SDA | PF8 / PE5（SDA 开漏） |
| 触摸 INT / RST | PE2 / PF2 |
| W25Q64_CS | PD3（暂未使用） |

引脚宏分别定义在 `BSP/LCD/st7789.h`、`BSP/FT6336U/MyI2C.h`、`BSP/FT6336U/ft6336u.h`，
不依赖 CubeMX 生成的引脚标签。

## 3. 软件架构

### 启动顺序（`Core/Src/main.c`）

1. HAL 初始化、系统时钟 160 MHz、各外设初始化
2. `lv_init()` + 启动 TIM7（1 kHz，LVGL tick）
3. `lv_port_disp_init()`：ST7789 + 双缓冲
4. `lv_port_indev_init()`：FT6336U 触摸
5. `ui_init()`：创建界面
6. `Task_Init()` → `vTaskStartScheduler()`，控制权交给 FreeRTOS

### 任务

| 任务 | 优先级 | 栈 | 职责 |
|---|---|---|---|
| `lcdflsh` | 3 | 1 KB | 接收通知后阻塞刷屏，完成后回调 `lv_display_flush_ready()` |
| `lvgl` | 2 | 8 KB | 跑 `lv_timer_handler()`，读触摸，按返回值休眠 |

参数集中在 `App/app_config.h`，并有编译期检查（优先级顺序、栈下限、堆占用）。
内核参数（tick 1 kHz、堆 64 KB、8 级优先级）在 `freertos/inc/FreeRTOSConfig.h`。

### 刷屏链路

```
LVGL 渲染完成 → disp_flush() → LCD_FlushArea() 通知 lcdflsh
   → ST7789_FlushArea() 分块 DMA（每块 4800 像素）
   → 刷完回调 → lv_display_flush_ready()
```

LVGL 的 flush 等待是忙等，所以 `lcdflsh` 优先级必须高于 `lvgl`。

### 目录结构

```
App/            应用层：任务创建、全局配置、lcd/lvgl 任务
BSP/            板级驱动：LCD(ST7789)、触摸(FT6336U+软件 I2C)、W25Q64
LVGL_myGUI/     界面实现（ui.c / ui.h）
lvgl/           LVGL 9.6 源码 + porting（显示/输入对接）
freertos/       FreeRTOS 内核、配置与移植层
Core/           CubeMX 生成：时钟、外设、中断、main.c
Drivers/        STM32U5 HAL 与 CMSIS
MDK-ARM/        Keil 工程（Project.uvprojx）
```

## 4. 构建与烧录

- IDE：Keil MDK-ARM，工程 `MDK-ARM/Project.uvprojx`，编译器 AC6
- 外设配置：`Project.ioc`（CubeMX）。重新生成时只改 USER CODE 区，生成区不要手改
- 日志：`printf` 已重定向到 USART1（115200），由 `main.c` 中的 `fputc` 与 `_sys_*` 空壳实现

## 5. 代码约定

- 任务优先级 / 栈 / 周期统一写在 `App/app_config.h`，不在任务文件里散落
- 驱动引脚宏写在各驱动头文件，不依赖 CubeMX 的 `*_GPIO_Port` 标签
- 注释格式：文件头 `@file / @brief / @note`，函数 `@brief / @param`，单行短语为主
- 构建产物、日志与个人笔记由 `.gitignore` 排除

## 6. 当前进度

- [x] ST7789 驱动（SPI2 + GPDMA1，分块刷屏）
- [x] FT6336U 触摸（软件 I2C，中断读取）
- [x] LVGL 9.6 移植与双任务框架
- [x] USART1 printf 重定向
- [ ] ADXL345 驱动与定时采样
- [ ] 振动特征提取（RMS / 峰值 / 峭度）
- [ ] 阈值分级与报警状态机
- [ ] W25Q64 历史数据存储
- [ ] 监测主界面、波形页、告警页
