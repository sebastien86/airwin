// Seb : Client pour MRL et test echanges SERIE en ARDUINO et MRL
// pour commande via la PS2
// Si Recoit LEDON u LEDOFF allume/eteind une led sur l'arduino et envoie en serie 0 (48) ou 1 (49)
// TEst 2 : envoie d'une commande serie Vers MRL
// MRL => affiche la commade et message en retour...
//

#define PIN            13

boolean DEBUG=false; // Active l'affichage des messages de debug
String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete
int cptin=0; // comptage du nb de caractères reçu

void setup() {
  // initialize serial:
  Serial.begin(19200);
  delay(200);
  
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
  
  pinMode(PIN, OUTPUT);
  Serial.println(0);
     
}


// ************ MAIN ****************
void loop() {
  // print the string when a newline arrives:
  if (stringComplete) {
    debugMsg(inputString);

    // chaineReception.trim(); // enlève les espaces
    analyseChaine(inputString); // appelle la fonction d'analyse de la chaine en réception
    
    // clear the string:
    inputString = "";
    stringComplete = false;
  }
}

/*
  SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();

    // add it to the inputString:
    inputString += inChar;
    cptin++;
   
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n' || cptin==10) {
      stringComplete = true;
      cptin=0;
      debugMsg(inputString);
    }
  }
}

//
//  Analyse les instructions recus via le serie
//
void analyseChaine(String chaineRecue) { // fonction d'analyse de la chaine recue
      int valeur=0; // variable utile
      String chaineTest; // objet STring pour analyse chaine recue

      // convertie les lettres en majuscules, pour rendre les commandes case insensitives...
      chaineRecue.toUpperCase();

      // Selectionne la rampe de led sur laquelle vont s'appliquer les effets
      if (chaineRecue.startsWith("LEDON"))    {
          digitalWrite(PIN, HIGH);
          Serial.println(1);    
      }
      
      if (chaineRecue.startsWith("LEDOFF")) {
        digitalWrite(PIN, LOW);
        Serial.println(0);
      }
} // fin fonction analyse chaine

// Affiche les messages en retour sur le port série
void debugMsg(String todisplay) {
  if (DEBUG==true)  Serial.println(todisplay);
}
