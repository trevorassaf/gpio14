#/bin/bash

set -e

result=`sudo i2cget -y 1 0x39 0x80 b`

if [ $result = "0x03" -o $result = "0x33" ]; then
  echo "Yes: $result"
elif [ $result = "0x00" ]; then
  echo "No: $result"
else
  echo "Unknown value: $result"
fi
