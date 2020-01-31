#include "Adafruit_Thermal.h"
#include "SoftwareSerial.h"
#include <Servo.h>
#define TX_PIN 4 // Arduino transmit  YELLOW WIRE  labeled RX on printer
#define RX_PIN 3 // Arduino receive   GREEN WIRE   labeled TX on printer
SoftwareSerial mySerial(RX_PIN, TX_PIN); // Declare SoftwareSerial obj first
Adafruit_Thermal printer(&mySerial);     // Pass addr to printer constructor



void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
