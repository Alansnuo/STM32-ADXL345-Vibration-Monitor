
/**
 * @file lv_conf.h
 * 适用于 v9.6.0 的配置文件
 * Configuration file for v9.6.0
 */

/*
 * 将此文件复制为 `lv_conf.h`
 * Copy this file as `lv_conf.h`
 * 1. 直接放在 `lvgl` 文件夹旁边，或者：
 * 1. simply next to `lvgl` folder
 * 2. 放到其他任意位置，并：
 * 2. or to any other place and
 *    - 定义 `LV_CONF_INCLUDE_SIMPLE`；
 *    - define `LV_CONF_INCLUDE_SIMPLE`;
 *    - 将该路径加入头文件搜索路径。
 *    - add the path as an include path.
 */

/* clang-format off */
#if 1 /* 设置为 "1" 以启用以下所有内容 */ /* Set this to "1" to enable content */

#ifndef LV_CONF_H
#define LV_CONF_H

/* 如需在此处引入任何内容，请在 `__ASSEMBLY__` 保护宏内进行
 * If you need to include anything here, do it inside the `__ASSEMBLY__` guard */
#if 0 && defined(__ASSEMBLY__)
#include "my_include.h"
#endif

/*============================================================================
 * MEMORY AND STANDARD LIBRARY
 *============================================================================*/

/** malloc 函数来源
 *  Malloc functions source
 *  可选值：
 *  Possible values:
 *  - LV_STDLIB_BUILTIN: LVGL 内置
 *  - LV_STDLIB_BUILTIN: LVGL built-in
 *  - LV_STDLIB_CLIB: C 标准库（malloc/realloc/free）
 *  - LV_STDLIB_CLIB: C standard library (malloc/realloc/free)
 *  - LV_STDLIB_MICROPYTHON: MicroPython
 *  - LV_STDLIB_MICROPYTHON
 *  - LV_STDLIB_RTTHREAD: RT-Thread
 *  - LV_STDLIB_RTTHREAD
 *  - LV_STDLIB_CUSTOM: 自定义（由外部实现）
 *  - LV_STDLIB_CUSTOM: Custom (implemented externally)
 */
#define LV_USE_STDLIB_MALLOC LV_STDLIB_BUILTIN

/** 字符串函数来源
 *  String functions source
 *  可选值：
 *  Possible values:
 *  - LV_STDLIB_BUILTIN: LVGL 内置
 *  - LV_STDLIB_BUILTIN: LVGL built-in
 *  - LV_STDLIB_CLIB: C 标准库（memcpy/memset/strlen/strcpy）
 *  - LV_STDLIB_CLIB: C standard library (memcpy/memset/strlen/strcpy)
 *  - LV_STDLIB_RTTHREAD: RT-Thread（rt_memcpy/rt_memset/rt_strlen/rt_strcpy）
 *  - LV_STDLIB_RTTHREAD: RT-Thread (rt_memcpy/rt_memset/rt_strlen/rt_strcpy)
 *  - LV_STDLIB_CUSTOM: 自定义（由外部实现）
 *  - LV_STDLIB_CUSTOM: Custom (implemented externally)
 */
#define LV_USE_STDLIB_STRING LV_STDLIB_BUILTIN

/** sprintf 函数来源
 *  Sprintf functions source
 *  可选值：
 *  Possible values:
 *  - LV_STDLIB_BUILTIN: LVGL 内置
 *  - LV_STDLIB_BUILTIN: LVGL built-in
 *  - LV_STDLIB_CLIB: C 标准库（vsnprintf）
 *  - LV_STDLIB_CLIB: C standard library (vsnprintf)
 *  - LV_STDLIB_RTTHREAD: RT-Thread（rt_vsnprintf）
 *  - LV_STDLIB_RTTHREAD: RT-Thread (rt_vsnprintf)
 *  - LV_STDLIB_CUSTOM: 自定义（由外部实现）
 *  - LV_STDLIB_CUSTOM: Custom (implemented externally)
 */
#define LV_USE_STDLIB_SPRINTF LV_STDLIB_BUILTIN

#if LV_USE_STDLIB_MALLOC == LV_STDLIB_BUILTIN
/** `lv_malloc()` 分配所用的内存池大小，至少需要 2kB（2048）。
 *  Size of the pool `lv_malloc()` allocates from. Needs to be at least 2kB (2048). */
#define LV_MEM_SIZE 131072

/** 将内存池放在固定地址，而不是作为普通数组分配。
 *  Place the pool at a fixed address instead of allocating it as a normal array.
 *  0：不使用。
 *  0: unused.
 */
#define LV_MEM_ADR 0x0

#endif /*LV_USE_STDLIB_MALLOC == LV_STDLIB_BUILTIN*/

/** 整型类型的头文件（stdint）
 *  Header for integer types (stdint) */
#define LV_STDINT_INCLUDE "stdint.h"

/** 标准定义的头文件（stddef）
 *  Header for standard definitions (stddef) */
#define LV_STDDEF_INCLUDE "stddef.h"

/** 布尔类型的头文件（stdbool）
 *  Header for boolean types (stdbool) */
#define LV_STDBOOL_INCLUDE "stdbool.h"

/** 定宽整数格式宏的头文件（inttypes）
 *  Header for fixed-width integer format macros (inttypes) */
#define LV_INTTYPES_INCLUDE "inttypes.h"

/** 实现相关限制的头文件（limits）
 *  Header for implementation limits (limits) */
#define LV_LIMITS_INCLUDE "limits.h"

/** 可变参数处理的头文件（stdarg）
 *  Header for variadic argument handling (stdarg) */
#define LV_STDARG_INCLUDE "stdarg.h"



/*============================================================================
 * OPERATING SYSTEM (OS)
 *============================================================================*/

/** 操作系统
 *  Operating system
 *  可选值：
 *  Possible values:
 *  - LV_OS_NONE: 无操作系统
 *  - LV_OS_NONE
 *  - LV_OS_PTHREAD: POSIX 线程（pthread）
 *  - LV_OS_PTHREAD: POSIX threads (pthread)
 *  - LV_OS_FREERTOS: FreeRTOS
 *  - LV_OS_FREERTOS
 *  - LV_OS_CMSIS_RTOS2: CMSIS-RTOS2
 *  - LV_OS_CMSIS_RTOS2
 *  - LV_OS_RTTHREAD: RT-Thread
 *  - LV_OS_RTTHREAD
 *  - LV_OS_WINDOWS: Windows
 *  - LV_OS_WINDOWS
 *  - LV_OS_MQX: MQX
 *  - LV_OS_MQX
 *  - LV_OS_SDL2: SDL2
 *  - LV_OS_SDL2
 *  - LV_OS_CUSTOM: 自定义
 *  - LV_OS_CUSTOM
 */
#define LV_USE_OS LV_OS_NONE

#if LV_USE_OS == LV_OS_CUSTOM
/** 自定义操作系统的头文件
 *  Custom OS include header */
#define LV_OS_CUSTOM_INCLUDE ""

#endif /*LV_USE_OS == LV_OS_CUSTOM*/

#if LV_USE_OS == LV_OS_FREERTOS
/** 使用直接任务通知进行同步，而不是借助二进制信号量这样的中间对象：
 *  Synchronize with direct task notifications instead of an intermediary object such as a
 *  快 45% 且占用更少 RAM，但仅当事件只有一个任务接收时才可用。
 *  binary semaphore: 45% faster and less RAM, but only usable when a single task can be
 *  the recipient of the event.
 */
#define LV_USE_FREERTOS_TASK_NOTIFY 1

/** 提供你自己的 lv_os_get_idle_percent()。在多核系统中有用，因为默认的
 *  Provide your own lv_os_get_idle_percent(). Useful on multi-core systems, where the
 *  FreeRTOS 实现可能无法跟踪所有核的空闲时间。
 *  default FreeRTOS implementation may not track idle time across all cores.
 */
#define LV_OS_IDLE_PERCENT_CUSTOM 0

#endif /*LV_USE_OS == LV_OS_FREERTOS*/


/*============================================================================
 * RENDERING CONFIGURATION
 *============================================================================*/

/** 默认颜色格式
 *  Default color format
 *  可选值：
 *  Possible values:
 *  - LV_COLOR_FORMAT_I1: 1 位索引色
 *  - LV_COLOR_FORMAT_I1
 *  - LV_COLOR_FORMAT_L8: 8 位灰度
 *  - LV_COLOR_FORMAT_L8
 *  - LV_COLOR_FORMAT_RGB565: RGB565
 *  - LV_COLOR_FORMAT_RGB565
 *  - LV_COLOR_FORMAT_RGB565_SWAPPED: RGB565（大端字节序）
 *  - LV_COLOR_FORMAT_RGB565_SWAPPED: RGB565 (Big-endian)
 *  - LV_COLOR_FORMAT_RGB888: RGB888
 *  - LV_COLOR_FORMAT_RGB888
 *  - LV_COLOR_FORMAT_XRGB8888: XRGB8888（保留一个字节）
 *  - LV_COLOR_FORMAT_XRGB8888
 *  - LV_COLOR_FORMAT_ARGB8888: ARGB8888（带透明度）
 *  - LV_COLOR_FORMAT_ARGB8888
 *  - LV_COLOR_FORMAT_ARGB8888_PREMULTIPLIED: ARGB8888 预乘透明度
 *  - LV_COLOR_FORMAT_ARGB8888_PREMULTIPLIED
 */
#define LV_COLOR_FORMAT_DEFAULT LV_COLOR_FORMAT_RGB565

/** 0：不调整，取结果的整数部分（向下取整）
 *  0: no adjustment, get the integer part of the result (round down)
 *  64：从 x.75 起向上取整
 *  64: round up from x.75
 *  128：从一半处向上取整
 *  128: round up from half
 *  192：从 x.25 起向上取整
 *  192: round up from x.25
 *  254：总是向上取整
 *  254: round up
 */
#define LV_COLOR_MIX_ROUND_OFS 0

/** 默认的显示刷新、输入设备读取和动画步进周期（毫秒）。 */
#define LV_DEF_REFR_PERIOD 17
/** Default display refresh, input device read and animation step period. */

/** 用于初始化默认尺寸，例如控件尺寸和样式内边距。 */
#define LV_DPI_DEF 130
/** Used to initialize default sizes such as widget sizes and style paddings. */

/** 所有图层和图像的每行字节数对齐到该数值的倍数。 */
#define LV_DRAW_BUF_STRIDE_ALIGN 1
/** Align the stride of all layers and images to this many bytes. */

/** draw_buf 地址的起始地址对齐到该数值的倍数。 */
#define LV_DRAW_BUF_ALIGN 4
/** Align the start address of draw_buf addresses to this many bytes. */

/** 3x3 矩阵 API（lv_matrix_t），用于图形变换。需要浮点支持。
 *  3x3 matrix API (lv_matrix_t) for transformations. Requires floating point support.
 *
 *  启用前提：LV_USE_FLOAT
 *  Enable: LV_USE_FLOAT
 */
#define LV_USE_MATRIX 0

#if LV_USE_MATRIX
/** 渲染引擎必须支持 3x3 矩阵变换。 */
#define LV_DRAW_TRANSFORM_USE_MATRIX 0
/** The rendering engine must support 3x3 matrix transformations. */

#endif /*LV_USE_MATRIX*/

/** 带有 `style_opa < 255`（不是 `bg_opa`、`text_opa` 等）或非 NORMAL 混合模式的控件，
 *  按此大小分块缓冲到一个"简单"图层中。
 *  "变换图层"（设置了 `transform_angle/zoom`）使用更大的缓冲区，且无法分块。
 */
#define LV_DRAW_LAYER_SIMPLE_BUF_SIZE 24576
/** Widgets with `style_opa < 255` (not `bg_opa`, `text_opa` etc) or a non-NORMAL blend mode are
 *  buffered into a "simple" layer in chunks of this size.
 *  "Transformed layers" (if `transform_angle/zoom` are set) use larger buffers and can't be chunked.
 */

/** 简单图层和变换图层的总内存上限；0 表示无限制。
 *  至少必须为 `LV_DRAW_LAYER_SIMPLE_BUF_SIZE`，并且当有变换图层时还需足够大，
 *  以容纳最大的控件（宽 x 高 x 4）。
 */
#define LV_DRAW_LAYER_MAX_MEMORY 0
/** Limit for simple and transformed layers together; 0 means no limit.
 *  Must be at least `LV_DRAW_LAYER_SIMPLE_BUF_SIZE`, and with transformed layers large enough
 *  for the largest widget too (width x height x 4).
 */

#if LV_USE_OS != LV_OS_NONE
/** 如果启用了 FreeType 或 ThorVG，建议将其设置为 32KB 或更多。 */
#define LV_DRAW_THREAD_STACK_SIZE 8192
/** If FreeType or ThorVG is enabled, it is recommended to set it to 32KB or more. */

/** 线程优先级控制绘图线程的相对重要性。
 *  取值对应 lv_os.h 中的 lv_thread_prio_t 枚举：
 *  0：LV_THREAD_PRIO_LOWEST（最低）
 *  1：LV_THREAD_PRIO_LOW（低）
 *  2：LV_THREAD_PRIO_MID（中，默认）
 *  3：LV_THREAD_PRIO_HIGH（高）
 *  4：LV_THREAD_PRIO_HIGHEST（最高）
 *
 *  更高的优先级可以提高渲染性能，但可能导致低优先级任务被饿死。
 */
#define LV_DRAW_THREAD_PRIO 3
/** Thread priority controls the relative importance of the drawing threads.
 *  Values correspond to lv_thread_prio_t enum in lv_os.h:
 *  0: LV_THREAD_PRIO_LOWEST
 *  1: LV_THREAD_PRIO_LOW
 *  2: LV_THREAD_PRIO_MID (default)
 *  3: LV_THREAD_PRIO_HIGH
 *  4: LV_THREAD_PRIO_HIGHEST
 *
 *  Higher priority can improve rendering performance but might cause
 *  starvation of lower priority tasks.
 */

#endif /*LV_USE_OS != LV_OS_NONE*/

/** 矢量绘图 API（lv_vector_dsc_*），用于路径、描边和填充。
 *  需要支持矢量的渲染器，例如带 ThorVG 的软件渲染器，或 VG-Lite。
 *
 *  启用前提：LV_USE_MATRIX
 */
#define LV_USE_VECTOR_GRAPHIC 0
/** Vector drawing API (lv_vector_dsc_*) for paths, strokes and fills.
 *  Needs a renderer with vector support, e.g. the SW renderer with ThorVG, or VG-Lite.
 *
 *  Enable: LV_USE_MATRIX
 */

/** 使用 lv_snapshot_take() 将控件及其子控件渲染到一个图像缓冲区。 */
#define LV_USE_SNAPSHOT 0
/** Render a widget and its children into an image buffer with lv_snapshot_take(). */

/** 为软件渲染器提供矢量图形支持的后端。 */
#define LV_USE_THORVG 0
/** Backend that gives the SW renderer vector graphics support. */

#if LV_USE_THORVG
/** 编译 LVGL 自带的 ThorVG 副本，而不是链接外部的。 */
#define LV_USE_THORVG_INTERNAL 1
/** Build the ThorVG copy shipped with LVGL instead of linking an external one. */

#endif /*LV_USE_THORVG*/

/** 在屏幕上绘制任何内容都必须开启。 */
#define LV_USE_DRAW_SW 1
/** Required to draw anything on the screen. */

#if LV_USE_DRAW_SW
/** RGB565 支持 */
#define LV_DRAW_SW_SUPPORT_RGB565 1
/** RGB565 */

/** RGB565 字节序交换支持 */
#define LV_DRAW_SW_SUPPORT_RGB565_SWAPPED 1
/** RGB565 swapped */

/** RGB565A8 支持 */
#define LV_DRAW_SW_SUPPORT_RGB565A8 1
/** RGB565A8 */

/** RGB888 支持 */
#define LV_DRAW_SW_SUPPORT_RGB888 1
/** RGB888 */

/** XRGB8888 支持 */
#define LV_DRAW_SW_SUPPORT_XRGB8888 1
/** XRGB8888 */

/** ARGB8888 支持 */
#define LV_DRAW_SW_SUPPORT_ARGB8888 1
/** ARGB8888 */

/** ARGB8888 预乘透明度支持 */
#define LV_DRAW_SW_SUPPORT_ARGB8888_PREMULTIPLIED 1
/** ARGB8888 premultiplied */

/** L8 灰度支持 */
#define LV_DRAW_SW_SUPPORT_L8 1
/** L8 */

/** AL88 灰度+透明度支持 */
#define LV_DRAW_SW_SUPPORT_AL88 1
/** AL88 */

/** A8 透明度支持 */
#define LV_DRAW_SW_SUPPORT_A8 1
/** A8 */

/** I1 索引色支持 */
#define LV_DRAW_SW_SUPPORT_I1 1
/** I1 */

#if LV_DRAW_SW_SUPPORT_I1
/** 渲染到 I1 时，亮度高于该阈值的像素变为激活（置位）。 */
#define LV_DRAW_SW_I1_LUM_THRESHOLD 127
/** Pixels brighter than this luminance become active (set) when rendering to I1. */

#endif /*LV_DRAW_SW_SUPPORT_I1*/

#if LV_USE_OS != LV_OS_NONE
/** 用于并行渲染一帧的线程数 */
#define LV_DRAW_SW_DRAW_UNIT_CNT 1
/** Number of threads used to render a frame in parallel */

#endif /*LV_USE_OS != LV_OS_NONE*/

/** 需要工程中包含 Arm-2D 库以及 "arm_2d.h" 的包含路径。 */
#define LV_USE_DRAW_ARM2D_SYNC 0
/** Requires the Arm-2D library in your project and an include path for "arm_2d.h". */

/** 关闭以让 Arm-2D 自行工作（仅用于测试）。 */
#define LV_USE_NATIVE_HELIUM_ASM 0
/** Disable to let Arm-2D work on its own (for testing only). */

/** 增加圆角、阴影、斜线和圆弧的绘制支持。
 *  关闭后只能绘制带渐变的矩形、图像、文本和直线。
 */
#define LV_DRAW_SW_COMPLEX 1
/** Adds rounded corners, shadows, skewed lines and arcs.
 *  Without it only rectangles with gradients, images, texts and straight lines can be drawn.
 */

/** 每增加一个渐变停止点会多占用（sizeof(lv_color_t) + 1）字节。 */
#define LV_GRADIENT_MAX_STOPS 2
/** Each additional stop costs (sizeof(lv_color_t) + 1) bytes. */

/** 增加带角度的线性渐变，以及径向和锥形渐变。 */
#define LV_USE_DRAW_SW_COMPLEX_GRADIENTS 0
/** Adds linear gradients at an angle, plus radial and conical gradients. */

#if LV_DRAW_SW_COMPLEX
/** 用于缓冲的最大阴影尺寸，其中阴影尺寸为 `shadow_width + radius`。
 *  占用该值的平方字节的 RAM；0 表示禁止缓存。
 */
#define LV_DRAW_SW_SHADOW_CACHE_SIZE 0
/** Maximum shadow size to buffer, where shadow size is `shadow_width + radius`.
 *  Costs this value squared in RAM; 0 disables caching.
 */

/** 1/4 圆的周长会被缓存用于抗锯齿，每个圆占用 radius * 4 字节。
 *  设置为 0 以禁用缓存。
 */
#define LV_DRAW_SW_CIRCLE_CACHE_SIZE 4
/** The circumference of a 1/4 circle is cached for anti-aliasing, costing
 *  radius * 4 bytes per circle. Set to 0 to disable caching.
 */

#endif /*LV_DRAW_SW_COMPLEX*/

