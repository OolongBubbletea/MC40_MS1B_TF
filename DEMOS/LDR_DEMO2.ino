int LDR1_PIN = A0; //Pin del LDR
int LDR1_V = 0; //Valor del LDR
int SENS_V = 500; //Valor de sensibilidad

void setup() {
  pinMode(LDR1_PIN,INPUT);
  Serial.begin(9600);  

}

void loop() {
  LDR1_V = analogRead(LDR1_PIN);
  Serial.print(" ");
  Serial.print(LDR1_V);
  Serial.print(" ");

  if (LDR1_V < SENS_V) {
    Serial.println("Hay algo frente al sensor");
  } else {
    Serial.println("No hay nada frente al sensor");
  }
  delay(50);
}
