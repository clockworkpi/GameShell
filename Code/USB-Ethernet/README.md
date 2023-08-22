## This is outdated,in os image v0.3 or later,usb network is already included,just flash the os image

# Setup USB Ethernet

## Install isc-dhcp-server
```
apt-get install isc-dhcp-server
```
## Edit file "isc-dhcp-server"
Open the file: ```/etc/default/isc-dhcp-server```

Add this:
```
INTERFACES="usb0"
``` 

## Edit file "dhcpd.conf"
Open the file: ```/etc/dhcp/dhcpd.conf```

Add this:
```
subnet 192.168.10.0 netmask 255.255.255.0 {
  range 192.168.10.10 192.168.10.250;
}
```
## Edit file "interfaces"
Open the file: ```/etc/network/interfaces```

Add this:
```
allow-hotplug usb0
auto usb0
iface usb0 inet static
      address 192.168.10.1
      netmask 255.255.255.0
```         

## Update the Kernel（ os image v0.1 )
Download the Kernel image:

https://github.com/clockworkpi/Kernel/raw/master/uImage

To the first partition of the micro SD card.