/** SW 汇编优化
 *  SW assembly optimization
 *  可选值：
 *  Possible values:
 *  - LV_DRAW_SW_ASM_NONE: 不使用汇编
 *  - LV_DRAW_SW_ASM_NONE
 *  - LV_DRAW_SW_ASM_NEON: ARM NEON
 *  - LV_DRAW_SW_ASM_NEON
 *  - LV_DRAW_SW_ASM_HELIUM: ARM Helium
 *  - LV_DRAW_SW_ASM_HELIUM
 *  - LV_DRAW_SW_ASM_RISCV_V: RISC-V Vector（RISC-V 向量）
 *  - LV_DRAW_SW_ASM_RISCV_V: RISC-V Vector
 *  - LV_DRAW_SW_ASM_SVE2: ARM SVE2
 *  - LV_DRAW_SW_ASM_SVE2
 *  - LV_DRAW_SW_ASM_CUSTOM: 自定义
 *  - LV_DRAW_SW_ASM_CUSTOM
 */
#define LV_USE_DRAW_SW_ASM LV_DRAW_SW_ASM_NONE

#if LV_USE_DRAW_SW_ASM == LV_DRAW_SW_ASM_CUSTOM
/** 自定义汇编包含文件 */
#define LV_DRAW_SW_ASM_CUSTOM_INCLUDE ""
/** Custom assembly include file */

#endif /*LV_USE_DRAW_SW_ASM == LV_DRAW_SW_ASM_CUSTOM*/
#endif /*LV_USE_DRAW_SW*/

/** 使用 VG-Lite GPU 渲染。需要 VG-Lite 驱动，或下面的 VG-Lite 模拟器。
 *  Renders with a VG-Lite GPU. Requires a VG-Lite driver, or the VG-Lite simulator below.
 *
 *  启用前提：LV_USE_MATRIX
 *  Enable: LV_USE_MATRIX
 */
#define LV_USE_DRAW_VG_LITE 0

#if LV_USE_DRAW_VG_LITE
/** 在首次使用 GPU 之前调用应用程序提供的 gpu_init()。 */
#define LV_VG_LITE_USE_GPU_INIT 0
/** Call an application-provided gpu_init() before the first use of the GPU. */

/** 使用 LV_ASSERT() 检查内部 VG-Lite 状态。调试时有用。 */
#define LV_VG_LITE_USE_ASSERT 0
/** Check internal VG-Lite state with LV_ASSERT(). Useful while debugging. */

/** GPU 在刷新前尝试批量处理的绘制任务数。 */
#define LV_VG_LITE_FLUSH_MAX_COUNT 8
/** The GPU tries to batch this many draw tasks before flushing. */

/** 通常更快，但达不到 SW 渲染器的渲染质量。 */
#define LV_VG_LITE_USE_BOX_SHADOW 1
/** Usually faster, but does not match the rendering quality of the SW renderer. */

/** 单个渐变占用的内存：
 *  单个渐变的内存占用：
 *          linear（线性）: 4K 字节。
 *          radial（径向）: radius * 4K 字节。
 */
#define LV_VG_LITE_GRAD_CACHE_CNT 32
/** The memory usage of a single gradient:
 *          linear: 4K bytes.
 *          radial: radius * 4K bytes.
 */

/** 描边缓存大小（条目数） */
#define LV_VG_LITE_STROKE_CACHE_CNT 32
/** Stroke cache size (entries) */

/** 非对齐位图字体缓存大小（条目数） */
#define LV_VG_LITE_BITMAP_FONT_CACHE_CNT 256
/** Unaligned bitmap font cache size (entries) */

/** 移除 VLC_OP_CLOSE 路径指令（NXP 的解决方法） */
#define LV_VG_LITE_DISABLE_VLC_OP_CLOSE 0
/** Remove VLC_OP_CLOSE path instruction (Workaround for NXP) */

/** 较老的未实现该扩展的 VG-Lite 驱动需要此项。 */
#define LV_VG_LITE_DISABLE_LINEAR_GRADIENT_EXT 0
/** Needed with older VG-Lite drivers that do not implement the extension. */

/** 以额外的 blit（位块传送）为代价来解决某些 GPU 上的硬件错误。 */
#define LV_VG_LITE_DISABLE_BLIT_RECT_OFFSET 0
/** Works around HW errors on some GPUs at the cost of extra blits. */

/** 最大路径转储长度（点数） */
#define LV_VG_LITE_PATH_DUMP_MAX_LEN 1000
/** Maximum path dump length (points) */

/** 编译 LVGL 自带的 VG-Lite 驱动，而不是链接厂商提供的驱动。 */
#define LV_USE_VG_LITE_DRIVER 0
/** Build the VG-Lite driver bundled with LVGL instead of linking a vendor-provided one. */

#if LV_USE_VG_LITE_DRIVER
/** VG-Lite GPU（系列和版本号）
 *  VG-Lite GPU (series and revision)
 *  可选值：
 *  Possible values:
 *  - LV_VG_LITE_GPU_GC255_0X40A: GC255（版本 0x40A）
 *  - LV_VG_LITE_GPU_GC255_0X40A: GC255 (revision 0x40A)
 *  - LV_VG_LITE_GPU_GC355_0X0_1215: GC355（版本 0x0_1215）
 *  - LV_VG_LITE_GPU_GC355_0X0_1215: GC355 (revision 0x0_1215)
 *  - LV_VG_LITE_GPU_GC355_0X0_1216: GC355（版本 0x0_1216）
 *  - LV_VG_LITE_GPU_GC355_0X0_1216: GC355 (revision 0x0_1216)
 *  - LV_VG_LITE_GPU_GC555_0X423: GC555（版本 0x423）
 *  - LV_VG_LITE_GPU_GC555_0X423: GC555 (revision 0x423)
 *  - LV_VG_LITE_GPU_GC555_0X423_ECO: GC555（版本 0x423 ECO）
 *  - LV_VG_LITE_GPU_GC555_0X423_ECO: GC555 (revision 0x423 ECO)
 *  - LV_VG_LITE_GPU_GCNANOULTRAV_0X1003: GCNanoUltraV（版本 0x1003）
 *  - LV_VG_LITE_GPU_GCNANOULTRAV_0X1003: GCNanoUltraV (revision 0x1003)
 */
#define LV_VG_LITE_GPU LV_VG_LITE_GPU_GC255_0X40A

/** GPU 基地址 */
#define LV_VG_LITE_HAL_GPU_BASE_ADDRESS 0x40240000
/** GPU base address */

#endif /*LV_USE_VG_LITE_DRIVER*/

/** 用 ThorVG 模拟 VG-Lite 硬件，用于在 PC 模拟器上调试和测试。
 *  需要内部或外部的 ThorVG 库。
 *  Simulate VG-Lite hardware with ThorVG for debugging and testing on a PC simulator.
 *  Requires the internal or an external ThorVG library.
 *
 *  启用前提：LV_USE_THORVG
 *  Enable: LV_USE_THORVG
 */
#define LV_USE_VG_LITE_THORVG 0

#if LV_USE_VG_LITE_THORVG
/** LVGL 混合模式 */
#define LV_VG_LITE_THORVG_LVGL_BLEND_SUPPORT 0
/** LVGL blend modes */

/** YUV 颜色格式 */
#define LV_VG_LITE_THORVG_YUV_SUPPORT 0
/** YUV color formats */

/** 线性渐变扩展 */
#define LV_VG_LITE_THORVG_LINEAR_GRADIENT_EXT_SUPPORT 0
/** Linear gradient extension */

/** 16 像素对齐 */
#define LV_VG_LITE_THORVG_16PIXELS_ALIGN 1
/** 16 pixel alignment */

/** 缓冲区地址对齐（字节） */
#define LV_VG_LITE_THORVG_BUF_ADDR_ALIGN 64
/** Buffer address alignment (bytes) */

/** 多线程渲染 */
#define LV_VG_LITE_THORVG_THREAD_RENDER 0
/** Multi-threaded rendering */

#endif /*LV_USE_VG_LITE_THORVG*/
#endif /*LV_USE_DRAW_VG_LITE*/

/** 使用瑞萨 RA 平台上搭载的 Dave2D GPU 加速绘制。 */
#define LV_USE_DRAW_DAVE2D 0
/** Accelerate drawing with the Dave2D GPU found on Renesas RA platforms. */

/** 使用 Think Silicon（TSi）NemaGFX GPU 库加速绘制。 */
#define LV_USE_NEMA_GFX 0
/** Accelerate drawing with the Think Silicon (TSi) NemaGFX GPU library. */

#if LV_USE_NEMA_GFX
/** 围绕绘制缓冲区清理和失效 CPU 缓存，使 GPU 能看到一致的数据。
 *  对于带数据缓存的内核是必需的。
 */
#define LV_NEMA_USE_CACHE 0
/** Clean and invalidate the CPU cache around draw buffers so the GPU sees
 *  coherent data. Needed on cores with a data cache.
 */

#if LV_NEMA_USE_CACHE
/** 缓存 HAL 头文件 */
#define LV_NEMA_CACHE_HAL_INCLUDE "stm32u5xx_hal.h"
/** Cache HAL header */

#endif /*LV_NEMA_USE_CACHE*/

/** 按目标 CPU 内核选择打包的 NemaGFX 库和头文件。
 *  Bundled NemaGFX library and headers to use, per target CPU core.
 *  None（无）会在构建时发出警告，并回退到 Cortex-M33（Rev C）。
 *  None warns at build time and falls back to Cortex-M33 (Rev C).
 *  可选值：
 *  Possible values:
 *  - LV_NEMA_LIB_NONE: 无
 *  - LV_NEMA_LIB_NONE
 *  - LV_NEMA_LIB_M33_REVC: Cortex-M33（Rev C 版本）
 *  - LV_NEMA_LIB_M33_REVC: Cortex-M33 (Rev C)
 *  - LV_NEMA_LIB_M33_NEMAPVG: Cortex-M33（NemaPVG）
 *  - LV_NEMA_LIB_M33_NEMAPVG: Cortex-M33 (NemaPVG)
 *  - LV_NEMA_LIB_M55: Cortex-M55
 *  - LV_NEMA_LIB_M55: Cortex-M55
 *  - LV_NEMA_LIB_M7: Cortex-M7
 *  - LV_NEMA_LIB_M7: Cortex-M7
 */
#define LV_USE_NEMA_LIB LV_NEMA_LIB_NONE

/** STM32 使用 LVGL 自带的 HAL。Custom（自定义）表示由应用自己
 *  提供 NemaGFX HAL（nema_hal.c）。
 *  STM32 uses the HAL bundled with LVGL. Custom means the application
 *  provides the NemaGFX HAL (nema_hal.c) itself.
 *  可选值：
 *  Possible values:
 *  - LV_NEMA_HAL_CUSTOM: 自定义
 *  - LV_NEMA_HAL_CUSTOM
 *  - LV_NEMA_HAL_STM32: STM32
 *  - LV_NEMA_HAL_STM32
 */
#define LV_USE_NEMA_HAL LV_NEMA_HAL_CUSTOM

#if LV_USE_NEMA_HAL == LV_NEMA_HAL_STM32
/** STM32 HAL 头文件 */
#define LV_NEMA_STM32_HAL_INCLUDE "stm32u5xx_hal.h"
/** STM32 HAL header */

/** 包含 LV_NEMA_CUSTOM_INCLUDE 指定的头文件，以覆盖
 *  如 LV_NEMA_STM32_HAL_ATTRIBUTE_POOL_MEM 等
 *  NemaGFX/STM32 HAL 特定的宏。
 */
#define LV_NEMA_USE_CUSTOM_INCLUDE 0
/** Include the header given by LV_NEMA_CUSTOM_INCLUDE to override
 *  NemaGFX/STM32 HAL-specific macros such as
 *  LV_NEMA_STM32_HAL_ATTRIBUTE_POOL_MEM.
 */

#endif /*LV_USE_NEMA_HAL == LV_NEMA_HAL_STM32*/

#if LV_NEMA_USE_CUSTOM_INCLUDE
/** 用于覆盖 NemaGFX/STM32 HAL 特定宏的可选头文件。
 *  Optional header to override NemaGFX/STM32 HAL-specific macros.
 *
 *  LV_NEMA_STM32_HAL_ATTRIBUTE_POOL_MEM
 *    应用于 STM32 目标上 NemaGFX 内存池的属性宏。
 *    用于将内存池放到 NemaGFX DMA 可访问的特定 RAM 区域。
 *    例如 __attribute__((section(".nema_pool")))
 */
#define LV_NEMA_CUSTOM_INCLUDE ""
/** Optional header to override NemaGFX/STM32 HAL-specific macros.
 *
 *  LV_NEMA_STM32_HAL_ATTRIBUTE_POOL_MEM
 *    Attribute applied to the NemaGFX memory pool on STM32 targets.
 *    Used to place the pool in a specific RAM region accessible by
 *    the NemaGFX DMA.
 *    e.g. __attribute__((section(".nema_pool")))
 */

#endif /*LV_NEMA_USE_CUSTOM_INCLUDE*/

/** 在 NemaGFX 之上使用 NemaVG 绘制矢量图形（lv_vector_dsc）。 */
#define LV_USE_NEMA_VG 0
/** Draw vector graphics (lv_vector_dsc) with NemaVG on top of NemaGFX. */

/** NemaVG 初始化的画布宽度。结合垂直分辨率，它也会决定
 *  STM32 上 NemaGFX 内存池的大小（RESX * RESY + 10KB）。
 *  Canvas width NemaVG is initialized for. With the vertical resolution it also
 *  sizes the NemaGFX memory pool on STM32 (RESX * RESY + 10KB).
 */
#define LV_NEMA_GFX_MAX_RESX 800

/** NemaVG 初始化的画布高度。 */
#define LV_NEMA_GFX_MAX_RESY 600
/** Canvas height NemaVG is initialized for. */

#endif /*LV_USE_NEMA_GFX*/

/** 使用 NXP i.MX RT SoC 的 PXP（像素流水线）
 *  引擎加速混合、填充和变换。
 *  Accelerate blends, fills and transforms with the PXP (Pixel Pipeline)
 *  engine of NXP i.MX RT SoCs.
 */
#define LV_USE_DRAW_PXP 0

#if LV_USE_DRAW_PXP
/** 使用 PXP 而不是 CPU 来旋转渲染后的显示缓冲区。 */
#define LV_USE_ROTATE_PXP 0
/** Rotate the rendered display buffer with the PXP instead of the CPU. */

#if LV_USE_OS != LV_OS_NONE
/** 在独立线程中调度 PXP 操作，使 CPU 可以并行继续渲染。需要操作系统。
 *  Dispatch PXP operations from their own thread so the CPU can keep
 *  rendering in parallel. Needs an OS.
 */
#define LV_USE_PXP_DRAW_THREAD 1

#endif /*LV_USE_OS != LV_OS_NONE*/

/** 检查每次 PXP 调用的状态，失败时断言。在调试新板卡时有用。
 *  Check the status of every PXP call and assert on failure. Useful while
 *  bringing up a board.
 */
#define LV_USE_PXP_ASSERT 0

#endif /*LV_USE_DRAW_PXP*/

/** 使用 Espressif SoC 的 PPA（像素处理加速器）
 *  外设加速混合、填充和变换。
 *  Accelerate blends, fills and transforms with the PPA (Pixel Processing
 *  Accelerator) peripheral of Espressif SoCs.
 *
 *  启用前提：LV_USE_DRAW_SW
 *  Enable: LV_USE_DRAW_SW
 */
#define LV_USE_PPA 0

#if LV_USE_PPA
/** 让 PPA 也绘制图像。仅限简单情况：未缩放、
 *  未旋转、完全不透明且没有遮罩。
 */
#define LV_USE_PPA_IMG 0
/** Let the PPA also draw images. Only simple cases qualify: unscaled,
 *  unrotated, fully opaque and without masks.
 */

/* 突发传输长度（字节） */
/* Burst length (bytes) */
#define LV_PPA_BURST_LENGTH 128

#endif /*LV_USE_PPA*/

/** 使用 STM32 DMA2D 外设加速混合、填充和图像解码。 */
#define LV_USE_DRAW_DMA2D 1
/** Accelerate blends, fills and image decoding with the STM32 DMA2D peripheral. */

#if LV_USE_DRAW_DMA2D
/** 声明目标 STM32 系列的 DMA2D HAL API 的头文件。 */
#define LV_DRAW_DMA2D_HAL_INCLUDE "stm32u5xx_hal.h"
/** Header that declares the DMA2D HAL API of the target STM32 family. */

/** 异步执行 DMA2D 传输而不是等待它们完成（需要操作系统）。
 *  从 DMA2D 全局中断服务函数（ISR）中调用
 *  lv_draw_dma2d_transfer_complete_interrupt_handler()。
 */
#define LV_USE_DRAW_DMA2D_INTERRUPT 0
/** Run DMA2D transfers asynchronously instead of waiting for them (needs an OS).
 *  Call lv_draw_dma2d_transfer_complete_interrupt_handler() from the DMA2D global ISR.
 */

#endif /*LV_USE_DRAW_DMA2D*/

/** 使用 SiFli BF0 SoC 的 EPIC（增强像素图像合成器）
 *  引擎加速混合、填充、图像和文本。不支持的
 *  操作会回退到软件渲染。
 *  Accelerate blends, fills, images and text with the EPIC (Enhanced
 *  Pixel Image Compositor) engine of SiFli BF0 SoCs. Unsupported
 *  operations fall back to software rendering.
 *
 *  启用前提：LV_USE_DRAW_SW
 *  Enable: LV_USE_DRAW_SW
 */
#define LV_USE_SIFLI_EPIC 0

#if LV_USE_OS != LV_OS_NONE
#if LV_USE_SIFLI_EPIC
/** 在独立线程中调度 EPIC 操作，使 CPU 可以并行渲染。
 *  Dispatch EPIC operations from their own thread so the CPU can keep
 *  rendering in parallel.
 */
#define LV_USE_SIFLI_EPIC_DRAW_THREAD 1

/** 检查每次 EPIC 调用的状态，失败时断言。在调试新板卡时有用。
 *  Check the status of every EPIC call and assert on failure. Useful
 *  while bringing up a board.
 */
#define LV_USE_SIFLI_EPIC_ASSERT 0

#endif /*LV_USE_SIFLI_EPIC*/
#endif /*LV_USE_OS != LV_OS_NONE*/

/** 将绘制卸载到通过 SPI 连接的外部 EVE（FT81X/BT81X）图形控制器。 */
#define LV_USE_DRAW_EVE 0
/** Offload drawing to an external EVE (FT81X/BT81X) graphics controller over SPI. */

#if LV_USE_DRAW_EVE
/** 所连接控制器的代数：2 = FT81x，3 = BT815/BT816，
 *  4 = BT817/BT818。代数越高，暴露的命令和寄存器越多。
 */
#define LV_DRAW_EVE_EVE_GENERATION 4
/** Generation of the connected controller: 2 = FT81x, 3 = BT815/BT816,
 *  4 = BT817/BT818. Higher generations expose more commands and registers.
 */

/** 每次 SPI 传输前缓冲的字节数。0 禁用缓冲；
 *  低于 4 的值按 0 处理。
 */
#define LV_DRAW_EVE_WRITE_BUFFER_SIZE 2048
/** Bytes buffered before each SPI transmission. 0 disables buffering;
 *  values below 4 are treated as 0.
 */

#endif /*LV_USE_DRAW_EVE*/

/** 使用 NXP G2D API（i.MX 2D GPU）加速混合、填充和图像块传送。
 *  需要 g2d 库及其头文件。
 *  Accelerate blends, fills and image blits with the NXP G2D API (i.MX 2D GPU).
 *  Requires the g2d library and its headers.
 *
 *  启用前提：LV_USE_DRAW_SW
 *  Enable: LV_USE_DRAW_SW
 */
#define LV_USE_DRAW_G2D 0

#if LV_USE_DRAW_G2D
/** 为 G2D 绘制单元映射的最大缓冲区数量，包括帧缓冲区
 *  和资源。表满后绘制会断言。
 */
