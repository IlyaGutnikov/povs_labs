/*
 * system.h - SOPC Builder system and BSP software package information
 *
 * Machine generated for CPU 'cpu' in SOPC Builder design 'niosII'
 * SOPC Builder design path: ../../../niosII.sopcinfo
 *
 * Generated: Tue Oct 06 14:09:33 MSK 2015
 */

/*
 * DO NOT MODIFY THIS FILE
 *
 * Changing this file will have subtle consequences
 * which will almost certainly lead to a nonfunctioning
 * system. If you do modify this file, be aware that your
 * changes will be overwritten and lost when this file
 * is generated again.
 *
 * DO NOT MODIFY THIS FILE
 */

/*
 * License Agreement
 *
 * Copyright (c) 2008
 * Altera Corporation, San Jose, California, USA.
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * This agreement shall be governed in all respects by the laws of the State
 * of California and by the laws of the United States of America.
 */

#ifndef __SYSTEM_H_
#define __SYSTEM_H_

/* Include definitions from linker script generator */
#include "linker.h"


/*
 * CPU configuration
 *
 */

#define ALT_CPU_ARCHITECTURE "altera_nios2_gen2"
#define ALT_CPU_BIG_ENDIAN 0
#define ALT_CPU_BREAK_ADDR 0x01400820
#define ALT_CPU_CPU_ARCH_NIOS2_R1
#define ALT_CPU_CPU_FREQ 50000000u
#define ALT_CPU_CPU_ID_SIZE 1
#define ALT_CPU_CPU_ID_VALUE 0x00000000
#define ALT_CPU_CPU_IMPLEMENTATION "fast"
#define ALT_CPU_DATA_ADDR_WIDTH 0x1a
#define ALT_CPU_DCACHE_BYPASS_MASK 0x80000000
#define ALT_CPU_DCACHE_LINE_SIZE 32
#define ALT_CPU_DCACHE_LINE_SIZE_LOG2 5
#define ALT_CPU_DCACHE_SIZE 4096
#define ALT_CPU_EXCEPTION_ADDR 0x01200020
#define ALT_CPU_FLASH_ACCELERATOR_LINES 0
#define ALT_CPU_FLASH_ACCELERATOR_LINE_SIZE 0
#define ALT_CPU_FLUSHDA_SUPPORTED
#define ALT_CPU_FREQ 50000000
#define ALT_CPU_HARDWARE_DIVIDE_PRESENT 0
#define ALT_CPU_HARDWARE_MULTIPLY_PRESENT 1
#define ALT_CPU_HARDWARE_MULX_PRESENT 0
#define ALT_CPU_HAS_DEBUG_CORE 1
#define ALT_CPU_HAS_DEBUG_STUB
#define ALT_CPU_HAS_EXTRA_EXCEPTION_INFO
#define ALT_CPU_HAS_ILLEGAL_INSTRUCTION_EXCEPTION
#define ALT_CPU_HAS_JMPI_INSTRUCTION
#define ALT_CPU_ICACHE_LINE_SIZE 32
#define ALT_CPU_ICACHE_LINE_SIZE_LOG2 5
#define ALT_CPU_ICACHE_SIZE 4096
#define ALT_CPU_INITDA_SUPPORTED
#define ALT_CPU_INST_ADDR_WIDTH 0x1a
#define ALT_CPU_NAME "cpu"
#define ALT_CPU_NUM_OF_SHADOW_REG_SETS 0
#define ALT_CPU_OCI_VERSION 1
#define ALT_CPU_RESET_ADDR 0x00800000


/*
 * CPU configuration (with legacy prefix - don't use these anymore)
 *
 */

