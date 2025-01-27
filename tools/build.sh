#!/bin/bash
cd ..
#pio run
#esptool.py erase_flash
pio run --target buildfs
pio run --target uploadfs
pio run --target upload
#pio remote --agent pve1 run --target upload
#pio remote --agent d1 run --target upload