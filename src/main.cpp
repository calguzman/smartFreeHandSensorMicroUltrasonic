#include <Arduino.h>
#include <SPI.h>
#include <RF24.h>


 
#define pulso 7  //define la salida por donde se manda el pulso como 9
#define rebote 6 //define la salida por donde se recibe el rebote como 10
int distancia;  //crea la variable "distancia"
float tiempo;  //crea la variable tiempo (como float)
const byte receiverID[6]="00001";

const int distanceSensorOperationPin = A0; // 
int distanceSensorOperationInput; 
int realDistanceSensorOperation;

RF24 radio(8, 9);



void setup()
{
  Serial.begin(9600);  //inicializa el puerto serie<
  pinMode(pulso, OUTPUT); //Declaramos el pin 9 como salida (pulso ultrasonido)
  pinMode(rebote, INPUT); //Declaramos el pin 8 como entrada (recepción del pulso)

  radio.begin();
  radio.openWritingPipe(receiverID);
  radio.setPALevel(RF24_PA_MIN); // Set Power Level to Transmition
  radio.stopListening(); // Set Transmiter Mode. 
  
}
 
void loop()
{

  // Distance Calculator
  // distanceSensorOperationInput = analogRead(distanceSensorOperationPin);
  // realDistanceSensorOperation = map(distanceSensorOperationInput,0,1023,5,20);
  // Serial.println("Distancia Programada");
  // Serial.println(realDistanceSensorOperation);

  digitalWrite(pulso,LOW); //Por cuestión de estabilización del sensor
  delayMicroseconds(5);
  digitalWrite(pulso, HIGH); //envío del pulso ultrasónico
  delayMicroseconds(10);
  tiempo = pulseIn(rebote, HIGH);  //funcion para medir el tiempo y guardarla en la variable "tiempo"
  distancia = 0.01715*tiempo; //fórmula para calcular la distancia
  if(distancia<=15){
    const char commandToOpen[]="1";
    radio.write(&commandToOpen, sizeof(commandToOpen));
     Serial.println("Lectura");
    //  Serial.println(handWashMode);
    delay(100);
  }   
   /*Monitorización en centímetros por el monitor serial*/
  Serial.print("Distancia: ");
  Serial.print(distancia);
  Serial.println(" cm");
  delay(1000);
}
 