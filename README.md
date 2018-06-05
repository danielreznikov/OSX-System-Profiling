# Profiling OS and Hardware: CSE 221 - Project
By Rebecca McKinley (mckinleyrebecca), Daniel Reznikov (danielreznikov), and Aaron Trefler (aarontrefler)

## Running Measurements
### Running CPU measurements
cd section4_1/
mkdir data
make
nice -n -20 ./1_driver.out
### Memory Measurements
cd section4_2/
make
nice -n -20 ./2_driver.out
### Network Measurements
cd section4_3/

### File System Measurements
cd section4_4/
make
nice -n -20 ./4_driver.out
