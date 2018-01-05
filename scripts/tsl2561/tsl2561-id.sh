#!/bin/bash

set -e

result=`sudo i2cget -y 1 0x39 0x8A b`
echo $result
