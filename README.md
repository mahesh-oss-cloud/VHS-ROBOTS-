
**Self-Driving Car for National Robotics Competition**
**Project Description**
This project aims to build a fully autonomous self-driving car for the Future Engineers category of the National Robotics Competition. The car is designed to complete three key challenges:

**Time Attack Race:** The car will drive autonomously on a closed track to achieve the fastest lap times.

**Obstacle Challenge:** The car will detect and avoid randomly placed obstacles while navigating the track.

**Traffic Sign Challenge:** The car will follow green and red traffic signs, determining its lane position based on the signs and changing directions when a red sign is detected.
The vehicle is expected to navigate these challenges using a combination of sensors, motors, and intelligent algorithms that allow for precise control, obstacle avoidance, and traffic sign detection. The end goal is to complete all challenges and perform a parallel parking maneuver successfully.

**Hardware Components**
**1. Motors & Motor Driver**
2. **TT Motors(4x)**:** These are used for driving the car forward and backward. They provide the necessary torque to propel the vehicle. The motors are connected to the rear wheels of the vehicle and controlled by a motor driver.

***Servo Motor (1x)**: ****This controls the steering system, allowing the vehicle to turn left or right. It is linked to the front wheels for precise direction control.

**L298N Motor Driver (1x)**: The motor driver controls the speed and direction of the DC motors. It allows for differential control of the two motors while maintaining their synchronized movement. This is essential for both straight driving and turning during obstacle detection and lane changes.

**3. Sensors**
**Ultrasonic Sensor (HC-SR04):** Used for obstacle detection. It measures the distance to an object by sending out sound waves and calculating the time taken for the echo to return. This data is used to avoid collisions.

**Color Sensor (TCS3200):** The color sensor detects green and red traffic signs placed on the track. Based on the color detected, the car decides to either continue in the current lane (green) or turn around (red).

**IR Sensors (2x):** Placed on the front of the car for line tracking. These sensors help the vehicle stay within its designated lane by detecting the boundaries of the track.

**4. Power Source**
**LiPo Battery (7.4V):** This lightweight battery powers the entire vehicle. It provides the necessary voltage to run both the motors and the sensors.

**5. Controller**
**Arduino Uno:** The main microcontroller that coordinates all the components. It processes the data from the sensors and controls the motors and servo for movement and steering.

**Software**
**1. Libraries Used
Servo.h:** Used to control the steering servo motor.

**NewPing.h:** Handles the ultrasonic sensor for distance measurement.

**TCS3200.h:** A custom library to interface with the color sensor for traffic sign detection
.
****Wire.h: ****Interfaces with the IMU sensor to gather orientation and acceleration data.

**2. Code Workflow**
The software is designed to run an event-driven system where each sensor triggers a specific response. Below is the basic workflow:
**1.Initialization:** All sensors and motors are initialized. The vehicle waits for the start signal to begin the challenge.

2**Obstacle Detection:** During navigation, the ultrasonic sensor continuously checks for obstacles. If an obstacle is detected within a certain range (e.g., 20 cm), the car halts and steers around the object before resuming its path.

**3.Lane Following:**The IR sensors detect the track’s boundaries. If the vehicle starts drifting outside the lane, corrective actions are taken by adjusting the steering angle via the servo motor.

**4.Traffic Sign Detection**: The TCS3200 color sensor scans for green and red traffic signs. A green sign instructs the vehicle to continue forward, while a red sign signals the vehicle to turn around and complete the final lap in the opposite direction.

**5.Parallel Parking:** Once all laps are complete, the vehicle uses the IMU and ultrasonic sensors to identify the parking lot and execute the parking maneuver by controlling both the steering and driving motors.

**Compilation**
**Steps to Build and Upload Code to Arduino:**
Connect all hardware components to the Arduino as per the circuit diagram (including motors, motor drivers, and sensors).

Install the necessary libraries in the Arduino IDE:

Go to Sketch > Include Library > Manage Libraries and install Servo, NewPing, TCS3200, and Wire.

Load the code onto the Arduino:

Open the Arduino IDE.

Select the correct board (Arduino Uno) under Tools > Board.

Select the correct port under Tools > Port.

Click the Upload button to upload the code to the Arduino.

Test the sensors and motors:

