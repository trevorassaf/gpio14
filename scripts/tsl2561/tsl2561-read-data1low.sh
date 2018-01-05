#!/bin/bash

set -ex

sudo i2cget -y 1 0x39 0xae b
