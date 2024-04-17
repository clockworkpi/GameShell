Linux kernel branch 5.15.y

```
git://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git
```

linux-5.15.y

git commit hash `5827ddaf4534c52d31dd464679a186b41810ef76`


After git apply all patches

```
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- clockworkpi_cpi3_defconfig
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf-
mkimage -A arm -O linux -T kernel -C none -a 0x40008000 -e 0x40008000 -n "Linux kernel" -d arch/arm/boot/zImage uImage
```