#define NIOS2_BIG_ENDIAN 0
#define NIOS2_BREAK_ADDR 0x01400820
#define NIOS2_CPU_ARCH_NIOS2_R1
#define NIOS2_CPU_FREQ 50000000u
#define NIOS2_CPU_ID_SIZE 1
#define NIOS2_CPU_ID_VALUE 0x00000000
#define NIOS2_CPU_IMPLEMENTATION "fast"
#define NIOS2_DATA_ADDR_WIDTH 0x1a
#define NIOS2_DCACHE_BYPASS_MASK 0x80000000
#define NIOS2_DCACHE_LINE_SIZE 32
#define NIOS2_DCACHE_LINE_SIZE_LOG2 5
#define NIOS2_DCACHE_SIZE 4096
#define NIOS2_EXCEPTION_ADDR 0x01200020
#define NIOS2_FLASH_ACCELERATOR_LINES 0
#define NIOS2_FLASH_ACCELERATOR_LINE_SIZE 0
#define NIOS2_FLUSHDA_SUPPORTED
#define NIOS2_HARDWARE_DIVIDE_PRESENT 0
#define NIOS2_HARDWARE_MULTIPLY_PRESENT 1
#define NIOS2_HARDWARE_MULX_PRESENT 0
#define NIOS2_HAS_DEBUG_CORE 1
#define NIOS2_HAS_DEBUG_STUB
#define NIOS2_HAS_EXTRA_EXCEPTION_INFO
#define NIOS2_HAS_ILLEGAL_INSTRUCTION_EXCEPTION
#define NIOS2_HAS_JMPI_INSTRUCTION
#define NIOS2_ICACHE_LINE_SIZE 32
#define NIOS2_ICACHE_LINE_SIZE_LOG2 5
#define NIOS2_ICACHE_SIZE 4096
#define NIOS2_INITDA_SUPPORTED
#define NIOS2_INST_ADDR_WIDTH 0x1a
#define NIOS2_NUM_OF_SHADOW_REG_SETS 0
#define NIOS2_OCI_VERSION 1
#define NIOS2_RESET_ADDR 0x00800000


/*
 * Define for each module class mastered by the CPU
 *
 */

#define __ALTERA_AVALON_JTAG_UART
#define __ALTERA_AVALON_ONCHIP_MEMORY2
#define __ALTERA_AVALON_PIO
#define __ALTERA_AVALON_SYSID_QSYS
#define __ALTERA_AVALON_TIMER
#define __ALTERA_GENERIC_TRISTATE_CONTROLLER
#define __ALTERA_NIOS2_GEN2


/*
 * System configuration
 *
 */

#define ALT_DEVICE_FAMILY "Cyclone IV E"
#define ALT_ENHANCED_INTERRUPT_API_PRESENT
#define ALT_IRQ_BASE NULL
#define ALT_LOG_PORT "/dev/null"
#define ALT_LOG_PORT_BASE 0x0
#define ALT_LOG_PORT_DEV null
#define ALT_LOG_PORT_TYPE ""
#define ALT_NUM_EXTERNAL_INTERRUPT_CONTROLLERS 0
#define ALT_NUM_INTERNAL_INTERRUPT_CONTROLLERS 1
#define ALT_NUM_INTERRUPT_CONTROLLERS 1
#define ALT_STDERR "/dev/jtag_uart"
#define ALT_STDERR_BASE 0x1401070
#define ALT_STDERR_DEV jtag_uart
#define ALT_STDERR_IS_JTAG_UART
#define ALT_STDERR_PRESENT
#define ALT_STDERR_TYPE "altera_avalon_jtag_uart"
#define ALT_STDIN "/dev/jtag_uart"
#define ALT_STDIN_BASE 0x1401070
#define ALT_STDIN_DEV jtag_uart
#define ALT_STDIN_IS_JTAG_UART
#define ALT_STDIN_PRESENT
#define ALT_STDIN_TYPE "altera_avalon_jtag_uart"
#define ALT_STDOUT "/dev/jtag_uart"
#define ALT_STDOUT_BASE 0x1401070
#define ALT_STDOUT_DEV jtag_uart
#define ALT_STDOUT_IS_JTAG_UART
#define ALT_STDOUT_PRESENT
#define ALT_STDOUT_TYPE "altera_avalon_jtag_uart"
#define ALT_SYSTEM_NAME "niosII"


