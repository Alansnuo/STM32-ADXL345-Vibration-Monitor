/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "dma2d.h"
#include "gpdma.h"
#include "i2c.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "lvgl.h"
#include "lv_port_disp.h"
#include "lv_port_indev.h"
#include "ui.h"
#include "app_freertos.h"  /* Task_Init：创建全部应用任务 */
#include "FreeRTOS.h"      /* configTOTAL_HEAP_SIZE 等 */
#include "task.h"          /* vTaskStartScheduler 的真身 */
#include <stdio.h>         /* printf → USART1 的重定向在下面 USER CODE 4 里 */
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_GPDMA1_Init();
  MX_I2C3_Init();
  MX_SPI2_Init();
  MX_SPI1_Init();
  MX_USART1_UART_Init();
  MX_TIM7_Init();
  MX_DMA2D_Init();
  /* USER CODE BEGIN 2 */

  /* ① LVGL 内核 */
  lv_init();

  /* ② 先把 tick 源开起来：TIM7 = 160MHz/160/1000 = 1kHz，1ms 一次中断 */
  HAL_TIM_Base_Start_IT(&htim7);

  /* ③ 显示：ST7789 240x320 @ SPI2 + GPDMA1（硬复位、初始化表都在驱动里） */
  lv_port_disp_init();

  /* ④ 输入：FT6336U 电容触摸 */
  lv_port_indev_init();

  /* ⑤ 界面（实现在 ui.c） */
  ui_init();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  /* 上面全是初始化（外设 / LVGL / 显示 / 输入 / 界面），从这两行起交给操作系统。
   *
   * ① Task_Init()：把 lcdflsh / lvgl 两个任务建出来。此时调度器还没跑，
   *    所以谁先建谁后建**不影响谁先跑** —— 决定执行顺序的是优先级，
   *    见 App/app_freertos.c。
   * ② vTaskStartScheduler()：点着调度器。它会按 configCPU_CLOCK_HZ 配好 SysTick、
   *    把 SVC/PendSV 压到最低优先级（configKERNEL_INTERRUPT_PRIORITY），
   *    然后切到 PSP、跳到优先级最高的就绪任务。
   *
   * **第②句正常不返回** —— 控制流从这一刻起就在各个任务之间转，
   * 主循环是 App/lvgl/task_lvgl.c 任务体里的那个 for(;;)。 */
  Task_Init();
  vTaskStartScheduler();

  /* 能从上面返回只有一种可能：堆不够，连 IDLE 任务都建不出来
   * （configTOTAL_HEAP_SIZE，见 freertos/inc/FreeRTOSConfig.h）。
   * Error_Handler() 会关中断死循环 —— 屏幕冻住，比带着坏状态乱跑好查。
   *
   * 下面这个 while(1) 是 CubeMX 生成的壳，永远到不了，
   * 留着只是为了不改动生成区的结构。 */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    Error_Handler();
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = RCC_MSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_0;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
  RCC_OscInitStruct.PLL.PLLMBOOST = RCC_PLLMBOOST_DIV4;
  RCC_OscInitStruct.PLL.PLLM = 3;
  RCC_OscInitStruct.PLL.PLLN = 10;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 1;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLLVCIRANGE_1;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_PCLK3;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* ==================== printf 重定向到 USART1（115200,8N1） ====================
 *
 * 【为什么这么短】
 * 本工程没勾 Use MicroLIB（useUlib=0），printf 的字符出口就是 fputc()，
 * 所以真正算得上“重定向”的只有 fputc 一个函数，其余全是库要求的空壳。
 *
 * 【为什么 8 个 _sys_* 一个都不能少】
 * 只要有**一处** printf，链接器就会为了 _initio() 把库里的 sys_io.o 拉进来，
 * 而 sys_io.o 里那 8 个 _sys_* 是一次性全给的 —— 你只接管其中几个，剩下的
 * 照样跟着进来，直接 L6200E 重复定义。实测过：只给 fputc + _sys_exit + _ttywrch，
 * 报 L6915E: _sys_open was referenced；再补上 _sys_open，又变成
 * L6200E: _sys_open multiply defined (by sys_io.o and main.o)。
 * 所以：要么全接管，要么一个都别接管。
 *
 * 【__use_no_semihosting 是保险丝，不是装饰】
 * 它是给链接器的硬约束：库里那个带 BKPT #0xab 的半主机版本一旦被链进来，
 * 链接阶段就报 L6915E 并把函数名点出来 —— 而不是编出一个上电就死的镜像。
 * 那句 __asm 是 AC6 下的标准写法（AC5 的 #pragma import(__use_no_semihosting)
 * 在 AC6 里已经不能用，网上抄来的写法大多是 AC5 的）。
 * 没有它的话，漏接管一个 _sys_* 的后果是：sys_io.o 静默进镜像，
 * __rt_lib_init → _initio() 在 main() 之前执行到 BKPT，板子上没挂调试器，
 * CPU 直接被带走 —— 症状是**全黑屏、一句代码都不执行**，而屏是本工程
 * 唯一的诊断通道，黑屏会把别的问题一起盖住。
 *
 * 【不用 printf 的时候它占多少】
 * 零。整条 stdio 链（_initio / sys_io / 格式化代码）都是链接器按需拉的，
 * 全工程没有 printf 调用点时一个字节都不进镜像。
 * 但只要谁哪天写了一句 printf，这套东西立刻开始干活。 */

