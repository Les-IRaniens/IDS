#!/bin/sh

path="$(dirname $0)/../"

make -C $path/libeasy/
make -C $path
