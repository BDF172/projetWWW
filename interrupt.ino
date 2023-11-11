void createInterrupt(){       // Définition de l'interruption par boutons
  pinMode(BOUTROUGE, INPUT);
  pinMode(BOUTVERT, INPUT);
  attachInterrupt(digitalPinToInterrupt(2), isr, CHANGE);
  attachInterrupt(digitalPinToInterrupt(3), isr, CHANGE);
}

void isr(){
  // On évite les rebonds en mettant un temps d'intervalle minimum entre deux interruptions
  if(((millis() - lastInter) < INTER_DELAY) || (!digitalRead(BOUTROUGE) && !digitalRead(BOUTVERT)))return;
  lastInter = millis();

  if(!digitalRead(BOUTVERT) || !digitalRead(BOUTROUGE)){
    // Si un bouton est appuyé, on retient lequel dans l'octet state
    if (!digitalRead(BOUTROUGE)) state |= (1 << BOUTROUGE);
    else if (!digitalRead(BOUTVERT)) state |= (1 << BOUTVERT);
    pressedTime = millis();
  }

  else if ((millis() - pressedTime) > PRESS_TIME){
    // Si un bouton est relâché, on regarde combien de temps il a été pressé, si c'est assez longtemps on procède

    // Si le bouton vert est pressé
    if(state & (1 << BOUTVERT)){
      // On enlève le bit bouton vert (indiqué qu'il n'est plus pressé)
      state &= ~(1 << BOUTVERT);
      // Si on est en mode économie, on désactive l'économie et on passe au mode standard
      if((state & (1 << ECONOM)) && !(state & (1 << MAINTE))){
        state &= ~(1 << ECONOM);
        state |= (1 << STANDA);
      }
      // Si on est en mode standard, on le désactive et passe au mode économie
      else if (state & (1 << STANDA) && !(state & (1 << MAINTE))){
        state &= ~(1 << STANDA);
        state |= (1 << ECONOM);
      }
    }

    // Si le bouton rouge est pressé
    if(state & (1 << BOUTROUGE)){
      // On enlève le bit bouton rouge (indiqué qu'il n'est plus pressé)
      state &= ~(1 << BOUTROUGE);
      // Si le mode maintenance est activé, on le désactive
      if(state & (1 << MAINTE)){
        state &= ~(1 << MAINTE);
      }
      // Sinon, on l'active
      else {
        state |= (1 << MAINTE);
      }
    }
  }
}