__asm(".global __use_no_semihosting\n");

/* printf 的字符出口 */
int fputc(int ch, FILE *f)
{
  (void)f;
  HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 100);
  return ch;
}

/* ---- 下面是库要求的空壳，签名一个都不能改 ---- */
int  _sys_open(const char *name, int openmode)                  { (void)name; (void)openmode; return 1; }  /* “:tt” 一律当开成功 */
int  _sys_close(int handle)                                     { (void)handle; return 0; }
int  _sys_write(int handle, const unsigned char *buf, unsigned len, int mode)
{
  (void)handle; (void)mode;
  if (buf != NULL && len != 0U) { HAL_UART_Transmit(&huart1, (uint8_t *)buf, (uint16_t)len, 100); }
  return 0;                                                                                               /* 只有 fwrite 走这里 */
}
int  _sys_read (int handle, unsigned char *buf, unsigned len, int mode) { (void)handle; (void)buf; (void)len; (void)mode; return 0; }
int  _sys_istty(int handle)                                     { (void)handle; return 1; }               /* 三个标准流都当终端 */
int  _sys_seek (int handle, long pos)                           { (void)handle; (void)pos; return 0; }
int  _sys_flen (int handle)                                     { (void)handle; return 0; }
int  _sys_tmpnam(char *name, int fileno, unsigned maxlength)    { (void)name; (void)fileno; (void)maxlength; return 0; }
void _ttywrch(int ch)                                           { (void)ch; }                             /* 调试器控制台 */
void _sys_exit(int return_code)                                 { (void)return_code; for (;;) { } }       /* 裸机没地方可退，停住 */

/* 注意：不要在这个文件里再定义 HAL_TIM_PeriodElapsedCallback。
 * CubeMX 的 Timebase Source 选的是 TIM6（不是 SysTick），所以它在**本文件末尾**
 * 已经生成了一个用于 HAL_IncTick() 的回调，TIM7 的 LVGL tick 也并在那一个里。
 * HAL 的这个回调是 __weak 的，全工程只允许有一个强定义，重复定义会编译报错。 */

/* USER CODE END 4 */

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM6 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM6)
  {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */
  /* TIM7 周期中断：每 1ms 给 LVGL 喂一个 tick。
   * TIM6 = HAL 时基（uwTick / HAL_Delay / HAL_GetTick）
   * TIM7 = LVGL 时基（lv_tick_inc）
   * 两者共用同一个 HAL 回调，所以必须合并成一个、按 Instance 分派。 */
  if (htim->Instance == TIM7)
  {
    lv_tick_inc(1); 
  }
  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