/*
 * buttons configuration
 *
 */

#define ALT_MODULE_CLASS_buttons altera_avalon_pio
#define BUTTONS_BASE 0x1401040
#define BUTTONS_BIT_CLEARING_EDGE_REGISTER 0
#define BUTTONS_BIT_MODIFYING_OUTPUT_REGISTER 0
#define BUTTONS_CAPTURE 1
#define BUTTONS_DATA_WIDTH 4
#define BUTTONS_DO_TEST_BENCH_WIRING 0
#define BUTTONS_DRIVEN_SIM_VALUE 0
#define BUTTONS_EDGE_TYPE "FALLING"
#define BUTTONS_FREQ 50000000
#define BUTTONS_HAS_IN 1
#define BUTTONS_HAS_OUT 0
#define BUTTONS_HAS_TRI 0
#define BUTTONS_IRQ 2
#define BUTTONS_IRQ_INTERRUPT_CONTROLLER_ID 0
#define BUTTONS_IRQ_TYPE "EDGE"
#define BUTTONS_NAME "/dev/buttons"
#define BUTTONS_RESET_VALUE 0
#define BUTTONS_SPAN 16
#define BUTTONS_TYPE "altera_avalon_pio"


/*
 * ext_flash_ctl configuration
 *
 */

#define ALT_MODULE_CLASS_ext_flash_ctl altera_generic_tristate_controller
#define EXT_FLASH_CTL_BASE 0x800000
#define EXT_FLASH_CTL_IRQ -1
#define EXT_FLASH_CTL_IRQ_INTERRUPT_CONTROLLER_ID -1
#define EXT_FLASH_CTL_NAME "/dev/ext_flash_ctl"
#define EXT_FLASH_CTL_SIZE 8388608
#define EXT_FLASH_CTL_SPAN 8388608
#define EXT_FLASH_CTL_TYPE "altera_generic_tristate_controller"


/*
 * ext_ram_ctl configuration
 *
 */

#define ALT_MODULE_CLASS_ext_ram_ctl altera_generic_tristate_controller
#define EXT_RAM_CTL_BASE 0x1200000
#define EXT_RAM_CTL_IRQ -1
#define EXT_RAM_CTL_IRQ_INTERRUPT_CONTROLLER_ID -1
#define EXT_RAM_CTL_NAME "/dev/ext_ram_ctl"
#define EXT_RAM_CTL_SPAN 2097152
#define EXT_RAM_CTL_SRAM_DATA_WIDTH 16
#define EXT_RAM_CTL_SRAM_MEMORY_SIZE 2097152
#define EXT_RAM_CTL_SRAM_MEMORY_UNITS 1
#define EXT_RAM_CTL_TYPE "altera_generic_tristate_controller"


/*
 * green_led configuration
 *
 */

#define ALT_MODULE_CLASS_green_led altera_avalon_pio
#define GREEN_LED_BASE 0x1401050
#define GREEN_LED_BIT_CLEARING_EDGE_REGISTER 0
#define GREEN_LED_BIT_MODIFYING_OUTPUT_REGISTER 0
#define GREEN_LED_CAPTURE 0
#define GREEN_LED_DATA_WIDTH 8
#define GREEN_LED_DO_TEST_BENCH_WIRING 0
#define GREEN_LED_DRIVEN_SIM_VALUE 0
#define GREEN_LED_EDGE_TYPE "NONE"
#define GREEN_LED_FREQ 50000000
#define GREEN_LED_HAS_IN 0
#define GREEN_LED_HAS_OUT 1
#define GREEN_LED_HAS_TRI 0
#define GREEN_LED_IRQ -1
#define GREEN_LED_IRQ_INTERRUPT_CONTROLLER_ID -1
#define GREEN_LED_IRQ_TYPE "NONE"
#define GREEN_LED_NAME "/dev/green_led"
#define GREEN_LED_RESET_VALUE 0
#define GREEN_LED_SPAN 16
#define GREEN_LED_TYPE "altera_avalon_pio"


