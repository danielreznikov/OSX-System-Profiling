#!bin/sh

for i in 1 2 3 4 5 6 7 8 9 10
do
    echo "iteration ${i}..."
    ./a.out
    mv ./results/file_read_time.csv ./results/file_read_time_t${i}.csv
done