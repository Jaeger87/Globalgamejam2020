void scegliProva()
{

  if (provaNFC && provaCoccodrilli && provaLontano)
  {
    chapter = YOUWIN;
    return;
  }

  while (1)
  {
    long randNumber = random(3);

    switch (randNumber)
    {
      case 0:
        {
          if (!provaNFC)
          {
            chapter = TROVAIL6;
            return;
          }
          break;
        }
      case 1:
        {
          if (!provaCoccodrilli)
          {
            chapter = COCCODRILLI;
            return;
          }
          break;
        }
      case 2:
        {
          if (!provaLontano)
          {
            chapter = ISTRUZIONILONTANE;
            return;
          }
          break;
        }
    }
  }
}
