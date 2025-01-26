#!/bin/bash

curl http://demo1.local/backup --output backup.tar
#curl -X POST -F "file=@backup.tar" http://demo1.local/restore
