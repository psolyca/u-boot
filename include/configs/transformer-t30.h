/* SPDX-License-Identifier: GPL-2.0-or-later */
/*
 * Copyright (c) 2010-2012, NVIDIA CORPORATION.  All rights reserved.
 */

#ifndef __CONFIG_H
#define __CONFIG_H

#include <linux/sizes.h>

#include "tegra30-common.h"

/* VDD core PMIC */
#define CONFIG_TEGRA_VDD_CORE_TPS62361B_SET3

/* High-level configuration options */
#define CONFIG_TEGRA_BOARD_STRING	"ASUS Transformer"

#define BOARD_EXTRA_ENV_SETTINGS \
	"kernel_addr_r=0x80008000\0" \
	"dtb_addr_r=0x83000000\0" \
	"ramdisk_addr_r=0x84000000\0" \
	"script_addr_r=0x87000000\0" \
	"ebt_offset_r=0x1C00\0" \
	"ebt_size=0x4000\0" \
	"sos_offset_r=0x3C00\0" \
	"sos_size=0x4000\0" \
	"lnx_offset_r=0x7C00\0" \
	"lnx_size=0x4000\0" \
	"kernel_file=vmlinuz\0" \
	"dtb_file="CONFIG_DEFAULT_DEVICE_TREE".dtb\0" \
	"ramdisk_file=uInitrd\0" \
	"bootloader_file=u-boot-dtb-tegra.bin\0" \
	"fastboot_raw_partition_boot=${lnx_offset_r} ${lnx_size} mmcpart 0\0" \
	"fastboot_raw_partition_recovery=${sos_offset_r} ${sos_size} mmcpart 0\0" \
	"fastboot_partition_alias_system=APP\0" \
	"fastboot_partition_alias_cache=CAC\0" \
	"fastboot_partition_alias_misc=MSC\0" \
	"fastboot_partition_alias_staging=USP\0" \
	"fastboot_partition_alias_vendor=VDR\0" \
	"fastboot_partition_alias_userdata=UDA\0" \
	"bootkernel=bootz ${kernel_addr_r} - ${dtb_addr_r}\0" \
	"bootrdkernel=bootz ${kernel_addr_r} ${ramdisk_addr_r} ${dtb_addr_r}\0" \
	"boot_bct=echo Loading BCT;" \
		"if load mmc 0:5 ${script_addr_r} uboot-transformer.bcs;" \
		"then env import -t -r ${script_addr_r} ${filesize};" \
		"else echo Boot Configuration NOT FOUND!; fi;" \
		"echo Loading DTB;" \
		"load ${dev_type} ${mmcdev}:${mmcpart} ${dtb_addr_r} ${dtb_file};" \
		"echo Loading Kernel;" \
		"load ${dev_type} ${mmcdev}:${mmcpart} ${kernel_addr_r} ${kernel_file};" \
		"echo Loading Initramfs;" \
		"if load ${dev_type} ${mmcdev}:${mmcpart} ${ramdisk_addr_r} ${ramdisk_file};" \
		"then echo Booting Kernel;" \
			"run bootrdkernel;" \
		"else echo Booting Kernel;" \
			"run bootkernel; fi\0" \
	"boot_lnx=echo Reading LNX partition;" \
		"mmc dev;" \
		"if mmc read ${kernel_addr_r} ${lnx_offset_r} ${lnx_size};" \
		"then echo Booting Kernel;" \
			"bootm ${kernel_addr_r};" \
		"else echo Reading LNX failed; fi\0" \
	"boot_sos=echo Reading SOS partition;" \
		"mmc dev;" \
		"if mmc read ${kernel_addr_r} ${sos_offset_r} ${sos_size};" \
		"then echo Booting Kernel;" \
			"bootm ${kernel_addr_r};" \
		"else echo Reading SOS failed; fi\0" \
	"flash_uboot=echo Reading U-Boot binary;" \
		"if load mmc 1:1 ${kernel_addr_r} ${bootloader_file};" \
		"then echo Writing U-Boot into EBT;" \
			"mmc dev;" \
			"mmc write ${kernel_addr_r} ${ebt_offset_r} ${ebt_size};" \
		"else echo Reading U-Boot failed; fi\0" \
	"bootmenu_0=boot with BCT=run boot_bct\0" \
	"bootmenu_1=boot LNX=run boot_lnx\0" \
	"bootmenu_2=boot SOS=run boot_sos\0" \
	"bootmenu_3=fastboot=fastboot usb 0\0" \
	"bootmenu_4=reboot=reset\0" \
	"bootmenu_5=power off=poweroff\0" \
	"bootmenu_6=update bootloader=run flash_uboot\0" \
	"bootmenu_delay=-1\0"

#undef CONFIG_BOOTCOMMAND
#define CONFIG_BOOTCOMMAND \
	"if button VolDown;" \
	"then bootmenu;" \
	"else echo Loading from uSD...;" \
		"echo Loading Kernel;" \
		"if load mmc 1:1 ${kernel_addr_r} ${kernel_file};" \
		"then echo Loading DTB;" \
			"load mmc 1:1 ${dtb_addr_r} ${dtb_file};" \
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
				"load mmc 0:1 ${dtb_addr_r} ${dtb_file};" \
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

/* Skip EFI check for eMMC */
#define SKIP_EFI_TEST

#define CONFIG_MACH_TYPE		MACH_TYPE_CARDHU

#include "tegra-common-post.h"
#include "tegra-common-usb-gadget.h"

#endif /* __CONFIG_H */