#define LV_G2D_HASH_TABLE_SIZE 50
/** Maximum number of buffers mapped for the G2D draw unit, including frame
 *  buffers and assets. Drawing asserts once the table is full.
 */

#if LV_USE_OS != LV_OS_NONE
/** 在独立线程中调度 G2D 操作，使 CPU 可以并行渲染。需要操作系统。
 *  Dispatch G2D operations from their own thread so the CPU can keep
 *  rendering in parallel. Needs an OS.
 */
#define LV_USE_G2D_DRAW_THREAD 1

#endif /*LV_USE_OS != LV_OS_NONE*/

/** 检查每次 G2D 调用的状态，失败时断言。在调试新板卡时有用。
 *  Check the status of every G2D call and assert on failure. Useful while
 *  bringing up a board.
 */
#define LV_USE_G2D_ASSERT 0

#endif /*LV_USE_DRAW_G2D*/

/** 在 OpenGL / OpenGL ES 着色器之上使用 NanoVG 矢量库绘制。
 *  Draw with the NanoVG vector library on top of OpenGL / OpenGL ES shaders.
 *
 *  启用前提：LV_USE_NANOVG、LV_USE_OPENGLES、LV_USE_MATRIX
 *  Enable: LV_USE_NANOVG, LV_USE_OPENGLES, LV_USE_MATRIX
 */
#define LV_USE_DRAW_NANOVG 0

#if LV_USE_DRAW_NANOVG
/** 要编译的 NanoVG 着色器风格。必须与显示驱动
 *  创建的 OpenGL 上下文匹配。
 *  可选值：
 *  Possible values:
 *  - LV_NANOVG_BACKEND_GL2: OpenGL 2.0
 *  - LV_NANOVG_BACKEND_GL2: OpenGL 2.0
 *  - LV_NANOVG_BACKEND_GL3: OpenGL 3.0+
 *  - LV_NANOVG_BACKEND_GL3: OpenGL 3.0+
 *  - LV_NANOVG_BACKEND_GLES2: OpenGL ES 2.0
 *  - LV_NANOVG_BACKEND_GLES2: OpenGL ES 2.0
 *  - LV_NANOVG_BACKEND_GLES3: OpenGL ES 3.0+
 *  - LV_NANOVG_BACKEND_GLES3: OpenGL ES 3.0+
 */
#define LV_NANOVG_BACKEND LV_NANOVG_BACKEND_GLES2

/** 保留为 GPU 纹理的已解码图像数量。 */
#define LV_NANOVG_IMAGE_CACHE_CNT 128
/** Number of decoded images kept as GPU textures. */

/** 文本绘制保留的已渲染字形数量。 */
#define LV_NANOVG_LETTER_CACHE_CNT 512
/** Number of rendered glyphs kept for text drawing. */

#endif /*LV_USE_DRAW_NANOVG*/

/** 使用 OpenGL ES 绘制，将已渲染控件和图像作为 GPU 纹理保留。
 *  Draw with OpenGL ES, keeping rendered widgets and images as GPU textures.
 *
 *  启用前提：LV_USE_OPENGLES
 *  Enable: LV_USE_OPENGLES
 */
#define LV_USE_DRAW_OPENGLES 0

#if LV_USE_DRAW_OPENGLES
/** 缓存中保留的纹理数量。条目越多意味着重绘越少，
 *  但 GPU 内存占用越多。
 */
#define LV_DRAW_OPENGLES_TEXTURE_CACHE_COUNT 64
/** Number of textures kept in the cache. More entries mean fewer redraws
 *  but more GPU memory.
 */

#endif /*LV_USE_DRAW_OPENGLES*/

/** 使用 SDL 渲染器 API 渲染，将控件和图像缓存为 SDL 纹理。
 *  Render with the SDL renderer API, caching widgets and images as SDL textures.
 *
 *  启用前提：LV_USE_DRAW_SW
 *  Enable: LV_USE_DRAW_SW
 */
#define LV_USE_DRAW_SDL 0



/*============================================================================
 * INPUT DEVICES
 *============================================================================*/

/** 指针开始滚动前需要移动的距离。 */
#define LV_INDEV_DEF_SCROLL_LIMIT 10
/** Distance the pointer needs to travel before scrolling starts. */

/** 释放滚动后施加的减速。数值越大减速越快。 */
#define LV_INDEV_DEF_SCROLL_THROW 10
/** Slow-down applied after releasing a scroll. Greater value means faster slow-down. */

/** 滚动超过可滚动控件边缘时，减速该倍数。 */
#define LV_INDEV_DEF_SCROLL_ELASTIC_FACTOR 4
/** Scrolling past the edge of a scrollable widget is slower by this factor. */

/** 按下多久之后发送 `LV_EVENT_LONG_PRESSED` 事件（毫秒）。 */
#define LV_INDEV_DEF_LONG_PRESS_TIME 400
/** Press time after which `LV_EVENT_LONG_PRESSED` is sent. */

/** 连续 `LV_EVENT_LONG_PRESSED_REPEAT` 事件之间的时间（毫秒）。 */
#define LV_INDEV_DEF_LONG_PRESS_REP_TIME 100
/** Time between `LV_EVENT_LONG_PRESSED_REPEAT` events. */

/** 判定为双击或三击的两次连续点击之间的最大时间（毫秒）。 */
#define LV_INDEV_DEF_DOUBLE_CLICK_TIME 400
/** Max time between consecutive clicks to count as a double or triple click. */

/** 检测到手势前指针需要移动的距离。 */
#define LV_INDEV_DEF_GESTURE_LIMIT 50
/** Distance the pointer needs to travel before a gesture is detected. */

/** 释放时报告滑动手势所需的最小指针速度。 */
#define LV_INDEV_DEF_GESTURE_MIN_VELOCITY 3
/** Minimum pointer velocity at release to report a swipe. */

/** 编码器差值乘以该值后再除以 256。 */
#define LV_INDEV_DEF_ROTARY_SENSITIVITY 256
/** The encoder diff is multiplied by this value and divided by 256. */

/** 使用方向键根据位置在容器的子控件之间移动焦点。 */
#define LV_USE_GRIDNAV 0
/** Move focus between a container's children with arrow keys, based on their position. */

/** 从多点触控输入中检测捏合和旋转手势。需要浮点支持。
 *  Detect pinch and rotate gestures from multi-touch input. Requires float support.
 *
 *  启用前提：LV_USE_FLOAT
 *  Enable: LV_USE_FLOAT
 */
#define LV_USE_GESTURE_RECOGNITION 0

#if LV_USE_GESTURE_RECOGNITION
/** 发送捏合事件前手指需要捏合到的缩放比例。 */
#define LV_INDEV_DEF_GESTURE_PINCH_DOWN_THRESHOLD 75
/** Scale the fingers need to pinch down to before pinch events are sent. */

/** 发送捏合事件前手指需要放大到的缩放比例。 */
#define LV_INDEV_DEF_GESTURE_PINCH_UP_THRESHOLD 150
/** Scale the fingers need to pinch up to before pinch events are sent. */

/** 起始缩放比例高于此值的捏合手势会被丢弃。
 *  必须大于捏合放大的阈值。
 *  A pinch starting above this scale is discarded.
 *  Must be greater than the pinch out threshold.
 */
#define LV_INDEV_DEF_GESTURE_PINCH_MAX_INITIAL_SCALE 250

/** 发送旋转事件前手指需要旋转的角度。 */
#define LV_INDEV_DEF_GESTURE_ROTATION_THRESHOLD 200
/** Angle the fingers need to rotate by before rotation events are sent. */

#endif /*LV_USE_GESTURE_RECOGNITION*/


/*============================================================================
 * CORE
 *============================================================================*/

/** 通过向每个 lv_obj_t 添加 2 个 32 位变量来加速样式属性查找。 */
#define LV_OBJ_STYLE_CACHE 1
/** Speed up style property lookups by adding 2 x 32 bit variables to each lv_obj_t. */

/** 控件名称（lv_obj_set_name） */
#define LV_USE_OBJ_NAME 0
/** Widget names (lv_obj_set_name) */

/** 控件 ID（lv_obj_set_id） */
#define LV_USE_OBJ_ID 0
/** Widget id (lv_obj_set_id) */

#if LV_USE_OBJ_ID
/** 创建控件时自动分配 ID */
#define LV_OBJ_ID_AUTO_ASSIGN 1
/** Automatic ID assignment on widget creation */

/** 使用内置的控件 ID 处理函数：
 *  Use builtin obj ID handler functions:
 *  - lv_obj_assign_id:    控件创建时调用。为每个控件类使用独立的计数器作为 ID。
 *  - lv_obj_assign_id:       Called when a widget is created. Use a separate counter for each widget class as an ID.
 *  - lv_obj_id_compare:     比较 ID 以判断是否与请求的值匹配。
 *  - lv_obj_id_compare:      Compare the ID to decide if it matches with a requested value.
 *  - lv_obj_stringify_id:   返回字符串形式的标识符，例如 "button3"。
 *  - lv_obj_stringify_id:    Return string-ified identifier, e.g. "button3".
 *  - lv_obj_free_id:        不做任何事，因为 ID 不占用内存。
 *  - lv_obj_free_id:         Does nothing, as there is no memory allocation for the ID.
 *  关闭时这些函数需要由用户实现。
 *  When disabled these functions needs to be implemented by the user.
 */
#define LV_USE_OBJ_ID_BUILTIN 1

#endif /*LV_USE_OBJ_ID*/

/** 通过一个通用的基于属性 ID 的 API 获取/设置任何控件的样式和属性。 */
#define LV_USE_OBJ_PROPERTY 0
/** Get and set any widget style or attribute through a single generic property ID based API. */

#if LV_USE_OBJ_PROPERTY
/** 为每个控件类添加名称表，以便按名称访问属性。
 *  注意，常量表会增大 Flash 占用。
 *  Add a name table to every widget class, so the property can be accessed by name.
 *  Note, the const table will increase flash usage.
 */
#define LV_USE_OBJ_PROPERTY_NAME 1

#endif /*LV_USE_OBJ_PROPERTY*/

/** 将你自己的数据和析构回调附加到事件、控件、观察者、
 *  动画、定时器、组、显示、输入设备和主题上，这样当
 *  LVGL 释放它们时你的资源也能被清理。
 */
#define LV_USE_EXT_DATA 0
/** Attach your own data plus a destructor callback to events, widgets, observers,
 *  animations, timers, groups, displays, input devices and themes, so your resources
 *  are cleaned up when LVGL frees them.
 */

/** 对需要亚像素精度的坐标和值使用 `float` 而不是 `int32_t`。 */
#define LV_USE_FLOAT 0
/** Use `float` instead of `int32_t` for coordinates and values that need sub-pixel precision. */

/** 将控件绑定到主题变量，值变化时自动更新。 */
#define LV_USE_OBSERVER 1
/** Bind widgets to subject variables so they update automatically when the value changes. */

/** 使用 lv_translation_get() 按 ID 查找所选语言的字符串。 */
#define LV_USE_TRANSLATION 0
/** Look up strings by ID for the selected language with lv_translation_get(). */

/** 颜色滤镜样式 */
#define LV_USE_COLOR_FILTER 0
/** Color filter style */



/*============================================================================
 * LOGGING
 *============================================================================*/

/** 日志功能 */
#define LV_USE_LOG 0
/** Logging */

#if LV_USE_LOG
/** 默认日志详细程度
 *  Default log verbosity
 *  可选值：
 *  Possible values:
 *  - LV_LOG_LEVEL_TRACE: 关于一切事物的详细信息
 *  - LV_LOG_LEVEL_TRACE: detailed information about everything
 *  - LV_LOG_LEVEL_INFO: 重要事件
 *  - LV_LOG_LEVEL_INFO: important events
 *  - LV_LOG_LEVEL_WARN: 发生了不希望发生的事但未造成问题
 *  - LV_LOG_LEVEL_WARN: something unwanted happened but caused no problem
 *  - LV_LOG_LEVEL_ERROR: 可能导致系统失败的关键问题
 *  - LV_LOG_LEVEL_ERROR: critical issues where the system may fail
 *  - LV_LOG_LEVEL_USER: 仅记录用户添加的日志
 *  - LV_LOG_LEVEL_USER: only logs added by the user
 *  - LV_LOG_LEVEL_NONE: 不记录任何内容
 *  - LV_LOG_LEVEL_NONE: nothing is logged
 */
#define LV_LOG_LEVEL LV_LOG_LEVEL_WARN

/** 若不设置，用户需要通过 lv_log_register_print_cb() 注册回调。 */
#define LV_LOG_PRINTF 0
/** If not set, the user needs to register a callback with lv_log_register_print_cb(). */

/** 为每条日志添加时间戳 */
#define LV_LOG_USE_TIMESTAMP 1
/** Add a timestamp to each log */

/** 为每条日志添加文件名和行号 */
#define LV_LOG_USE_FILE_LINE 1
/** Add the file name and line number to each log */

/** 内存 */
#define LV_LOG_TRACE_MEM 1
/** Memory */

/** 定时器 */
#define LV_LOG_TRACE_TIMER 1
/** Timer */

/** 输入设备 */
#define LV_LOG_TRACE_INDEV 1
/** Input devices */

/** 显示刷新 */
#define LV_LOG_TRACE_DISP_REFR 1
/** Display refresh */

/** 事件 */
#define LV_LOG_TRACE_EVENT 1
/** Events */

/** 控件创建 */
#define LV_LOG_TRACE_OBJ_CREATE 1
/** Widget creation */

/** 布局 */
#define LV_LOG_TRACE_LAYOUT 1
/** Layout */

/** 动画 */
#define LV_LOG_TRACE_ANIM 1
/** Animations */

/** 缓存 */
#define LV_LOG_TRACE_CACHE 1
/** Cache */

#endif /*LV_USE_LOG*/


/*============================================================================
 * THEMES
 *============================================================================*/

/** LVGL 的演示和示例使用的功能齐全的主题。 */
#define LV_USE_THEME_DEFAULT 1
/** Full-featured theme used by LVGL's demos and examples. */

#if LV_USE_THEME_DEFAULT
/** 深色模式 */
#define LV_THEME_DEFAULT_DARK 0
/** Dark mode */

/** 按下时控件放大 */
#define LV_THEME_DEFAULT_GROW 1
/** Grow on press */

/** 过渡时间（毫秒） */
#define LV_THEME_DEFAULT_TRANSITION_TIME 80
/** Transition time (ms) */

#endif /*LV_USE_THEME_DEFAULT*/

/** 极简样式，是自定义主题的一个很好的起点。 */
#define LV_USE_THEME_SIMPLE 1
/** Minimal styling, a good starting point for a custom theme. */

/** 面向 1 位显示（如电子纸和点阵面板）的样式。 */
#define LV_USE_THEME_MONO 1
/** Styling for 1-bit displays such as e-paper and dot-matrix panels. */



/*============================================================================
 * LAYOUTS
 *============================================================================*/

/** 将子控件排列为可换行、可伸缩的行或列，类似 CSS 中的 Flexbox。 */
#define LV_USE_FLEX 1
/** Arrange children in a row or column that wraps and grows, similar to Flexbox in CSS. */

/** 将子控件排列为行和列，类似 CSS 中的 Grid。 */
#define LV_USE_GRID 1
/** Arrange children in rows and columns, similar to Grid in CSS. */



/*============================================================================
 * IMAGE SETTINGS
 *============================================================================*/

/** 避免重复打开和解码相同图像，代价是占用 RAM。
 *  只使用内置图像格式时收益不大。
 *  Avoids repeatedly opening and decoding the same images, at the cost of RAM.
 *  Of little benefit with only the built-in image formats.
 */
#define LV_CACHE_DEF_SIZE 0

/** 避免重复读取图像头部，代价是占用 RAM。
 *  只使用内置图像格式时收益不大。
 *  Avoids repeatedly reading image headers, at the cost of RAM.
 *  Of little benefit with only the built-in image formats.
 */
#define LV_IMAGE_HEADER_CACHE_DEF_CNT 0

/** LVGL 行程编码（RLE）二进制图像格式的解码器。 */
#define LV_USE_RLE 0
/** Decoder for LVGL's run-length encoded binary image format. */

/** LZ4 压缩/解压函数，用于 LVGL 的压缩二进制图像。 */
#define LV_USE_LZ4 0
/** LZ4 compress/decompress functions, used by LVGL's compressed binary images. */

#if LV_USE_LZ4
/** 内置的 LZ4 */
#define LV_USE_LZ4_INTERNAL 1
/** Bundled LZ4 */

#endif /*LV_USE_LZ4*/

/** 将二进制图像解码到 RAM */
#define LV_BIN_DECODER_RAM_LOAD 0
/** Decode binary images to RAM */

/** PNG 解码器（LodePNG） */
#define LV_USE_LODEPNG 0
/** PNG decoder (LodePNG) */

/** PNG 解码器（libpng） */
#define LV_USE_LIBPNG 0
/** PNG decoder (libpng) */

/** BMP 解码器 */
#define LV_USE_BMP 0
/** BMP decoder */

/** 也支持分裂 JPEG，一种为嵌入式系统优化的自定义格式。 */
#define LV_USE_TJPGD 0
/** Also decodes split JPEG, a custom format optimized for embedded systems. */

/** 支持完整 JPEG 规范的高性能解码器。 */
#define LV_USE_LIBJPEG_TURBO 0
/** High-performance decoder supporting the complete JPEG specifications. */

/** WebP 解码器 */
#define LV_USE_LIBWEBP 0
/** WebP decoder */

/** SVG
 *
 *  启用前提：LV_USE_VECTOR_GRAPHIC
 *  Enable: LV_USE_VECTOR_GRAPHIC
 */
#define LV_USE_SVG 0

#if LV_USE_SVG
/** SVG 动画 */
#define LV_USE_SVG_ANIMATION 0
/** SVG animation */

/** SVG 调试日志 */
#define LV_USE_SVG_DEBUG 0
/** SVG debug logs */

#endif /*LV_USE_SVG*/


/*============================================================================
 * TEXT & FONT SETTINGS
 *============================================================================*/

/** 你的 IDE 或编辑器应设置为相同的字符编码。
 *  Your IDE or editor should be set to the same character encoding.
 *  可选值：
 *  Possible values:
 *  - LV_TXT_ENC_UTF8: UTF-8 编码
 *  - LV_TXT_ENC_UTF8
 *  - LV_TXT_ENC_ASCII: ASCII 编码
 *  - LV_TXT_ENC_ASCII
 */
#define LV_TXT_ENC LV_TXT_ENC_UTF8

/** 文本换行时作为断点（换行）的字符 */
#define LV_TXT_BREAK_CHARS " ,.;:-_)]}"
/** Characters to break (wrap) text on */

/** 如果某个单词至少这么长，就在"最合适"的位置断开。
 *  要禁用，请设置为 <= 0 的值。
 *  If a word is at least this long, will break wherever 'prettiest'.
 *  To disable, set to a value <= 0.
 */
#define LV_TXT_LINE_BREAK_LONG_LEN 0

#if LV_TXT_LINE_BREAK_LONG_LEN > 0
/** 长单词在断开前放在一行上的最少字符数。 */
#define LV_TXT_LINE_BREAK_LONG_PRE_MIN_LEN 3
/** Minimum number of characters in a long word to put on a line before a break. */

/** 长单词在断开后放在一行上的最少字符数 */
#define LV_TXT_LINE_BREAK_LONG_POST_MIN_LEN 3
/** Minimum number of characters in a long word to put on a line after a break */

#endif /*LV_TXT_LINE_BREAK_LONG_LEN > 0*/

/** 文本重新着色（recolor）的控制字符 */
#define LV_TXT_COLOR_CMD "#"
/** Text recoloring control character */

