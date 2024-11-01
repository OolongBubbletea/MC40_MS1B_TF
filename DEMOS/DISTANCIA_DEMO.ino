#include <NewPing.h> // Se usará la libreria NewPing para simplificar el codigo

const int P_TRI = 7; //Pin Trigger
const int P_ECH = 8; //Pin echo
const int D_MAX = 1000; //Distancia maxima

int D_SIN = 0; //Distancia sin procesar
int D_PRO = 0; //Distancia procesada

NewPing sonar(P_TRI, P_ECH, D_MAX); //Inicialización de la función Newping

//Variables para conseguir el promedio de la distancia:
int D_LIS[5] = {0, 0, 0, 0, 0}; //lista para almacenar los valores
int index = 0; //Indice para la lista

void setup() {
  Serial.begin(9600); //Inicialización del puerto serial

  pinMode(P_TRI, OUTPUT); //Configuración del pin trigger
  pinMode(P_ECH, INPUT); //Configuración del pin echo

}

void loop() {

  D_SIN = sonar.ping_cm(); //Guardar la distancia obtenida(cm) en la variable D_SIN

  //Promedio de las ultimas 5 lecturas, para estabilizar la cifra obtenida Y reducir el ruido del sensor:
  D_LIS[index] = D_SIN; //Guardar el valor en la lista (este paso y el anterior se pueden combinar, pero lo dejé asi para que sea mas legible)
  index = (index + 1) % 10; //Actualizar el valor del indice entre 0 y 9
  D_PRO = (D_LIS[0] + D_LIS[1] + D_LIS[2]+ D_LIS[3] + D_LIS[4]) / 5; //Promedio de los valores de distancia


   //Configuración de la información a enviar
  if (Dist >= 100){
    Serial.println("FUERA DE RANGO");
  }else if (Dist == 0){
    Serial.println("ERROR DE SENSOR");    
  }else(Serial.println(String(D_PRO)));  
}
