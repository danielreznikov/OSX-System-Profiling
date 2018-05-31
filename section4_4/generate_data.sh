#!bin/sh

# random.data should be a kilobyte large, file size is 512KB.
dd if=/dev/urandom of=data/data_proc$1 bs=1024 count=512
