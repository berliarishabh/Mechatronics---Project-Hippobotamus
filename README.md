# Mechatronics---Project-Hippobotamus

### Project Images


#### Front View
[! front-view](https://github.com/berliarishabh/Mechatronics---Project-Hippobotamus/blob/master/Project%20Images/FrontView.jpg?raw=true)

#### Back View
[! back-view](https://github.com/berliarishabh/Mechatronics---Project-Hippobotamus/blob/master/Project%20Images/BackView.jpg?raw=true)

#### Bottom View
[! bottom view](https://github.com/berliarishabh/Mechatronics---Project-Hippobotamus/blob/master/Project%20Images/BottomView.jpg?raw=true)

#### Top View
[! top_view](https://github.com/berliarishabh/Mechatronics---Project-Hippobotamus/blob/master/Project%20Images/TopView.jpg?raw=true) 

#### Shooter 
[! shooter](https://github.com/berliarishabh/Mechatronics---Project-Hippobotamus/blob/master/Project%20Images/Shooter.jpg?raw=true)

#### Vision System
[! VisionSys](https://github.com/berliarishabh/Mechatronics---Project-Hippobotamus/blob/master/Project%20Images/Vision%20System.jpg?raw=true)


###OBJECTIVE:
To design, build and manufacture a complete autonomous robot that can compete in the robot version of the game, Hungry Hungry Hippos.

###MOTIVATION:
The name “Cthulhu Bot” has been inspired by a fictional cosmic entity created by writer and lunatic H.P. Lovecraft. Cthulhu was a half octopus, half man and half dragon from before time who inspired cultists. Late one night a team member was inspired to add USB tentacles to our robot by sleep deprivation. Or possibly by something that exists beyond time and sleeps in sunken Ryleh. Aiai Ftaghan.

###SYSTEM OVERVIEW:


The entire project is divided into the following subsystems:

#### 1. The Collector subsystem

Given the lack of machinists in the group, we focussed on utilizing 3d printers to create this device. Early in the project, a very inexpensive, battery powered vacuum was found at a thrift shop, pointing us towards a vacuum based collection system both due to price and easy availability. 
The vacuum was a disassembled, and initially attached to pipes scavenged from the project depot. Unfortunately the pipes did not prove to be very efficient at maintaining vacuum or collecting balls. In the end tower unit with a helical manifold was designed and printed. This manifold handled vacuum routing, ball collection/storage, and bolt on point for external boards and devices. The vacuum fan and motor was attached to the bottom of the tower using silicone caulk. It should be noted that the actual vacuum motor is not included in solidworks as it was an awkward shape to model, and so very rough dimensions of height and diameter were used in design planning rather than an actual model.	
The front nozzle allows for attachment of an air hose to connect to a front collection unit. The hole in the rear allows for mounting of a vacuum gate. For clarity a cutaway view above shows the helix and central vacuum distribution network.
The large helical channel is for storage of collected balls. The central channel and smaller holes penetrating the sides of central channel are for vacuum distribution. Their size and number allow for vacuum to be distributed with minimal friction losses and insure that as balls are collected, many holes will remain uncovered to distribute vacuum.
In order to maximize efficiency of collections, a suction head modelled off that of a standard vacuum was placed in the front of robot. This suction head had a wide front angled back to a channel permitting a single ball to pass and  a hose to be connected. This head was equipped with holes allowing a pair of casters to be placed so that it could roll freely on floor.
A significant use of the fillet feature in solidworks allowed for savings of material and print time in design of the vacuum head.  It also lowered frictional losses in vacuum, and allowed for higher likelihood of successful prints by preventing sharp transitions.
 The vacuum collector system was completed by a blast gate on rear of robot modelled off standard shop vacuum gates. It was bolted over rear opening on tower system. When gate was closed, smooth surfaces and strong vacuum allowed for efficient collection of balls. Actuated by a servomotor scavenged from the project depot and a rack and pinion track system, it could be opened when a payload of balls was collected. The angle of the downward spout allowed for balls to be gravity fed into the shooting mechanism subsystem with minimal intervention and no additional guidance tubes.

The entirety of vacuum system was mounted on a perforated acrylic platform with a 1” hole spacing pattern to allow for easy reconfiguration of system and mounting of additional part modules if needed.
Lucite cylinders (never modelled in solidworks) were cut, drilled and tapped on a late. These cylinders were used to mount the tower assembly over main platform of system. The systems main platform was initially made using perfboard, but proved both heavy and . For final iterations, acrylic sheet was cut on a laser cutter, while maintaining a similar hole pattern for convenience in mounting parts and routing wires.

#### 2. The Shooter Subsystem
One of the most common methods for firing ping pong balls in robotic contests and table tennis accessories is the flywheel mechanism.  The operating principle is that a pair of spinning wheels will contact the ball. Assuming negligible deformation and good contact friction the flywheels accelerate the ball both linearly to the right and give it some counterclockwise rotation and linearly to the left, giving it clockwise rotation.  When the interaction is over, the flywheel will lose some of its energy and angular momentum and the ball will gain some linear and angular momentum. As a result the entire counter rotating flywheel mechanism imparts the ball enough force to follow a straight line trajectory.
The flywheels were round foam pieces scavenged from the ITLL Project Depot. They were mounted on a shaft, and bearings were used to support said shaft and minimize friction. A housing was printed using PLA and the design was completed with two metal plates for motor mounting. 
After the initial print it was observed that the spaces for flywheels were not enough for the motors to sufficiently provide enough torque. Thus, a new design iteration was made with better spacing to provide enough room for the flywheels to rotate. The final design is shown below.


Earlier, it was thought that the shooter assembly could be made to align itself in straight line with the hoop, by providing it certain angles using a stepper motor with a belt drive mechanism. Though this design was incorporated, it could not be effectively used in the final demonstration. Therefore, at the very last moment, the shooter was super glued at an angle that directly points towards the centre of the hoop.


#### 3. The Drive Subsystem 

Two stepper motors (each equipped with a 4” diameter omniwheel) form the drive system. Initial designs had called for larger wheels, and more wheels to overcome the challenges of the proposed ⅜” foam barrier. However when it was eliminated from proposed arena our team was able to scale back drive requirements. A pair of casters under the suction head and another pair of casters under the circuitboard case in rear reduced friction and potential for robot to tip due to imbalances. 
The structure of the robot consists of an acrylic sheet mounted with wheels and casters. The shooter is mounted in the front with vacuum sweeper at the back. The front of the bot also consists of a power board enclosed in a 3D printed casing with 2 casters at the bottom. The back of the robot has vacuum sweeper with bottom mounts for the casters. In the middle of the acrylic sheet, there are 4 stands holding up another acrylic plate, where the collector unit is mounted. Above the collector unit stands the rotating vision system circuit. The bottom of the bot, also has a 3D printed case to hold the batteries.

#### 4. The Electrical Subsystem

##### Components Used
* Freedom KL64F development board
* 2 High Speed DC Brushless Motors (for shooter)
* Vacuum Motor 
* Stepper Motor(BJ28Y) and driver (ULN2003) (For Vision System)
* 12V DC Motors with encoder (Drive system)
* 2 L293D motor driver (Shooter and Drive system)
* 3D Filament Rolls
* Circuit for the Vision System
* Polulu md07a motor driver (for the Vacuum Switch)
* USB Powered Tentacles.

The initial design called for use of a Raspberry Pi 2 with camera interface, but this resulted in very inconsistent image processing and had to be scrapped. In its place as simpler system using a single IR Receiver Transistor communicating with the Freescale Mbed was implemented.

Other electronic subsystems were designed individually during build of robot, and code was written/ validated on each individual system before being combined in system integration step. This saved a lot of time in final assembly of robot, and allowed for flaws in code to be found early in process. 
A problem that did crop up in the final stages of design however was power supply overheating due to the current draw of the vacuum fan and drive wheels. In order to mitigate this an enclosure was designed and 12 Volt fan mounted on it to drive air across the heat sinks.

However the biggest challenge was the vision system. Unbeknownst to the team, the PCB we had etched to communicate with it was damaged in the final stages of system integration. This gave us a significant amount of signal noise and false positives detected randomly even when there was no IR light in the vicinity. Significant time was lost in determining that root cause was not software but hardware based. System also suffered from motion artifacts when it was moved from stationary test bed to robot. The team was forced to design a new vision system in the final days of project, and did not have adequate time for proper calibration. 

Another significant challenge was the shooting system. Initially it was meant to have a variable angle controlled by a stepper motor so that it could shoot from any range and aim at smaller or larger target depending on whether central tower was blocking smaller target. Unfortunately this stepper motor required significant current, more current in fact than the motor drivers available to team could provide.This resulted in the motor driver burning out the night before competition. The team was then forced to fix shooter angle and change code to accommodate fixed angle. 

The third significant issue was the vacuum motor. A cheap (but powerful) handheld vacuum was sourced at a thrift shop. To satisfy our design needs we needed to disassemble it and integrate its motor into the robot. The motor however kept blowing the fuse we placed even at highest possible amperage of the Polulu Motor driver. It was later that Professor Reamon told us that the current spikes in such heavy motors could be a lot in the beginning. So as per his suggestion we moved to a higher amperage fuse and things worked out just fine.

#### 5. The Software Subsystem
The software development was done using the mbed’s online IDE and compiler. mbed has a great development IDE for a wide range of embedded microcontrollers and provides easy-to-use libraries and APIs.
The initial code flow has functions for each of the subsystems and test codes to test each of the individual subsystem. The various individual subsystems involved in the software flow are: Drive system, Shooter System, Vacuum suction system, Vacuum gate system, Vision/Beacon system and the Line follower system.
Flow Chart for system is shown on next page.

The most significant programming challenge was converting between integers and floats. It had been assumed that the x,y coordinates we provided would be implicitly converted to integers, but this did not prove to be the case. For example, we had a x y values of  260 and 360. Dividing should have given us an output of 0.72 in radians but the function was passing 0. After considerable frustration, we concluded that mbed compiler does not support implicit conversion. So we had to provide the float value directly.




#### Lessons Learned
This project has been a valuable learning experience and has taught a lot of short hand tricks and long term design challenges required in a real time project. Some of the lessons learned are:
Creating a component or an entire robot is an iterative process, that needs work everyday. So, procrastinating is the worst practice.
The better you prototype the design, the less you have to change in the actual product.
3D printing is a double edged sword. While it can save significant time with appropriate design (and luck) it can also cost a lot of time if the printer jams mid job or if there are flaws in the solidworks model.
Proper planning and a lucrative thought process is very important.
Just making the robot is not enough. The robot requires testing and iterative programing in the intended context to work out the bugs. 
It is inevitable that loose wires will be disconnected. Once initial design is concluded, fixing location of microcontroller and boards is critical so that wires can be routed through system.
We learned that you should question every assumption of yours if stuck in an unexplainable situation. There is always an explanation, you just need to look at the right place.
The most rookie and time costing mistake that we made was to connect the GND and VCC pins otherway. This blew up our mbed and a few motor drivers. We had to set up all this again and this cost a lot of time. 
We learnt that scavenging parts is a good idea but you need to identify the parts before hand and discard them if they do not fit your needs.
It’s okay to make mistakes, that how we learn and hopefully the future semester students can learn from them. 