/** 允许混合从左到右（LTR）和从右到左（RTL）的文本。
 *  方向将根据 Unicode 双向算法处理：
 *  Allows mixing Left-to-Right and Right-to-Left texts.
 *  The direction will be processed according to the Unicode Bidirectional Algorithm:
 *  https://www.w3.org/International/articles/inline-bidi-markup/uba-basics
 */
#define LV_USE_BIDI 0

#if LV_USE_BIDI
/** 默认基本方向
 *  Default base direction
 *  可选值：
 *  Possible values:
 *  - LV_BASE_DIR_LTR: 从左到右
 *  - LV_BASE_DIR_LTR: Left-to-Right
 *  - LV_BASE_DIR_RTL: 从右到左
 *  - LV_BASE_DIR_RTL: Right-to-Left
 *  - LV_BASE_DIR_AUTO: 自动检测
 *  - LV_BASE_DIR_AUTO: Auto detect
 */
#define LV_BIDI_BASE_DIR_DEF LV_BASE_DIR_AUTO

#endif /*LV_USE_BIDI*/

/** 在这些语言中，字符应根据其在文本中的位置
 *  被替换为另一种形式。
 *  In these languages characters should be replaced with
 *  another form based on their position in the text.
 */
#define LV_USE_ARABIC_PERSIAN_CHARS 0

/** 包含 ASCII 字符集和一些符号的 Montserrat 字体，bpp = 4
 *  Montserrat fonts with ASCII range and some symbols using bpp = 4
 *  https://fonts.google.com/specimen/Montserrat
 */
#define LV_FONT_MONTSERRAT_8 0

/** Montserrat 10 号字体 */
#define LV_FONT_MONTSERRAT_10 0
/** Montserrat 10 */

/** Montserrat 12 号字体 */
#define LV_FONT_MONTSERRAT_12 0
/** Montserrat 12 */

/** Montserrat 14 号字体 */
#define LV_FONT_MONTSERRAT_14 1
/** Montserrat 14 */

/** Montserrat 16 号字体 */
#define LV_FONT_MONTSERRAT_16 0
/** Montserrat 16 */

/** Montserrat 18 号字体 */
#define LV_FONT_MONTSERRAT_18 0
/** Montserrat 18 */

/** Montserrat 20 号字体 */
#define LV_FONT_MONTSERRAT_20 1
/** Montserrat 20 */

/** Montserrat 22 号字体 */
#define LV_FONT_MONTSERRAT_22 0
/** Montserrat 22 */

/** Montserrat 24 号字体 */
#define LV_FONT_MONTSERRAT_24 0
/** Montserrat 24 */

/** Montserrat 26 号字体 */
#define LV_FONT_MONTSERRAT_26 0
/** Montserrat 26 */

/** Montserrat 28 号字体 */
#define LV_FONT_MONTSERRAT_28 0
/** Montserrat 28 */

/** Montserrat 30 号字体 */
#define LV_FONT_MONTSERRAT_30 0
/** Montserrat 30 */

/** Montserrat 32 号字体 */
#define LV_FONT_MONTSERRAT_32 0
/** Montserrat 32 */

/** Montserrat 34 号字体 */
#define LV_FONT_MONTSERRAT_34 0
/** Montserrat 34 */

/** Montserrat 36 号字体 */
#define LV_FONT_MONTSERRAT_36 0
/** Montserrat 36 */

/** Montserrat 38 号字体 */
#define LV_FONT_MONTSERRAT_38 0
/** Montserrat 38 */

/** Montserrat 40 号字体 */
#define LV_FONT_MONTSERRAT_40 0
/** Montserrat 40 */

/** Montserrat 42 号字体 */
#define LV_FONT_MONTSERRAT_42 0
/** Montserrat 42 */

/** Montserrat 44 号字体 */
#define LV_FONT_MONTSERRAT_44 0
/** Montserrat 44 */

/** Montserrat 46 号字体 */
#define LV_FONT_MONTSERRAT_46 0
/** Montserrat 46 */

/** Montserrat 48 号字体 */
#define LV_FONT_MONTSERRAT_48 0
/** Montserrat 48 */

/** Montserrat 28 号（压缩版） */
#define LV_FONT_MONTSERRAT_28_COMPRESSED 0
/** Montserrat 28 (compressed) */

/** Dejavu 16 号字体（波斯语、希伯来语、阿拉伯语） */
#define LV_FONT_DEJAVU_16_PERSIAN_HEBREW 0
/** Dejavu 16 (Persian, Hebrew, Arabic) */

/** 思源黑体 14 号（CJK，中日韩统一表意文字） */
#define LV_FONT_SOURCE_HAN_SANS_SC_14_CJK 0
/** SourceHanSansSC 14 (CJK) */

/** 思源黑体 16 号（CJK，中日韩统一表意文字） */
#define LV_FONT_SOURCE_HAN_SANS_SC_16_CJK 0
/** SourceHanSansSC 16 (CJK) */

/** 像素完美的等宽字体 */
#define LV_FONT_UNSCII_8 0
/** Pixel perfect monospaced fonts */

/** UNSCII 16 号字体 */
#define LV_FONT_UNSCII_16 0
/** UNSCII 16 */

/** 包含 LV_FONT_CUSTOM_INCLUDE 指定的头文件，以声明自定义
 *  字体（LV_FONT_CUSTOM_DECLARE）或覆盖字体相关宏。
 *  Include the header given by LV_FONT_CUSTOM_INCLUDE to declare custom
 *  fonts (LV_FONT_CUSTOM_DECLARE) or override font-related macros.
 */
#define LV_FONT_USE_CUSTOM_INCLUDE 0

#if LV_FONT_USE_CUSTOM_INCLUDE
/** 用于覆盖字体相关宏的可选头文件。
 *  Optional header to override font-related macros.
 *
 *  典型用途是通过 LV_FONT_CUSTOM_DECLARE 声明额外字体：
 *  Typical use is to declare extra fonts through LV_FONT_CUSTOM_DECLARE:
 *      #define LV_FONT_CUSTOM_DECLARE  LV_FONT_DECLARE(my_font_24)
 *
 *  也可以用来将默认字体覆盖为自定义字体：
 *  It can also be used to override the default font to a custom one:
 *      #define LV_FONT_DEFAULT         &my_font_24
 */
#define LV_FONT_CUSTOM_INCLUDE ""

#endif /*LV_FONT_USE_CUSTOM_INCLUDE*/

/** 启用此选项可将 LV_FONT_DEFAULT 设置为自定义字体，
 *  而不是使用下面的内置字体。启用后，
 *  内置默认字体的选择会被隐藏，因此你必须自己定义
 *  LV_FONT_DEFAULT，方式如下：
 *  Enable this to set LV_FONT_DEFAULT to a font you define yourself
 *  rather than one of the built-in fonts below. When enabled, the
 *  built-in default-font selection is hidden, so you MUST define
 *  LV_FONT_DEFAULT yourself, either:
 *    - 在构建系统中，例如 -DLV_FONT_DEFAULT='&my_font_24'，或
 *    - from the build system, e.g. -DLV_FONT_DEFAULT='&my_font_24', or
 *    - 在 LV_FONT_CUSTOM_INCLUDE 指定的头文件中，例如
 *    - in the header given by LV_FONT_CUSTOM_INCLUDE, e.g.
 *          #define LV_FONT_CUSTOM_DECLARE  LV_FONT_DECLARE(my_font_24)
 *          #define LV_FONT_DEFAULT         &my_font_24
 *
 *  如果没有这样做，LV_FONT_DEFAULT 会回退到内置字体，
 *  而该字体已不再编译进工程，会导致链接错误。
 *  If you do not, LV_FONT_DEFAULT falls back to a builtin font,
 *  which is no longer compiled in, causing a link error.
 */
#define LV_USE_CUSTOM_FONT_DEFAULT 0

#if !LV_USE_CUSTOM_FONT_DEFAULT
/** 主题和未显式设置字体的控件使用的字体。
 *  Font used by the themes and by widgets that do not set one explicitly.
 *  可选值：
 *  Possible values:
 *  - LV_FONT_DEFAULT_MONTSERRAT_8 （启用：LV_FONT_MONTSERRAT_8）
 *  - LV_FONT_DEFAULT_MONTSERRAT_8 (enable: LV_FONT_MONTSERRAT_8)
 *  - LV_FONT_DEFAULT_MONTSERRAT_10 （启用：LV_FONT_MONTSERRAT_10）
 *  - LV_FONT_DEFAULT_MONTSERRAT_10 (enable: LV_FONT_MONTSERRAT_10)
 *  - LV_FONT_DEFAULT_MONTSERRAT_12 （启用：LV_FONT_MONTSERRAT_12）
 *  - LV_FONT_DEFAULT_MONTSERRAT_12 (enable: LV_FONT_MONTSERRAT_12)
 *  - LV_FONT_DEFAULT_MONTSERRAT_14 （启用：LV_FONT_MONTSERRAT_14）
 *  - LV_FONT_DEFAULT_MONTSERRAT_14 (enable: LV_FONT_MONTSERRAT_14)
 *  - LV_FONT_DEFAULT_MONTSERRAT_16 （启用：LV_FONT_MONTSERRAT_16）
 *  - LV_FONT_DEFAULT_MONTSERRAT_16 (enable: LV_FONT_MONTSERRAT_16)
 *  - LV_FONT_DEFAULT_MONTSERRAT_18 （启用：LV_FONT_MONTSERRAT_18）
 *  - LV_FONT_DEFAULT_MONTSERRAT_18 (enable: LV_FONT_MONTSERRAT_18)
 *  - LV_FONT_DEFAULT_MONTSERRAT_20 （启用：LV_FONT_MONTSERRAT_20）
 *  - LV_FONT_DEFAULT_MONTSERRAT_20 (enable: LV_FONT_MONTSERRAT_20)
 *  - LV_FONT_DEFAULT_MONTSERRAT_22 （启用：LV_FONT_MONTSERRAT_22）
 *  - LV_FONT_DEFAULT_MONTSERRAT_22 (enable: LV_FONT_MONTSERRAT_22)
 *  - LV_FONT_DEFAULT_MONTSERRAT_24 （启用：LV_FONT_MONTSERRAT_24）
 *  - LV_FONT_DEFAULT_MONTSERRAT_24 (enable: LV_FONT_MONTSERRAT_24)
 *  - LV_FONT_DEFAULT_MONTSERRAT_26 （启用：LV_FONT_MONTSERRAT_26）
 *  - LV_FONT_DEFAULT_MONTSERRAT_26 (enable: LV_FONT_MONTSERRAT_26)
 *  - LV_FONT_DEFAULT_MONTSERRAT_28 （启用：LV_FONT_MONTSERRAT_28）
 *  - LV_FONT_DEFAULT_MONTSERRAT_28 (enable: LV_FONT_MONTSERRAT_28)
 *  - LV_FONT_DEFAULT_MONTSERRAT_30 （启用：LV_FONT_MONTSERRAT_30）
 *  - LV_FONT_DEFAULT_MONTSERRAT_30 (enable: LV_FONT_MONTSERRAT_30)
 *  - LV_FONT_DEFAULT_MONTSERRAT_32 （启用：LV_FONT_MONTSERRAT_32）
 *  - LV_FONT_DEFAULT_MONTSERRAT_32 (enable: LV_FONT_MONTSERRAT_32)
 *  - LV_FONT_DEFAULT_MONTSERRAT_34 （启用：LV_FONT_MONTSERRAT_34）
 *  - LV_FONT_DEFAULT_MONTSERRAT_34 (enable: LV_FONT_MONTSERRAT_34)
 *  - LV_FONT_DEFAULT_MONTSERRAT_36 （启用：LV_FONT_MONTSERRAT_36）
 *  - LV_FONT_DEFAULT_MONTSERRAT_36 (enable: LV_FONT_MONTSERRAT_36)
 *  - LV_FONT_DEFAULT_MONTSERRAT_38 （启用：LV_FONT_MONTSERRAT_38）
 *  - LV_FONT_DEFAULT_MONTSERRAT_38 (enable: LV_FONT_MONTSERRAT_38)
 *  - LV_FONT_DEFAULT_MONTSERRAT_40 （启用：LV_FONT_MONTSERRAT_40）
 *  - LV_FONT_DEFAULT_MONTSERRAT_40 (enable: LV_FONT_MONTSERRAT_40)
 *  - LV_FONT_DEFAULT_MONTSERRAT_42 （启用：LV_FONT_MONTSERRAT_42）
 *  - LV_FONT_DEFAULT_MONTSERRAT_42 (enable: LV_FONT_MONTSERRAT_42)
 *  - LV_FONT_DEFAULT_MONTSERRAT_44 （启用：LV_FONT_MONTSERRAT_44）
 *  - LV_FONT_DEFAULT_MONTSERRAT_44 (enable: LV_FONT_MONTSERRAT_44)
 *  - LV_FONT_DEFAULT_MONTSERRAT_46 （启用：LV_FONT_MONTSERRAT_46）
 *  - LV_FONT_DEFAULT_MONTSERRAT_46 (enable: LV_FONT_MONTSERRAT_46)
 *  - LV_FONT_DEFAULT_MONTSERRAT_48 （启用：LV_FONT_MONTSERRAT_48）
 *  - LV_FONT_DEFAULT_MONTSERRAT_48 (enable: LV_FONT_MONTSERRAT_48)
 *  - LV_FONT_DEFAULT_MONTSERRAT_28_COMPRESSED （启用：LV_FONT_MONTSERRAT_28_COMPRESSED）
 *  - LV_FONT_DEFAULT_MONTSERRAT_28_COMPRESSED (enable: LV_FONT_MONTSERRAT_28_COMPRESSED)
 *  - LV_FONT_DEFAULT_DEJAVU_16_PERSIAN_HEBREW: Dejavu 16 号（波斯语、希伯来语、阿拉伯语）（启用：LV_FONT_DEJAVU_16_PERSIAN_HEBREW）
 *  - LV_FONT_DEFAULT_DEJAVU_16_PERSIAN_HEBREW: Dejavu 16 (Persian, Hebrew, Arabic) (enable: LV_FONT_DEJAVU_16_PERSIAN_HEBREW)
 *  - LV_FONT_DEFAULT_SOURCE_HAN_SANS_SC_14_CJK （启用：LV_FONT_SOURCE_HAN_SANS_SC_14_CJK）
 *  - LV_FONT_DEFAULT_SOURCE_HAN_SANS_SC_14_CJK (enable: LV_FONT_SOURCE_HAN_SANS_SC_14_CJK)
 *  - LV_FONT_DEFAULT_SOURCE_HAN_SANS_SC_16_CJK （启用：LV_FONT_SOURCE_HAN_SANS_SC_16_CJK）
 *  - LV_FONT_DEFAULT_SOURCE_HAN_SANS_SC_16_CJK (enable: LV_FONT_SOURCE_HAN_SANS_SC_16_CJK)
 *  - LV_FONT_DEFAULT_UNSCII_8 （启用：LV_FONT_UNSCII_8）
 *  - LV_FONT_DEFAULT_UNSCII_8 (enable: LV_FONT_UNSCII_8)
 *  - LV_FONT_DEFAULT_UNSCII_16 （启用：LV_FONT_UNSCII_16）
 *  - LV_FONT_DEFAULT_UNSCII_16 (enable: LV_FONT_UNSCII_16)
 */
#define LV_FONT_DEFAULT LV_FONT_DEFAULT_MONTSERRAT_14

#endif /*!LV_USE_CUSTOM_FONT_DEFAULT*/

/** 使用更大的内部偏移量，使包含大量字形的字体保持可寻址。
 *  确切限制取决于字体大小、字面和格式，但如果你在超过约
 *  10,000 个字符的字体上遇到问题，请启用它。
 */
#define LV_FONT_FMT_TXT_LARGE 0
/** Use larger internal offsets so fonts with many glyphs stay addressable.
 *  The exact limit depends on font size, face and format, but enable it if
 *  you see issues with fonts above roughly 10,000 characters.
 */

/** 压缩字体 */
#define LV_USE_FONT_COMPRESSED 0
/** Compressed fonts */

/** 当字体中缺少某个字形时，绘制一个占位矩形而不是什么都不画。 */
#define LV_USE_FONT_PLACEHOLDER 1
/** Draw a placeholder rectangle instead of nothing when a glyph is missing
 *  from the font.
 */

/** 按名称加载字体，在控件之间共享，并通过引用计数释放。
 *  Load fonts by name, share them between widgets and free them by reference
 *  counting.
 */
#define LV_USE_FONT_MANAGER 0

#if LV_USE_FONT_MANAGER
/** 字体名称最大长度（字符数） */
#define LV_FONT_MANAGER_NAME_MAX_LEN 32
/** Font name max length (characters) */

#endif /*LV_USE_FONT_MANAGER*/

/** 在 label 和 span 控件中使用图像作为字形，例如渲染表情符号。 */
#define LV_USE_IMGFONT 0
/** Use images as glyphs in label and span widgets, e.g. to render emojis. */

/** FreeType 字体引擎 */
#define LV_USE_FREETYPE 0
/** FreeType */

#if LV_USE_FREETYPE
/** 启用后，FreeType 将使用 LVGL 的内存分配器和文件系统
 *  抽象，而不是平台默认实现。
 */
#define LV_FREETYPE_USE_LVGL_PORT 0
/** When enabled, FreeType will use LVGL's 
 * ory allocator and file system
 *  abstraction instead of the platform defaults.
 */

/** 字形缓存大小（字形数） */
#define LV_FREETYPE_CACHE_FT_GLYPH_CNT 256
/** Glyph cache size (glyphs) */

#if LV_USE_OS == LV_OS_NONE
/** L1 字形度量缓存（无锁，仅单线程） */
#define LV_FREETYPE_CACHE_FT_GLYPH_L1 1
/** L1 glyph metrics cache (lock-free, single-thread only) */

#endif /*LV_USE_OS == LV_OS_NONE*/
#endif /*LV_USE_FREETYPE*/

/** 内置的 TTF 解码器 */
#define LV_USE_TINY_TTF 0
/** Built-in TTF decoder */

#if LV_USE_TINY_TTF
/** 从文件加载 TTF 数据 */
#define LV_TINY_TTF_FILE_SUPPORT 0
/** Load TTF data from files */

/** 字形缓存大小（字形数） */
#define LV_TINY_TTF_CACHE_GLYPH_CNT 128
/** Glyph cache size (glyphs) */

/** 字距调整缓存大小（条目数） */
#define LV_TINY_TTF_CACHE_KERNING_CNT 256
/** Kerning cache size (entries) */

#endif /*LV_USE_TINY_TTF*/


/*============================================================================
 * WIDGETS
 *============================================================================*/

/** 使这些控件在创建时被赋予默认值。
 *  Causes these widgets to be given default values at creation time.
 *  - lv_buttonmatrix_t:  获得默认映射：{"Btn1", "Btn2", "Btn3", "\n", "Btn4", "Btn5", ""}，否则映射未设置。
 *  - lv_buttonmatrix_t:  Get default maps:  {"Btn1", "Btn2", "Btn3", "\n", "Btn4", "Btn5", ""}, else map not set.
 *  - lv_checkbox_t    :  字符串标签设置为 "Check box"，否则设置为空字符串。
 *  - lv_checkbox_t    :  String label set to "Check box", else set to empty string.
 *  - lv_dropdown_t    :  选项设置为 "Option 1", "Option 2", "Option 3"，否则不设置任何值。
 *  - lv_dropdown_t    :  Options set to "Option 1", "Option 2", "Option 3", else no values are set.
 *  - lv_roller_t      :  选项设置为 "Option 1", "Option 2", "Option 3", "Option 4", "Option 5"，否则不设置任何值。
 *  - lv_roller_t      :  Options set to "Option 1", "Option 2", "Option 3", "Option 4", "Option 5", else no values are set.
 *  - lv_label_t       :  文本设置为 "Text"，否则为空字符串。
 *  - lv_label_t       :  Text set to "Text", else empty string.
 *  - lv_arclabel_t   :   文本设置为 "Arced Text"，否则为空字符串。
 *  - lv_arclabel_t   :   Text set to "Arced Text", else empty string.
 */
