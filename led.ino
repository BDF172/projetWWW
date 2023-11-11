void ledAlert(){
  while(true){
    if(ledBools & (1 << SHORTRED)){
      leds.setColorRGB(0,255,0,0);
      delay(1000);
    }
    if(ledBools & (1 << SHORTBLUE)){
      leds.setColorRGB(0,0,0,255);
      delay(1000);
    }
    if(ledBools & (1 << SHORTYEL)){
      leds.setColorRGB(0,255,255,0);
      delay(1000);
    }
    if(ledBools & (1 << LONGYEL)){
      leds.setColorRGB(0,255,255,0);
      delay(2000);
    }
    if(ledBools & (1 << SHORTGREEN)){
      leds.setColorRGB(0,0,255,0);
      delay(1000);
    }
    if(ledBools & (1 << LONGGREEN)){
      leds.setColorRGB(0,0,255,0);
      delay(2000);
    }
    if(ledBools & (1 << SHORTWHITE)){
      leds.setColorRGB(0,255,255,255);
      delay(1000);
    }
    if(ledBools & (1 << LONGWHITE)){
      leds.setColorRGB(0,255,255,255);
      delay(2000);
    }
  }
}