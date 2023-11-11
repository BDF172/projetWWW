// Définition des adresses mémoire EEPROM pour différentes données
#define SENS_STAT_EE      0
#define STATE             1
#define LUMIN_LOW_EE      2
#define LUMIN_HIGH_EE     6
#define MIN_TEMP_A_EE     10
#define MAX_TEMP_A_EE     14
#define HYGR_MINT_EE      18
#define HYGR_MAXT_EE      22
#define PRES_MIN_EE       26
#define PRES_MAX_EE       30
#define TIMEOUT           34
#define MAXLINES          38
#define LOG_INTERVAL      42

// Classe pour gérer la sauvegarde de données de type float dans l'EEPROM
class saveOff {
  public : 
  // Constructeur de la classe
  saveOff(uint8_t addressToSet){
    address = addressToSet;
    value = getValue();
  }

  // Méthode pour changer la valeur stockée
  void changeValue(float valueToSet){
    value = valueToSet;
    // Découpage de la valeur float en octets individuels et stockage dans l'EEPROM
    uint8_t var1 = *((char *)(&valueToSet));
    uint8_t var2 = *((char *)(&valueToSet) + 1);
    uint8_t var3 = *((char *)(&valueToSet) + 2);
    uint8_t var4 = *((char *)(&valueToSet) + 3);

    EEPROM.write(address, var1);
    EEPROM.write(address + 1, var2);
    EEPROM.write(address + 2, var3);
    EEPROM.write(address + 3, var4);
  }

  // Méthode pour récupérer la valeur stockée
  float getValue(){
    *((char *)(&value)) = EEPROM.read(address);
    *((char *)(&value) + 1) = EEPROM.read(address + 1);
    *((char *)(&value) + 2) = EEPROM.read(address + 2);
    *((char *)(&value) + 3)= EEPROM.read(address + 3);

    return value;
  }

  private :
  uint8_t address;
  float value;
};

// Classe pour gérer la sauvegarde de données de type uint8_t (8 bits) dans l'EEPROM
class stateOff {
  public : 
  // Constructeur de la classe
  stateOff(uint8_t addressToSet){
    address = addressToSet;
    value = EEPROM.read(address);
  }

  // Méthode pour changer la valeur stockée
  void changeValue(uint8_t valueToSet){
    value = valueToSet;
    EEPROM.write(address, value);
  }

  // Méthode pour récupérer la valeur stockée
  uint8_t getValue(){
    return value;
  }

  private :
  uint8_t address;
  uint8_t value;
};
