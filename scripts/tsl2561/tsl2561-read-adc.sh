#!/bin/bash

set -ex

# Off
sudo i2cset -y 1 0x39 0x80 0x00 b

# On
sudo i2cset -y 1 0x39 0x80 0x03 b

# Set timer config for 0x12 = HighLong
sudo i2cset -y 1 0x39 0x81 0x12

sleep 0.5

# Read data 0
sudo i2cget -y 1 0x39 0x8C w

# Read data 1
sudo i2cget -y 1 0x39 0x8E w
