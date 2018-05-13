#!bin/sh

# radmon.data should be a kilobyte large
dd if=/dev/urandom of=random16.data bs=1024 count=16777216
