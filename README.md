# zeeRobotMazeLogic
Science fair project that uses Arduino robot, HC_SR04 Ultra Sonic sensor to navigate a maze.  The maze must have an entrance and exit on the outside wall.  The hallways cannot go under or over each other.

We will use the simple rule follow the right side to get out.

The robot will be a modified Elegoo Smart Robot Car Kit V3.0.
We are using 3 Ultra Sonic Sensors(HC_SR04 Ultra Sonic).  1 Sensor in Front to detect what's in front and avoid collision.  2 Sensors on the right side to know if we have a wall parallel and to know when to turn.

We will also have a Line Reader(from Elegoo Robot kit) which we use to know when we exit the maze.  The Line Reader will not be used to navigate the maze, it will be used as a way to detect the finish line.

We have 2 LEDs to give us feedback on wall detection.  We may add a 3rd LED using one color for moving forward, another color for turning right, and a color for turning left.

We will use the Adafruit Motor/Stepper/Servo Shield for Arduino v2 Kit and the Adafruit Motor Shield V2 Library to control the DCMotors. https://github.com/adafruit/Adafruit_Motor_Shield_V2_Library




