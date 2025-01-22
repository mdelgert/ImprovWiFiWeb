#!/bin/bash

VERSION="v1.0.18"

echo "Current version is $VERSION"
git tag -d $VERSION
git push origin --delete $VERSION
git tag -a $VERSION -m "Test"
git push origin $VERSION
