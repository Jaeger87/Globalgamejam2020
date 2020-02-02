//A = 2
//B = 0
//C = 3
//D = 1


boolean giocoLontano()
{
  statiLontano gameStatus = START;
  bool isOver = false;

  while (!isOver)
  {
    statiBOTTONE check = ERRORE;
    switch (gameStatus)
    {
      case START:
        //Serial.println("START");
        setColorStrip(BLACK);

        check = checkTelecomando(50, 4, teleDPin);
        if (check == OK)
          gameStatus = DEBUG;

        break;
      case DEBUG:
        Serial.println("DEBUG");
        setColorStrip(RED);
        check = checkTelecomando(redButtonPinRP, 5, blackButtonPinRP);
        if (check == OK)
          gameStatus = PREMIB;
        else if (check == ERRORE)
          gameStatus = START;
        break;
      case PREMIB:
        Serial.println("PREMIB");
        setColorStrip(CYAN);
        check = checkTelecomando(50, 4, teleBPin);
        if (check == OK)
          gameStatus = NERO;
        else if (check == ERRORE)
          gameStatus = START;
        break;

      case NERO:
        Serial.println("nero");
        setColorStrip(MAGENTA);
        check = checkTelecomando(redButtonPinRP, 5, blackButtonPinRP);
        if (check == OK)
          gameStatus = GIALLO;
        else if (check == ERRORE)
          gameStatus = START;
        break;
      case GIALLO:
        Serial.println("giallo");
        delayMio(1800);
        check = checkTelecomando(redButtonPinRP, 5, yellowButtonPinRP);
        if (check == OK)
          gameStatus = STAMPA;
        else if (check == ERRORE)
          gameStatus = START;
        break;
      case STAMPA:
        Serial.println("stampa");
        printer.println(F("Di all'operatore verde di premere i suoi tasti verdi\n\n"));
        delayMio(500);
        gameStatus = VERDEPREMEIVERDI;
        break;
      case VERDEPREMEIVERDI:
        Serial.println("VERDEPREMEIVERDI");
        int buttonRedOperatorState = digitalRead(greenButtonPinGreenP);
        int buttonGreenOperatorState = digitalRead(buttonGreenOperator);
        if (buttonRedOperatorState == HIGH && buttonGreenOperatorState == HIGH)
          isOver = true;
        break;
    }

    delayMio(50);

    if (gameOver)
      return false;
  }
  setColorStrip(BLACK);
  return true;
}

enum statiBOTTONE checkTelecomando(int startLeggere, int lunghezza, int quelloCheVoglio)
{
  statiBOTTONE stato = NIENTE;
  for (int i = startLeggere; i < startLeggere + lunghezza; i++)
  {
    int valueRead = digitalRead(i);
    //Serial.println(i);
    //Serial.println(valueRead);
    if (valueRead == HIGH)
    {
      
      if (i == quelloCheVoglio)
        stato = OK;
      else
        return ERRORE;
    }
  }

  return stato;
}
