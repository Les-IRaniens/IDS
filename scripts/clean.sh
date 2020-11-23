#!/bin/sh

path="$(dirname $0)/../"

make clean -C $path/libeasy
make clean -C $path
