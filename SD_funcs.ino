void sdInit(){
  // Vérification du branchement de la carte SD
  if (!sd.begin(4)) {
    ledBools = (1 << SHORTRED) | (1 << LONGWHITE);
    ledAlert();
  }
}

void changeFile(){
  bool done = false;
  char buffer[18];
  SdFile file;
  while(true){
    // On crée un nom de fichier du format AAMMJJ_RR.log année mois jour révision
    sprintf(buffer, "%02d%02d%02d_%02d.log", RTC.getYear(), RTC.getMonth(), RTC.getDay(), ++filesCreated);
    linesWritten = 0;
    if(!sd.exists(buffer))break;
    if (!file.open(buffer, O_READ)) {
      ledBools = (1 << SHORTRED) | (1 << LONGWHITE);
      ledAlert();
    }
    while (file.available()) {
      if (file.read() == '\n') {
        linesWritten++;
      }
    }
    file.close();
    if(linesWritten >= maxLines.getValue()) {
      continue;
    }
    break;
  }
  fileName = buffer;           // On stocke le nom de fichier dans un String global
}

void writeToFile() {
  SdFile file;
  file.open(fileName.c_str(), O_WRITE | O_APPEND | O_CREAT);
  if (file) {
    if (!file.print(toSend)){  // On vérifie que la ligne a été écrite dans le fichier
      ledBools = (1 << SHORTRED) | (1 << LONGWHITE);
      ledAlert();
    }
    file.close();
  } else {
    ledBools = (1 << SHORTRED) | (1 << LONGWHITE);
    ledAlert();
  }
}


void jumpLine() {
  if(!mustWrite){
    Serial.println(" ");
  }
  else{
    SdFile file;
    file.open(fileName.c_str(), O_WRITE | O_APPEND | O_CREAT);

    if (file) {
      if (file.println(""));
      else {
        ledBools = (1 << SHORTRED) | (1 << LONGWHITE);
        ledAlert();
      }
      file.close();
    } else {
      ledBools = (1 << SHORTRED) | (1 << LONGWHITE);
      ledAlert();
    }
  }
}