/*********
  BUN BUN BUN
  Complete project details at https://RandomNerdTutorials.com/esp-now-one-to-many-esp32-esp8266/

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*********/

#include <esp_now.h>
#include <WiFi.h>
#include <Servo_ESP32.h>
#include <Stepper.h>

int stepsPerRevolution = 10;
static const int servoPin = 16; // pin printed as G14
static const int servoFocus = 23;
int servoPosition = 100;

const int LimitaStanga = 2;
const int LimitaDreapta = 13; // PROBLEMA
const int LimitaSus = 4;
const int LimitaJos = 22;


Servo_ESP32 servo1;
Servo_ESP32 servo2;

Stepper myStepper(stepsPerRevolution, 32, 33, 14, 15);
Stepper myStepper2(stepsPerRevolution, 27, 25, 26, 19);

//Structure example to receive data
//Must match the sender structure


int focushold = 0;
int plushold = 0;

const int motor1Pin1 = 0;
const int motor1Pin2 = 4;


typedef struct test_struct {
  int x;
  int y;
} test_struct;

//Create a struct_message called myData
test_struct myData;

//callback function that will be executed when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.println("Bytes received: ");
  Serial.println(len);
  Serial.print("x: ");
  Serial.println(myData.x);
  Serial.print("y: ");
  Serial.println(myData.y);
  Serial.println();
}

void setup() {
  //Initialize Serial Monitor
  Serial.begin(115200);
  delay(1000);

  Serial.println("Successfully initialized");


  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);


  //Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  //Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_register_recv_cb(OnDataRecv);

}

void loop() {

  /**
     ONLY FOR DEVICE WITH NUMBER 2
  */
  if (myData.y == 2) {

    if ((myData.x == 1) && (digitalRead(LimitaStanga) == HIGH)) {

      digitalWrite(motor1Pin1, LOW);
      digitalWrite(motor1Pin2, HIGH);

      delay(10);
      Serial.println(" LEFT ");
    }
    if ((myData.x == 2) && (digitalRead(LimitaJos) == LOW)) {

      digitalWrite(motor1Pin1, HIGH);
      digitalWrite(motor1Pin2, LOW);

      delay(10);
      Serial.println(" DOWN ");
    }
    //    if ((myData.x == 3) && (digitalRead(LimitaDreapta) == LOW)) {
    //      myStepper2.step(stepsPerRevolution);
    //      delay(1);
    //      Serial.println(" RIGHT ");
    //    }
    //    if ((myData.x == 4) && (digitalRead(LimitaSus) == HIGH)) {
    //      myStepper.step(-stepsPerRevolution);
    //      delay(1);
    //      Serial.println(" UP ");
    //    }


  } // if (myData.y == 2)

}
