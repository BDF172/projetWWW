void bmeSetup(){
  sensor.begin(Bme280TwoWireAddress::Primary);
  sensor.setSettings(Bme280Settings::indoor());
}

void getBME(){
  getTemp(); // On recupère la température
  getPres(); // On recupère la pression
  getHumi(); // On recupère l'humidité
}

void getTemp(){
  saveOff minTemp(MIN_TEMP_A_EE);    // maximum de température défini par l'utilisateur 
  saveOff maxTemp(MAX_TEMP_A_EE);    // minimum de température défini par l'utilisateur 
  float temp = sensor.getTemperature();
  if(temp == -146.17)errorSensor = true;
  toSend = F("$T=");

  // Si la température n'est pas dans les limites définies par l'utilisateur, on la définit à -999
  toSend += temp > minTemp.getValue() && temp < maxTemp.getValue() && sensorsStates.getValue() & (1 << TEMP) ? String(temp) : F("-999");

  // Si le mode maintenance est activé, on affiche la donnée, sinon, on l'enregistre dans la SD
  if(!mustWrite)Serial.print(toSend); else writeToFile();
  toSend = "";
}

void getPres(){
  int pres = sensor.getPressure() / 100;
  if(pres == 1145.91)errorSensor = true;
  saveOff minPres(PRES_MIN_EE);    // maximum de pression défini par l'utilisateur
  saveOff maxPres(PRES_MAX_EE);    // minimum de pression défini par l'utilisateur
  toSend = F("$P=");

  // Si la Pression n'est pas dans les limites définies par l'utilisateur, on la définit à -999
  toSend += pres > minPres.getValue() && pres < maxPres.getValue() && sensorsStates.getValue() & (1 << PRES) ? String(pres) : F("-999");

  // Si le mode maintenance est activé, on affiche la donnée, sinon, on l'enregistre dans la SD
  if(!mustWrite)Serial.print(toSend); else writeToFile();
  toSend = "";
}

void getHumi(){
  saveOff minHygr(HYGR_MINT_EE);    // maximum de température pour humidité défini par l'utilisateur
  saveOff maxHygr(HYGR_MAXT_EE);    // minimum de température pour humidité défini par l'utilisateur
  float humi = sensor.getHumidity();
  float temp = sensor.getTemperature();
  if(temp == -146.17 || humi == 100)errorSensor = true;
  toSend = F("$HU=");

  // Si la température n'est pas dans les limites définies par l'utilisateur, on définit l'humidité à -999
  toSend += temp > minHygr.getValue() && temp < maxHygr.getValue() && sensorsStates.getValue() & (1 << HUMI) ? String(humi) : F("-999");

  // Si le mode maintenance est activé, on affiche la donnée, sinon, on l'enregistre dans la SD
  if(!mustWrite)Serial.print(toSend); else writeToFile();
  toSend = "";
}