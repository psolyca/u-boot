/* SPDX-License-Identifier: GPL-2.0-or-later */
/*
 * Copyright (c) 2010-2012, NVIDIA CORPORATION.  All rights reserved.
 */

#ifndef __CONFIG_H
#define __CONFIG_H

#include <linux/sizes.h>

#include "tegra30-common.h"
#include "transformer-common.h"

/* VDD core PMIC */
#define CONFIG_TEGRA_VDD_CORE_TPS62361B_SET3

#define BOARD_EXTRA_ENV_SETTINGS \
	MEM_LAYOUT_ENV_SETTINGS \
	TRANSFORMER_T30_EMMC_LAYOUT \
	TRANSFORMER_DEFAULT_FILESET \
	TRANSFORMER_BOOTZ \
	TRANSFORMER_BOOTMENU

#undef CONFIG_BOOTCOMMAND
#define CONFIG_BOOTCOMMAND \
	"if button VolDown;" \
	"then bootmenu;" \
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
			"if load mmc 0:1 ${kernel_addr_r} ${kernel_file};" \
			"then echo Loading DTB;" \
				"load mmc 0:1 ${fdt_addr_r} ${fdtfile};" \
				"setenv bootargs console=ttyS0,115200n8 root=/dev/mmcblk0p8 rw gpt;" \
				"echo Loading Initramfs;" \
				"if load mmc 0:1 ${ramdisk_addr_r} ${ramdisk_file};" \
				"then echo Booting Kernel;" \
					"run bootrdkernel;" \
				"else echo Booting Kernel;" \
					"run bootkernel; fi;" \
			"else echo Loading Kernel FAILED! Turning power off;" \
				"poweroff; fi;" \
		"fi;" \
	"fi;"

/* Board-specific serial config */
#define CONFIG_TEGRA_ENABLE_UARTA
#define CONFIG_SYS_NS16550_COM1		NV_PA_APB_UARTA_BASE

#define CONFIG_MACH_TYPE		MACH_TYPE_CARDHU

#include "tegra-common-post.h"
#include "tegra-common-usb-gadget.h"

#endif /* __CONFIG_H */
