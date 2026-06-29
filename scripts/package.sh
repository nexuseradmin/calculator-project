#!/bin/bash

VERSION=$1

mkdir -p release

cp build/calculator_app release/

tar -czf calculator-${VERSION}.tar.gz release
