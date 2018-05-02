#!bin/sh

# radmon.data should be a kilobyte large
dd if=/dev/random of=random.data bs=1024 count=1000 