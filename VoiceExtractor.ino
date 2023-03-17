#include <Audio.h>
#include <SPI.h>
#include <SD.h>
#include "MyDsp.h"


File                      musicFile;
AudioControlSGTL5000      audioShield;
AudioInputI2S             in;
AudioOutputI2S            out;
AudioPlaySdWav            playWav;
MyDsp                     myDsp;


// Connecte la piste audio à la bibliothèque MyDsp puis à la sortie audio (prise jack)
AudioConnection          patchCord1(playWav, 0, myDsp, 0);                                // 1ère connexion pour "volume"
AudioConnection          patchCord2(playWav, 1, myDsp, 1);                                // 2ème connexion pour "stereo"
AudioConnection          patchCord3(myDsp, 0, out, 0);                                    // connexion à la sortie stéréo L
AudioConnection          patchCord4(myDsp, 1, out, 1);                                    // connexion à la sortie stéréo R


int pause = 0;
int bouton1 = 0;
int indicateur = 0;



void setup() {
  Serial.begin(9600);
  AudioMemory(8);                       // nécessaire pour les connexions audio
  audioShield.enable();
  audioShield.volume(0.5);
  pinMode(4, INPUT);

// Initialisation de la carte SD
  if (!SD.begin(10)) {
    Serial.println("No SD card");
    return;
  }
  Serial.println("SD card connected");

// Existence du fichier audio
  musicFile = SD.open("Careless.WAV");
  if(musicFile) {
    Serial.println("File exists");
    musicFile.close();
  }
  else {
    Serial.println("error opening");
  }  
}


// Lecture audio
void playMusic() {
  playWav.play("Careless.WAV");
  delay(25);                          // un cours delay permet de lire les info WAV 
  while (playWav.isPlaying()) {
    update();
  }  
}



void update() {
    myDsp.setParamValue("FullAudio", analogRead(A1)/1023.0);    
    myDsp.setParamValue("Audio", analogRead(A1)/1023.0);
           

    if ((digitalRead(4) == 1) && (bouton1 == 0)) {
      myDsp.setParamValue("ApplyMono", !indicateur);      // A l'état 0 ou 1 -> quand il est multiplié à "Audio", le résultat obtenu est soit rien (0) soit la partie mono de la musique (1)  
      indicateur = !indicateur;
      bouton1 = 1;
    } 
    else if (digitalRead(4) == 0) {
    bouton1 = 0;
  }
}


void loop() {
  playMusic();
  delay(1000); 
}
