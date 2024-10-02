// Right sensor
#define TRIG_RIGHT A2
#define ECHO_RIGHT A1

// Left sensor
#define TRIG_LEFT 3
#define ECHO_LEFT 2
 
 void doPingRight(void);
void doPingLeft(void);
void getDistances(void);
void setupPins(void);
 
 int distance_right;
int distance_left;


 void setup(){
 
  setupPins();
   
  // Setup serial communication 
  Serial.begin(9600);
}

void loop(){
 
  getDistances();
  
  // Print the distances in inches
  Serial.println((String)"Distance Right: " + distance_right); 
  Serial.println((String)"Distance Left: " + distance_left);
  Serial.println("");
  
  // Pause for 1.0 second
  delay(1000);
}
 
void doPingRight() {
  
  digitalWrite(TRIG_RIGHT, LOW);
  delayMicroseconds(2); 
      
  
  digitalWrite(TRIG_RIGHT, HIGH);

  delayMicroseconds(10);
  digitalWrite(TRIG_RIGHT, LOW);
       
        distance_right = pulseIn(ECHO_RIGHT, HIGH);

         distance_right = distance_right / 74 / 2;
  distance_right = abs(distance_right);
}
void doPingLeft(){
 
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
 
void setupPins(){
  // Configure HC-SR04 pins
  pinMode(TRIG_RIGHT, OUTPUT);
  pinMode(ECHO_RIGHT, INPUT);
  pinMode(TRIG_LEFT, OUTPUT);
  pinMode(ECHO_LEFT, INPUT);
}