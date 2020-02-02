void writePlease()
{
  lc.clearDisplay(0);
  lc.setDigit(0, 6, 18, false); //P
  lc.setDigit(0, 5, 20, false); //l
  lc.setDigit(0, 4, 14, false); //e
  lc.setDigit(0, 3, 10, false); //a
  lc.setDigit(0, 2, 5, false); //s
  lc.setDigit(0, 1, 14, false); //e
}

void writeRepair()
{
  lc.clearDisplay(0);
  lc.setDigit(0, 6, 25, false); //r
  lc.setDigit(0, 5, 14, false); //e
  lc.setDigit(0, 4, 18, false); //p
  lc.setDigit(0, 3, 10, false); //a
  lc.setDigit(0, 2, 19, false); //i
  lc.setDigit(0, 1, 25, false); //r
}

void writeMe()
{
  lc.clearDisplay(0);
  lc.setDigit(0, 5, 21, false); //M1
  lc.setDigit(0, 4, 22, false); //M2
  lc.setDigit(0, 3, 14, false); //e
}

void scriviTempo(byte minuti, byte secondi, byte decimiSecondi)
{
  lc.clearDisplay(0);
  if (minuti >= 100)
  {
    byte centinaia = minuti / 100;
    lc.setDigit(0, 7, centinaia, false);
    minuti -= centinaia * 100;
  }
  lc.setDigit(0, 6, minuti / 10, false);
  lc.setDigit(0, 5, minuti % 10, true);
  lc.setDigit(0, 3, secondi / 10, false);
  lc.setDigit(0, 2, secondi % 10, true);
  lc.setDigit(0, 0, decimiSecondi, false);
}


void initialAnimation()
{
  bool startGame = false;
  int animationCounter = 0;
  bool buttonRedOperatorState = LOW;
  bool buttonGreenOperatorState = LOW;
  while (!startGame)
  {
    int whichAnimation = animationCounter % 9;

    buttonRedOperatorState = digitalRead(buttonRedOperator);
    buttonGreenOperatorState = digitalRead(buttonGreenOperator);


    if (buttonRedOperatorState == HIGH && buttonGreenOperatorState == HIGH)
      startGame = true;

    switch (whichAnimation)
    {
      case 0:
        {
          writePlease();
          setColorStrip(RED);
          break;
        }
      case 1:
        {
          writePlease();
          setColorStrip(RED);
          break;
        }
      case 2:
        {
          lc.clearDisplay(0);
          setColorStrip(BLACK);
          break;
        }
      case 3:
        {
          writeRepair();
          setColorStrip(RED);
          break;
        }
      case 4:
        {
          writeRepair();
          setColorStrip(RED);
          break;
        }
      case 5:
        {
          lc.clearDisplay(0);
          setColorStrip(BLACK);
          break;
        }
      case 6:
        {
          writeMe();
          setColorStrip(RED);
          break;
        }
      case 7:
        {
          writeMe();
          setColorStrip(RED);
          break;
        }
      case 8:
        {
          lc.clearDisplay(0);
          setColorStrip(BLACK);
          break;
        }
    }
    animationCounter++;
    delay(500);
  }
}



void aggiornaTempo()
{
  noTone(buzzer);
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

    if (minuti == 1 && secondi == randomLieScontrini && !lieScontrini)
    {
      incoraggiamento = true;
      Serial2.println("id:2:");
    }

    if (minuti == 0 && secondi == 45 && !incoraggiamento)
    {
      incoraggiamento = true;
      Serial2.println("id:4:");
    }
    if (vecchiMinuti < minuti) //UNDERFLOW
    {
      minuti = 0;
      secondi = 0;
      decimiSecondi = 0;
      gameOver = true;
    }
  }
  oldTime = currentTime;
}

void aggiornaTempoNoBuzzer()
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
      gameOver = true;
      Serial.println("GameOver");
    }
  }
  oldTime = currentTime;
}