#define LV_WIDGETS_HAS_DEFAULT_VALUE 1

/** 3D 纹理 */
#define LV_USE_3DTEXTURE 0
/** 3D texture */

/** 动画图像 */
#define LV_USE_ANIMIMG 1
/** Animated image */

/** 弧 */
#define LV_USE_ARC 1
/** Arc */

/** 弧标签 */
#define LV_USE_ARCLABEL 1
/** Arc label */

/** 进度条 */
#define LV_USE_BAR 1
/** Bar */

/** 生成 Code 128 条形码。
 *  Generates Code 128 barcodes.
 *
 *  启用前提：LV_USE_CANVAS
 *  Enable: LV_USE_CANVAS
 */
#define LV_USE_BARCODE 0

/** 按钮 */
#define LV_USE_BUTTON 1
/** Button */

/** 按钮矩阵 */
#define LV_USE_BUTTONMATRIX 1
/** Button matrix */

/** 日历 */
#define LV_USE_CALENDAR 1
/** Calendar */

#if LV_USE_CALENDAR
/** 一周从星期一开始 */
#define LV_CALENDAR_WEEK_STARTS_MONDAY 0
/** Week starts on Monday */

/** 星期一的缩写字符串 */
#define LV_MONDAY_STR "Mo"
/** Shortened string for Monday */

/** 星期二的缩写字符串 */
#define LV_TUESDAY_STR "Tu"
/** Shortened string for Tuesday */

/** 星期三的缩写字符串 */
#define LV_WEDNESDAY_STR "We"
/** Shortened string for Wednesday */

/** 星期四的缩写字符串 */
#define LV_THURSDAY_STR "Th"
/** Shortened string for Thursday */

/** 星期五的缩写字符串 */
#define LV_FRIDAY_STR "Fr"
/** Shortened string for Friday */

/** 星期六的缩写字符串 */
#define LV_SATURDAY_STR "Sa"
/** Shortened string for Saturday */

/** 星期日的缩写字符串 */
#define LV_SUNDAY_STR "Su"
/** Shortened string for Sunday */

/** 一月的字符串 */
#define LV_JANUARY_STR "January"
/** String for January */

/** 二月的字符串 */
#define LV_FEBRUARY_STR "February"
/** String for February */

/** 三月的字符串 */
#define LV_MARCH_STR "March"
/** String for March */

/** 四月的字符串 */
#define LV_APRIL_STR "April"
/** String for April */

/** 五月的字符串 */
#define LV_MAY_STR "May"
/** String for May */

/** 六月的字符串 */
#define LV_JUNE_STR "June"
/** String for June */

/** 七月的字符串 */
#define LV_JULY_STR "July"
/** String for July */

/** 八月的字符串 */
#define LV_AUGUST_STR "August"
/** String for August */

/** 九月的字符串 */
#define LV_SEPTEMBER_STR "September"
/** String for September */

/** 十月的字符串 */
#define LV_OCTOBER_STR "October"
/** String for October */

/** 十一月的字符串 */
#define LV_NOVEMBER_STR "November"
/** String for November */

/** 十二月的字符串 */
#define LV_DECEMBER_STR "December"
/** String for December */

/** 带箭头按钮的头部 */
#define LV_USE_CALENDAR_HEADER_ARROW 1
/** Header with arrow buttons */

/** 带下拉框的头部 */
#define LV_USE_CALENDAR_HEADER_DROPDOWN 1
/** Header with dropdowns */

/** 中国农历 */
#define LV_USE_CALENDAR_CHINESE 0
/** Chinese calendar */

#endif /*LV_USE_CALENDAR*/

/** 画布
 *  Canvas
 *
 *  启用前提：LV_USE_IMAGE
 *  Enable: LV_USE_IMAGE
 */
#define LV_USE_CANVAS 1

/** 图表 */
#define LV_USE_CHART 1
/** Chart */

/** 复选框 */
#define LV_USE_CHECKBOX 1
/** Checkbox */

/** 下拉框
 *  Dropdown
 *
 *  启用前提：LV_USE_LABEL
 *  Enable: LV_USE_LABEL
 */
#define LV_USE_DROPDOWN 1

/** 使用 FFmpeg 解码图像和播放视频。支持所有主流图像
 *  格式，因此不要与其他图像解码器同时启用。
 */
#define LV_USE_FFMPEG 0
/** Decodes images and plays videos with FFmpeg. It supports all major image
 *  formats, so do not enable other image decoders together with it.
 */

#if LV_USE_FFMPEG
/** 将输入流信息打印到 stderr，并保持 FFmpeg 日志
 *  启用（否则会被静默）。
 */
#define LV_FFMPEG_DUMP_FORMAT 0
/** Print the input stream information to stderr and keep FFmpeg logging
 *  enabled (it is silenced otherwise).
 */

/** 启用后无法再打开 URL。FFmpeg 图像解码器
 *  始终使用 LVGL 文件系统，与该选项无关。
 */
#define LV_FFMPEG_PLAYER_USE_LV_FS 0
/** URLs can no longer be opened once this is enabled. The FFmpeg image
 *  decoder always uses the LVGL file system regardless of this option.
 */

#endif /*LV_USE_FFMPEG*/

/** GIF 解码器 */
#define LV_USE_GIF 0
/** GIF decoder */

#if LV_USE_GIF
/** 以额外 16KB RAM 为代价加速播放。 */
#define LV_GIF_CACHE_DECODE_DATA 0
/** Speeds up playback at the cost of an extra 16KB of RAM. */

/** 更宽的 GIF 会被拒绝；提高此值会增加内存占用。 */
#define LV_GIF_MAX_WIDTH 480
/** Wider GIFs are rejected; raising this value increases memory usage. */

/** 更高的 GIF 会被拒绝；此值不影响内存占用。 */
#define LV_GIF_MAX_HEIGHT 32768
/** Taller GIFs are rejected; this value has no impact on memory usage. */

#endif /*LV_USE_GIF*/

/** 解析和渲染 3D 模型（.gltf/.glb）。
 *  Parses and renders 3D models (.gltf/.glb).
 *
 *  启用前提：LV_USE_3DTEXTURE
 *  Enable: LV_USE_3DTEXTURE
 */
#define LV_USE_GLTF 0

/** 需要 gstreamer-1.0、gstreamer-video-1.0 和 gstreamer-app-1.0
 *  开发库。
 *  Requires the gstreamer-1.0, gstreamer-video-1.0 and gstreamer-app-1.0
 *  development libraries.
 *
 *  启用前提：LV_USE_IMAGE
 *  Enable: LV_USE_IMAGE
 */
#define LV_USE_GSTREAMER 0

/** 图像 */
#define LV_USE_IMAGE 1
/** Image */

/** 图像按钮 */
#define LV_USE_IMAGEBUTTON 1
/** Image button */

/** 中文输入法，将键盘控件上输入的拼音
 *  转换为汉字。
 *  Chinese input method that converts Pinyin typed on a keyboard widget
 *  into Chinese characters.
 *
 *  启用前提：LV_USE_KEYBOARD
 *  Enable: LV_USE_KEYBOARD
 */
#define LV_USE_IME_PINYIN 0

#if LV_USE_IME_PINYIN
/** 9 键输入模式 */
#define LV_IME_PINYIN_USE_K9_MODE 1
/** 9-key input mode */

#if LV_IME_PINYIN_USE_K9_MODE
/** 9 键输入模式的最大候选面板数量 */
#define LV_IME_PINYIN_K9_CAND_TEXT_NUM 3
/** Maximum number of candidate panels for 9-key input mode */

#endif /*LV_IME_PINYIN_USE_K9_MODE*/

/** 关闭后，必须在输入法使用前用 lv_ime_pinyin_set_dict()
 *  设置字典。
 */
#define LV_IME_PINYIN_USE_DEFAULT_DICT 1
/** Without it, a dictionary must be set with lv_ime_pinyin_set_dict()
 *  before the IME is used.
 */

/** 根据屏幕尺寸调整此值，因为所有候选面板必须能容纳在屏幕上。 */
#define LV_IME_PINYIN_CAND_TEXT_NUM 6
/** Adjust this to the screen size, as all candidate panels must fit on it. */

#endif /*LV_USE_IME_PINYIN*/

/** 键盘 */
#define LV_USE_KEYBOARD 1
/** Keyboard */

/** 标签 */
#define LV_USE_LABEL 1
/** Label */

#if LV_USE_LABEL
/** 文本选择 */
#define LV_LABEL_TEXT_SELECTION 1
/** Text selection */

/** 每个标签多存 12 字节，以加速超长文本的绘制。 */
#define LV_LABEL_LONG_TXT_HINT 1
/** Stores 12 extra bytes per label to speed up drawing of very long texts. */

/** 循环滚动文本末尾与重新开始之间的间隔，
 *  以空格字符宽度衡量。
 */
#define LV_LABEL_WAIT_CHAR_COUNT 3
/** Gap between the end and the restart of circularly scrolled text,
 *  measured in space-character widths.
 */

#endif /*LV_USE_LABEL*/

/** LED 指示灯 */
#define LV_USE_LED 1
/** LED */

/** 线条 */
#define LV_USE_LINE 1
/** Line */

/** 列表 */
#define LV_USE_LIST 1
/** List */

#if LV_USE_THORVG
/** 使用 ThorVG Lottie 解析器播放 Lottie JSON 动画。
 *  Plays Lottie JSON animations using the ThorVG Lottie parser.
 *
 *  启用前提：LV_USE_VECTOR_GRAPHIC
 *  Enable: LV_USE_VECTOR_GRAPHIC
 */
#define LV_USE_LOTTIE 0

#endif /*LV_USE_THORVG*/

/** 菜单 */
#define LV_USE_MENU 1
/** Menu */

/** 消息框
 *  Message box
 *
 *  启用前提：LV_USE_LABEL
 *  Enable: LV_USE_LABEL
 */
#define LV_USE_MSGBOX 1

/** 二维码
 *  QR code
 *
 *  启用前提：LV_USE_CANVAS
 *  Enable: LV_USE_CANVAS
 */
#define LV_USE_QRCODE 0

/** 旧版 rlottie 绑定，为兼容性保留。请改用 LV_USE_LOTTIE。 */
#define LV_USE_RLOTTIE 0
/** Legacy rlottie binding, kept for compatibility. Use LV_USE_LOTTIE instead. */

/** 滚轮
 *  Roller
 *
 *  启用前提：LV_USE_LABEL
 *  Enable: LV_USE_LABEL
 */
#define LV_USE_ROLLER 1

/** 标尺 */
#define LV_USE_SCALE 1
/** Scale */

/** 滑块
 *  Slider
 *
 *  启用前提：LV_USE_BAR
 *  Enable: LV_USE_BAR
 */
#define LV_USE_SLIDER 1

/** 跨度（富文本）
 *  Span
 */
#define LV_USE_SPAN 1

#if LV_USE_SPAN
/** 最大跨度描述符数量 */
#define LV_SPAN_SNIPPET_STACK_SIZE 64
/** Maximum number of span descriptors */

#endif /*LV_USE_SPAN*/

/** 数字微调框 */
#define LV_USE_SPINBOX 1
/** Spinbox */

/** 旋转指示器 */
#define LV_USE_SPINNER 1
/** Spinner */

/** 开关 */
#define LV_USE_SWITCH 1
/** Switch */

/** 文本框
 *  Text area
 *
 *  启用前提：LV_USE_LABEL
 *  Enable: LV_USE_LABEL
 */
#define LV_USE_TEXTAREA 1

#if LV_USE_TEXTAREA
/** 默认密码显示时间（毫秒） */
#define LV_TEXTAREA_DEF_PWD_SHOW_TIME 1500
/** Default password show time (ms) */

#endif /*LV_USE_TEXTAREA*/

/** 表格 */
#define LV_USE_TABLE 1
/** Table */

/** 选项卡视图 */
#define LV_USE_TABVIEW 1
/** Tabview */

/** 平铺视图 */
#define LV_USE_TILEVIEW 1
/** Tileview */

/** 窗口 */
#define LV_USE_WIN 1
/** Window */



/*============================================================================
 * DRIVERS
 *============================================================================*/

/** /dev/dri/card 的驱动 */
#define LV_USE_LINUX_DRM 0
/** Driver for /dev/dri/card */

#if LV_USE_LINUX_DRM
/** 旧版行为，计划移除：后端根据 LV_USE_OPENGLES 推断
 *  （启用时为 EGL）。关闭此项并在"渲染后端"选项中显式选择后端。
 */
#define LV_LINUX_DRM_AUTO_BACKEND 1
/** Legacy behavior, slated for removal: the backend is inferred from
 *  LV_USE_OPENGLES (EGL when it is enabled). Disable this and pick a backend
 *  explicitly in the "Rendering backend" choice.
 */

/** 选择 Linux DRM 驱动如何呈现渲染帧。
 *  Select how the Linux DRM driver presents rendered frames.
 *  可选值：
 *  Possible values:
 *  - LV_LINUX_DRM_BACKEND_FBDEV: 哑缓冲区（无 GPU）
 *  - LV_LINUX_DRM_BACKEND_FBDEV: Dumb buffers (no GPU)
 *  - LV_LINUX_DRM_BACKEND_GBM: GBM DMA 缓冲区
 *  - LV_LINUX_DRM_BACKEND_GBM: GBM DMA buffers
 *  - LV_LINUX_DRM_BACKEND_EGL: EGL（OpenGL ES，硬件加速）（启用前提：LV_USE_OPENGLES）
 *  - LV_LINUX_DRM_BACKEND_EGL: EGL (OpenGL ES, hardware-accelerated) (enable: LV_USE_OPENGLES)
 */
#define LV_LINUX_DRM_BACKEND LV_LINUX_DRM_BACKEND_FBDEV

#endif /*LV_USE_LINUX_DRM*/

/** /dev/fb 的驱动 */
#define LV_USE_LINUX_FBDEV 0
/** Driver for /dev/fb */

#if LV_USE_LINUX_FBDEV
/** BSD 风格的帧缓冲设备 */
#define LV_LINUX_FBDEV_BSD 0
/** BSD-flavored framebuffer device */

/** 渲染模式
 *  Render mode
 *  可选值：
 *  Possible values:
 *  - LV_DISPLAY_RENDER_MODE_PARTIAL: 部分模式
 *  - LV_DISPLAY_RENDER_MODE_PARTIAL: Partial mode
 *  - LV_DISPLAY_RENDER_MODE_DIRECT: 直接模式
 *  - LV_DISPLAY_RENDER_MODE_DIRECT: Direct mode
 *  - LV_DISPLAY_RENDER_MODE_FULL: 全屏模式
 *  - LV_DISPLAY_RENDER_MODE_FULL: Full mode
 */
#define LV_LINUX_FBDEV_RENDER_MODE LV_DISPLAY_RENDER_MODE_PARTIAL

#define LV_LINUX_FBDEV_BUFFER_COUNT 1

#if LV_LINUX_FBDEV_BUFFER_COUNT == 0
/** 自定义部分缓冲区大小（行数） */
#define LV_LINUX_FBDEV_BUFFER_SIZE 60
/** Custom partial buffer size (rows) */

#endif /*LV_LINUX_FBDEV_BUFFER_COUNT == 0*/

/** 通过 mmap() 而不是 write() 调用来访问帧缓冲。 */
#define LV_LINUX_FBDEV_MMAP 1
/** Access the framebuffer through mmap() instead of write() calls. */

#endif /*LV_USE_LINUX_FBDEV*/

/** 通过 SPI 连接的 FT81X EVE 图形控制器的驱动。 */
#define LV_USE_FT81X 0
/** Driver for FT81X EVE graphics controllers connected over SPI. */

/** 基于 LovyanGFX C++ 库的显示和触摸驱动，该库必须存在于构建中。 */
#define LV_USE_LOVYAN_GFX 0
/** Display and touch driver built on the LovyanGFX C++ library, which must be available in the build. */

#if LV_USE_LOVYAN_GFX
/** LovyanGFX 用户配置的头文件 */
#define LV_LGFX_USER_INCLUDE "lv_lgfx_user.hpp"
/** Header for LovyanGFX user configuration */

#endif /*LV_USE_LOVYAN_GFX*/

/** 通过 SPI 或并口连接的 LCD 设备的驱动。
 *  如果你的 LCD 控制器未列在下面专门的驱动中，请使用它。
 */
#define LV_USE_GENERIC_MIPI 0
/** Driver for LCD devices connected via SPI or parallel port.
 *  Use it if your LCD controller is not listed among the dedicated drivers below.
 */

/** ST7735 驱动
 *  ST7735
 *
 *  启用前提：LV_USE_GENERIC_MIPI
 *  Enable: LV_USE_GENERIC_MIPI
 */
#define LV_USE_ST7735 0

/** ST7789 驱动
 *  ST7789
 *
 *  启用前提：LV_USE_GENERIC_MIPI
 *  Enable: LV_USE_GENERIC_MIPI
 */
#define LV_USE_ST7789 0

/** ST7796 驱动
 *  ST7796
 *
 *  启用前提：LV_USE_GENERIC_MIPI
 *  Enable: LV_USE_GENERIC_MIPI
 */
#define LV_USE_ST7796 0

/** ILI9341 驱动
 *  ILI9341
 *
 *  启用前提：LV_USE_GENERIC_MIPI
 *  Enable: LV_USE_GENERIC_MIPI
 */
#define LV_USE_ILI9341 0

/** NV3007 驱动
 *  NV3007
 *
 *  启用前提：LV_USE_GENERIC_MIPI
 *  Enable: LV_USE_GENERIC_MIPI
 */
#define LV_USE_NV3007 0

/** 在已初始化的 NXP ELCDIF LCD 控制器上创建显示。 */
#define LV_USE_NXP_ELCDIF 0
/** Create a display on an already initialized NXP ELCDIF LCD controller. */

/** 创建由瑞萨 GLCDC 外设驱动的显示。 */
#define LV_USE_RENESAS_GLCDC 0
/** Create a display driven by the Renesas GLCDC peripheral. */

/** 创建绑定到 ST LTDC 外设某个图层的显示。 */
#define LV_USE_ST_LTDC 0
/** Create a display bound to a layer of the ST LTDC peripheral. */

#if !LV_USE_DRAW_DMA2D
#if LV_USE_ST_LTDC
/** 使用 DMA2D 在渲染的同时并行刷新部分模式的 LTDC 显示。
 *  仅在 DMA2D 渲染器被禁用时可用。
 */
#define LV_ST_LTDC_USE_DMA2D_FLUSH 0
/** Flush partial mode LTDC displays with DMA2D, in parallel with rendering.
 *  Only available when the DMA2D renderer is disabled.
 */

#endif /*LV_USE_ST_LTDC*/
#endif /*!LV_USE_DRAW_DMA2D*/

/** 基于 TFT_eSPI Arduino 库的显示驱动，该库必须存在于构建中。 */
#define LV_USE_TFT_ESPI 0
/** Display driver built on the TFT_eSPI Arduino library, which must be available in the build. */

/** 从 Linux /dev/input 事件设备读取触摸屏、鼠标和键盘输入。 */
#define LV_USE_EVDEV 0
/** Read touchscreen, mouse and keyboard input from Linux /dev/input event devices. */

/** 通过 libinput 读取指针、触摸和键盘输入，该库必须存在于构建中。 */
#define LV_USE_LIBINPUT 0
/** Read pointer, touch and keyboard input through libinput, which must be available in the build. */

#if LV_USE_LIBINPUT
/** libinput 的 BSD 变体 */
#define LV_LIBINPUT_BSD 0
/** BSD variant of libinput */

/** 使用 XKB 布局将按键事件映射为字符，使修饰键和非美式布局正常工作。
 *  需要链接 -lxkbcommon。
 */
