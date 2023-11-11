void getTime()
{
  verifyRTC();      // On vérifie que l'horloge RTC fontionne, si oui, on enregistre l'heure actuelle, sinon, on affiche l'erreur LED jusqu'à résolution
  toSend = "$HE=";
  toSend += (String(RTC.getHours(), DEC) + ":");
  toSend += (String(RTC.getMinutes(), DEC) + ":");
  toSend += (String(RTC.getSeconds(), DEC));
  if(!mustWrite) Serial.print(toSend); else writeToFile();
}

void verifyRTC(){
  bool red = true;
  while(true){
    if(!(RTC.getYear() == 2000)){
      if(!(RTC.getYear() == 2165)){
        break;
      }
    }
    ledBools = (1 << SHORTRED) | (1 << SHORTBLUE);
    ledAlert();
  }
}