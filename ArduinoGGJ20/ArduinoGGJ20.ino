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

  initializeGame();

}

void loop() {
  // put your main code here, to run repeatedly:
  switch (chapter)
  {
    case INIT:
      {

        bool startGame = false;
        int animationCounter = 0;
        while(!startGame)
        {
          
          delay(500);
        }
        break;
      }

    case SETUP:
      {
        initializeGame();
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

        while(!software6Installed)
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

void aggiornaTempo()
{
  byte vecchiMinuti = minuti;
  long currentTime = millis();
  if (oldTime - currentTime > 100)
  {
    decimiSecondi -= 1;
    if (decimiSecondi > 10)//UNDERFLOW
    {
      decimiSecondi = 9;
      secondi--;
      tone(buzzer, 900);
    }
    if (secondi > 61)
    {
      secondi = 59;
      minuti--;
    }

    if (vecchiMinuti < minuti) //UNDERFLOW
    {
      minuti = 0;
      secondi = 0;
      decimiSecondi = 0;
    }
  }
  oldTime = currentTime;
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
  oldTime = millis();
}
