# zeeRobotMazeLogic
Science fair project that uses Arduino robot, HC_SR04 Ultra Sonic sensor to navigate a maze.  The maze must have an entrance and exit on the outside wall.  The hallways cannot go under or over each other.

We will use the simple rule follow the right side to get out.

We are using 3 Ultra Sonic Sensors.  1 Sensor in Front to detect what's in front and avoid collision.  2 Sensors on the right side to know if we have a wall parallel and to know when to turn.

We will also have a Line Reader which we use to know when we exit the maze.  The Line Reader will not be used to navigate the maze, it will be used as a finish line.

We have 2 LEDs to give us feedback on wall detection.  We may add a 3rd LED using one color for moving forward, another color for turning right, and a color for turning left.




