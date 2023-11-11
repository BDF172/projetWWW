void getGps(){
  getGps(0);
}

void getGps(uint8_t max){
  if(max != 3){
    toSend = "$";
    unsigned int count = 0;   // contient le nombre de sauts à la ligne demandés par le GPS
    char c;
    unsigned long begin = millis();
    do{
      if (SoftSerial.available())
        while(SoftSerial.available()){
          c = SoftSerial.read();
          toSend += c;
          count += (c == '$');  // On compte (dans count) le nombre de signes $ (Une entrée GPS pour en avoir maximum 10)
        }
    }while(count!=10 && millis() - begin < 5000 && toSend.length() < 300);

    // On recherche la trame GPGGA 
    char toFind[] = "GPGGA";
    count = 1;
    while (count != toSend.length()) {
      bool verified = true;
      if (toSend.charAt(count) != '$'){  // Le dollar signifie le début d'une trame, on supprime donc tout jusqu'à atteindre la prochaine
        toSend.remove(count, 1);
        continue;
      }
      toSend.remove(count, 1);
      for (int i = 0; i < 5; i++) {
        if(toSend.charAt(count+i) != toFind[i])verified = false;  // On vérifie qu'il s'agit bien des lettres GPGGA
      }
      if(!verified)continue;                                      // Si ce n'est pas le cas, on revient au début de la boucle
      while (toSend.charAt(++count) != '$');
      toSend.remove(count, toSend.length() - count);              
      break;
    }
    if(toSend.length() < 10){
      getGps(++max);                                              // Si la trame GPGGA n'est pas complète, on recommence (maximum 3 fois)
    }
    if(max != 0) return;
  }
  else{
    toSend = F("$GPGGANAN");                                      // En cas de manque de signal GPS ou de trame GPGGA, on l'initialise comme NAN
    errorSensor = true;
  }
  if(!mustWrite){
    Serial.println(toSend);                                       // On affiche à l'utilisateur si il est en mode maintenance
    toSend = "";
    return;
  }
  SdFile file;                                                    // Sinon on l'écrit dans le fichier
  file.open(fileName.c_str(), O_WRITE | O_APPEND | O_CREAT);

  if (file) {
    for(uint8_t i = 0; i < toSend.length()-2; i++){
      if (file.print(toSend.charAt(i))){
      }
      else{
        while(true);
      }
    }
    file.close();
  } else {
    while(true);
  }
}
