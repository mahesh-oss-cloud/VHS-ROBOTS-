
const int s0 = 2;   // Frequency scaling pin S0
const int s1 = 3;   // Frequency scaling pin S1
const int s2 = 12;  // Color sensor pin S2
const int s3 = 13;  // Color sensor pin S3
const int out = 11; // Output pin of color sensor

// Motor control pins
const int leftMotorForward = 6;
const int leftMotorBackward = 7;
const int rightMotorForward = 8;
const int rightMotorBackward = 9;

// Ultrasonic sensor pins
const int trigPin = A1;  // Trigger pin for ultrasonic sensor
const int echoPin = A2;  // Echo pin for ultrasonic sensor (analog pin)

// Distance settings
const int stopDistance = 10; // Stop distance in cm

// Variables to store color values
int Red = 0, Blue = 0, Green = 0;

void setup() {
  // Setup color sensor pins
  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(out, INPUT);

  // Setup motor control pins
  pinMode(leftMotorForward, OUTPUT);
  pinMode(leftMotorBackward, OUTPUT);
  pinMode(rightMotorForward, OUTPUT);
  pinMode(rightMotorBackward, OUTPUT);

  // Setup ultrasonic sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.begin(9600); // Initialize serial communication

  // Set frequency scaling to 100% (HIGH, HIGH)
  digitalWrite(s0, HIGH);
  digitalWrite(s1, HIGH);

  // Start moving forward at the beginning
  moveForward(); // Move forward at the start
}

void loop() {
  int distance = getDistance(); // Get distance from ultrasonic sensor

  // Stop the robot if an obstacle is detected within the stop distance
  if (distance <= stopDistance) {
    Serial.println("Obstacle detected - Stopping");
    moveStop(); // Stop the robot
    return; // Exit the loop early
  }

  GetColors();  // Get the color values

  // Check for green color detection
  if (Green > Red && Green > Blue) {
    Serial.println("Green detected - Turning Left");
    turnLeft(); // Turn left
  } 
  // Check for red color detection
  else if (Red > Blue && Red > Green) {
    Serial.println("Red detected - Turning Right");
    turnRight(); // Turn right
  } 
  // Check for blue color detection
  else if (Blue > Red && Blue > Green) {
    Serial.println("Blue detected - Turning Right");
    turnRight(); // Turn right
  } 
  // Check for magenta (Red + Blue > Green)
  else if (Red > Green && Blue > Green && (Red - Green) > 50 && (Blue - Green) > 50) {
    Serial.println("Magenta detected - Parallel Parking");
    parallelPark(); // Perform parallel parking
  }
  else {
    Serial.println("No dominant color detected - Moving Forward");
    moveForward(); // Move forward if no specific color is detected
  }

  delay(500); // Delay to allow sensor reading stabilization
}

// Function to get distance from ultrasonic sensor
int getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Use analogRead to get the echo pin value
  int echoValue = analogRead(echoPin);
  
  // Convert the analog value to distance in cm
  int distance = map(echoValue, 0, 1023, 0, 400); // Adjust mapping based on your setup
  return distance; // Return distance in cm
}

// Function to get color values
void GetColors() {
  // Read Red value
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);
  Red = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
  delay(20);

  // Read Blue value
  digitalWrite(s3, HIGH);
  Blue = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
  delay(20);

  // Read Green value, 
  digitalWrite(s2, HIGH);
  Green = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
  delay(20);

  // Debugging: print out the raw color values
  Serial.print("Red: ");
  Serial.print(Red);
  Serial.print(" Blue: ");
  Serial.print(Blue);
  Serial.print(" Green: ");
  Serial.println(Green);
}

// Function to move forward
void moveForward() {
  digitalWrite(leftMotorForward, HIGH);
  digitalWrite(rightMotorForward, HIGH);
  digitalWrite(leftMotorBackward, LOW);
  digitalWrite(rightMotorBackward, LOW);
}

// Function to stop
void moveStop() {
  digitalWrite(leftMotorForward, LOW);
  digitalWrite(rightMotorForward, LOW);
  digitalWrite(leftMotorBackward, LOW);
  digitalWrite(rightMotorBackward, LOW);
}

// Function to turn left
void turnLeft() {
  digitalWrite(leftMotorForward, LOW);
  digitalWrite(rightMotorForward, HIGH);
  delay(500); // Adjust delay for a proper turn
  moveForward(); // Continue moving forward
}

// Function to turn right
void turnRight() {
  digitalWrite(leftMotorForward, HIGH);
  digitalWrite(rightMotorForward, LOW);
  delay(500); // Adjust delay for a proper turn
  moveForward(); // Continue moving forward
}

// Function to parallel park
void parallelPark() {
  // Move backward
  digitalWrite(leftMotorBackward, HIGH);
  digitalWrite(rightMotorBackward, HIGH);
  delay(1000); // Adjust the delay to reverse into the parking spot

  // Turn right while moving backward
  digitalWrite(leftMotorBackward, HIGH);
  digitalWrite(rightMotorBackward, LOW);
  delay(500); // Adjust for the right angle turn

  // Move backward to complete parking
  digitalWrite(leftMotorBackward, HIGH);
  digitalWrite(rightMotorBackward, HIGH);
  delay(1000); // Adjust as needed to back up further

  // Stop after parking
  moveStop();
  
  Serial.println("Parallel Parking Completed");
}
