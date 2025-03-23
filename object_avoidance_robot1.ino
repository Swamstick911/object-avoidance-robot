// C++ code

//Motor Pins
#define ENA 6
#define ENB 7
#define IN1 2
#define IN2 3
#define IN3 4
#define IN4 8

//Ultrasonic sensor pins
#define sigPin 9
#define MAX_DISTANCE 200


void setup() {
  pinMode(sigPin, OUTPUT);
  
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  digitalWrite(ENA, HIGH);
  digitalWrite(ENB, HIGH);
  
  Serial.begin(9600);
}

void loop () {
  long duration;
  int distance;
  
  pinMode(sigPin, OUTPUT);
  digitalWrite(sigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(sigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(sigPin, LOW);
  
  pinMode(sigPin, INPUT);
  duration = pulseIn(sigPin, HIGH);
  distance = duration * 0.034 / 2;
  
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(" cm");
  
  if (distance > 20 || distance <= 0) {
    moveForward();
  } else {
    stopMotors();
    delay(500);
    moveBackward();
    delay(700);
    
    // Try right turn first, if still blocked try left turn
    turnRight();
    delay(600);
    
    long newDistance;
    pinMode(sigPin, INPUT);
    newDistance =  pulseIn(sigPin, HIGH) *0.034 / 2;
    
    if(newDistance <= 20) {
      turnLeft();
      delay(600);
    }
  }
}

void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void moveBackward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void turnRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void turnLeft() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}