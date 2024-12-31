#!/bin/bash

VERSION="v1.0.1"

echo "Current version is $VERSION"

git tag -d $VERSION
git push origin --delete $VERSION
git tag -a $VERSION -m "Test2"
git push origin $VERSION
