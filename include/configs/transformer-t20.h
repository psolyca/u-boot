/* SPDX-License-Identifier: 2.0-or-later */
/*
 *  (C) Copyright 2010,2011
 *  NVIDIA Corporation <www.nvidia.com>
 */

#ifndef __CONFIG_H
#define __CONFIG_H

#include <linux/sizes.h>

#include "tegra20-common.h"
#include "transformer-common.h"

#define BOARD_EXTRA_ENV_SETTINGS \
	MEM_LAYOUT_ENV_SETTINGS \
	TRANSFORMER_T20_EMMC_LAYOUT \
	TRANSFORMER_DEFAULT_FILESET \
	TRANSFORMER_BOOTZ

#undef CONFIG_BOOTCOMMAND
#define CONFIG_BOOTCOMMAND \
	"if button VolDown;" \
	"then fastboot usb 0;" \
	"else echo Loading from uSD...;" \
		"echo Loading Kernel;" \
		"if load mmc 1:1 ${kernel_addr_r} ${kernel_file};" \
		"then echo Loading DTB;" \
			"load mmc 1:1 ${fdt_addr_r} ${fdtfile};" \
			"setenv bootargs console=ttyS0,115200n8 root=/dev/mmcblk1p2 rw gpt;" \
			"echo Loading Initramfs;" \
			"if load mmc 1:1 ${ramdisk_addr_r} ${ramdisk_file};" \
			"then echo Booting Kernel;" \
				"run bootrdkernel;" \
			"else echo Booting Kernel;" \
				"run bootkernel; fi;" \
		"else echo Loading from uSD failed!;" \
			"echo Loading from eMMC...;" \
			"echo Loading Kernel;" \
			"load mmc 0:1 ${kernel_addr_r} ${kernel_file};" \
			"echo Loading DTB;" \
			"load mmc 0:1 ${fdt_addr_r} ${fdtfile};" \
			"setenv bootargs console=ttyS0,115200n8 root=/dev/mmcblk0p8 rw gpt;" \
			"echo Loading Initramfs;" \
			"if load mmc 0:1 ${ramdisk_addr_r} ${ramdisk_file};" \
			"then echo Booting Kernel;" \
				"run bootrdkernel;" \
			"else echo Booting Kernel;" \
				"run bootkernel; fi;" \
		"fi;" \
	"fi;"

/* Board-specific serial config */
#define CONFIG_TEGRA_ENABLE_UARTD
#define CONFIG_SYS_NS16550_COM1		NV_PA_APB_UARTD_BASE

#define CONFIG_MACH_TYPE		MACH_TYPE_VENTANA

#include "tegra-common-post.h"
#include "tegra-common-usb-gadget.h"

#endif /* __CONFIG_H */
