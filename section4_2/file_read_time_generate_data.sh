#!bin/sh

# Generae multiple files for "file read time" experiments 
echo "Generating 2^14 bit file..."
dd if=/dev/urandom of=data/random_16K.data bs=1024 count=16
echo "Generating 2^15 bit file..."
dd if=/dev/urandom of=data/random_32K.data bs=1024 count=32
echo "Generating 2^16 bit file..."
dd if=/dev/urandom of=data/random_64K.data bs=1024 count=64
echo "Generating 2^17 bit file..."
dd if=/dev/urandom of=data/random_128K.data bs=1024 count=128
echo "Generating 2^18 bit file..."
dd if=/dev/urandom of=data/random_256K.data bs=1024 count=256