/*
 * hal configuration
 *
 */

#define ALT_INCLUDE_INSTRUCTION_RELATED_EXCEPTION_API
#define ALT_MAX_FD 32
#define ALT_SYS_CLK SYS_CLK_TIMER
#define ALT_TIMESTAMP_CLK none


/*
 * high_res_timer configuration
 *
 */

#define ALT_MODULE_CLASS_high_res_timer altera_avalon_timer
#define HIGH_RES_TIMER_ALWAYS_RUN 0
#define HIGH_RES_TIMER_BASE 0x1401000
#define HIGH_RES_TIMER_COUNTER_SIZE 32
#define HIGH_RES_TIMER_FIXED_PERIOD 0
#define HIGH_RES_TIMER_FREQ 50000000
#define HIGH_RES_TIMER_IRQ -1
#define HIGH_RES_TIMER_IRQ_INTERRUPT_CONTROLLER_ID -1
#define HIGH_RES_TIMER_LOAD_VALUE 49
#define HIGH_RES_TIMER_MULT 1.0E-6
#define HIGH_RES_TIMER_NAME "/dev/high_res_timer"
#define HIGH_RES_TIMER_PERIOD 1
#define HIGH_RES_TIMER_PERIOD_UNITS "us"
#define HIGH_RES_TIMER_RESET_OUTPUT 0
#define HIGH_RES_TIMER_SNAPSHOT 1
#define HIGH_RES_TIMER_SPAN 32
#define HIGH_RES_TIMER_TICKS_PER_SEC 1000000
#define HIGH_RES_TIMER_TIMEOUT_PULSE_OUTPUT 0
#define HIGH_RES_TIMER_TYPE "altera_avalon_timer"


/*
 * instruction_tcm configuration
 *
 */

#define ALT_MODULE_CLASS_instruction_tcm altera_avalon_onchip_memory2
#define INSTRUCTION_TCM_ALLOW_IN_SYSTEM_MEMORY_CONTENT_EDITOR 0
#define INSTRUCTION_TCM_ALLOW_MRAM_SIM_CONTENTS_ONLY_FILE 0
#define INSTRUCTION_TCM_BASE 0x2000000
#define INSTRUCTION_TCM_CONTENTS_INFO ""
#define INSTRUCTION_TCM_DUAL_PORT 1
#define INSTRUCTION_TCM_GUI_RAM_BLOCK_TYPE "AUTO"
#define INSTRUCTION_TCM_INIT_CONTENTS_FILE "niosII_instruction_tcm"
#define INSTRUCTION_TCM_INIT_MEM_CONTENT 1
#define INSTRUCTION_TCM_INSTANCE_ID "NONE"
#define INSTRUCTION_TCM_IRQ -1
#define INSTRUCTION_TCM_IRQ_INTERRUPT_CONTROLLER_ID -1
#define INSTRUCTION_TCM_NAME "/dev/instruction_tcm"
#define INSTRUCTION_TCM_NON_DEFAULT_INIT_FILE_ENABLED 0
#define INSTRUCTION_TCM_RAM_BLOCK_TYPE "AUTO"
#define INSTRUCTION_TCM_READ_DURING_WRITE_MODE "DONT_CARE"
#define INSTRUCTION_TCM_SINGLE_CLOCK_OP 0
#define INSTRUCTION_TCM_SIZE_MULTIPLE 1
#define INSTRUCTION_TCM_SIZE_VALUE 16384
#define INSTRUCTION_TCM_SPAN 16384
#define INSTRUCTION_TCM_TYPE "altera_avalon_onchip_memory2"
#define INSTRUCTION_TCM_WRITABLE 1


/*
 * jtag_uart configuration
 *
 */