Use the Serial Monitor to debug sensor data and ensure the sensors are working correctly.

Test motor functionality to verify forward, backward, and turning movements.

Run the full program to start the vehicle in autonomous mode.
**Challenges and Solutions**
**1. Sensor Interference**

Challenge: During initial testing, the ultrasonic sensor showed inconsistent readings when detecting obstacles, especially when the surface of the object was uneven or reflective.

Solution: We adjusted the positioning of the sensor and fine-tuned the threshold values in the code to account for noisy data. Additionally, we added a delay between sensor readings to avoid rapid triggering.

**2. Steering Calibration**
Challenge: The servo motor responsible for steering had difficulty maintaining precise turns, particularly on sharp curves. It also resulted in some over-steering during the first trials.

Solution: We implemented a proportional control algorithm that adjusts the steering angle based on the vehicle’s current position on the track. This allowed smoother turns and more controlled driving.

**3. Battery Management**

**Challenge: **The vehicle experienced power fluctuations when the motors and sensors drew high amounts of current simultaneously, which led to inconsistent behavior.

**Solution**: We introduced a capacitor into the circuit to stabilize the power supply and used a voltage regulator to ensure consistent power delivery to the motors and sensors.

**4. Traffic Sign Detection**

**Challenge: **The color sensor initially had trouble differentiating between red and green traffic signs in varied lighting conditions.

**Solution:** We programmed dynamic thresholding based on ambient light conditions. The vehicle now performs a calibration routine at the start of the run to adjust sensor sensitivity according to the lighting environment.

**Self-Driving Car for National Robotics Competition

