# Profiling OS and Hardware: CSE 221 - Project
By Rebecca McKinley (mckinleyrebecca), Daniel Reznikov (danielreznikov), and Aaron Trefler (aarontrefler)

Read our Project Report: https://github.com/danielreznikov/OSX-System-Profiling/tree/master/Report/osx-system-measurement.pdf

## Running Measurements
### Running CPU measurements
```
cd section4_1/  
mkdir data  
make  
nice -n -20 ./1_driver.out
```
### Memory Measurements
```
cd section4_2/  
make  
nice -n -20 ./2_driver.out
```
### Network Measurements
### Local Server
Open new terminal  
```
cd section4_3/  
python XYZ_server.py  
```
XYZ is the name of the experiment you want to run: bandwidth, connection, or rtt  
### Local Client
Open another new terminal  
```
cd section4_3/  
python XYZ_client.py 127.0.0.1 
```
XYZ is the name of the experiment you want to run: bandwidth, connection, or rtt  
### Remote Server
Open new terminal  
```
cd section4_3/  
python XYZ_server.py  
```
XYZ is the name of the experiment you want to run: bandwidth, connection, or rtt  
### Remote Client
Open another new terminal  
```
cd section4_3/  
python XYZ_client.py IP_ADDR 
```
XYZ is the name of the experiment you want to run: bandwidth, connection, or rtt  
IP_ADDR is found by going into Network Preferences and using your listed IP on your WiFi
### File System Measurements
```
cd section4_4/
make
nice -n -20 ./4_driver.out
```
