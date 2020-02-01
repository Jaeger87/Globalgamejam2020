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
  while(cocchibenConnessi < 5)
  {
    int coccoIndex = counterCocco % 8;

    digitalWrite(redCoccoPinRP, redSignal[coccoIndex]);
    digitalWrite(yellowCoccoPinRP, yellowSignal[coccoIndex]);
    digitalWrite(greenCoccoPinRP, greenSignal[coccoIndex]);
    digitalWrite(whiteCoccoPinRP, whiteSignal[coccoIndex]);
    digitalWrite(blackCoccoPinRP, blackSignal[coccoIndex]);
    counterCocco++;
    delayMio(50);
  }
  
  return false;
}
