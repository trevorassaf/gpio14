#!/bin/bash

set -x

sudo i2cget -y 1 0x39 0x81 b
