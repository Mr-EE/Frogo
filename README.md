#Frogo#

First stab at an autonomous robot. Small 2 wheeled frog looking thing.

##Introduction##
Started off with the idea to make a platform to investigate robotic control, path planning, servo control, etc... 

###Original vision###
- Four wheeled, controlled by DC motors with encoders
- Double decker wood base
- Powered by 4 AA batteries
- Breadboard for some glue circuitry (i.e. power regulators, motor drivers, etc.)
- "Frog eyes" i.e. ultrasound sensors
- Brains by Xplain Atmel development kit
- 4.3" LCD screen for diagnostic purposes as well as to look cool

![Alt text](https://github.com/Mr-EE/Frogo/blob/master/MECHware/3DModel_Frogo_Front.png "Frogo Front")
![Alt text](https://github.com/Mr-EE/Frogo/blob/master/MECHware/3DModel_Frogo_Side.png "Frogo Front")


###Actual Hardware###
- ~~Four~~ **Two** wheeled, controlled by DC motors with encoders **(added front caster)**
- ~~Double decker~~ **Single** wood base
- Powered by 4 AA batteries
- Breadboard for some glue circuitry (i.e. power regulators, motor drivers, etc.)
- ~~"Frog eyes" i.e. ultrasound sensors~~
- Brains by Xplain Atmel development kit
- ~~4.3" LCD screen for diagnostic purposes as well as to look cool~~

![Alt text](https://github.com/Mr-EE/Frogo/blob/master/Pics/RealModel_Front.jpg)
![Alt text](https://github.com/Mr-EE/Frogo/blob/master/Pics/RealModel_Side.jpg)



##Progress##
I started this project in 2010 but then I moved homes and this guy got packed up. I got busy with life so I never revived this project.

It's not the smartest robot. In fact all it does is drive in a straight line for a certain amount of encoder counts. The framework is there to drive the motors based on commands. I played around a bit by pre-programming a path such as to go straight for xx counts, turn left for yy counts, etc. I had the thought of connecting a ZigBee radio and communicating to it with a computer running a program to give commands. But never made it to that point


##License##
GPL v3
