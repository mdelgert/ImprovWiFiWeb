#!/bin/bash
cd ..
#pio run
pio run --target upload
#pio remote --agent pve1 run --target upload
#pio remote --agent d1 run --target upload