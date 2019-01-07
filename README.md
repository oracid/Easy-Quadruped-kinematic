# Easy-Quadruped-kinematic

Please, have a look at the vidéo, https://youtu.be/u2TaByk-uVE

KinematicV9.ino is a very simple program in C language to test your quadruped kinematic.
This example is for a 8 servos quadruped like a Kame. Credit to JavierIH, owenlab, manic-3d-print.
All servos work simultaneously. This is the good of this program.
Do the following :
- Consider the Kinematic() function as a black box.
- You have to modify the value of the 3 variables, mySrv, nbFeet, Speed.
- You have to fill the table of your kinematic values. But if you have no idea, you can just use like there are or modify them a little to see what append.
- You must modify the SrvAdjust table. In this table, you can adjust the neutral position(90°) of each servo. If no idea, modify with zeros.
- And that's it.

QuadrupedKinematicStroll-V3.ino is a program based on KinematicV9.ino
This program is a stroll example with forward, turn left and turn right. Notice that the 4 first lines of the tables are the same but in different order.

QuadrupedKinematicUS-V1.ino is a program using an ultrasonic sensor. It looks very much like QuadrupedKinematicStroll-V3.ino exept that it uses the ultrasonic sensor to change way.
