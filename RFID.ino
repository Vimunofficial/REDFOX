#include <SPI.h>
#include <MFRC522.h>
#include "thingProperties.h" // Include the generated code by the Arduino IoT Cloud

#define SS_PIN  21
#define RST_PIN 22
#define LED_G   12
MFRC522 mfrc522(SS_PIN, RST_PIN);

String patientName1 = "Raju";
String lastTreatment1 = "Physical Therapy";
String lastVisited1 = "2023-05-12";

String patientName2 = "Ramu";
String lastTreatment2 = "None";
String lastVisited2 = "Never";

const String UID_1 = "60 0A 30 59";
const String UID_2 = "59 8A F1 18";

void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  pinMode(LED_G, OUTPUT);
  Serial.println("Put your card to the reader...");
  Serial.println();
  
  // Initialize Arduino IoT Cloud
  initProperties();
  
  // Connect to Wi-Fi
  Serial.println("Connecting to Wi-Fi...");
  ArduinoCloud.begin("VIMUN", "12345678");
  
  // Wait for connection
  while (ArduinoCloud.connected() != 1) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to Wi-Fi!");
  
  // Set the secret key for Arduino IoT Cloud
  ArduinoCloud.setSecretKey("VtVfJOA4gL!kzB4PCQW5IKKwK");
}

void printPatientData(String patientUID) {
  if (patientUID == UID_1) {
    Serial.println("Patient One Detected");
    Serial.println("Patient Information:");
    Serial.println("Name: " + patientName1);
    Serial.println("Last Treatment: " + lastTreatment1);
    Serial.println("Last Visited: " + lastVisited1);
    Serial.println("................................................. " );
    Serial.println("................................................. " );
    // Send data to Arduino IoT Cloud
    Serial.println("Sending patient 1 data to Arduino IoT Cloud...");
    Raju_Name = patientName1;
    Physical_Therapy = lastTreatment1;
    Last_Visited = lastVisited1;
  } else if (patientUID == UID_2) {
    Serial.println("Patient Two Detected");
    Serial.println("Patient Information:");
    Serial.println("Name: " + patientName2);
    Serial.println("Last Treatment: " + lastTreatment2);
    Serial.println("Last Visited: " + lastVisited2);
    // Send data to Arduino IoT Cloud
    Serial.println("Sending patient 2 data to Arduino IoT Cloud...");
    Ramu_Name = patientName2;
    None = lastTreatment2;
    Never = lastVisited2;
  }
  // Update Arduino IoT Cloud
  ArduinoCloud.update();
}

void loop() {
  if (!mfrc522.PICC_IsNewCardPresent()) {
    delay(2000);
    return;
  }
  
  if (!mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  String content = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();
  
  if (content.substring(1) == UID_1) {
    printPatientData(UID_1);
    delay(500);
    digitalWrite(LED_G, HIGH);
    delay(2500);
    digitalWrite(LED_G, LOW);
  } else if (content.substring(1) == UID_2) {
    printPatientData(UID_2);
    delay(500);
    digitalWrite(LED_G, HIGH);
    delay(2500);
    digitalWrite(LED_G, LOW);
  } else {
    Serial.println("Access denied");
  }
  
  delay(1000);
}
