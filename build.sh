#!/bin/sh


autoreconf --force --install

rm -rf build/
mkdir -p build && cd build/

../configure \
  --prefix=/usr \
  --sysconfdir=/etc \
  --disable-sanitizers

make
