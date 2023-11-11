void standard(){
  mustWrite = true;                   // L'écriture est demandée vers la carte SD
  while(state & (1 << STANDA)){       // Répéter tant que le mode standard est actif
    if((millis() - lastSaved) > (waitingTime.getValue() * 60000))recupDonnees();
    if(state & (1 << MAINTE))maintenance();
    if(errorSensor) leds.setColorRGB(0, 199,36,177); else leds.setColorRGB(0, 0, 255, 0);
  }
}

void economic(){
  mustWrite = true;                   // L'écriture est demandée vers la carte SD
  while(state & (1 << ECONOM)){       // Répéter tant que le mode economie est actif
  if(errorSensor) leds.setColorRGB(0, 199,36,177); else leds.setColorRGB(0, 0, 0, 255);
    if((millis() - lastSaved) > (waitingTime.getValue() * 120000))recupDonnees();
    if(state & (1 << MAINTE))maintenance();
  }
}

void maintenance(){
  mustWrite = false;                             // L'écriture est arrêtée vers la carte SD
  while(state & (1 << MAINTE)){
    recupDonnees();                              // Répéter tant que le mode maintenance est actif
    if(errorSensor) leds.setColorRGB(0, 199,36,177); else leds.setColorRGB(0, 255, 128, 0);
  }
  sdInit();
}