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
    switch (gameStatus)
    {
      case START:
        setColorStrip(BLACK);
        statiBOTTONE check = checkTelecomando(teleBPin, 4, teleDPin);
        if (check == OK)
          gameStatus = DEBUG;
          
        break;
      case DEBUG:
        setColorStrip(RED);
        break;
      case PREMIB:
        setColorStrip(CYAN);
        break;
      case NERO:
        setColorStrip(MAGENTA);
        break;
      case GIALLO:

        break;
      case STAMPA:
        break;
      case VERDEPREMEIVERDI:

        isOver = true;
        break;
    }
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
