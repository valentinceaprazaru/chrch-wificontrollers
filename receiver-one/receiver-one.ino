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
int relay = 21;

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

int releu = 0;




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

  servo1.attach(servoPin);
  servo2.attach(servoFocus);
  //servo1.write(100);
  delay(100);
  myStepper.setSpeed(600);
  myStepper2.setSpeed(600);
  pinMode(relay, OUTPUT);

  pinMode(LimitaStanga, INPUT);
  pinMode(LimitaDreapta, INPUT);
  pinMode(LimitaSus, INPUT);
  pinMode(LimitaJos, INPUT);


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

  if (myData.y == 1)

  { if (releu == 0) {
      digitalWrite(relay, LOW);
      Serial.println(" Releu ON ");
      releu = 1;
    }

    //  if (myData.x == 1)  { myStepper2.step(-stepsPerRevolution); delay(1); Serial.println(" LEFT ");   }
    //  if (myData.x == 2)  { myStepper.step(stepsPerRevolution); delay(1); Serial.println(" DOWN ");   }
    //  if (myData.x == 3)  { myStepper2.step(stepsPerRevolution); delay(1); Serial.println(" RIGHT ");   }
    //  if (myData.x == 4)  { myStepper.step(-stepsPerRevolution); delay(1); Serial.println(" UP ");   }

    //if (digitalRead(LimitaStanga) == LOW) { Serial.println(" LimitaStanga ");   }
    //if (digitalRead(LimitaDreapta) == HIGH) { Serial.println(" LimitaDreapta ");   }
    //if (digitalRead(LimitaJos) == HIGH) { Serial.println(" LimitaJos ");   }
    //if (digitalRead(LimitaSus) == LOW) { Serial.println(" LimitaSus ");   }

    if ((myData.x == 1) && (digitalRead(LimitaStanga) == HIGH)) {
      myStepper2.step(-stepsPerRevolution);
      delay(1);
      Serial.println(" LEFT ");
    }
    if ((myData.x == 2) && (digitalRead(LimitaJos) == LOW)) {
      myStepper.step(stepsPerRevolution);
      delay(1);
      Serial.println(" DOWN ");
    }
    if ((myData.x == 3) && (digitalRead(LimitaDreapta) == LOW)) {
      myStepper2.step(stepsPerRevolution);
      delay(1);
      Serial.println(" RIGHT ");
    }
    if ((myData.x == 4) && (digitalRead(LimitaSus) == HIGH)) {
      myStepper.step(-stepsPerRevolution);
      delay(1);
      Serial.println(" UP ");
    }

    if (myData.x == 5) {
      servo2.write(78);
      delay(100);
      Serial.println(" FOCUS ");
      focushold = 1;
    }
    if ((myData.x == 15) && ( focushold == 1 )) {
      servo2.write(70);
      delay(100);
      Serial.println(" Remove FOCUS ");
      focushold = 0;
    }



    //FAST ZOOM IN / tasta 9

    if ((myData.x == 9) && ( plushold == 0 )) {
      {

        servo1.write(101); delay(20);
        servo1.write(103); delay(20);
        servo1.write(105); delay(20);
        servo1.write(107); delay(20);
        servo1.write(109); delay(20);
        servo1.write(111); delay(20);
        servo1.write(113); delay(20);
        servo1.write(115); delay(20);
        servo1.write(117); delay(20);
        servo1.write(119); delay(20);
        servo1.write(121); delay(20);
        servo1.write(123); delay(20);
        servo1.write(125);  servoPosition = 125;
      }  Serial.println(" FAST ZOOM IN "); plushold = 1;
    }

    if ((myData.x == 19) && ( plushold == 1 ))

    {
      servo1.write(124); delay(20);
      servo1.write(122); delay(20);
      servo1.write(120); delay(20);
      servo1.write(118); delay(20);
      servo1.write(116); delay(20);
      servo1.write(114); delay(20);
      servo1.write(112); delay(20);
      servo1.write(110); delay(20);
      servo1.write(108); delay(20);
      servo1.write(106); delay(20);
      servo1.write(104); delay(20);
      servo1.write(102); delay(20);
      servo1.write(100); servoPosition = 100;
      Serial.println(" Remove FAST ZOOM IN "); plushold = 0;
    }


    //SLOW ZOOM IN / tasta 8

    if ((myData.x == 8) && ( plushold == 0 )) {
      {

        servo1.write(101); delay(20);
        // servo1.write(102); delay(20);
        servo1.write(103); delay(20);
        //servo1.write(104); delay(20);
        servo1.write(105); delay(20);
        //servo1.write(106); delay(20);
        servo1.write(107); delay(20);
        //servo1.write(108); delay(20);
        servo1.write(109); delay(20);
        //servo1.write(110); delay(20);
        servo1.write(111); delay(20);
        //servo1.write(112); delay(20);
        servo1.write(113); delay(20);
        //servo1.write(114); delay(20);
        servo1.write(115); delay(20);
        servo1.write(117); delay(20);
        servo1.write(119); delay(20);
        servo1.write(121);  servoPosition = 121;
      }  Serial.println(" SLOW ZOOM IN "); plushold = 1;
    }

    if ((myData.x == 18) && ( plushold == 1 ))

    { servo1.write(120); delay(20);
      servo1.write(118); delay(20);
      servo1.write(116); delay(20);
      servo1.write(114); delay(20);
      //servo1.write(113); delay(20);
      servo1.write(112); delay(20);
      //servo1.write(111); delay(20);
      servo1.write(110); delay(20);
      //servo1.write(109); delay(20);
      servo1.write(108); delay(20);
      //servo1.write(107); delay(20);
      servo1.write(106); delay(20);
      //servo1.write(105); delay(20);
      servo1.write(104); delay(20);
      //servo1.write(103); delay(20);
      servo1.write(102); delay(20);
      //servo1.write(101); delay(20);
      servo1.write(100); servoPosition = 100;
      Serial.println(" Remove SLOW ZOOM IN "); plushold = 0;
    }



    //SLOW ZOOM OUT / tasta 7

    if ((myData.x == 7) && ( plushold == 0 )) {
      {

        servo1.write(99); delay(20);
        // servo1.write(102); delay(20);
        servo1.write(97); delay(20);
        //servo1.write(104); delay(20);
        servo1.write(95); delay(20);
        //servo1.write(106); delay(20);
        servo1.write(93); delay(20);
        //servo1.write(108); delay(20);
        servo1.write(91); delay(20);
        //servo1.write(110); delay(20);
        servo1.write(89); delay(20);
        //servo1.write(112); delay(20);
        servo1.write(87); delay(20);
        //servo1.write(114); delay(20);
        servo1.write(85);  servoPosition = 85;
      }  Serial.println(" SLOW ZOOM OUT "); plushold = 1;
    }




    if ((myData.x == 17) && ( plushold == 1 ))

    {
      servo1.write(86); delay(20);
      //servo1.write(113); delay(20);
      servo1.write(88); delay(20);
      //servo1.write(111); delay(20);
      servo1.write(90); delay(20);
      //servo1.write(109); delay(20);
      servo1.write(92); delay(20);
      //servo1.write(107); delay(20);
      servo1.write(94); delay(20);
      //servo1.write(105); delay(20);
      servo1.write(96); delay(20);
      //servo1.write(103); delay(20);
      servo1.write(98); delay(20);
      //servo1.write(101); delay(20);
      servo1.write(100); servoPosition = 100;
      Serial.println(" Remove SLOW ZOOM OUT "); plushold = 0;
    }



    //FAST ZOOM OUT / tasta 6

    if ((myData.x == 6) && ( plushold == 0 )) {
      {

        servo1.write(99); delay(20);
        servo1.write(97); delay(20);
        servo1.write(95); delay(20);
        servo1.write(93); delay(20);
        servo1.write(91); delay(20);
        servo1.write(89); delay(20);
        servo1.write(87); delay(20);
        servo1.write(85); delay(20);
        servo1.write(83); delay(20);
        servo1.write(81); delay(20);
        servo1.write(79); delay(20);
        servo1.write(77); delay(20);
        servo1.write(75);  servoPosition = 75;
      }  Serial.println(" FAST ZOOM OUT "); plushold = 1;
    }

    if ((myData.x == 16) && ( plushold == 1 ))

    {
      servo1.write(76); delay(20);
      servo1.write(78); delay(20);
      servo1.write(80); delay(20);
      servo1.write(82); delay(20);
      servo1.write(84); delay(20);
      servo1.write(86); delay(20);
      servo1.write(88); delay(20);
      servo1.write(90); delay(20);
      servo1.write(92); delay(20);
      servo1.write(94); delay(20);
      servo1.write(96); delay(20);
      servo1.write(98); delay(20);
      servo1.write(100); servoPosition = 100;
      Serial.println(" Remove FAST ZOOM OUT "); plushold = 0;
    }

  } else {
    digitalWrite(relay, HIGH);
    Serial.println(" Releu OFF ");
    releu = 0;
  }

}
