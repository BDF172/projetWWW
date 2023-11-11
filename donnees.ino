void recupDonnees(){
  if (RTC.getDay() != day){    // On change la variable globale du jour si il a changé
    filesCreated = 0;          // Si le jour a changé a changé, le nombre de fichiers créé pour ce dernier est nul
    changeFile();              // On ouvre le prochain fichier pour les logs
    day = RTC.getDay();        // On récupère le jour à l'horloge RTC
  }
if(mustWrite && ++linesWritten > maxLines.getValue()){    // Si le nombre maximum de lignes par fichier est atteint, on change de fichier
  changeFile();
  day = RTC.getDay();
  linesWritten = 0;
}
  getGps();       // On écrit les données GPS
  getTime();      // On écrit les données RTC
  getBME();       // On écrit les données de l'air
  lightData();    // On écrit les données de luminosité
  jumpLine();     // On saute une ligne pour la prochaine entrée

  lastSaved = millis();
}

void recupDonneesEco(){
  if (RTC.getDay() != day){
    changeFile();
    day = RTC.getDay();
  }
  static bool gpsLastTime = false;
  if(++linesWritten == maxLines.getValue()){
      changeFile();
      day = RTC.getDay();
      linesWritten = 0;
  }
  if(gpsLastTime = !gpsLastTime)getGps();    // On écrit les données GPS
  getTime();                                 // On écrit les données RTC
  getBME();                                  // On écrit les données de l'air
  lightData();                               // On écrit les données de luminosité
  jumpLine();                                // On saute une ligne pour la prochaine entrée

  lastSaved = millis();
}