#define LV_LIBINPUT_XKB 0
/** Map key events to characters with XKB layouts, so modifiers and non-US layouts work.
 *  Requires linking with -lxkbcommon.
 */

#if LV_LIBINPUT_XKB
/** 运行 `setxkbmap -query` 来找出适合你键盘的正确值。 */
#define LV_LIBINPUT_XKB_RULES ""
/** Run `setxkbmap -query` to find the right values for your keyboard. */

/** XKB 型号 */
#define LV_LIBINPUT_XKB_MODEL "pc101"
/** XKB model */

/** XKB 布局 */
#define LV_LIBINPUT_XKB_LAYOUT "us"
/** XKB layout */

/** XKB 变体 */
#define LV_LIBINPUT_XKB_VARIANT ""
/** XKB variant */

/** 为 XKB 选项传入 NULL，以应用系统默认值（例如来自
 *  XKB_DEFAULT_OPTIONS 环境变量）。否则使用 LV_LIBINPUT_XKB_OPTIONS。
 */
#define LV_LIBINPUT_XKB_OPTIONS_USE_DEFAULT 1
/** Pass NULL for the XKB options so the system default applies (e.g. from the
 *  XKB_DEFAULT_OPTIONS env var). Otherwise LV_LIBINPUT_XKB_OPTIONS is used.
 */

#if !LV_LIBINPUT_XKB_OPTIONS_USE_DEFAULT
/** XKB 选项 */
#define LV_LIBINPUT_XKB_OPTIONS ""
/** XKB options */

#endif /*!LV_LIBINPUT_XKB_OPTIONS_USE_DEFAULT*/
#endif /*LV_LIBINPUT_XKB*/
#endif /*LV_USE_LIBINPUT*/

/** NuttX 的显示和输入驱动，包括 /dev/fb 帧缓冲设备。 */
#define LV_USE_NUTTX 0
/** Display and input drivers for NuttX, including the /dev/fb framebuffer device. */

#if LV_USE_NUTTX
/** 从独立的 NuttX 堆分配缓存的图像缓冲区，避免主堆碎片化。 */
#define LV_USE_NUTTX_INDEPENDENT_IMAGE_HEAP 0
/** Allocate cached image buffers from a separate NuttX heap to keep the main heap from fragmenting. */

#if LV_USE_NUTTX_INDEPENDENT_IMAGE_HEAP
/** 默认绘制缓冲区使用的独立图像堆 */
#define LV_NUTTX_DEFAULT_DRAW_BUF_USE_INDEPENDENT_IMAGE_HEAP 0
/** Independent image heap for the default draw buffer */

#endif /*LV_USE_NUTTX_INDEPENDENT_IMAGE_HEAP*/

/** 从 libuv 事件循环驱动 LVGL 定时器处理器以及显示/输入定时器，而不是默认的定时器循环。 */
#define LV_USE_NUTTX_LIBUV 0
/** Drive the LVGL timer handler and the display/input timers from a libuv loop instead of the default timer loop. */

/** 跳过 lv_nuttx_init() 中的显示和输入设备创建，让应用自己设置。 */
#define LV_USE_NUTTX_CUSTOM_INIT 0
/** Skip the display and input device creation in lv_nuttx_init() so the application can set them up itself. */

/** 在 NuttX LCD 字符设备上创建显示，而不是帧缓冲设备。 */
#define LV_USE_NUTTX_LCD 0
/** Create the display on a NuttX LCD character device instead of the framebuffer device. */

#define LV_NUTTX_LCD_BUFFER_COUNT 0

#if LV_NUTTX_LCD_BUFFER_COUNT == 0
#if LV_USE_NUTTX_LCD
/** 自定义部分缓冲区大小（行数） */
#define LV_NUTTX_LCD_BUFFER_SIZE 60
/** Custom partial buffer size (rows) */

#endif /*LV_USE_NUTTX_LCD*/
#endif /*LV_NUTTX_LCD_BUFFER_COUNT == 0*/

/** 触摸屏 */
#define LV_USE_NUTTX_TOUCHSCREEN 0
/** Touchscreen */

#if LV_USE_NUTTX_TOUCHSCREEN
/** 0 表示禁用光标。 */
#define LV_NUTTX_TOUCHSCREEN_CURSOR_SIZE 0
/** 0 disables the cursor. */

#endif /*LV_USE_NUTTX_TOUCHSCREEN*/

/** 鼠标 */
#define LV_USE_NUTTX_MOUSE 0
/** Mouse */

#if LV_USE_NUTTX_MOUSE
/** 鼠标移动步进（像素） */
#define LV_USE_NUTTX_MOUSE_MOVE_STEP 1
/** Mouse movement step (pixels) */

#endif /*LV_USE_NUTTX_MOUSE*/

#if LV_USE_PROFILER_BUILTIN
/** 将内置分析器的输出写入文件，而不是控制台。 */
#define LV_USE_NUTTX_TRACE_FILE 0
/** Write the built-in profiler output to a file instead of the console. */

#endif /*LV_USE_PROFILER_BUILTIN*/

#if LV_USE_NUTTX_TRACE_FILE
/** 分析器跟踪文件路径 */
#define LV_NUTTX_TRACE_FILE_PATH "/data/lvgl-trace.log"
/** Profiler trace file path */

#endif /*LV_USE_NUTTX_TRACE_FILE*/
#endif /*LV_USE_NUTTX*/

/** 通用 OpenGL ES 显示驱动，用于将 LVGL 嵌入到另一个应用中，
 *  或通过 GLFW/EGL 驱动它。
 *  Generic OpenGL ES display driver, for embedding LVGL in another application or driving it through GLFW/EGL.
 *
 *  启用前提：LV_USE_MATRIX
 *  Enable: LV_USE_MATRIX
 */
#define LV_USE_OPENGLES 0

#if LV_USE_OPENGLES
/** 在每次 GL 调用之后检查 OpenGL 错误，并连同调用位置一起记录。 */
#define LV_USE_OPENGLES_DEBUG 0
/** Check for an OpenGL error after every GL call and log it with the call site. */

#endif /*LV_USE_OPENGLES*/

#if !LV_USE_EGL
/** 在 PC 桌面上用 GLFW 打开窗口，并读取鼠标和键盘输入。
 *  Open a window on a PC desktop with GLFW and read mouse and keyboard input.
 *
 *  启用前提：LV_USE_OPENGLES
 *  Enable: LV_USE_OPENGLES
 */
#define LV_USE_GLFW 0

#endif /*!LV_USE_EGL*/

/** 在 QNX Screen 窗口上创建显示，并读取指针和键盘输入。 */
#define LV_USE_QNX 0
/** Create a display on a QNX Screen window and read pointer and keyboard input. */

#if LV_USE_QNX
/** 屏幕大小缓冲区数量 */
#define LV_QNX_BUF_COUNT 1
/** Number of screen-sized buffers */

#endif /*LV_USE_QNX*/

/** 在 PC 桌面上用 SDL2 打开窗口，并读取鼠标和键盘输入。 */
#define LV_USE_SDL 0
/** Open a window on a PC desktop with SDL2 and read mouse and keyboard input. */

#if LV_USE_SDL
/** SDL 包含路径 */
#define LV_SDL_INCLUDE_PATH "SDL2/SDL.h"
/** SDL include path */

/** 旧版行为，计划移除：EGL 以旧方式推断
 *  （LV_USE_OPENGLES 搭配 OpenGL 绘制单元）。关闭此项并在
 *  "渲染后端"选项中显式选择后端。
 *  Legacy behavior, slated for removal: EGL is inferred the legacy way
 *  (LV_USE_OPENGLES with an OpenGL draw unit). Disable this and pick a backend
 *  explicitly in the "Rendering backend" choice.
 */
#define LV_SDL_AUTO_BACKEND 1

/** 选择 SDL 驱动如何呈现渲染帧。
 *  Select how the SDL driver presents rendered frames.
 *  可选值：
 *  Possible values:
 *  - LV_SDL_BACKEND_SW: 软件（SDL 表面）
 *  - LV_SDL_BACKEND_SW: Software (SDL surface)
 *  - LV_SDL_BACKEND_TEXTURE: 缓存的 SDL 纹理（启用前提：LV_USE_DRAW_SDL）
 *  - LV_SDL_BACKEND_TEXTURE: Cached SDL textures (enable: LV_USE_DRAW_SDL)
 *  - LV_SDL_BACKEND_EGL: EGL（OpenGL ES，硬件加速）（需要 LV_USE_DRAW_OPENGLES || LV_USE_DRAW_NANOVG）
 *  - LV_SDL_BACKEND_EGL: EGL (OpenGL ES, hardware-accelerated) (requires LV_USE_DRAW_OPENGLES || LV_USE_DRAW_NANOVG)
 */
#define LV_SDL_BACKEND LV_SDL_BACKEND_SW

/** 为了最佳性能，推荐使用直接模式。
 *  Direct mode is recommended for best performance.
 *  可选值：
 *  Possible values:
 *  - LV_DISPLAY_RENDER_MODE_PARTIAL: 部分模式
 *  - LV_DISPLAY_RENDER_MODE_PARTIAL: Partial mode
 *  - LV_DISPLAY_RENDER_MODE_DIRECT: 直接模式
 *  - LV_DISPLAY_RENDER_MODE_DIRECT: Direct mode
 *  - LV_DISPLAY_RENDER_MODE_FULL: 全屏模式
 *  - LV_DISPLAY_RENDER_MODE_FULL: Full mode
 */
#define LV_SDL_RENDER_MODE LV_DISPLAY_RENDER_MODE_DIRECT

/** 屏幕大小缓冲区数量 */
#define LV_SDL_BUF_COUNT 1
/** Number of screen-sized buffers */

/** 请求 SDL 使用 GPU 支持的渲染器，而不是软件渲染器。 */
#define LV_SDL_ACCELERATED 1
/** Ask SDL for a GPU-backed renderer instead of a software one. */

/** 全屏 */
#define LV_SDL_FULLSCREEN 0
/** Fullscreen */

/** 当所有窗口关闭时退出 */
#define LV_SDL_DIRECT_EXIT 1
/** Exit when all windows are closed */

/** SDL 鼠标滚轮模式
 *  SDL mousewheel mode
 *  可选值：
 *  Possible values:
 *  - LV_SDL_MOUSEWHEEL_MODE_ENCODER: 编码器输入设备
 *  - LV_SDL_MOUSEWHEEL_MODE_ENCODER: Encoder input device
 *  - LV_SDL_MOUSEWHEEL_MODE_CROWN: 智能手表表冠
 *  - LV_SDL_MOUSEWHEEL_MODE_CROWN: Smart watch crown
 */
#define LV_SDL_MOUSEWHEEL_MODE LV_SDL_MOUSEWHEEL_MODE_ENCODER

#endif /*LV_USE_SDL*/

/** UEFI 固件的显示和输入驱动，基于图形输出、键盘和指针协议。 */
#define LV_USE_UEFI 0
/** Display and input drivers for UEFI firmware, based on the Graphics Output, keyboard and pointer protocols. */

#if LV_USE_UEFI
/** 封装 UEFI 框架（EDK2、gnu-efi 等）的头文件 */
#define LV_USE_UEFI_INCLUDE "myefi.h"
/** Header wrapping the UEFI framework (EDK2, gnu-efi, ...) */

/** 使用 UEFI 启动服务而不是 C 库来分配内存。
 *  仅在自定义 stdlib malloc 实现下生效。
 */
#define LV_UEFI_USE_MEMORY_SERVICES 0
/** Allocate memory with the UEFI boot services instead of the C library.
 *  Only takes effect with the custom stdlib malloc implementation.
 */

#endif /*LV_USE_UEFI*/

/** 在 Linux 或 BSD 的 Wayland 合成器上打开窗口，并读取鼠标、键盘和触摸输入。 */
#define LV_USE_WAYLAND 0
/** Open a window on a Wayland compositor on Linux or BSD and read mouse, keyboard and touch input. */

#if LV_USE_WAYLAND
/** 在应用程序退出前先反初始化 LVGL。 */
#define LV_WAYLAND_DIRECT_EXIT 1
/** LVGL is deinitialized before the application exits. */

#if !LV_USE_DRAW_OPENGLES
#if !LV_USE_DRAW_NANOVG
/** 默认后端，使用 wl_shm 进行双缓冲直接渲染。
 *  兼容所有 Wayland 合成器；不需要特殊硬件。
 *  在 OpenGL ES 和 NanoVG 渲染器下不可用，它们只能
 *  渲染到 GPU 表面。
 *  Default backend, using wl_shm for double-buffered direct rendering.
 *  Compatible with all Wayland compositors; no special hardware required.
 *  Unavailable with the OpenGL ES and NanoVG renderers, which can only
 *  render into a GPU surface.
 */
#define LV_WAYLAND_USE_SHM 1

/** 通过线性 DMA-BUF 呈现软件渲染的帧，合成器可以直接扫描输出，
 *  省去从共享内存拷贝的一次操作。
 *  Presents software-rendered frames through linear DMA-BUFs that the
 *  compositor can scan out directly, saving its copy out of shared memory.
 *  需要支持 zwp_linux_dmabuf_v1 且带 gbm 实现（能分配 CPU 可映射缓冲区）的合成器，
 *  以及 libdrm 和 gbm（-ldrm -lgbm）。
 *  Requires a compositor with zwp_linux_dmabuf_v1 and a gbm implementation
 *  able to allocate CPU-mappable buffers, plus libdrm and gbm (-ldrm -lgbm).
 *  不需要 GPU API：在 OpenGL ES 和 NanoVG 渲染器下不可用，它们只能
 *  渲染到 GPU 表面。
 *  Needs no GPU API: unavailable with the OpenGL ES and NanoVG renderers,
 *  which can only render into a GPU surface.
 */
#define LV_WAYLAND_USE_DMABUF 0

#endif /*!LV_USE_DRAW_NANOVG*/
#endif /*!LV_USE_DRAW_OPENGLES*/

/** 通过 OpenGL ES 2.0 和 EGL 进行硬件加速渲染，兼容
 *  LVGL 3D/glTF 渲染。目标硬件需要 OpenGL ES 2.0，
 *  并链接 wayland-egl（-lwayland-egl）。
 *  是 OpenGL ES 和 NanoVG 渲染器唯一可用的后端。
 *  Hardware-accelerated rendering via OpenGL ES 2.0 and EGL, compatible
 *  with LVGL 3D/glTF rendering. Requires OpenGL ES 2.0 on the target
 *  hardware and linking with wayland-egl (-lwayland-egl).
 *  The only backend available with the OpenGL ES and NanoVG renderers.
 *
 *  启用前提：LV_USE_OPENGLES
 *  Enable: LV_USE_OPENGLES
 */
#define LV_WAYLAND_USE_EGL 0

#if !LV_USE_DRAW_OPENGLES
#if !LV_USE_DRAW_NANOVG
/** 通过 NXP 的 G2D 引擎进行硬件加速 2D 渲染。
 *  支持安装了 G2D 库的 NXP i.MX6/i.MX8 平台。
 *  在 OpenGL ES 和 NanoVG 渲染器下不可用，它们只能
 *  渲染到 GPU 表面。
 *  Hardware-accelerated 2D rendering via NXP's G2D engine.
 *  Supports NXP i.MX6/i.MX8 platforms with G2D library installed.
 *  Unavailable with the OpenGL ES and NanoVG renderers, which can only
 *  render into a GPU surface.
 *
 *  启用前提：LV_USE_DRAW_G2D
 *  Enable: LV_USE_DRAW_G2D
 */
#define LV_WAYLAND_USE_G2D 0

#endif /*!LV_USE_DRAW_NANOVG*/
#endif /*!LV_USE_DRAW_OPENGLES*/
#endif /*LV_USE_WAYLAND*/

#if LV_USE_OS == LV_OS_WINDOWS
/** 使用 Win32 API 打开窗口，并读取鼠标、触摸、键盘和鼠标滚轮输入。 */
#define LV_USE_WINDOWS 0
/** Open a window with the Win32 API and read mouse, touch, keyboard and mousewheel input. */

#endif /*LV_USE_OS == LV_OS_WINDOWS*/

/** 在 X11 桌面上打开窗口，并读取鼠标和键盘输入。 */
#define LV_USE_X11 0
/** Open a window on an X11 desktop and read mouse and keyboard input. */

#if LV_USE_X11
/** 双缓冲 */
#define LV_X11_DOUBLE_BUFFER 1
/** Double buffering */

/** 当所有窗口关闭时退出 */
#define LV_X11_DIRECT_EXIT 1
/** Exit when all windows are closed */

/** 渲染模式
 *  Render mode
 *  可选值：
 *  Possible values:
 *  - LV_DISPLAY_RENDER_MODE_PARTIAL: 部分模式
 *  - LV_DISPLAY_RENDER_MODE_PARTIAL: Partial mode
 *  - LV_DISPLAY_RENDER_MODE_DIRECT: 直接模式
 *  - LV_DISPLAY_RENDER_MODE_DIRECT: Direct mode
 *  - LV_DISPLAY_RENDER_MODE_FULL: 全屏模式
 *  - LV_DISPLAY_RENDER_MODE_FULL: Full mode
 */
#define LV_X11_RENDER_MODE LV_DISPLAY_RENDER_MODE_PARTIAL

#endif /*LV_USE_X11*/

/** 编译自带的 NanoVG 矢量图形库。NanoVG 渲染器需要它。 */
#define LV_USE_NANOVG 0
/** Build the bundled NanoVG vector graphics library. Required by the NanoVG renderer. */



/*============================================================================
 * FILE SYSTEM
 *============================================================================*/

/** 设置默认驱动器字母可以让你在文件路径中省略驱动前缀。
 *  Setting a default drive letter allows skipping the driver
 *  prefix in filepaths.
 */
#define LV_FS_DEFAULT_DRIVER_LETTER 0

/** stdio 文件系统 */
#define LV_USE_FS_STDIO 0
/** stdio */

#if LV_USE_FS_STDIO
/** stdio 的驱动器字母（65 = 'A'，0 = 禁用） */
#define LV_FS_STDIO_LETTER 0
/** Drive letter for stdio (65 = 'A', 0 = disabled) */

/** stdio 的工作目录 */
#define LV_FS_STDIO_PATH ""
/** Working directory for stdio */

/** stdio 的读取缓存大小（字节，0 = 禁用） */
#define LV_FS_STDIO_CACHE_SIZE 0
/** Read cache size in bytes for stdio (0 = disabled) */

#endif /*LV_USE_FS_STDIO*/

/** POSIX 文件系统 */
#define LV_USE_FS_POSIX 0
/** POSIX */

#if LV_USE_FS_POSIX
/** POSIX 的驱动器字母（65 = 'A'，0 = 禁用） */
#define LV_FS_POSIX_LETTER 0
/** Drive letter for POSIX (65 = 'A', 0 = disabled) */

/** POSIX 的工作目录 */
#define LV_FS_POSIX_PATH ""
/** Working directory for POSIX */

/** POSIX 的读取缓存大小（字节，0 = 禁用） */
#define LV_FS_POSIX_CACHE_SIZE 0
/** Read cache size in bytes for POSIX (0 = disabled) */

#endif /*LV_USE_FS_POSIX*/

/** Win32 文件系统 */
#define LV_USE_FS_WIN32 0
/** Win32 */

#if LV_USE_FS_WIN32
/** Win32 的驱动器字母（65 = 'A'，0 = 禁用） */
#define LV_FS_WIN32_LETTER 0
/** Drive letter for Win32 (65 = 'A', 0 = disabled) */

/** Win32 的工作目录 */
#define LV_FS_WIN32_PATH ""
/** Working directory for Win32 */

/** Win32 的读取缓存大小（字节，0 = 禁用） */
#define LV_FS_WIN32_CACHE_SIZE 0
/** Read cache size in bytes for Win32 (0 = disabled) */

