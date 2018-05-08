#!bin/sh

# radmon.data should be a kilobyte large
dd if=/dev/urandom of=random.data bs=1024 count=3145728