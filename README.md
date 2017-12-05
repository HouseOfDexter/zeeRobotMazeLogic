# zeeRobotMazeLogic
Science fair project that uses Arduino robot, HC_SR04 Ultra Sonic sensors to navigate a maze.  The maze must have an entrance and exit on the outside wall.  The hallways cannot go under or over each other.

We will use the simple rule, to follow the right side to get out.

The robot will be a modified Elegoo Smart Robot Car Kit V3.0.
We are using 3 Ultra Sonic Sensors(HC_SR04 Ultra Sonic).  1 Sensor in Front to detect what's in front and avoid collision.  2 Sensors on the right side to know if we have a wall parallel and to know when to turn.

We will also have a Line Reader(from Elegoo Robot kit) which we use to know when we exit the maze.  The Line Reader will not be used to navigate the maze, it will be used as a way to detect the finish line.

We have 2 LEDs to give us feedback on wall detection.  We may add a 3rd LED using one color for moving forward, another color for turning right, and a color for turning left.

We may use the Adafruit Motor/Stepper/Servo Shield for Arduino v2 Kit and the Adafruit Motor Shield V2 Library to control the DCMotors. https://github.com/adafruit/Adafruit_Motor_Shield_V2_Library or the Shield that comes with the Elegoo kit.

We upgraded the motherboard from Elegoo Uno 3(Arduino Uno clone), to Elegoo AT2560 R3(Arduino AT2560 clone). We upgrade the board because most of the pins where being used by Robot Car(only 2 free pins).  We went with Elegoo's Servo Shield.

AFTERMATH:

We weren't able to get the Robot through the maze.  The problem was a timing issue, with 3 UltraSonic sensors, we had a delay of about 1000 ms with 3 sensors going.  Unfortunately the Arduino boards do not have an OS or multiple cores, this causes everything to be on a single thread.  Coded around everything but the sensors inherent delay in reading the Ultra Sonic pulse. The robot was also slowed down, but then the robot had a torque problem with the DC motors.  If done again, would definately not use the HC SR04 Ultra Sensors.  There's just to much of a delay in the sensors to use for navigation.  They make fine sensors for obstical avoidance.  A Laser Range Finder would be used if done again.




