//A = 2
//B = 0
//C = 3
//D = 1




boolean giocoLontano()
{
  statiLontano gameStatus = START;

  switch (gameStatus)
  {
    case START:

      break;
    case DEBUG:
      break;
    case PREMIB:
      break;
    case NERO:
      break;
    case GIALLO:
      break;
    case STAMPA:
      break;
    case VERDEPREMEIVERDI:
      break;
  }

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
