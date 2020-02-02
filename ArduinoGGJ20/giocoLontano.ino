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
        setColorStrip(BLACK);
        check = checkTelecomando(teleBPin, 4, teleDPin);
        if (check == OK)
          gameStatus = DEBUG;

        break;
      case DEBUG:
        setColorStrip(RED);
        check = checkTelecomando(redButtonPinRP, 5, blackButtonPinRP);
        if (check == OK)
          gameStatus = PREMIB;
        else
          gameStatus = START;
        break;
      case PREMIB:
        setColorStrip(CYAN);
        check = checkTelecomando(teleBPin, 4, teleBPin);
        if (check == OK)
          gameStatus = NERO;
        else
          gameStatus = START;
        break;

      case NERO:
        setColorStrip(MAGENTA);
        check = checkTelecomando(redButtonPinRP, 5, blackButtonPinRP);
        if (check == OK)
          gameStatus = GIALLO;
        else
          gameStatus = START;
        break;
      case GIALLO:
        delayMio(1800);
        check = checkTelecomando(redButtonPinRP, 5, yellowButtonPinRP);
        if (check == OK)
          gameStatus = STAMPA;
        else
          gameStatus = START;
        break;
      case STAMPA:
        printer.println(F("Di all'operatore verde di premere i suoi tasti verdi\n\n"));
        delayMio(500);
        gameStatus = VERDEPREMEIVERDI;
        break;
      case VERDEPREMEIVERDI:
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
    if (valueRead == HIGH)
      if (i == quelloCheVoglio)
        stato = OK;
      else
        return ERRORE;
  }

  return stato;

}
