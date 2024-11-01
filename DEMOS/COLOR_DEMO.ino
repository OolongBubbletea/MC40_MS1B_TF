#include <tcs3200.h>  // Se usará la libreria NewPing para simplificar el codigo

int R_SIN = 0;   //Cantidad de color rojo (Red) (Sin normalizar)
int G_SIN = 0;   //Cantidad de color verde (Green) (Sin normalizar)
int B_SIN = 0;   //Cantidad de color azul (Blue) (Sin normalizar)
int L_BIT = 0;  //Cantidad de brillo (C)(Se usa para normalizar el resto de canales)

float R_NOR = 0;  //Cantidad de color rojo (Normalizado)
float G_NOR = 0;  //Cantidad de color verde (Normalizado)
float B_NOR = 0;  //Cantidad de color azul (Normalizado)

tcs3200 tcs(2, 3, 4, 5, 6);  // Pines: S0, S1, S2, S3, out

void setup() {
  Serial.begin(9600);  //Inicialización del puerto serial
}

void loop() {

  //Valores RGBW sin procesar:
  R_SIN = tcs.colorRead('r', 20);    //Guardar la información del canal 'r' en la variable R_SIN,
  G_SIN = tcs.colorRead('g', 20);    //Guardar la información del canal 'g' en la variable G_SIN
  B_SIN = tcs.colorRead('b', 20);    //Guardar la información del canal 'b' en la variable B_SIN
  L_BIT = tcs.colorRead('c', 100);  //Guardar la información del canal 'c' en la variable G_SIN
  //'20' '100' es el escalado (Una propiedad de la libreria, multiplica el valor del canal por esta cifra para que sea mas facil de leer)

  //El sensor tiene LEDS blancos que ayudan a iluminar los objetos en frente del sensor
  //Esto es util pero también nos puede causar problemas ya que la luz blanca altera el color leido
  //Para solucionar esto se tienen que normalizar los valores de 'r', 'g' y 'b'
  //La normalización se realiza dividiendo la información de cada canal entre la cantidad de brillo recibida por el sensor y multiplicando el resultado por 255
  //Se está usando 255 simplemente porque arduino suele usar el rango de 0-255 para muchas funciones, pero la verdad no se si es la mejor forma de realizar la normalización
  
  if (L_BIT != 0) { // Si el brillo es distinto de 0 se realiza la normalización (se usa esta condicional para evitar dividir entre 0)
    R_NOR = (float)R_SIN / L_BIT * 255;
    G_NOR = (float)G_SIN / L_BIT * 255;
    B_NOR = (float)B_SIN / L_BIT * 255;
  } else { //Si el brillo es igual a 0 se igualan todos los valores a 0 (Los LEDS deberian de iluminar el ambiente, asi que un brillo de 0 deberia ser imposible, pero es mejor añadir la posibilidad y evitar que el codigo se quiebre)
    R_NOR = 0;
    G_NOR = 0;
    B_NOR = 0;
  }

  if (R_NOR > G_NOR && R_NOR > B_NOR && L_BIT >= 80) { // Si el valor R_NOR es mayor al de los otros 2 canales normalizados se enviará "rojo" al monitor serial
    Serial.println("rojo");
  }
  if (G_NOR > R_NOR && G_NOR > B_NOR && L_BIT >= 80) { // Si el valor G_NOR es mayor al de los otros 2 canales normalizados se enviará "rojo" al monitor serial
    Serial.println("verde");
  }
  if (B_NOR > G_NOR && B_NOR > R_NOR && L_BIT >= 80) { // Si el valor B_NOR es mayor al de los otros 2 canales normalizados se enviará "rojo" al monitor serial
    Serial.println("azul");
  }
  if (L_BIT <= 80) {  // Si el valor BRILLO es menor a 80 se enviará "No detectado" al monitor serial, con esto estamos 
    Serial.println("No detectado");
  }


  //Lo siguiente es un poco de codigo para calibrar el sensor de ser necesario, quizá te ayude para definir que valores usar en los "if" 
  //Serial.print("R= ");
  //Serial.print(R_NOR);
  //Serial.print("    ");

  //Serial.print("G= ");
  //Serial.print(G_NOR);
  //Serial.print("    ");

  //Serial.print("B= ");
  //Serial.print(B_NOR);
  //Serial.print("    ");

  //Serial.print("W(clear)= ");
  //Serial.print(L_BIT);
  //Serial.print("    ");

  //Serial.println();

  delay(500);
}
