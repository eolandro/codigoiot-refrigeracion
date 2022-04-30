/*
 * Estructura básica
 * Por: Leonardo Valdes arteaga (eolandro)
 * Fecha: 28 de junio de 2021
 * 
 * Programa de refrigeracion basado en una maquina de estados
 * o automata finito
 */

// Bibliotecas
#include "DHT.h"
// Constantes
#define MAXT 30
// Hardware
#define DHTPIN 15
#define DHTTYPE DHT11
// botones
#define BTN1_Manual  16
#define BTN2_Alta 2
#define BTN3_Sobre 14
// LEDS
#define LED_Manual 13
#define LED_Auto 12
// Variables
byte Estado = 0;
boolean Temp = false;
boolean LecT = false;
float t = 0;
int Manual = 0;
int Alta = 0;
int Sobre = 0;
unsigned long InicioTiempo;
unsigned long FinTiempo;
unsigned long NSegundos = 0;
// Definición de objetos
DHT dht(DHTPIN, DHTTYPE);
////////////////////////////////////////////////////////////////
void info(){
  String Res = "";
  Serial.println(Res+t+","+NSegundos+","+Estado+","+Manual+","+Alta+","+Sobre);
}
////////////////////////////////////////////////////////////////
void controlTiempo(){
  unsigned long Delta;
  FinTiempo = millis();
  Delta = FinTiempo - InicioTiempo;
  if (Delta >= 1000){
    InicioTiempo = FinTiempo;
    NSegundos++;
  }
}
////////////////////////////////////////////////////////////////
void revisarInput(){
  Manual = digitalRead(BTN1_Manual); //Leer el pin del boton1 (Manual)
  Alta   = digitalRead(BTN2_Alta); //Leer el pin del boton1 (alta demanda)
  Sobre = digitalRead(BTN3_Sobre); //Leer el pin del boton1 (sobrecarga)
}
////////////////////////////////////////////////////////////////
void revisarTemperatura(){
  byte reloj = NSegundos % 2;
  /////////////////////
  if (reloj == 1 && !LecT){
    t = dht.readTemperature(); // Leer la temp en celsius
    LecT = true;
    /////////////////////
    if (isnan(t)) {
      t = 0;
      LecT = false;
    }
    Temp = false;
    if (t >= MAXT){
      Temp = true;
    }
    /////////////////////
    info();
  }
  if(reloj == 0){
    LecT = false;
  }
}
////////////////////////////////////////////////////////////////
void cambioEstado(){
  //////////////////////////////////////////
  boolean AltaSobre = Alta == LOW || Sobre == LOW;
  if (AltaSobre && Temp){
    Estado = 3;
    return;
  }
  /////////////////////////////////////////
  if (Manual == LOW){
    Estado = 1;
    return;
  }
  /////////////////////////////////////////
  if (AltaSobre){
    Estado = 2;
    return;
  }
  /////////////////////////////////////////
  if (Temp){
    Estado = 2;
    return;
  }
  /////////////////////////////////////////
  Estado = 0;
}
////////////////////////////////////////////////////////////////
void base(){
  digitalWrite(LED_Manual,LOW); //empieza el led apagado
  digitalWrite(LED_Auto,LOW); //empieza el led apagado
}
void manual(){
  digitalWrite(LED_Manual,HIGH); //empieza el led apagado
  digitalWrite(LED_Auto,LOW); //empieza el led apagado
}
void automatico(){
  digitalWrite(LED_Manual,LOW); //empieza el led apagado
  digitalWrite(LED_Auto,HIGH); //empieza el led apagado
}
void emergencia(){
  digitalWrite(LED_Manual,HIGH); //empieza el led apagado
  digitalWrite(LED_Auto,HIGH); //empieza el led apagado
}
////////////////////////////////////////////////////////////////
// Condiciones iniciales - Se ejecuta sólo una vez al energizar
void setup() {// Inicio de void setup ()
  // Aquí va tu código
  Serial.begin (115200); // Iniciar comunicacion serial
  ////////////////////////////////////////////////////////
  //Configurar el pin del boton como entrada
  pinMode(BTN1_Manual,INPUT_PULLUP); 
  pinMode(BTN2_Alta,INPUT_PULLUP); 
  pinMode(BTN3_Sobre,INPUT_PULLUP); 
  ////////////////////////////////////////////////////////
  pinMode(LED_Manual,OUTPUT); //Configurar el pin de led como salida
  pinMode(LED_Auto,OUTPUT); //Configurar el pin de led como salida
  ////////////////////////////////////////////////////////
  digitalWrite(LED_Manual,LOW); //empieza el led apagado
  digitalWrite(LED_Auto,LOW); //empieza el led apagado
  ////////////////////////////////////////////////////////
  dht.begin();
  delay (5000);
  ////////////////////////////////////////////////////////
  InicioTiempo = millis();
}// Fin de void setup

// Cuerpo del programa - Se ejecuta constamente
void loop() {// Inicio de void loop
  // put your main code here, to run repeatedly:
  controlTiempo();
  revisarInput();
  revisarTemperatura();
  cambioEstado();
  //
  switch(Estado){
    case 0: //Estado base
      base();
    break;
    case 1: //Estado Manual
      manual();
    break;
    case 2: //Estado Automatico
      automatico();
    break;
    case 3: // Estado Emergencia
      emergencia();
    break;
  }
}// Fin de void loop

// Funcioes del usuario
