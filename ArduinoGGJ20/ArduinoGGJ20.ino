#include "Adafruit_Thermal.h"
#include "SoftwareSerial.h"
#include "LedControl.h"
#include <Servo.h>
#include <Adafruit_PN532.h>
#include <Wire.h>
#include <SPI.h>
#define PN532_IRQ   (2)
#define PN532_RESET (3) 
#define TX_PIN 8 // Arduino transmit  YELLOW WIRE  labeled RX on printer
#define RX_PIN 9 // Arduino receive   GREEN WIRE   labeled TX on printer
#define LEDSTRIPPIN 4

LedControl lc=LedControl(7,6,5,1);
SoftwareSerial mySerial(RX_PIN, TX_PIN); // Declare SoftwareSerial obj first
Adafruit_Thermal printer(&mySerial);     // Pass addr to printer constructor

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

Adafruit_PN532 nfc(PN532_IRQ, PN532_RESET);
Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, LEDSTRIPPIN, NEO_GRB + NEO_KHZ800);

const byte colorsIntensity = 190;
const byte whiteIntensity = 170;

const uint32_t RED = strip.Color(colorsIntensity, 0, 0);
const uint32_t GREEN = strip.Color(0, colorsIntensity, 0);
const uint32_t BLU = strip.Color(0, 0, colorsIntensity);
const uint32_t YELLOW = strip.Color(colorsIntensity, colorsIntensity, 0);
const uint32_t WHITE = strip.Color(whiteIntensity, whiteIntensity, whiteIntensity);
const uint32_t BLACK = strip.Color(0, 0, 0);

uint32_t current_color_led_strip = BLACK;


const int redButtonPinRP = 40;
const int yellowButtonPinRP = 41;
const int greenButtonPinRP = 42;
const int blueButtonPinRP = 43;
const int blackButtonPinRP = 44;

const int redButtonPinGreenP = 45;
const int yellowButtonPinGreenP = 46;
const int greenButtonPinGreenP = 47;
const int blueButtonPinGreenP = 48;
const int blackButtonPinGreenP = 49;

void setup() {
  // put your setup code here, to run once:
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

  mySerial.begin(9600); 
  printer.begin(); 
}

void loop() {
  // put your main code here, to run repeatedly:

}