Welcome to the official repository for the Self-Driving Car project. For detailed documentation, including hardware setup, software details, and troubleshooting, please visit our [GitHub Wiki].( https://github.com/mahesh-oss-cloud/Self-driving-Car.wiki.git)

The codes for the System program of the car :-
****Ultrasonic Sensors(HC2R04)**
**// Right sensor**
#define TRIG_RIGHT A2
#define ECHO_RIGHT A1

**// Left sensor**
#define TRIG_LEFT 3
#define ECHO_LEFT 2
 
 void doPingRight(void);
void doPingLeft(void);
void getDistances(void);
void setupPins(void);
 
 int distance_right;
int distance_left;


 **void setup(){**
 
  setupPins();
   
  // Setup serial communication 
  Serial.begin(9600);
}

**void loop(){**
 
  getDistances();
  
  // Print the distances in inches
  Serial.println((String)"Distance Right: " + distance_right); 
  Serial.println((String)"Distance Left: " + distance_left);
  Serial.println("");
  
  // Pause for 1.0 second
  delay(1000);
}
 
**void doPingRight() {**
  
  digitalWrite(TRIG_RIGHT, LOW);
  delayMicroseconds(2); 
      
  
  digitalWrite(TRIG_RIGHT, HIGH);

  delayMicroseconds(10);
  digitalWrite(TRIG_RIGHT, LOW);
       
        distance_right = pulseIn(ECHO_RIGHT, HIGH);

         distance_right = distance_right / 74 / 2;
  distance_right = abs(distance_right);
}
**void doPingLeft(){**
 
  digitalWrite(TRIG_LEFT, LOW);
  delayMicroseconds(2); 
      
  
  digitalWrite(TRIG_LEFT, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_LEFT, LOW);
       
  distance_left = pulseIn(ECHO_LEFT, HIGH);
  
  
  distance_left = distance_left / 74 / 2;
  distance_left = abs(distance_left); 
}
 void getDistances() {
  // Take distance readings on the HC-SR04
  doPingRight();
  doPingLeft();   
}
 
**void setupPins(){**
  // Configure HC-SR04 pins
  pinMode(TRIG_RIGHT, OUTPUT);
  pinMode(ECHO_RIGHT, INPUT);
  pinMode(TRIG_LEFT, OUTPUT);
  pinMode(ECHO_LEFT, INPUT);
}


**2.Motor Driver(L298D)**
**//Define pins for Motor A**
#define ENABLE_A 5
#define MOTOR_A1 6
#define MOTOR_A2 4
 
**// Define pins for Motor B**
#define ENABLE_B 8
#define MOTOR_B1 7
#define MOTOR_B2 9
void disableMotors(void);
void enableMotors(void);
void goForward(void);
void goLeft(void);
void goRight(void);
void setupPins(void);


****void setup() {**
**
  **setupPins();**
    
  // Set the data rate in bits per second
  Serial.begin(9600);  
}

****void loop() {  **
  enableMotors();
  goForward();
  delay(2000);
  goRight();
  delay(500);
  goForward();
  delay(2000);  
  goLeft();
  delay(500);
  goForward();
  delay(2000); 
  disableMotors();
  delay(3000);
}

**void disableMotors(){**
  digitalWrite(ENABLE_A, LOW);
  digitalWrite(ENABLE_B, LOW);
}

**void enableMotors(){**
  digitalWrite(ENABLE_A, HIGH);
  digitalWrite(ENABLE_B, HIGH);  
}

**void goForward(){**
  digitalWrite(MOTOR_A1, LOW);
  digitalWrite(MOTOR_A2, HIGH);
  digitalWrite(MOTOR_B1, LOW);
  digitalWrite (MOTOR_B2, HIGH);
}

**void goLeft(){**
  digitalWrite(MOTOR_A1, LOW);
  digitalWrite(MOTOR_A2, HIGH);
  digitalWrite(MOTOR_B1, HIGH);
  digitalWrite (MOTOR_B2, LOW);
}

**void goRight(){**
  digitalWrite(MOTOR_A1, HIGH);
  digitalWrite(MOTOR_A2, LOW);
  digitalWrite(MOTOR_B1, LOW);
  digitalWrite (MOTOR_B2, HIGH);
}

**void setupPins(){**
  // Configure motor pins
  pinMode(ENABLE_A, OUTPUT);
  pinMode(MOTOR_A1, OUTPUT);
  pinMode(MOTOR_A2, OUTPUT);    
  pinMode(ENABLE_B, OUTPUT);
  pinMode(MOTOR_B1, OUTPUT);
  pinMode(MOTOR_B2, OUTPUT);  
}

**
**
**3.Color Sensors(TCS3200):-**
**// define pins**
const int S0 = 2;
const int S1 = 3;
const int S2 = 4;
const int S3 = 5;
const int signal = 6;

**// LED pins**
const int redLED = 10;
const int greenLED = 9;
const int blueLED = 8;

**// define variables for pulses**
unsigned long red;
unsigned long blue;
unsigned long green;
unsigned long clear;

**void setup() { // put your setup code here, to run once:**
  // set pin modes
  pinMode(S0,OUTPUT);
  pinMode(S1,OUTPUT);
  pinMode(S2,OUTPUT);
  pinMode(S3,OUTPUT);
  pinMode(signal,INPUT);
  pinMode(redLED,OUTPUT);
  pinMode(greenLED,OUTPUT);
  pinMode(blueLED,OUTPUT);

  
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);

  **// initialize serial communication**
  Serial.begin(9600);
}

**void loop() { 
  **
  // clear
  digitalWrite(S2,HIGH);
  digitalWrite(S3,LOW);
  clear = pulseIn(signal,HIGH);
  
 ** // red**
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  red = pulseIn(signal,HIGH);

  // green
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  green = pulseIn(signal,HIGH);

  // blue
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  blue = pulseIn(signal,HIGH);

  
  red = map(red,80,30,0,255);
  green = map(green,80,30,0,255);
  blue = map(blue,80,30,0,255);
  
  // turn LEDs on depending on which color is detected
  if(red>200 && green<100 && blue<100){  // red detected
    digitalWrite(redLED,HIGH);
    digitalWrite(greenLED,LOW);
    digitalWrite(blueLED,LOW);
  }
  else if(red<100 && green>150 && blue<150){  // green detected
    digitalWrite(redLED,LOW);
    digitalWrite(greenLED,HIGH);
    digitalWrite(blueLED,LOW);
  }
  else if(red<100 && green<100 && blue>80){  // blue detected
    digitalWrite(redLED,LOW);
    digitalWrite(greenLED,LOW);
    digitalWrite(blueLED,HIGH);
  }
  else{  

  // print readings
  
  Serial.print("Red: ");
  Serial.print(red);
  Serial.print(" | Green: ");
  Serial.print(green);
  Serial.print(" | Blue: ");
  Serial.println(blue);
  

}
