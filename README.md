# ESP8266-01  SoftAP y UDP Server

Instituto Tecnológico de Costa Rica  
Computer Engineering  
Introduction to programming and Programming Workshop  
2018

### Prerequisites
To run this project you will need:
1. ESP8266-01 WiFi module
2. Python 3.6.4 
3. Arduino IDE  
The libraries used are:  
* Arduino
1. ESP8266WiFi.h
2. WiFiUdp.h
* Python
3. socket
4. sys
5. Time

## Getting Started
This is an example of how to create an access point with ESP8266 module working with UDP Server.  
Also, an UDP Python Client is included, in order to demostrate a simple connection.  
This is an academic project, for that reason the internal documentation is in Spanish.
Please make sure the client device is connected to the network before sending messages.
The AP ssid will be **CarWiFi**

### Server Side
Once the power supply is connected, the module is going to start the Serial communication.  
If something fails during the setting up, the module will enter to a "while true" loop waiting for be reseted.
Otherwise the Serial output will be the next one:
```
Creating an Access Point  
Settiing soft-AP confuguration .... Ready  
Settiing the Access Point ....  Ready
Starting UDP server
Listenning at
IP:192.168.4.7
local Port:7070
Waiting for connection ....
```
### Client Side
The function UdpMessage is in charge of making the connection and send data to the server.  
UdpMessage receives a string, then it convert the string to bytes and starts sending the data.
The socket client will try to send the message, after that, it is going to wait a response for 2 seconds. 
If none response is given, a timeout exception will raise, and if the counter is lower than 9, it will try to send the command again.  
If a new message is received, the counter sets to 10, convert the bytes to string and print it, as shown below, finally returns the incommig string.
```
Try n°[1:9] to send message
.
.
Message from Server {msg}
```
### Tutorials
- [Programming ESP8266 with Arduino](https://www.hackster.io/harshmangukiya/how-to-program-esp8266-with-arduino-uno-efb05f)
- [Install ESP8266WiFi.h](http://esp8266.github.io/Arduino/versions/2.0.0/doc/installing.html)

### Known problems
In my computer (toshiba ultrabook satellite u940) the controller resets when is trying to connecto to the AP.
The AP resets after a while, this can be cause by an exception in the software or lack of power.   
## Author
Santiago Gamboa Ramírez  
santigr17@gmail.com  
2014092362  

### Version
1.0.0
