/* SPDX-License-Identifier: GPL-2.0-or-later */
/*
 *  (C) Copyright 2010,2011
 *  NVIDIA Corporation <www.nvidia.com>
 */

#ifndef __CONFIG_H
#define __CONFIG_H

#include <linux/sizes.h>

#include "tegra20-common.h"
#include "transformer-common.h"

#define TRANSFORMER_BOOTARGS \
	"console=ttyS0,115200n8 root=/dev/mmcblk0p${rootpart} rw gpt"

#define BOARD_EXTRA_ENV_SETTINGS \
	TRANSFORMER_T20_EMMC_LAYOUT \
	TRANSFORMER_DEFAULT_FILESET \
	TRANSFORMER_BOOTZ \
	TRANSFORMER_FASTBOOT_ALIAS

#undef CONFIG_BOOTCOMMAND
#define CONFIG_BOOTCOMMAND \
	"if button VolDown;" \
	"then echo Starting Fastboot protocol ...;" \
		"fastboot usb 0;" \
	"else echo Loading from uSD...;" \
		"setenv bootdev 1;" \
		"setenv rootpart 2;" \
		TRANSFORMER_LOAD_KERNEL \
		"else echo Loading from uSD failed!;" \
			"echo Loading from eMMC...;" \
			"setenv bootdev 0;" \
			"setenv rootpart 8;" \
			TRANSFORMER_LOAD_KERNEL \
		"fi;" \
	"fi;"

/* Board-specific serial config */
#define CONFIG_TEGRA_ENABLE_UARTD
#define CONFIG_SYS_NS16550_COM1		NV_PA_APB_UARTD_BASE

#define CONFIG_MACH_TYPE		MACH_TYPE_VENTANA

#include "tegra-common-post.h"

#endif /* __CONFIG_H */
