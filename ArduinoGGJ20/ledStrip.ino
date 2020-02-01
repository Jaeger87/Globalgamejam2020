void setColorStrip(uint32_t color)
{
  for (int i = 0; i < strip.numPixels(); i++)
    strip.setPixelColor(i, color);
  strip.show();
}
