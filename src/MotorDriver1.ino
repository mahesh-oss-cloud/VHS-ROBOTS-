//Define pins for Motor A
#define ENABLE_A 5
#define MOTOR_A1 6
#define MOTOR_A2 4
 
// Define pins for Motor B
#define ENABLE_B 8
#define MOTOR_B1 7
#define MOTOR_B2 9
void disableMotors(void);
void enableMotors(void);
void goForward(void);
void goLeft(void);
void goRight(void);
void setupPins(void);


void setup() {

  setupPins();
    
  // Set the data rate in bits per second
  Serial.begin(9600);  
}

void loop() {  
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

void disableMotors(){
  digitalWrite(ENABLE_A, LOW);
  digitalWrite(ENABLE_B, LOW);
}

void enableMotors(){
  digitalWrite(ENABLE_A, HIGH);
  digitalWrite(ENABLE_B, HIGH);  
}

void goForward(){
  digitalWrite(MOTOR_A1, LOW);
  digitalWrite(MOTOR_A2, HIGH);
  digitalWrite(MOTOR_B1, LOW);
  digitalWrite (MOTOR_B2, HIGH);
}

void goLeft(){
  digitalWrite(MOTOR_A1, LOW);
  digitalWrite(MOTOR_A2, HIGH);
  digitalWrite(MOTOR_B1, HIGH);
  digitalWrite (MOTOR_B2, LOW);
}

void goRight(){
  digitalWrite(MOTOR_A1, HIGH);
  digitalWrite(MOTOR_A2, LOW);
  digitalWrite(MOTOR_B1, LOW);
  digitalWrite (MOTOR_B2, HIGH);
}

void setupPins(){
  // Configure motor pins
  pinMode(ENABLE_A, OUTPUT);
  pinMode(MOTOR_A1, OUTPUT);
  pinMode(MOTOR_A2, OUTPUT);    
  pinMode(ENABLE_B, OUTPUT);
  pinMode(MOTOR_B1, OUTPUT);
  pinMode(MOTOR_B2, OUTPUT);  
}