#define ALT_MODULE_CLASS_jtag_uart altera_avalon_jtag_uart
#define JTAG_UART_BASE 0x1401070
#define JTAG_UART_IRQ 1
#define JTAG_UART_IRQ_INTERRUPT_CONTROLLER_ID 0
#define JTAG_UART_NAME "/dev/jtag_uart"
#define JTAG_UART_READ_DEPTH 64
#define JTAG_UART_READ_THRESHOLD 8
#define JTAG_UART_SPAN 8
#define JTAG_UART_TYPE "altera_avalon_jtag_uart"
#define JTAG_UART_WRITE_DEPTH 64
#define JTAG_UART_WRITE_THRESHOLD 8


/*
 * seven_seg configuration
 *
 */

#define ALT_MODULE_CLASS_seven_seg altera_avalon_pio
#define SEVEN_SEG_BASE 0x1401060
#define SEVEN_SEG_BIT_CLEARING_EDGE_REGISTER 0
#define SEVEN_SEG_BIT_MODIFYING_OUTPUT_REGISTER 0
#define SEVEN_SEG_CAPTURE 0
#define SEVEN_SEG_DATA_WIDTH 32
#define SEVEN_SEG_DO_TEST_BENCH_WIRING 0
#define SEVEN_SEG_DRIVEN_SIM_VALUE 0
#define SEVEN_SEG_EDGE_TYPE "NONE"
#define SEVEN_SEG_FREQ 50000000
#define SEVEN_SEG_HAS_IN 0
#define SEVEN_SEG_HAS_OUT 1
#define SEVEN_SEG_HAS_TRI 0
#define SEVEN_SEG_IRQ -1
#define SEVEN_SEG_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SEVEN_SEG_IRQ_TYPE "NONE"
#define SEVEN_SEG_NAME "/dev/seven_seg"
#define SEVEN_SEG_RESET_VALUE -1
#define SEVEN_SEG_SPAN 16
#define SEVEN_SEG_TYPE "altera_avalon_pio"


/*
 * sys_clk_timer configuration
 *
 */

#define ALT_MODULE_CLASS_sys_clk_timer altera_avalon_timer
#define SYS_CLK_TIMER_ALWAYS_RUN 0
#define SYS_CLK_TIMER_BASE 0x1401020
#define SYS_CLK_TIMER_COUNTER_SIZE 32
#define SYS_CLK_TIMER_FIXED_PERIOD 0
#define SYS_CLK_TIMER_FREQ 50000000
#define SYS_CLK_TIMER_IRQ 0
#define SYS_CLK_TIMER_IRQ_INTERRUPT_CONTROLLER_ID 0
#define SYS_CLK_TIMER_LOAD_VALUE 49999
#define SYS_CLK_TIMER_MULT 0.001
#define SYS_CLK_TIMER_NAME "/dev/sys_clk_timer"
#define SYS_CLK_TIMER_PERIOD 1
#define SYS_CLK_TIMER_PERIOD_UNITS "ms"
#define SYS_CLK_TIMER_RESET_OUTPUT 0
#define SYS_CLK_TIMER_SNAPSHOT 1
#define SYS_CLK_TIMER_SPAN 32
#define SYS_CLK_TIMER_TICKS_PER_SEC 1000
#define SYS_CLK_TIMER_TIMEOUT_PULSE_OUTPUT 0
#define SYS_CLK_TIMER_TYPE "altera_avalon_timer"


/*
 * sysid configuration
 *
 */

#define ALT_MODULE_CLASS_sysid altera_avalon_sysid_qsys
#define SYSID_BASE 0x1401078
#define SYSID_ID 0
#define SYSID_IRQ -1
#define SYSID_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SYSID_NAME "/dev/sysid"
#define SYSID_SPAN 8
#define SYSID_TIMESTAMP 1444122932
#define SYSID_TYPE "altera_avalon_sysid_qsys"

#endif /* __SYSTEM_H_ */
