#include <Arduino.h> //Solo si estas usando Platformio, no el IDE de Arduino.
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define BLYNK_PRINT Serial


// Coloque aqui su clave de autenticacion
char auth[] = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";


// Coloque aqui su nombre de red y clave Wi Fi
char ssid[] = "xxxxxxx";
char pass[] = "xxxxxxx";


BlynkTimer timer;


// Esta funcion envia los datos del sensor a la placa cada un segundo.
void sendSensor()
{

  // Leemos el valor de A0
  int ADC = analogRead(A0);

  //Si no se leen datos imprimir "No se pueden leer datos del sensor!"
  if (isnan(ADC)) {
    Serial.println("No se pueden leer datos del sensor!");
    return;
  }

  // Enviar los datos al pin virtual 5 de Blynk
  Blynk.virtualWrite(5, ADC);
}

void setup()
{

  // Iniciamos comunicacion Serial
  Serial.begin(9600);

  // Se inicia la conexion
  Blynk.begin(auth, ssid, pass);


  //Esperamos un minuto para que inicie el sensor
  Serial.print("Calentando el sensor, espera un minuto");
  Serial.print(".");
  delay(1000);
  Serial.print(".");
  delay(1000);
  Serial.print(".");
  delay(1000);
  delay(60000);


  // Envia los datos de la funcion sendSensor cada un segundo
  timer.setInterval(1000L, sendSensor);
}

void loop()
{
  //Imprime los valores del sensor (esto no es necesario)
  Serial.println(analogRead(A0));

  //Ejecuta el resto del codigo
  Blynk.run();
  timer.run();
}
