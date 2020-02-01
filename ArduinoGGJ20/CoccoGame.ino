byte greenSignal[8] = {1, 1, 1, 0, 0, 0, 0, 0}; //11100000
byte redSignal[8] = {1, 1, 1, 0, 0, 0, 1, 0};//11100010
byte whiteSignal[8] = {1, 1, 1, 0, 0, 1, 0, 0};//11100100
byte yellowSignal[8] = {1, 1, 1, 0, 1, 0, 0, 0};//11101000
byte blackSignal[8] = {1, 1, 1, 0, 1, 1, 0, 0};//11101100



boolean coccoGame()
{
  int cocchibenConnessi = 0;

  int counterCocco = 0;

  int red1Counter = 0;
  int green1Counter = 0;
  int white1Counter = 0;
  int yellow1Counter = 0;
  int black1Counter = 0;

  boolean redConnesso = false;
  boolean greenConnesso = false;
  boolean whiteConnesso = false;
  boolean yellowConnesso = false;
  boolean blackConnesso = false;

  while (cocchibenConnessi < 5)
  {
    int coccoIndex = counterCocco % 8;

    digitalWrite(redCoccoPinRP, redSignal[coccoIndex]);
    digitalWrite(yellowCoccoPinRP, yellowSignal[coccoIndex]);
    digitalWrite(greenCoccoPinRP, greenSignal[coccoIndex]);
    digitalWrite(whiteCoccoPinRP, whiteSignal[coccoIndex]);
    digitalWrite(blackCoccoPinRP, blackSignal[coccoIndex]);

    checkCocco(redCoccoPinRP, red1Counter, redConnesso, redCoccoPinRP, redCoccoPinGreenP, coccoIndex, cocchibenConnessi);
    checkCocco(yellowCoccoPinRP, yellow1Counter, yellowConnesso, yellowCoccoPinRP, yellowCoccoPinGreenP, coccoIndex, cocchibenConnessi);
    checkCocco(greenCoccoPinRP, green1Counter, greenConnesso, greenCoccoPinRP, greenCoccoPinGreenP, coccoIndex, cocchibenConnessi);
    checkCocco(whiteCoccoPinRP, white1Counter, whiteConnesso, whiteCoccoPinRP, whiteCoccoPinGreenP, coccoIndex, cocchibenConnessi);
    checkCocco(blackCoccoPinRP, black1Counter, blackConnesso, blackCoccoPinRP, blackCoccoPinGreenP, coccoIndex, cocchibenConnessi);

    counterCocco++;

    int i = 0;
    for (i = 0; i < cocchibenConnessi; i++)
    {
      digitalWrite(coccoLed1 + 1, HIGH);
    }

    for(i = cocchibenConnessi; i < 5; i++)
    {
      digitalWrite(coccoLed1 + 1, LOW);
    }
    delayMio(50);
  }

  return false;
}


void checkCocco(int colorSignal[], int &counter, boolean &coccoConnesso, int coccoPinRP, int coccoPinGreenP, int coccoIndex, int &cocchibenConnessi)
{
  digitalWrite(redCoccoPinRP, redSignal[coccoIndex]);
  int colorValueRead = digitalRead(coccoPinGreenP);

  if (counter < 3)
  {
    if (colorValueRead == 1)
      counter++;
    else
      counter = 0;
  }
  else
  {
    if (colorValueRead == colorSignal[coccoIndex])
    {
      if (coccoIndex == 7)
      {
        cocchibenConnessi++;
        coccoConnesso = true;
      }
    }
    else
      counter = 0;
    if (coccoConnesso)
      cocchibenConnessi--;
    coccoConnesso = false;
  }

}
