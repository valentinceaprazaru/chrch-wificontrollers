/*********
  BUN BUN BUN
  Complete project details at https://RandomNerdTutorials.com/esp-now-one-to-many-esp32-esp8266/

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*********/


// The default I2C address
//#define MPR121_I2CADDR_DEFAULT 0x5A           ///< default I2C address
//#define MPR121_TOUCH_THRESHOLD_DEFAULT    13  ///< default touch threshold value
//#define MPR121_RELEASE_THRESHOLD_DEFAULT  6   ///< default relese threshold value


#include <esp_now.h>
#include <WiFi.h>
#include <Wire.h>
#include "Adafruit_MPR121.h"
#include "Adafruit_DRV2605.h"
#include <Adafruit_NeoPixel.h>

//define NeoPixel Pin and Number of LEDs
#define PIN 17
#define NUM_LEDS 3
//create a NeoPixel strip
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);


Adafruit_MPR121 cap1 = Adafruit_MPR121();

uint16_t lasttouched1 = 0;
uint16_t currtouched1 = 0;

int mod = 0;

int igrec = 1;
int verificareigrec = 0;

Adafruit_DRV2605 drv;

// REPLACE WITH YOUR ESP RECEIVER'S MAC ADDRESS
uint8_t broadcastAddress1[] = {0xF0, 0x08, 0xD1, 0xD4, 0xDE, 0x78};
uint8_t broadcastAddress2[] = {0x7C, 0x9E, 0xBD, 0x06, 0xA6, 0xD0}; // 7C:9E:BD:06:A6:D0
////uint8_t broadcastAddress3[] = {0xFF, , , , , };

typedef struct test_struct {
  int x;
  int y;
} test_struct;

test_struct test;

// callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  char macStr[18];
  Serial.print("Packet to: ");
  // Copies the sender mac address to a string
  snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
           mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
  Serial.print(macStr);
  Serial.print(" send status:\t");
  // Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void setup() {


  Serial.begin(115200);

  strip.begin();
  strip.show();

  if (!cap1.begin(0x5D)) {
    Serial.println("MPR121 A not found, check wiring?");
    while (1);
  }
  Serial.println("MPR121 A found!");

  drv.begin();

  drv.selectLibrary(1);

  // I2C trigger by sending 'go' command
  // default, internal trigger when sending GO command
  drv.setMode(DRV2605_MODE_INTTRIG);


  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_register_send_cb(OnDataSent);

  // register peer
  esp_now_peer_info_t peerInfo;
  peerInfo.channel = 0;
  peerInfo.encrypt = false;
  // register first peer
  memcpy(peerInfo.peer_addr, broadcastAddress1, 6);
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }
  //   register second peer
  memcpy(peerInfo.peer_addr, broadcastAddress2, 6);
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }
  /// register third peer
  // memcpy(peerInfo.peer_addr, broadcastAddress3, 6);
  // if (esp_now_add_peer(&peerInfo) != ESP_OK){
  //  Serial.println("Failed to add peer");
  //  return;
  //}


  for ( int i = 0; i <= 2; i++ ) {
    strip.setPixelColor(i, 60, 100, 0);
  } strip.show();

}


uint8_t effect = 1;


