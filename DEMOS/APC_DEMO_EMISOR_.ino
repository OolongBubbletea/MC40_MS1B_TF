//Demostración del empaquetamiento y envio de datos desde el arduino a la PC (ARDUINO - PC)


//Estas variables representan valores de sensores:
float A = 0;
int B = 0;
int C = 0;
int D = 0;

//La función delay fuerza a arduino a detener su codigo
//Estas pausas pueden interferir con la comunicación serial
//Debido a esto trabajaremos con millis

//Variables para usar millis
unsigned long M_PRE = 0; //Millis previo
unsigned long M_ACT = 0; //Millis actual
const int M_INT = 250; //Intervalo para millis

void setup() {
  Serial.begin(9600); ////Inicialización del puerto serial 
}

void loop() {
  
  //Formula estandar para crear eventos usando millis:
  M_ACT = millis(); //En cada loop se actualiza el valor de millis
  if (M_ACT - T_PRV >= M_INT) { //Se enviarán datos cada que el tiempo actual - el anterior sea igual o mayor al intervalo establecido
    //Crear un mensaje para cada valor genera errores y requiere programación complicada
    //Por eso vamos a crear un paquete de datos
    //Primero obtendremos los valores de los sensores
    A = 3.14;
    B = 2024;
    C = 20;
    D = 5;
    //Despues los convertiremos a string
    //Y los encadenaremos junto a unos marcadores que la PC puede usar para decodificar el codigo
    Serial.println(String(A) + "A" + String(B) + "B" + String(C) + "C" + String(D) + "D"); // No se pueden encadenar variables int, String permite convertir una variable int o float a string
    //Asi queda el paquete de datos que se enviará a la pc a traves del puerto serial: 3.14A2024B20C5D

    T_Prv = T_Act; //Se actualiza el valor del tiempo anterior para reiniciar el conteo

  }  
}
