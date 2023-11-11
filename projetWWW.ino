#include <I2C_RTC.h>
#include <SdFat.h>
#include <Bme280.h>
#include <ChainableLED.h>
#include <SPI.h>
#include <EEPROM.h>
#include <SoftwareSerial.h>
#include "saveoff.h"

#define lightSensor       0
#define BOUTROUGE         3
#define BOUTVERT          2

#define MAINTE            5
#define STANDA            6 
#define ECONOM            7

#define PRESS_TIME    500
#define INTER_DELAY   10

#define LIGHT     0
#define PRES      1
#define TEMP      2
#define HUMI      3
#define GPS       4

#define SHORTRED    0
#define SHORTBLUE   1
#define SHORTYEL    2
#define LONGYEL     3
#define SHORTGREEN  4
#define LONGGREEN   5
#define SHORTWHITE  6
#define LONGWHITE   7

uint8_t ledBools = 0;

stateOff sensorsStates(SENS_STAT_EE);  // Octet des différents états de capteurs (activés ou non)
uint8_t state = (1 << STANDA);         // Octet des modes (standard, configuration, économie)
stateOff waitingTime(LOG_INTERVAL);    // Temps d'attente en minutes stocké dans l'EEPROM
stateOff maxLines(MAXLINES);           // Nombre maximum d'entrées par fichier
bool mustWrite = true;                 // Booléen indiquant si on doit afficher ou écrire les données
String fileName;                       // Chaine de caractères contenant le nom du fichier actuel
String toSend;                         // Chaine de caractères à écrire/afficher pour éviter l'empilement

SoftwareSerial SoftSerial(8, 9);       // Connexion avec le GPS
DS1307 RTC;                            // Objet permettant la communication avec l'horloge RTC
SdFat sd;                              // Objet permettant la communication avec la carte SD
Bme280TwoWire sensor;                  // Objet permettant la communication avec le capteur BME280
ChainableLED leds(5,6,1);              // Objet permettant la communication avec la LED RGB

unsigned long lastInter = 0;           // Contient le moment de la dernière interruption
unsigned long pressedTime = 0;         // Contient le moment où le bouton a été pressé
uint16_t filesCreated = 0;             // Contient le nombre de fichiers créé dans une journée
unsigned long lastSaved = 0;           // Contient le moment de la dernière sauvegarde
uint8_t day = 0;                       // Contient le jour
uint8_t linesWritten = 0;              // Contient le nombre de lignes écrites dans le fichier actuel
bool errorSensor = false;              // Un booléen indiquant si un capteur a eu un problème

void setup() {
  Serial.begin(9600);
  SoftSerial.begin(9600);
  while(Serial.available())Serial.read();   // On vide le tampon série en cas d'entrée en attente
  RTC.begin();                        
  sdInit();
  bmeSetup();
  leds.setColorRGB(0, 0, 0, 0);
  if (!digitalRead(BOUTROUGE)) configuration();
  else delay(2000);
  createInterrupt();
  recupDonnees();
}

void loop(){
  toSend = "";
  if (state & (1 << MAINTE))maintenance();
  if (state & (1 << STANDA))standard();
  if (state & (1 << ECONOM))economic();
}