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

LedControl lc = LedControl(7, 6, 5, 1);
SoftwareSerial mySerial(RX_PIN, TX_PIN); // Declare SoftwareSerial obj first
Adafruit_Thermal printer(&mySerial);     // Pass addr to printer constructor

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

Adafruit_PN532 nfc(PN532_IRQ, PN532_RESET);
Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, LEDSTRIPPIN, NEO_GRB + NEO_KHZ800);

const byte delayStandard = 50;

const byte colorsIntensity = 190;
const byte whiteIntensity = 170;

const uint32_t RED = strip.Color(colorsIntensity, 0, 0);
const uint32_t GREEN = strip.Color(0, colorsIntensity, 0);
const uint32_t BLU = strip.Color(0, 0, colorsIntensity);
const uint32_t YELLOW = strip.Color(colorsIntensity, colorsIntensity, 0);
const uint32_t WHITE = strip.Color(whiteIntensity, whiteIntensity, whiteIntensity);
const uint32_t BLACK = strip.Color(0, 0, 0);

uint32_t current_color_led_strip = BLACK;


const int buttonRedOperator = 27;
const int buttonGreenOperator = 28;

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

const byte buzzer = 19;
byte minuti = 0;
byte secondi = 0;
byte decimiSecondi = 0;
byte decimiDaTogliere = 1;

bool timeIsOver = false;

const int shortDelayPrinter = 800;
const int longDelayPrinter = 1500;
const int veryLongDelayPrinter = 4500;

bool provaNFC = false;
bool provaCoccodrilli = false;
bool provaLontano = false;

long oldTime = millis();

//Dichiarazione dei capitoli della storia (stati in cui si può trovare il gioco)
enum  computerStatus {
  SETUP, INIT, TROVAIL6, COCCODRILLI, ISTRUZIONILONTANE, YOUDIE, YOUWIN
};
computerStatus chapter = INIT;

void setup() {
  // put your setup code here, to run once:
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

  nfc.begin();
  uint32_t versiondata = nfc.getFirmwareVersion();
  if (! versiondata) {
    Serial.print("Didn't find PN53x board");
    while (1); // halt
  }
  // Got ok data, print it out!
  Serial.print("Found chip PN5"); Serial.println((versiondata >> 24) & 0xFF, HEX);
  Serial.print("Firmware ver. "); Serial.print((versiondata >> 16) & 0xFF, DEC);
  Serial.print('.'); Serial.println((versiondata >> 8) & 0xFF, DEC);

  // configure board to read RFID tags
  nfc.SAMConfig();


  mySerial.begin(9600);
  printer.begin();

  pinMode(buttonRedOperator, INPUT);
  pinMode(buttonGreenOperator, INPUT);
  pinMode(redButtonPinRP, INPUT);
  pinMode(yellowButtonPinRP, INPUT);
  pinMode(greenButtonPinRP, INPUT);
  pinMode(blueButtonPinRP, INPUT);
  pinMode(blackButtonPinRP, INPUT);
  pinMode(redButtonPinGreenP, INPUT);
  pinMode(yellowButtonPinGreenP, INPUT);
  pinMode(greenButtonPinGreenP, INPUT);
  pinMode(blueButtonPinGreenP, INPUT);
  pinMode(blackButtonPinGreenP, INPUT);

  initializeGame();

}

void loop() {
  // put your main code here, to run repeatedly:
  switch (chapter)
  {
    case INIT:
      {
        printer.println(F("Per favore\nriparatemi\noperatori\nQuando siete pronti premete\nI vostri tasti operatore\n\n"));
        delayMio(shortDelayPrinter);
        initialAnimation();

        
        oldTime = millis();
        scriviTempo(minuti, secondi, decimiSecondi);
        break;
      }

    case SETUP:
      {
        initializeGame();
        delay(2000);
        break;
      }

    case TROVAIL6:
      {
        printer.println(F("Operatori, andate nel reparto\nsoftware, recuperate e\ninstallate il software 6.\nOgni tre errori il tempo\ncalerà di 30 secondi\n\n"));
        delayMio(shortDelayPrinter);

        uint8_t success;
        uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };  // Buffer to store the returned UID
        uint8_t uidLength;                        // Length of the UID (4 or 7 bytes depending on ISO14443A card type)

        // Wait for an ISO14443A type cards (Mifare, etc.).  When one is found
        // 'uid' will be populated with the UID, and uidLength will indicate
        // if the uid is 4 bytes (Mifare Classic) or 7 bytes (Mifare Ultralight)

        bool software6Installed = false;

        while (!software6Installed)
        {
          success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);

        }

        break;
      }
    default:
      {
        break;
      }

  }
  aggiornaScriviAspettaTempo();

}

void delayMio(int milliSeconds)
{
  int stops = milliSeconds / delayStandard;

  for (int i = 0; i < stops; i++)
    aggiornaScriviAspettaTempo();
}

void aggiornaScriviAspettaTempo()
{
  aggiornaTempo();
  scriviTempo(minuti, secondi, decimiSecondi);
  delay(delayStandard);
}

void initializeGame()
{
  lc.shutdown(0, false);
  // Enable display
  lc.setIntensity(0, 10);
  // Set brightness level (0 is min, 15 is max)
  lc.clearDisplay(0);
  // Clear display register

  minuti = 2;
  secondi = 0;
  decimiSecondi = 0;
  timeIsOver = false;

  provaNFC = false;
  provaCoccodrilli = false;
  provaLontano = false;
}
