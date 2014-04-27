/*
 * Copyright (c) 2012-2014, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

// Device driver for BCM2835 - EMMC (External Mass Media Controller)

#include <Kernel/StdTypes.h>
#include <Kernel/Logging.h>
#include <Device/BCM2835_EMMC.h>

#define EMMC_BASE                  ((volatile UnsignedWord32*) 0x20300000)
#define EMMC_ARG2_OFFSET           (0x00)
#define EMMC_BLKSIZECNT_OFFSET     (0x01)
#define EMMC_ARG1_OFFSET           (0x02)
#define EMMC_CMDTM_OFFSET          (0x03)
#define EMMC_RESP0_OFFSET          (0x04)
#define EMMC_RESP1_OFFSET          (0x05)
#define EMMC_RESP2_OFFSET          (0x06)
#define EMMC_RESP3_OFFSET          (0x07)
#define EMMC_DATA_OFFSET           (0x08)
#define EMMC_STATUS_OFFSET         (0x09)
#define EMMC_CONTROL0_OFFSET       (0x0A)
#define EMMC_CONTROL1_OFFSET       (0x0B)
#define EMMC_INTERRUPT_OFFSET      (0x0C)
#define EMMC_IRPT_MASK_OFFSET      (0x0D)
#define EMMC_IRPT_EN_OFFSET        (0x0E)
#define EMMC_CONTROL2_OFFSET       (0x0F)
#define EMMC_FORCE_IRPT_OFFSET     (0x14)
#define EMMC_BOOT_TIMEOUT_OFFSET   (0x1C)
#define EMMC_DBG_SEL_OFFSET        (0x1D)
#define EMMC_EXRDFIFO_CFG_OFFSET   (0x20)
#define EMMC_EXRDFIFO_EN_OFFSET    (0x21)
#define EMMC_TUNE_STEP_OFFSET      (0x22)
#define EMMC_TUNE_STEPS_STD_OFFSET (0x23)
#define EMMC_TUNE_STEPS_DDR_OFFSET (0x24)
#define EMMC_SPI_INT_SPT_OFFSET    (0x3C)
#define EMMC_SLOTISR_VER_OFFSET    (0x3F)

void emmcInit(void)
{
}

void emmcShutdown(void)
{
}
