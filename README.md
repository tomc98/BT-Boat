# BT-Boat
Bluetooth boat made for Microprocessor Techniques 2303ENG

[*Using a Tiva C Series TM4C123G*](http://www.ti.com/tool/EK-TM4C123GXL "Product Page")
# Project Documentation
## Final Features
- Bluetooth Control
- Dual Motor paddle
- Internal Timer
- Buzzer horn
## Cut/Omitted Features 
- Ultrasonic Sensor
- Autonomous Control
### Reason for omission:
*The ultrasonic sensor did not want to register the distance between the boat and object. (Programming Error)*

# Process Flowchart
![alt text](https://github.com/tomc98/BT-Boat/blob/master/flow.JPG "Flowchart")

# Building The Boat
|                                      Picture                                      | Description                                                                                                                                                                                                                                                                                                                                                                            |
|:-----------------------------------------------------------------------------------:|------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| ![alt text](https://github.com/tomc98/BT-Boat/blob/master/paddles.JPG "Paddles")    | The paddles are made of bent plastic spoons that were hot glued onto a round plastic cutout. The spoons were bent using a hair dryer but a heat gun would have done a better job of it.    The round cutout that holds everything is placed onto an axle connected to the motor.    The hot glue seems to hold everything on very well and I have not had any issues with it. |
| ![alt text](https://github.com/tomc98/BT-Boat/blob/master/motor.JPG "Motor")        |  Two 3V motors are geared down to move the paddles independently. They are held on top of the raft with the use of hot glue.   The motors are controlled by a single L293DNE motor controller. They are rated from 4.4V and up but still work with 3.3V.                                                                                                                         |
| ![alt text](https://github.com/tomc98/BT-Boat/blob/master/raft.JPG "Raft")          |  The raft is a plastic tupperware container with a bit of foam hot glued to the lid. This foam serves to get the paddles further away from the container so that they do not collide with the raft.   A hole has been cut into the lid to allow the wires to pass through.                                                                                                    |
| ![alt text](https://github.com/tomc98/BT-Boat/blob/master/internal.JPG "Internals") |  A bluetooth slave takes everything coming from the computer and passes it to the Tiva.  The bluetooth is using a baud rate of 9600 and has no parity, and one stop bit.   A buzzer can be turned on and off while the boat is running. This is used as a makeshift horn.                                                                                                     |
## Note if using code
In *computer/control.py* line *13* change **NORMAL** to the name of your bluetooth device.
```python
13| if bluetooth.lookup_name( i ) == "NORMAL":
```
## Issues with control
When controling with bluetooth there is a latency between when a buttton is pressed and when it gets executed on the motors. This lag is due to the way bluetooth handles data and requests. A radio system would work far better.