void loop() {
  if (igrec == 4) {
    igrec = 0;
  }

  //if ((igrec == 1) && (verificareigrec == 0)) { strip.setPixelColor(0, 105, 0, 2); strip.show(); verificareigrec = 1;
  //test.y = igrec; esp_err_t result = esp_now_send(0, (uint8_t *) &test, sizeof(test_struct)); }

  // MPR121 A
  currtouched1 = cap1.touched();

  for (uint8_t i = 0; i < 12; i++) {
    // it if *is* touched and *wasnt* touched before, alert!
    if ((currtouched1 & _BV(i)) && !(lasttouched1 & _BV(i)) ) {
      Serial.print(i); Serial.println(" A touched");


      if (i == 1)  {
        drv.setWaveform(0, 25);
        drv.setWaveform(1, 0);
        drv.go();
        test.x = 1;
      }
      if (i == 2)  {
        drv.setWaveform(0, 25);
        drv.setWaveform(1, 0);
        drv.go();
        test.x = 2;
      }
      if (i == 3)  {
        drv.setWaveform(0, 25);
        drv.setWaveform(1, 0);
        drv.go();
        test.x = 3;
      }
      if (i == 4)  {
        drv.setWaveform(0, 25);
        drv.setWaveform(1, 0);
        drv.go();
        test.x = 4;
      }
      if (i == 5)  {
        drv.setWaveform(0, 25);
        drv.setWaveform(1, 0);
        drv.go();
        test.x = 5;
      }
      if (i == 6)  {
        drv.setWaveform(0, 25);
        drv.setWaveform(1, 0);
        drv.go();
        test.x = 6;
      }
      if (i == 7)  {
        drv.setWaveform(0, 25);
        drv.setWaveform(1, 0);
        drv.go();
        test.x = 7;
      }
      if (i == 8)  {
        drv.setWaveform(0, 25);
        drv.setWaveform(1, 0);
        drv.go();
        test.x = 8;
      }
      if (i == 9)  {
        drv.setWaveform(0, 25);
        drv.setWaveform(1, 0);
        drv.go();
        test.x = 9;
      }
      if (i == 10)  {
        if ((igrec == 1) && (verificareigrec == 0)) {
          for ( int i = 0; i <= 2; i++ ) {
            strip.setPixelColor(i, 0, 0, 0);
          }
          strip.show();
          strip.setPixelColor(0, 105, 0, 2); strip.show(); verificareigrec = 1;
          test.y = igrec; esp_err_t result = esp_now_send(0, (uint8_t *) &test, sizeof(test_struct));
        }
        else {
          for ( int i = 0; i <= 2; i++ ) {
            strip.setPixelColor(i, 0, 0, 0);
          } strip.show(); igrec++; test.y = igrec;  if (igrec != 4) {
            mod++; strip.setPixelColor(mod, 105, 0, 2); strip.show();
            if ( mod >= 2 ) {
              mod = -1;
            }
          }
          drv.setWaveform(0, 25); drv.setWaveform(1, 0); drv.go(); test.x = 10;
        }
      }

      esp_err_t result = esp_now_send(0, (uint8_t *) &test, sizeof(test_struct));

    }

    // if it *was* touched and now *isnt*, alert!
    if (!(currtouched1 & _BV(i)) && (lasttouched1 & _BV(i)) ) {
      Serial.print(i); Serial.println(" A released");

      if (i == 1)  {
        drv.setWaveform(0, 25);
        drv.setWaveform(1, 0);
        drv.go();
        test.x = 11;
      }
      if (i == 2)  {
        drv.setWaveform(0, 25);
        drv.setWaveform(1, 0);
        drv.go();
        test.x = 12;
      }
      if (i == 3)  {
        drv.setWaveform(0, 25);
        drv.setWaveform(1, 0);
        drv.go();
        test.x = 13;
      }
      if (i == 4)  {
        drv.setWaveform(0, 25);
        drv.setWaveform(1, 0);
        drv.go();
        test.x = 14;
      }
      if (i == 5)  {
        drv.setWaveform(0, 25);
        drv.setWaveform(1, 0);
        drv.go();
        test.x = 15;
      }
      if (i == 6)  {
        drv.setWaveform(0, 25);
        drv.setWaveform(1, 0);
        drv.go();
        test.x = 16;
      }
      if (i == 7)  {
        drv.setWaveform(0, 25);
        drv.setWaveform(1, 0);
        drv.go();
        test.x = 17;
      }
      if (i == 8)  {
        drv.setWaveform(0, 25);
        drv.setWaveform(1, 0);
        drv.go();
        test.x = 18;
      }
      if (i == 9)  {
        drv.setWaveform(0, 25);
        drv.setWaveform(1, 0);
        drv.go();
        test.x = 19;
      }
      if (i == 10)  {
        drv.setWaveform(0, 25);
        drv.setWaveform(1, 0);
        drv.go();
        test.x = 20;
      }

      esp_err_t result = esp_now_send(0, (uint8_t *) &test, sizeof(test_struct));


    }
  }

  // reset our state
  lasttouched1 = currtouched1;

  // MPR121 A
  currtouched1 = cap1.touched();



  //  test.y = 0;

  //  esp_err_t result = esp_now_send(0, (uint8_t *) &test, sizeof(test_struct));

  //  if (result == ESP_OK) {
  //    Serial.println("Sent with success");
  //  }
  //  else {
  //   Serial.println("Error sending the data");
  //  }
  delay(100);





  // comment out this line for detailed data from the sensor!
  return;



  // debugging info, what
  Serial.print("\t\t\t\t\t\t\t\t\t\t\t\t\t 0x"); Serial.println(cap1.touched(), HEX);
  Serial.print("Filt: ");
  for (uint8_t i = 0; i < 12; i++) {
    Serial.print(cap1.filteredData(i)); Serial.print("\t");
  }
  Serial.println();
  Serial.print("Base: ");
  for (uint8_t i = 0; i < 12; i++) {
    Serial.print(cap1.baselineData(i)); Serial.print("\t");
  }
  Serial.println();



}
