#define sensorPin A0  
const int minSensorValue = 1;  
const int maxSensorValue = 150;  
const int minDegree = 0;  
const int maxDegree = 180;  
const int degreeStep = 5; 

int maxBendDegree = 0;  

void setup() {
  Serial.begin(9600);  

}

void loop() {
  int sensorValue = analogRead(sensorPin);  

  float normalizedVoltage = constrain(sensorValue, minSensorValue, maxSensorValue) / (float)maxSensorValue;
  int bendDegree = map(normalizedVoltage * normalizedVoltage, 0, 1, minDegree, maxDegree);

 if (sensorValue < 40) {
    bendDegree = 0;
  } else if (sensorValue < 45) {
    bendDegree = 5;
  } else if (sensorValue < 50) {
    bendDegree = 10;
  } else if (sensorValue < 55) {
    bendDegree = 15;
  } else if (sensorValue < 60) {
    bendDegree = 20;
  } else if (sensorValue < 65) {
    bendDegree = 25;
  } else if (sensorValue < 70) {
    bendDegree = 30;
  } else if (sensorValue < 75) {
    bendDegree = 35;
  } else if (sensorValue < 80) {
    bendDegree = 40;
  } else if (sensorValue < 85) {
    bendDegree = 45;
  } else if (sensorValue < 90) {
    bendDegree = 50;
  } else if (sensorValue < 95) {
    bendDegree = 55;
  } else if (sensorValue < 100) {
    bendDegree = 60;
  } else if (sensorValue < 105) {
    bendDegree = 65;
  } else if (sensorValue < 110) {
    bendDegree = 70;
  } else if (sensorValue < 115) {
    bendDegree = 75;
  } else if (sensorValue < 120) {
    bendDegree = 80;
  } else if (sensorValue < 125) {
    bendDegree = 85;
  } else if (sensorValue < 130) {
    bendDegree = 90;
  } else if (sensorValue < 135) {
    bendDegree = 95;
  } else if (sensorValue < 140) {
    bendDegree = 100;
  } else if (sensorValue < 145) {
    bendDegree = 105;
  } else if (sensorValue < 150) {
    bendDegree = 110;
  } else if (sensorValue <= 150) {
    int numSteps = (sensorValue - 40) / degreeStep; 
    bendDegree = numSteps * degreeStep; 
  } else {
    bendDegree = 0;  
  }

  if (bendDegree > maxBendDegree) {
    maxBendDegree = bendDegree;
  }

  Serial.print("Sensor value: ");
  Serial.print(sensorValue);
  Serial.print("  Bend degree: ");
  Serial.println(bendDegree);

  delay(100);  
}

bool calibrateSensor() {
  return true; 
}
