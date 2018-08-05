#!/bin/bash

sudo i2cdetect -y 1

echo "Performing forced temperature read..."
clear_hum_cmd="sudo i2cset -y 1 0x76 0xF2 0x00"
clear_pres_and_config_tmp_cmd="sudo i2cset -y 1 0x76 0xF4 `printf '0x%x' \"$((2#00100001))\"`"
echo "Clear humidity command: $clear_hum_cmd"
echo "Clear pressure and config temp command: $clear_pres_and_config_tmp_cmd"
$($clear_hum_cmd)
$($clear_pres_and_config_tmp_cmd)

sleep 1
msb=`sudo i2cget -y 1 0x76 0xFA | cut -b 3-`
sleep 1
lsb=`sudo i2cget -y 1 0x76 0xFB | cut -b 3-`
sleep 1
xsb=`sudo i2cget -y 1 0x76 0xFC | cut -b 3-`

echo "Raw temperature readout: 0x$msb$lsb$xsb"
