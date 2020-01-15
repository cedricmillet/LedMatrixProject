
#define PIN_BUZZER  2 //DIGITAL PIN


void EmitSound1() {
  
  for(int i=0; i<80; i++)// Premier son à une fréquence
  {
    analogWrite(PIN_BUZZER, 50);// Faire du bruit
    delay(50);// Attendre 10ms
    analogWrite(PIN_BUZZER, 0);// Silence
    delay(50);// Attendre 10ms
  }
}



void SetupSoundSystem() {
  pinMode(PIN_BUZZER, OUTPUT);

  EmitSound1();
}
