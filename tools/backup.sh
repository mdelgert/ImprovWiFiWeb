#!/bin/bash

curl http://demo1.local/backup --output backup.tar

#curl -X POST -F "file=@backup.tar" http://demo1.local/restore

# Untar the file
#tar -xzvf backup.tar
tar -xvf backup.tar
