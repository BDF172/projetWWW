#define CONFIGTIME 1800000

void configReset() {
  // Ensemble des valeurs stockées dans l'eeprom qui ne sont pas actuellement déclarées
  saveOff minLight(LUMIN_LOW_EE);
  saveOff maxLight(LUMIN_HIGH_EE);
  saveOff minTemp(MIN_TEMP_A_EE);
  saveOff maxTemp(MAX_TEMP_A_EE);
  saveOff minHygr(HYGR_MINT_EE);
  saveOff maxHygr(HYGR_MAXT_EE);
  saveOff minPres(PRES_MIN_EE);
  saveOff maxPres(PRES_MAX_EE);

  // On réactive tous les capteurs
  sensorsStates.changeValue((1 << LIGHT) | (1 << PRES) | (1 << TEMP) | (1 << HUMI) | (1 << GPS));
  
  // On réinitialise les valeurs à leur état d'origine 
  minLight.changeValue(0);
  maxLight.changeValue(100);
  minTemp.changeValue(-40);
  maxTemp.changeValue(85);
  minHygr.changeValue(-40);
  maxHygr.changeValue(85);
  minPres.changeValue(300);
  maxPres.changeValue(1100);
  maxLines.changeValue(8);
  waitingTime.changeValue(10);

  Serial.println("RESET !");
}

bool intPossible(const String& str) {
  // Si la chaine est constitué de chiffres, on renvoie true, sinon false
  for (size_t i = 0; i < str.length(); i++) if (!isdigit(str.charAt(i))) return false;
  return true;
}

void configuration(){
  // On attend d'être connecté en série
  while(!Serial);

  // Ensemble des valeurs stockées dans l'eeprom qui ne sont pas actuellement déclarées
  saveOff minLight(LUMIN_LOW_EE);
  saveOff maxLight(LUMIN_HIGH_EE);
  saveOff minTemp(MIN_TEMP_A_EE);
  saveOff maxTemp(MAX_TEMP_A_EE);
  saveOff minHygr(HYGR_MINT_EE);
  saveOff maxHygr(HYGR_MAXT_EE);
  saveOff minPres(PRES_MIN_EE);
  saveOff maxPres(PRES_MAX_EE);

  // On active la LED dans la couleur du mode maintenance
  leds.setColorRGB(0, 255, 255, 0);

  // On initialise le moment où la dernière activité a été recensée
  unsigned long configBegin = millis();

  // On vide le tampon Serial
  while (Serial.available()) {
    Serial.read();
  }

  // On regarde la commande entrée par l'utilisateur pour voir ce qu'il a demandé
  while ((millis() - configBegin) < CONFIGTIME) {
    if (Serial.available()) {
      configBegin = millis();
      String userEntry = Serial.readStringUntil('\r');
      while(Serial.available())Serial.read();

      int eqIndex = userEntry.indexOf('=');

      // Si l'utilisateur n'a pas entré de "="
      if(eqIndex == -1){
        if(userEntry.equals(F("VERSION"))){
          Serial.println(F("1"));
        }
        else if(userEntry.equals(F("RESET"))){
          configReset();
        }
        else if(userEntry.equals(F("EXIT"))){
          break;
        }
        else {
        Serial.println("?");
        }
        continue;
      }

      if (eqIndex == 0 || eqIndex == 31) {
        continue;
      }

      String command = userEntry.substring(0, eqIndex);     // Commande avant le "="
      String number = userEntry.substring(eqIndex + 1);     // Contenu de la commande (après le =)
      if(!intPossible(number)){
        continue;
      }
      int content = number.toInt();

      if (command==F("LUMIN")) {
        if (content == 0 || content == 1)sensorsStates.changeValue(sensorsStates.getValue() & ~((1-content) << LIGHT));
        else{
          continue;
        }
      }
      else if (command==F("LUMIN_LOW")) {
        if (content >= 0 && content <= 100)minLight.changeValue(content);
        else{
          continue;
        }
      } 
      else if (command==F("LUMIN_MAX")) {
        if (content >= 0 && content <= 100)maxLight.changeValue(content);
        else{
          continue;
        }
      }
      else if(command == F("TEMP_AIR")){
        if(content == 1 || content == 0)sensorsStates.changeValue(sensorsStates.getValue() & ~((1-content) << TEMP));
        else{
          continue;
        }
      }
      else if(command == F("MIN_TEMP_AIR")){
        if(content > -40 || content < 85)minTemp.changeValue(content);
        else{
          continue;
        }
      }
      else if(command == F("MAX_TEMP_AIR")){
        if(content > -40 || content < 85)maxTemp.changeValue(content);
        else{
          continue;
        }
      }
      else if(command == F("HYGR")){
        if(content == 1 || content == 0)sensorsStates.changeValue(sensorsStates.getValue() & ~((1-content) << HUMI));
        else{
          continue;
        }
      }
      else if(command == F("HYGR_MIN_T")){
        if(content > -40 || content < 85)minHygr.changeValue(content);
        else{
          continue;
        }
      }
      else if(command == F("HYGR_MAX_T")){
        if(content > -40 || content < 85)maxHygr.changeValue(content);
        else{
          continue;
        }
      }
      else if(command == F("PRESSURE")){
        if(content == 1 || content == 0)sensorsStates.changeValue(sensorsStates.getValue() & ~((1-content) << PRES));
        else{
          continue;
        } 
      }
      else if(command == F("PRESSURE_MIN")){
        if(content > 300 || content < 1100)minPres.changeValue(content);
        else{
          continue;
        }
      }
      else if(command == F("PRESSURE_MAX")){
        if(content > 300 || content < 1100)maxPres.changeValue(content);
        else{
          continue;
        }
      }
      else if(command == F("LOG_INTERVAL")){
        if(content > 0) waitingTime.changeValue(content); 
        else{
          continue;
        }
      }
      else if(command == F("FILE_MAX_SIZE")){
        if(content > 0) maxLines.changeValue(content);
        else{
          continue;
        }
      }
      else {
        continue;
      }
      Serial.print(F("Command : "));
      Serial.println(userEntry);
    }
  }
}