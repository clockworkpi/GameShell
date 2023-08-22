# Kernel
clockworkPI (CPI3) Linux Kernel 4.14.2 Patch

## Cross compiler:
gcc-linaro-7.2.1-2017.11-x86_64_arm-linux-gnueabihf

## Compilation process:
* cp ./arch/arm/configs/clockworkpi_cpi3_defconfig .config
* make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf-
* mkimage -A arm -O linux -T kernel -C none -a 0x40008000 -e 0x40008000 -n "Linux kernel" -d arch/arm/boot/zImage uImage
