#!/bin/bash

set -e

sudo i2cset -y 1 0x39 0x81 0x10 b
