void lightData(){
  saveOff minLight(LUMIN_LOW_EE);     // maximum de température défini par l'utilisateur 
  saveOff maxLight(LUMIN_HIGH_EE);    // minimum de température défini par l'utilisateur 
  toSend = F("$L=");
  if(verifyLight()){
    float light = (analogRead(lightSensor)/7.77);
    toSend += light >= minLight.getValue() && light <= maxLight.getValue() && sensorsStates.getValue() & (1 << LIGHT) ? String(light) : F("-999");
  }
  else toSend += F("-999");

  // Si le mode maintenance est activé, on affiche la donnée, sinon, on l'enregistre dans la SD
  if(!mustWrite)Serial.print(toSend); else writeToFile();
}

bool verifyLight(){
  for(uint8_t i = 0; i<20; i++){
    float entree = analogRead(0);
    delay(1);
    entree -= analogRead(0);
    if(entree > 50 || entree < -50){
      errorSensor = true;
      return false;
    }
  }
  return true;
}