#endif /*LV_USE_FS_WIN32*/

/** FatFS 文件系统 */
#define LV_USE_FS_FATFS 0
/** FatFS */

#if LV_USE_FS_FATFS
/** FatFS 的驱动器字母（65 = 'A'，0 = 禁用） */
#define LV_FS_FATFS_LETTER 0
/** Drive letter for FatFS (65 = 'A', 0 = disabled) */

/** FatFS 的工作目录 */
#define LV_FS_FATFS_PATH ""
/** Working directory for FatFS */

/** FatFS 的读取缓存大小（字节，0 = 禁用） */
#define LV_FS_FATFS_CACHE_SIZE 0
/** Read cache size in bytes for FatFS (0 = disabled) */

#endif /*LV_USE_FS_FATFS*/

/** littlefs 文件系统 */
#define LV_USE_FS_LITTLEFS 0
/** littlefs */

#if LV_USE_FS_LITTLEFS
/** littlefs 的驱动器字母（65 = 'A'，0 = 禁用） */
#define LV_FS_LITTLEFS_LETTER 0
/** Drive letter for littlefs (65 = 'A', 0 = disabled) */

/** littlefs 的工作目录 */
#define LV_FS_LITTLEFS_PATH ""
/** Working directory for littlefs */

#endif /*LV_USE_FS_LITTLEFS*/

/** Arduino ESP littlefs 文件系统 */
#define LV_USE_FS_ARDUINO_ESP_LITTLEFS 0
/** Arduino ESP littlefs */

#if LV_USE_FS_ARDUINO_ESP_LITTLEFS
/** Arduino ESP littlefs 的驱动器字母（65 = 'A'，0 = 禁用） */
#define LV_FS_ARDUINO_ESP_LITTLEFS_LETTER 0
/** Drive letter for Arduino ESP littlefs (65 = 'A', 0 = disabled) */

/** Arduino ESP littlefs 的工作目录 */
#define LV_FS_ARDUINO_ESP_LITTLEFS_PATH ""
/** Working directory for Arduino ESP littlefs */

#endif /*LV_USE_FS_ARDUINO_ESP_LITTLEFS*/

/** Arduino SD 文件系统 */
#define LV_USE_FS_ARDUINO_SD 0
/** Arduino SD */

#if LV_USE_FS_ARDUINO_SD
/** Arduino SD 的驱动器字母（65 = 'A'，0 = 禁用） */
#define LV_FS_ARDUINO_SD_LETTER 0
/** Drive letter for Arduino SD (65 = 'A', 0 = disabled) */

/** Arduino SD 的工作目录 */
#define LV_FS_ARDUINO_SD_PATH ""
/** Working directory for Arduino SD */

#endif /*LV_USE_FS_ARDUINO_SD*/

/** UEFI 文件系统 */
#define LV_USE_FS_UEFI 0
/** UEFI */

#if LV_USE_FS_UEFI
/** UEFI 的驱动器字母（65 = 'A'，0 = 禁用） */
#define LV_FS_UEFI_LETTER 0
/** Drive letter for UEFI (65 = 'A', 0 = disabled) */

#endif /*LV_USE_FS_UEFI*/

/** FrogFS 文件系统 */
#define LV_USE_FS_FROGFS 0
/** FrogFS */

#if LV_USE_FS_FROGFS
/** FrogFS 的驱动器字母（65 = 'A'，0 = 禁用） */
#define LV_FS_FROGFS_LETTER 0
/** Drive letter for FrogFS (65 = 'A', 0 = disabled) */

#endif /*LV_USE_FS_FROGFS*/

/** 在没有真实文件系统的情况下，通过 lv_fs API 访问已在内存中的数据。 */
#define LV_USE_FS_MEMFS 0
/** Reach data already in memory through the lv_fs API, without a real file system. */

#if LV_USE_FS_MEMFS
/** memfs 的驱动器字母（65 = 'A'，0 = 禁用） */
#define LV_FS_MEMFS_LETTER 0
/** Drive letter for memfs (65 = 'A', 0 = disabled) */

#endif /*LV_USE_FS_MEMFS*/


/*============================================================================
 * DEBUGGING
 *============================================================================*/

/** 周期性收集 CPU、FPS 和内存统计信息，并可选地在屏幕上以
 *  叠加层显示。
 */
#define LV_USE_SYSMON 1
/** Periodically collect CPU, FPS and memory statistics and optionally show them in an
 *  on-screen overlay.
 */

#if LV_USE_SYSMON
/** 移植层在系统级空闲百分比之外，额外提供
 *  `lv_os_get_proc_idle_percent` 返回的按进程空闲百分比。
 *  LVGL 为 Linux 系统提供了默认实现。
 */
#define LV_SYSMON_PROC_IDLE_AVAILABLE 0
/** The port provides `lv_os_get_proc_idle_percent` a per-process idle percentage
 *  in addition to the system-wide one. LVGL provides a default one for linux systems.
 */

/** 在屏幕上的标签中显示 CPU 使用率和 FPS 计数。 */
#define LV_USE_PERF_MONITOR 1
/** Show the CPU usage and FPS count in a label on the screen. */

#if LV_USE_PERF_MONITOR
/** 性能监视器位置
 *  Performance monitor position
 *  可选值：
 *  Possible values:
 *  - LV_ALIGN_TOP_LEFT: 左上
 *  - LV_ALIGN_TOP_LEFT
 *  - LV_ALIGN_TOP_MID: 顶部居中
 *  - LV_ALIGN_TOP_MID: Top middle
 *  - LV_ALIGN_TOP_RIGHT: 右上
 *  - LV_ALIGN_TOP_RIGHT
 *  - LV_ALIGN_BOTTOM_LEFT: 左下
 *  - LV_ALIGN_BOTTOM_LEFT
 *  - LV_ALIGN_BOTTOM_MID: 底部居中
 *  - LV_ALIGN_BOTTOM_MID: Bottom middle
 *  - LV_ALIGN_BOTTOM_RIGHT: 右下
 *  - LV_ALIGN_BOTTOM_RIGHT
 *  - LV_ALIGN_LEFT_MID: 左中
 *  - LV_ALIGN_LEFT_MID: Left middle
 *  - LV_ALIGN_RIGHT_MID: 右中
 *  - LV_ALIGN_RIGHT_MID: Right middle
 *  - LV_ALIGN_CENTER: 居中
 *  - LV_ALIGN_CENTER
 */
#define LV_USE_PERF_MONITOR_POS LV_ALIGN_BOTTOM_RIGHT

/** 将性能数据打印到日志，而不是显示屏幕上的标签。 */
#define LV_USE_PERF_MONITOR_LOG_MODE 0
/** Print the performance data to the log instead of showing the on-screen label. */

#endif /*LV_USE_PERF_MONITOR*/

#if LV_USE_STDLIB_MALLOC == LV_STDLIB_BUILTIN
/** 在屏幕上的标签中显示已用内存和内存碎片情况。 */
#define LV_USE_MEM_MONITOR 1
/** Show the used memory and the memory fragmentation in a label on the screen. */

#endif /*LV_USE_STDLIB_MALLOC == LV_STDLIB_BUILTIN*/

#if LV_USE_MEM_MONITOR
/** 内存监视器位置
 *  Memory monitor position
 *  可选值：
 *  Possible values:
 *  - LV_ALIGN_TOP_LEFT: 左上
 *  - LV_ALIGN_TOP_LEFT
 *  - LV_ALIGN_TOP_MID: 顶部居中
 *  - LV_ALIGN_TOP_MID: Top middle
 *  - LV_ALIGN_TOP_RIGHT: 右上
 *  - LV_ALIGN_TOP_RIGHT
 *  - LV_ALIGN_BOTTOM_LEFT: 左下
 *  - LV_ALIGN_BOTTOM_LEFT
 *  - LV_ALIGN_BOTTOM_MID: 底部居中
 *  - LV_ALIGN_BOTTOM_MID: Bottom middle
 *  - LV_ALIGN_BOTTOM_RIGHT: 右下
 *  - LV_ALIGN_BOTTOM_RIGHT
 *  - LV_ALIGN_LEFT_MID: 左中
 *  - LV_ALIGN_LEFT_MID: Left middle
 *  - LV_ALIGN_RIGHT_MID: 右中
 *  - LV_ALIGN_RIGHT_MID: Right middle
 *  - LV_ALIGN_CENTER: 居中
 *  - LV_ALIGN_CENTER
 */
#define LV_USE_MEM_MONITOR_POS LV_ALIGN_BOTTOM_LEFT

#endif /*LV_USE_MEM_MONITOR*/

/** 包含 LV_SYSMON_CUSTOM_INCLUDE 指定的头文件，以覆盖系统
 *  监视器宏，例如 LV_SYSMON_GET_IDLE。
 *  Include the header given by LV_SYSMON_CUSTOM_INCLUDE to override system
 *  monitor macros such as LV_SYSMON_GET_IDLE.
 */
#define LV_SYSMON_USE_CUSTOM_INCLUDE 0

#if LV_SYSMON_USE_CUSTOM_INCLUDE
/** 用于覆盖系统监视器空闲测量宏的可选头文件。
 *  Optional header to override system monitor idle measurement macros.
 *
 *  LV_SYSMON_GET_IDLE
 *    返回自上次调用以来的 CPU 空闲百分比（0-100）的表达式。
 *    Expression returning the CPU idle percentage (0-100) since last call.
 *    例如 my_rtos_get_idle_percent()
 *    e.g. my_rtos_get_idle_percent()
 *
 *  LV_SYSMON_GET_PROC_IDLE
 *    返回按进程空闲百分比的表达式，如果 RTOS 支持的话。
 *    Expression returning per-process idle percentage, if supported by
 *    需要启用 LV_SYSMON_PROC_IDLE_AVAILABLE。
 *    the RTOS. Requires LV_SYSMON_PROC_IDLE_AVAILABLE to be enabled
 *    例如 my_rtos_get_proc_idle_percent()
 *    e.g. my_rtos_get_proc_idle_percent()
 */
#define LV_SYSMON_CUSTOM_INCLUDE ""

#endif /*LV_SYSMON_USE_CUSTOM_INCLUDE*/
#endif /*LV_USE_SYSMON*/

/** 用跟踪钩子对 LVGL 内部进行插桩，以测量运行时性能。 */
#define LV_USE_PROFILER 0
/** Instrument LVGL internals with trace hooks to measure runtime performance. */

/** 内置分析器
 *  Built-in profiler
 *
 *  启用前提：LV_USE_PROFILER
 *  Enable: LV_USE_PROFILER
 */
#define LV_USE_PROFILER_BUILTIN 0

#if LV_USE_PROFILER_BUILTIN
/** 跟踪缓冲区大小（字节） */
#define LV_PROFILER_BUILTIN_BUF_SIZE 16384
/** Trace buffer size (bytes) */

/** 初始化时开始分析 */
#define LV_PROFILER_BUILTIN_DEFAULT_ENABLE 1
/** Start profiling at init */

/** POSIX 移植层 */
#define LV_USE_PROFILER_BUILTIN_POSIX 0
/** POSIX port */

#endif /*LV_USE_PROFILER_BUILTIN*/

#if LV_USE_PROFILER
/** 定义以下分析器钩子宏的头文件路径：
 *  Path to a header that defines the following profiler hook macros:
 *
 *  LV_PROFILER_BEGIN
 *    在分析作用域开始时调用。
 *    Called at the start of a profiled scope.
 *    例如 #define LV_PROFILER_BEGIN  my_profiler_begin()
 *    e.g. #define LV_PROFILER_BEGIN  my_profiler_begin()
 *
 *  LV_PROFILER_END
 *    在分析作用域结束时调用。
 *    Called at the end of a profiled scope.
 *    例如 #define LV_PROFILER_END    my_profiler_end()
 *    e.g. #define LV_PROFILER_END    my_profiler_end()
 *
 *  LV_PROFILER_BEGIN_TAG(tag)
 *    在带字符串标签的分析作用域开始时调用。
 *    Called at the start of a profiled scope with a string tag.
 *    例如 #define LV_PROFILER_BEGIN_TAG(tag)  my_profiler_begin_tag(tag)
 *    e.g. #define LV_PROFILER_BEGIN_TAG(tag)  my_profiler_begin_tag(tag)
 *
 *  LV_PROFILER_END_TAG(tag)
 *    在带字符串标签的分析作用域结束时调用。
 *    Called at the end of a profiled scope with a string tag.
 *    例如 #define LV_PROFILER_END_TAG(tag)    my_profiler_end_tag(tag)
 *    e.g. #define LV_PROFILER_END_TAG(tag)    my_profiler_end_tag(tag)
 *
 *  默认头文件通过内置分析器提供这些宏。
 *  设置为自己的头文件以使用自定义分析器后端。
 *  The default header provides these via the built-in profiler.
 *  Set this to your own header to use a custom profiler backend.
 */
#define LV_PROFILER_INCLUDE "lvgl/debugging/profiler/lv_profiler_builtin.h"

/** 布局 */
#define LV_PROFILER_LAYOUT 1
/** Layout */

/** 显示刷新 */
#define LV_PROFILER_REFR 1
/** Display refresh */

/** 绘制 */
#define LV_PROFILER_DRAW 1
/** Draw */

/** 输入设备 */
#define LV_PROFILER_INDEV 1
/** Input devices */

/** 图像解码器 */
#define LV_PROFILER_DECODER 1
/** Image decoder */

/** 字体 */
#define LV_PROFILER_FONT 1
/** Font */

/** 文件系统 */
#define LV_PROFILER_FS 1
/** File system */

/** 样式 */
#define LV_PROFILER_STYLE 0
/** Style */

/** 定时器 */
#define LV_PROFILER_TIMER 1
/** Timer */

/** 缓存 */
#define LV_PROFILER_CACHE 1
/** Cache */

/** 事件 */
#define LV_PROFILER_EVENT 1
/** Events */

#endif /*LV_USE_PROFILER*/

/** 模拟输入设备、时间仿真和截图比较。 */
#define LV_USE_TEST 0
/** Emulated input devices, time emulation, and screenshot compares. */

#if LV_USE_TEST
/** 启用 `lv_test_screenshot_compare()`。需要额外几 MB RAM。
 *  Enable `lv_test_screenshot_compare()`. Requires a few MB of extra RAM.
 *
 *  启用前提：LV_USE_LODEPNG
 *  Enable: LV_USE_LODEPNG
 */
#define LV_USE_TEST_SCREENSHOT_COMPARE 0

#if LV_USE_TEST_SCREENSHOT_COMPARE
/** 当参考图像还不存在时，从渲染的屏幕创建它，
 *  而不是让比较失败。
 */
#define LV_TEST_SCREENSHOT_CREATE_REFERENCE_IMAGE 1
/** When a reference image does not exist yet, create it from the rendered
 *  screen instead of failing the compare.
 */

#endif /*LV_USE_TEST_SCREENSHOT_COMPARE*/

#if LV_USE_DRAW_NANOVG
/** 渲染到屏幕外的 EGL pbuffer 而不是窗口，并把像素
 *  读回 LVGL 绘制缓冲区，使截图比较与软件渲染器
 *  的工作方式相同。需要 EGL 和 GLESv2。
 */
#define LV_USE_NANOVG_TEST_HEADLESS 0
/** Render into an off-screen EGL pbuffer instead of a window and read the
 *  pixels back into the LVGL draw buffer, so screenshot compares work the
 *  same way as with the software renderer. Requires EGL and GLESv2.
 */

#endif /*LV_USE_DRAW_NANOVG*/
#endif /*LV_USE_TEST*/

/** 向 UI 发送随机输入事件以进行压力测试。 */
#define LV_USE_MONKEY 0
/** Feed random input events to the UI for stress testing. */

/** 在重绘区域上绘制随机彩色矩形。 */
#define LV_USE_REFR_DEBUG 0
/** Draw random colored rectangles over the redrawn areas. */

/** 在 ARGB 图层上绘制红色叠加层，在 RGB 图层上绘制绿色叠加层。 */
#define LV_USE_LAYER_DEBUG 0
/** Draw a red overlay over ARGB layers and a green overlay over RGB layers. */

/** 为每个绘制单元的任务绘制不同颜色的叠加层，并在
 *  白色背景上显示绘制单元的索引号（图层为黑色）。
 */
#define LV_USE_PARALLEL_DRAW_DEBUG 0
/** Draw an overlay in a different color for each draw unit's tasks, with the
 *  draw unit's index number on a white background (black for layers).
 */



/*============================================================================
 * OTHERS
 *============================================================================*/

/** 管理一个带有自身生命周期和返回栈的控件子树，类似于 Android 的 Fragment。 */
#define LV_USE_FRAGMENT 0
/** Manage a widget subtree with its own lifecycle and back stack, similar to Android fragments. */

/** 文件浏览器
 *  File explorer
 *
 *  启用前提：LV_USE_TABLE
 *  Enable: LV_USE_TABLE
 */
#define LV_USE_FILE_EXPLORER 0

#if LV_USE_FILE_EXPLORER
/** 最大路径长度（字节） */
#define LV_FILE_EXPLORER_PATH_MAX_LEN 128
/** Maximum path length (bytes) */

/** 添加一个带常用位置快捷方式的侧边栏。可以通过点击浏览区域
 *  左上角的按钮隐藏它，这在屏幕较小时很有用。
 */
#define LV_FILE_EXPLORER_QUICK_ACCESS 1
/** Add a sidebar with shortcuts to common places. It can be hidden by clicking the
 *  button at the top left corner of the browsing area, which is useful on small screens.
 */

#endif /*LV_USE_FILE_EXPLORER*/


/*============================================================================
 * BUILD
 *============================================================================*/

/** 从 `lvgl.h` 中包含 `lvgl_private.h`，使 LVGL 内部数据
 *  结构和函数默认可访问。
 */
#define LV_USE_PRIVATE_API 0
/** Include `lvgl_private.h` from `lvgl.h` so that LVGL internal data
 *  structures and functions are accessible by default.
 */

/** 默认情况下，LVGL 将所有运行时状态保存在单个静态
 *  'lv_global_t' 变量中，这对大多数单显示
 *  单线程应用已经足够。
 *  By default, LVGL stores all runtime state in a single static
 *  'lv_global_t' variable, sufficient for most single-display
 *  single-threaded applications.
 *
 *  如果你需要在同一进程中拥有多个独立的 LVGL 实例，请启用此选项，
 *  例如：
 *  Enable this if you need multiple independent LVGL instances in
 *  the same process, for example:
 *    - 带有独立渲染循环的多个物理显示器
 *    - Multiple physical displays with separate render loops
 *    - RTOS（FreeRTOS、Zephyr 等）上的每线程 LVGL 上下文
 *    - Per-thread LVGL contexts on an RTOS (FreeRTOS, Zephyr, etc.)
 *    - 可热替换或沙箱化的 UI 实例
 *    - Hot-swappable or sandboxed UI instances
 *
 *  启用后，LVGL 内部对全局状态的每次访问都通过
 *  LV_GLOBAL_CUSTOM() 而不是静态变量。你必须
 *  实现 'lv_global_t *lv_global_default(void)' 来返回
 *  当前上下文的正确实例（例如通过线程局部存储
 *  或受保护的指针切换）。
 *  When enabled, every LVGL internal access to global state goes
 *  through LV_GLOBAL_CUSTOM() instead of a static variable. You
 *  must implement 'lv_global_t *lv_global_default(void)' to return
 *  the correct instance for the current context (e.g. by thread-local
 *  storage or a guarded pointer switch).
 *
 *  该函数返回 NULL 是安全的；LVGL 会将库视为
 *  在该上下文中未初始化。
 *  Returning NULL from that function is safe; LVGL will treat the
 *  library as uninitialized for that context.
 */
#define LV_ENABLE_GLOBAL_CUSTOM 0

