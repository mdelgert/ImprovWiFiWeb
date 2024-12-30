#!/bin/bash
git tag -d v1.0.0
git push origin --delete v1.0.0
git tag -a v1.0.0 -m "Testing actions"
git push origin v1.0.0
