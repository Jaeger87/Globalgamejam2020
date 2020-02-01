boolean nfcLoop()
{
  int errors = 0;
  while (1)
  {
    uint8_t success;
    uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };  // Buffer to store the returned UID
    uint8_t uidLength;                        // Length of the UID (4 or 7 bytes depending on ISO14443A card type)
    success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);

    if (success) {
      // Display some basic information about the card
      nfc.PrintHex(uid, uidLength);

      if (uidLength == 4)
      {
        // We probably have a Mifare Classic card ...
        uint32_t cardid = uid[0];
        cardid <<= 8;
        cardid |= uid[1];
        cardid <<= 8;
        cardid |= uid[2];
        cardid <<= 8;
        cardid |= uid[3];


        if (cardid == software6NFCCode)
          return true;
        else
          {
            errors++;
            secondi -= errors / 3;
            tone(buzzer, 200);
            delayMioNoBuzzer(1000);
            noTone(buzzer);
            delayMio(2000);
          }
        }
    }
    delayMio(500);
  }
}