#if LV_ENABLE_GLOBAL_CUSTOM
/** 使用自定义头文件声明：
 *        lv_global_t *lv_global_default(void);
 *  Use a custom header for the declaration of:
 *        lv_global_t *lv_global_default(void);
 */
#define LV_GLOBAL_USE_CUSTOM_INCLUDE 0

#if LV_GLOBAL_USE_CUSTOM_INCLUDE
/** 声明以下内容的头文件路径：
 *  Path to the header that declares:
 *    lv_global_t *lv_global_default(void);
 *
 *  该头文件会在 LVGL 需要解析
 *  LV_GLOBAL_DEFAULT() 宏的任何地方被包含。请保持轻量，
 *  因为它会被包含在性能关键的路径中。
 *  This header is included wherever LVGL needs to resolve the
 *  LV_GLOBAL_DEFAULT() macro. Keep it lightweight, it is included
 *  in performance-critical paths.
 */
#define LV_GLOBAL_CUSTOM_INCLUDE "lv_global.h"

#endif /*LV_GLOBAL_USE_CUSTOM_INCLUDE*/
#endif /*LV_ENABLE_GLOBAL_CUSTOM*/

/** LV_ASSERT / LV_ASSERT_MSG / LV_ASSERT_FORMAT_MSG 断言宏 */
#define LV_USE_ASSERT 0
/** LV_ASSERT / LV_ASSERT_MSG / LV_ASSERT_FORMAT_MSG */

/** LV_ASSERT_MALLOC 内存分配断言 */
#define LV_USE_ASSERT_MALLOC 0
/** LV_ASSERT_MALLOC */

/** LV_ASSERT_NULL 空指针断言 */
#define LV_USE_ASSERT_NULL 0
/** LV_ASSERT_NULL */

/** LV_ASSERT_STYLE 样式断言 */
#define LV_USE_ASSERT_STYLE 0
/** LV_ASSERT_STYLE */

/** LV_ASSERT_MEM_INTEGRITY 内存完整性断言 */
#define LV_USE_ASSERT_MEM_INTEGRITY 0
/** LV_ASSERT_MEM_INTEGRITY */

/** LV_ASSERT_OBJ 对象断言 */
#define LV_USE_ASSERT_OBJ 0
/** LV_ASSERT_OBJ */

/** 禁用提示 `LV_ASSERT_HANDLER_INCLUDE` 已废弃的警告。
 *  此设置允许你继续使用依赖
 *  LV_ASSERT_HANDLER_INCLUDE 的旧版 LVGL，而不触发编译器警告。
 *  Disable warning saying `LV_ASSERT_HANDLER_INCLUDE` is deprecated.
 *  This setting allows you to keep using old LVGL versions which rely on
 *  LV_ASSERT_HANDLER_INCLUDE without triggering a compiler warning.
 *
 *  LV_ASSERT_HANDLER_INCLUDE 已被废弃，取而代之的新方式是：
 *  使用头文件路径定义 LV_ASSERT_CUSTOM_INCLUDE，并把
 *  LV_ASSERT_HANDLER 宏定义放到该头文件内。
 *  LV_ASSERT_HANDLER_INCLUDE has been deprecated in favor of the new approach:
 *  define LV_ASSERT_CUSTOM_INCLUDE with the header path, and place the
 *  LV_ASSERT_HANDLER macro definition inside that header instead.
 *
 *  仅在你需要兼容仍使用 LV_ASSERT_HANDLER_INCLUDE 且
 *  无法立即迁移的现有代码时启用。
 *  新工程应直接使用 LV_ASSERT_CUSTOM_INCLUDE 和 LV_ASSERT_HANDLER。
 *  Only enable this if you are maintaining compatibility with existing code
 *  that uses LV_ASSERT_HANDLER_INCLUDE and cannot migrate immediately.
 *  New projects should use LV_ASSERT_CUSTOM_INCLUDE and LV_ASSERT_HANDLER
 *  directly.
 */
#define LV_DISABLE_ASSERT_HANDLER_INCLUDE_WARNING 0

/** 包含 LV_ASSERT_CUSTOM_INCLUDE 指定的头文件，该头文件必须定义
 *  自定义的 LV_ASSERT_HANDLER。
 */
#define LV_ASSERT_USE_CUSTOM_INCLUDE 0
/** Include the header given by LV_ASSERT_CUSTOM_INCLUDE, which must define
 *  a custom LV_ASSERT_HANDLER.
 */

#if LV_ASSERT_USE_CUSTOM_INCLUDE
/** 用于覆盖断言相关宏的可选头文件。
 *  Optional header to override assert-related macros.
 *
 *  LV_ASSERT_HANDLER
 *    断言失败时执行的语句。
 *    Statement to execute when an assertion fails.
 *    例如 #define LV_ASSERT_HANDLER my_assert_failed(__FILE__, __LINE__);
 *    e.g. #define LV_ASSERT_HANDLER my_assert_failed(__FILE__, __LINE__);
 */
#define LV_ASSERT_CUSTOM_INCLUDE ""

#endif /*LV_ASSERT_USE_CUSTOM_INCLUDE*/

/** LV_CHECK_ARG 在运行时校验函数参数：检查失败时
 *  记录警告并执行指定操作。关闭后所有这些
 *  检查都编译为空，这只有在资源非常受限、
 *  不变量得到保证的环境下才是安全的。
 *  LV_CHECK_ARG validates function arguments at runtime: a failed check
 *  logs a warning and executes the specified action. When disabled all
 *  these checks compile to nothing, which is only safe in very resource
 *  constrained environments where invariants are guaranteed to hold.
 */
#define LV_USE_CHECK_ARG 1

#if LV_USE_CHECK_ARG
/** 当 LV_CHECK_ARG 检查失败时，在执行操作之前
 *  也调用 LV_ASSERT_HANDLER。
 */
#define LV_CHECK_ARG_ASSERT_ON_FAIL 0
/** Also invoke LV_ASSERT_HANDLER when an LV_CHECK_ARG check fails,
 *  before the action is executed.
 */

/** 控制 LV_CHECK_ARG 检查失败时记录什么内容。
 *  Minimal 和 Verbose 需要 LV_USE_LOG；在不启用它的情况下
 *  选择这两者之一会导致编译错误。
 *  可选值：
 *  Possible values:
 *  - LV_CHECK_ARG_LOG_MODE_NONE: 失败时无日志输出
 *  - LV_CHECK_ARG_LOG_MODE_NONE: no log output on failure
 *  - LV_CHECK_ARG_LOG_MODE_MINIMAL: 仅记录 'Check failed'（文件/行来自 LV_LOG_WARN）（需要 LV_USE_LOG）
 *  - LV_CHECK_ARG_LOG_MODE_MINIMAL: log 'Check failed' only (file/line from LV_LOG_WARN) (requires LV_USE_LOG)
 *  - LV_CHECK_ARG_LOG_MODE_VERBOSE: 记录 'Check failed: <cond>' 以及调用方提供的消息（需要 LV_USE_LOG）
 *  - LV_CHECK_ARG_LOG_MODE_VERBOSE: log 'Check failed: <cond>' plus caller-supplied message (requires LV_USE_LOG)
 */
#define LV_CHECK_ARG_LOG_MODE LV_CHECK_ARG_LOG_MODE_NONE

/** LV_CHECK_OBJ 使用 lv_obj_has_class() 校验对象是否具有
 *  预期的类。关闭后跳过类检查
 *  （LV_CHECK_OBJ 退化为 NULL 检查）。
 */
#define LV_USE_CHECK_OBJ_CLASSTYPE 0
/** LV_CHECK_OBJ verifies with lv_obj_has_class() that the object has the
 *  expected class. When disabled the class check is skipped
 *  (LV_CHECK_OBJ collapses to a NULL check).
 */

/** LV_CHECK_OBJ 使用 lv_obj_is_in_widget_tree() 校验对象是否
 *  仍然是控件树的一部分。关闭后跳过有效性检查
 *  （只保留类/NULL 检查）。
 */
#define LV_USE_CHECK_OBJ_VALIDITY 0
/** LV_CHECK_OBJ verifies with lv_obj_is_in_widget_tree() that the object is
 *  still part of the widget tree. When disabled the validity check is
 *  skipped (only the class/NULL check remains).
 */

#if LV_USE_CHECK_OBJ_VALIDITY
#if LV_USE_ASSERT
/** 在沿父级链向上遍历时，lv_obj_is_in_widget_tree 还会检查
 *  每个父级的子控件数组中是否包含该子控件。这可以发现
 *  子控件的父指针与父级的子控件列表不一致的损坏情况。
 *  代价是从每级 O(1) 变为 O(兄弟数量)，LV_ASSERT 会报告不匹配。
 */
#define LV_USE_CHECK_OBJ_PARENT_LINK 0
/** While walking up the parent chain, lv_obj_is_in_widget_tree also checks that
 *  each parent's children array contains the child. This finds corruption where
 *  a child's parent pointer and the parent's children list disagree. The cost is
 *  O(siblings) per level instead of O(1), and LV_ASSERT reports the mismatch.
 */

#endif /*LV_USE_ASSERT*/
#endif /*LV_USE_CHECK_OBJ_VALIDITY*/
#endif /*LV_USE_CHECK_ARG*/


/*============================================================================
 * COMPILER SETTINGS
 *============================================================================*/

/** 大端系统 */
/** Big endian system */
#define LV_BIG_ENDIAN_SYSTEM 0

/** 包含 LV_ATTRIBUTE_CUSTOM_INCLUDE 指定的头文件，以便为你的平台
 *  覆盖 LV_ATTRIBUTE_* 宏。
 */
/** Include the header given by LV_ATTRIBUTE_CUSTOM_INCLUDE to override the
 *  LV_ATTRIBUTE_* macros for your platform.
 */
#define LV_ATTRIBUTE_USE_CUSTOM_INCLUDE 0

#if LV_ATTRIBUTE_USE_CUSTOM_INCLUDE
/** 用于覆盖平台 LV_ATTRIBUTE_* 宏的可选头文件。
 *  留空则使用默认值（所有宏都展开为空）。
 *
 *  创建一个头文件并在此设置其路径，例如 "my_lv_attr.h"。
 *  可以在其中定义以下宏：
 *
 *  LV_ATTRIBUTE_MEM_ALIGN
 *    需要内存对齐的位置（例如使用 -Os 编译时，数据默认可能不会
 *    对齐到所需边界）。
 *    例如 __attribute__((aligned(4)))
 *
 *  LV_ATTRIBUTE_TICK_INC
 *    应用于 lv_tick_inc()。通常从定时器中断中调用，因此将其放置
 *    在快速内存中可以降低延迟。
 *    例如 __attribute__((section(".itcm"))) 或 __ramfunc (IAR)
 *
 *  LV_ATTRIBUTE_TIMER_HANDLER
 *    应用于 lv_timer_handler()。
 *    例如 __attribute__((section(".itcm")))
 *
 *  LV_ATTRIBUTE_FLUSH_READY
 *    应用于 lv_display_flush_ready()。通常从 DMA 或显示中断中调用。
 *    例如 __attribute__((section(".itcm")))
 *
 *  LV_ATTRIBUTE_SYNC_READY
 *    应用于 lv_display_sync_ready()。与 FLUSH_READY 类似，从中断
 *    上下文中调用时很有用。
 *    例如 __attribute__((section(".itcm")))
 *
 *  LV_ATTRIBUTE_LARGE_CONST
 *    应用于大型只读数组，例如字体位图。用于将它们放置到特定的
 *    Flash 区域或外部存储器中。
 *    例如 __attribute__((section(".ext_flash")))
 *
 *  LV_ATTRIBUTE_LARGE_RAM_ARRAY
 *    应用于分配在 RAM 中的大型数组。
 *    例如 __attribute__((section(".ext_ram")))
 *
 *  LV_ATTRIBUTE_FAST_MEM
 *    应用于性能关键的函数，将它们放置到更快的存储器中，
 *    例如 ITCM 或 SRAM。
 *    例如 __attribute__((section(".itcm"))) 或 __ramfunc (IAR)
 *
 *  LV_ATTRIBUTE_EXTERN_DATA
 *    所有全局 extern 数据声明的前缀。用于将共享数据放置在指定
 *    段中或应用导出属性。
 *    例如 __attribute__((section(".shared_mem")))
 *
 *  LV_EXPORT_CONST_INT(int_value)
 *    将整型常量导出到语言绑定 API，例如 MicroPython。对 LV_<CONST>
 *    形式的所有常量调用。如果不使用绑定则保持未定义。
 *    例如 mp_rom_map_elem_t entry = {MP_ROM_QSTR(MP_QSTR_##int_value), MP_ROM_INT(int_value)}
 */
/** Optional header to override LV_ATTRIBUTE_* macros for your platform.
 *  Leave empty to use defaults (all expand to nothing).
 *
 *  Create a header file and set this to its path, e.g. "my_lv_attr.h".
 *  The following macros can be defined in it:
 *
 *  LV_ATTRIBUTE_MEM_ALIGN
 *    Where memory needs to be aligned (e.g. with -Os, data may not be
 *    aligned to the required boundary by default).
 *    e.g. __attribute__((aligned(4)))
 *
 *  LV_ATTRIBUTE_TICK_INC
 *    Applied to lv_tick_inc(). Often called from a timer ISR, so fast
 *    memory placement can reduce latency.
 *    e.g. __attribute__((section(".itcm"))) or __ramfunc (IAR)
 *
 *  LV_ATTRIBUTE_TIMER_HANDLER
 *    Applied to lv_timer_handler().
 *    e.g. __attribute__((section(".itcm")))
 *
 *  LV_ATTRIBUTE_FLUSH_READY
 *    Applied to lv_display_flush_ready(). Often called from a DMA or
 *    display ISR.
 *    e.g. __attribute__((section(".itcm")))
 *
 *  LV_ATTRIBUTE_SYNC_READY
 *    Applied to lv_display_sync_ready(). Similar to FLUSH_READY, useful
 *    when called from an ISR context.
 *    e.g. __attribute__((section(".itcm")))
 *
 *  LV_ATTRIBUTE_LARGE_CONST
 *    Applied to large read-only arrays such as font bitmaps. Use to place
 *    them in a specific flash region or external memory.
 *    e.g. __attribute__((section(".ext_flash")))
 *
 *  LV_ATTRIBUTE_LARGE_RAM_ARRAY
 *    Applied to large arrays allocated in RAM.
 *    e.g. __attribute__((section(".ext_ram")))
 *
 *  LV_ATTRIBUTE_FAST_MEM
 *    Applied to performance-critical functions to place them in faster
 *    memory such as ITCM or SRAM.
 *    e.g. __attribute__((section(".itcm"))) or __ramfunc (IAR)
 *
 *  LV_ATTRIBUTE_EXTERN_DATA
 *    Prefix for all global extern data declarations. Useful for placing
 *    shared data in a named section or applying export attributes.
 *    e.g. __attribute__((section(".shared_mem")))
 *
 *  LV_EXPORT_CONST_INT(int_value)
 *    Exports an integer constant to a language binding API such as
 *    MicroPython. Called for all constants in the form LV_<CONST>.
 *    Leave undefined if not using a binding.
 *    e.g. mp_rom_map_elem_t entry = {MP_ROM_QSTR(MP_QSTR_##int_value), MP_ROM_INT(int_value)}
 */
#define LV_ATTRIBUTE_CUSTOM_INCLUDE ""

#endif /*LV_ATTRIBUTE_USE_CUSTOM_INCLUDE*/


/*============================================================================
 * EXAMPLES
 *============================================================================*/

/** 构建示例 */
/** Build examples */
#define LV_BUILD_EXAMPLES 1



/*============================================================================
 * DEMOS
 *============================================================================*/

/** 构建演示 */
/** Build demos */
#define LV_BUILD_DEMOS 1

#if LV_BUILD_DEMOS
/** 基准测试演示
 *
 *  需要启用：LV_FONT_MONTSERRAT_14, LV_FONT_MONTSERRAT_20, LV_FONT_MONTSERRAT_24, LV_FONT_MONTSERRAT_26, LV_USE_DEMO_WIDGETS
 */
/** Benchmark demo
 *
 *  Enable: LV_FONT_MONTSERRAT_14, LV_FONT_MONTSERRAT_20, LV_FONT_MONTSERRAT_24, LV_FONT_MONTSERRAT_26, LV_USE_DEMO_WIDGETS
 */
#define LV_USE_DEMO_BENCHMARK 0

#if LV_USE_DEMO_BENCHMARK
/** 使用演示自带的、带有对齐字形位图的 Montserrat 字体，
 *  而不是 LV_FONT_MONTSERRAT_* 字体。
 */
/** Use the demo's own Montserrat fonts with aligned glyph bitmaps instead
 *  of the LV_FONT_MONTSERRAT_* fonts.
 */
#define LV_DEMO_BENCHMARK_ALIGNED_FONTS 0

#endif /*LV_USE_DEMO_BENCHMARK*/

#if LV_USE_GLTF
/** glTF 演示 */
/** glTF demo */
#define LV_USE_DEMO_GLTF 0

#endif /*LV_USE_GLTF*/

/** 键盘和编码器演示 */
/** Keypad and encoder demo */
#define LV_USE_DEMO_KEYPAD_AND_ENCODER 0

/** 音乐播放器演示 */
/** Music player demo */
#define LV_USE_DEMO_MUSIC 0

#if LV_USE_DEMO_MUSIC
/** 方形布局 */
/** Square layout */
#define LV_DEMO_MUSIC_SQUARE 0

/** 横屏布局 */
/** Landscape layout */
#define LV_DEMO_MUSIC_LANDSCAPE 0

/** 圆形布局 */
/** Round layout */
#define LV_DEMO_MUSIC_ROUND 0

/** 大型布局 */
/** Large layout */
#define LV_DEMO_MUSIC_LARGE 0

/** 自动播放 */
/** Auto play */
#define LV_DEMO_MUSIC_AUTO_PLAY 0

#endif /*LV_USE_DEMO_MUSIC*/

/** 渲染每种绘图原语以进行视觉对比。
 *  需要至少 480x272 的显示器。
 *
 *  需要启用：LV_USE_GRID
 */
/** Renders each drawing primitive for visual comparison.
 *  Requires a display of at least 480x272.
 *
 *  Enable: LV_USE_GRID
 */
#define LV_USE_DEMO_RENDER 0

/** 压力测试演示 */
/** Stress demo */
#define LV_USE_DEMO_STRESS 0

/** 矢量图形演示
 *
 *  需要启用：LV_USE_VECTOR_GRAPHIC
 */
/** Vector graphic demo
 *
 *  Enable: LV_USE_VECTOR_GRAPHIC
 */
#define LV_USE_DEMO_VECTOR_GRAPHIC 0

/** 控件演示 */
/** Widgets demo */
#define LV_USE_DEMO_WIDGETS 0

/** Flex 布局演示 */
/** Flex layout demo */
#define LV_USE_DEMO_FLEX_LAYOUT 0

/** 多语言演示 */
/** Multi-language demo */
#define LV_USE_DEMO_MULTILANG 0

/** 智能手表演示 */
/** Smartwatch demo */
#define LV_USE_DEMO_SMARTWATCH 0

/** 电动自行车演示 */
/** E-bike demo */
#define LV_USE_DEMO_EBIKE 0

#if LV_USE_DEMO_EBIKE
/** 竖屏布局 */
/** Portrait layout */
#define LV_DEMO_EBIKE_PORTRAIT 0

#endif /*LV_USE_DEMO_EBIKE*/

/** 高分辨率演示 */
/** High resolution demo */
#define LV_USE_DEMO_HIGH_RES 0

#endif /*LV_BUILD_DEMOS*/


/*--LV_CONF_H 结束--*/
/*--END OF LV_CONF_H--*/

#endif /*LV_CONF_H*/

#endif /*内容启用结束*/
/* End of "Content enable" */
