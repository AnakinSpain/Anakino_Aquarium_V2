
///////////////////////////////////////////////////////////////
//
//
//
//
//     CONTROLADOR DE ACUARIO CON LA APP BLYNK 
//     
//     V. 07-2019
//
//     PLACA Arduino Mega + wifi ESP8266
//     
//     TO DO: 1) Añadir opcion de luces auto, man on o man off y controladas por el arduino
//            2) Añadir los pines para los reles. segun ya tengo conectado
//            3) Añadir led verde o rojo segun si está online o no
//
/////// PUERTOS VIRTUALES BLYNK /////
//                     
//        V0       Datos de thingspeak webhook 500 puntos en app blynk
//        V1       Temperatura deseada del acuario desde blynk numeric input 400
//        V2       Modo Airador menu setting 400
//        V3       Modo lamp UV menu setting 400
//        V4       Modo relleno menu setting 400
//        V5       Modo Comedero menu setting 400
//        
//        V10      LED bomba relleno funcionando 100
//        V11      LED ventilador funcionando 100
//        V12      LED calentador funcionando 100
//        V13      LED funcionando lampara UV 100
//        V14      LED esta funcionando el aireador 100
//        V15      LED esta funcionando el CO2 100
//        V16      LED deposito agua vacio 100
//        V17      LED temperatura fuera parametros 100
//
//       
//        V20      temp de agua display 200
//        V21      temp habitacion display 200
//        V22      libre
//        V23      Tanto por ciento al que están los ventiladores display 200
//        V24      valor de pH display 200
//        
//        V30      boton de comederos manual tipo push 200
//        v31      Disparador de la peris 1 time input 200
//        V32      Disparador de la peris 2 time input 200
//
//
//        V40      Disparador del temporizador del aireador (temporizadores) timer 200
//        V41      Disparador del temporizador de la Lamp UV (temporizadores) timer 200
//        V42      Temporizador CO2 libre timer 200
//        V43 .    Temporizador comedero time input 200
//       
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
//Librerias necesarias
///////////////////////////////////////////////////////////////
#define BLYNK_PRINT Serial

#include <EEPROM.h>
#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>
#include <SPI.h>
#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Servo.h>
#include <TimeLib.h>
#include <WidgetRTC.h>
#include <U8g2lib.h>
#include "GravityTDS.h"
////////////////////////////////////////////////////////////////
//#define NOCONTADOR
#define CONTADOR
#define DEBUG
////////////////////////////////////////////////////////////////
// Definimos los pines y variables
////////////////////////////////////////////////////////////////
#define ver 1
#define vent_agua   2    // PWM Ventilador agua pin 2
#define vent_pant   3    // PWM Ventilador pantalla pin 3
#define luz         4    // PWM Luz blanca
#define luz_azul    5    // PWM leds azules noche

#define sensores_temp  22   // Sensores de temp de agua y pantalla leds
#define nivel_acu  23   // Boya nivel agua acuario
#define nivel_dep  24   // Pin lee nivel agua deposito auxiliar
#define bomba      25   // Pin accionara la bomba de llenado 

#define calentador 26   // Calentador    * RELE 1         
#define aireador   27   // Aireador      * RELE 2
#define lamp_uv    28   // Lampara UV    * RELE 3
#define CO2        29   // CO2           * RELE 4
#define peris1     30   // peristaltica 1
#define peris2     31   // peristáltica 2
#define servoPin   36   // servo comedero
#define DHTPIN     37   // Sensor dht22 Pin humedad y temp habitacion

#define led_rojo   53   // pin led de aviso rojo

#define temp_margen  0.1    // Margen de actuacion del calentador

#define sensor_ph  A15   // sensor de pH
#define Offset 0.00            //deviation compensate of pH


#define TdsSensorPin A14
GravityTDS gravityTds;


////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
//CONFIGURACION WIFI Y TOKEN
////////////////////////////////////////////////////////////////////////

  char auth[] = "xxxxx"; // INTRODUCIR TOKEN
  char ssid[] = "xxxxxx";          // NOMBRE WIFI
  char pass[] = "xxxxxx";  // CONTRASEÑA WIFI 

////////////////////////////////////////////////////////////////
  
// Hardware Serial on Mega, Leonardo, Micro...poner Serial3 para la placa robotdyn
#define EspSerial Serial1

#define ESP8266_BAUD 115200 // Your ESP8266 baud rate:

ESP8266 wifi(&EspSerial);

////////////////////////////////////////////////////////////////////////
//VARIABLES DE Alarma y estado del acuario
////////////////////////////////////////////////////////////////////////

 bool alarma_enviada = false;  // variable en el que se guardaran si se ha enviado la  alarma
 bool alarma_activa = false; // indica se hay alarma activada
 int tipo_alarma; // En esta variable podremos añadir los diferentes tipos del sistema
//bit 0;     // estado ventilador disipador 
//bit 1;     // estado del calentador
//bit 2;     // estado de la temperatura (caliente) Influye alarma en pantalla
//bit 3;     // estado de la iluminacion
//bit 4;     // estado del PH del acuario

//*********************** Variables de control de temperatura del agua ********************
// Preparamos otras variable

 float temp_agua;             //Temperatura del agua
 float temp_agua_des;         //temperatura agua deseada
 byte contador_temp = 0;
 byte contador_med_temp = 0;
 float temperatura_agua_temp; // Temperatura temporal del agua
 int contador_1 = 0;

 float temp_agua_inst;
 float temp_habit_inst;
 float temp_disp_inst;
 
 //float tempHB;    //Temperatura de la habitacion
 float temp2_temp;  //temperatura temporal sistema

 float temperatura_disipador_temp; // Temperatura temporal del disipador
 float temperatura_habitacion_temp; // temperatura temporal de la habitacion
    
 float tempD = 0;     // Temperatura del disipador
 float tempHB = 0;    // Temperatura habitacion
 byte  percent_vent;  // tanto porciento de los ventiladores para enfriar agua

 float phValue;      // valor de pH
 unsigned long int avgValue;     //Store the average value of the pH sensor feedback

 float temperature; // variables para tds
 float tdsValue; // variable para tds
/////////////////////////////////////////////////
// Preparamos  modos de funcionamiento

bool modo_relleno; // Rellenador 1 -> activado // 0-> desactivado
int modo_uv;      // modo de funcionamiento uv
int modo_ai;      // modo de funcionamiento aireador
int modo_comedero;// Modo comedero true=automatico, false= off

int temp_uv;    // Variable para indicar si activa o no la lamp uv desde blynk por el temporizador
int temp_ai;    // Variable para indicar si activa o no el aireador desde blynk por el temporizador
int temp_comedero;
  
/////////////////////////////////////////////////////////////////
//Blynk
////////////////////////////////////////////////////////////////

char currentTime[9];
char startTime[9];
int SThour;
int STmin;

bool peris1_today;
int peris1STHour;
int peris1STMin;
int peris1STSec;
int peris1FNSec;

bool peris2_today;
int peris2STHour;
int peris2STMin;
int peris2STSec;
int peris2FNSec;

bool feeded = false; // variable que indica que el comedero ha dejado comido en la hora prevista
bool feed_today;

BlynkTimer timer;

WidgetRTC rtc;

bool tweet_enviado = false;

bool isConnected;

int Vcount; // variable para controlar la sincronizacion

  BLYNK_CONNECTED()     // This function will run every time Blynk connection is established
  {  
   
   //BlynkSyncAllHack();
   rtc.begin();  // Synchronize time on connection
   Blynk.syncVirtual(V1, V2, V3, V4, V5, V31, V43); 
   //Blynk.syncAll();  // Request Blynk server to re-send latest values for all pins
   }
   
  BLYNK_WRITE(V1)  // variable de la temperatura del agua deseada
{
  float temp_agua_des_blynk = param.asFloat(); // Asigna un valor a la variable temp_agua_des desde el slider de la app
  Serial.println("Temp Deseada blynk: " + String(temp_agua_des_blynk));
  temp_agua_des = (temp_agua_des_blynk);
}
    
  BLYNK_WRITE(V2) // Variable del modo AIREADOR (auto, manual on, off )
{
  modo_ai = param.asInt(); 
  Serial.println("V2 modo_ai value is: "+ String(modo_ai));
}

  BLYNK_WRITE(V3) //  Variable del modo LAMPARA UV (auto, manual on, off )
{
  modo_uv = param.asInt(); 
  Serial.println("V3 modo_uv value is: " + String(modo_uv));
}

  BLYNK_WRITE(V4) //  Variable del modo relleno
{
  modo_relleno = param.asInt(); 
  Serial.println("V4 modo relleno value is: " + String(modo_relleno));
}

  BLYNK_WRITE(V5) //  Variable del modo comedero
{
  bool modo_comedero = param.asInt(); 
  Serial.println("V5 modo comedero value is: " + String(modo_comedero));
}

 WidgetLED led1(V10);  // esta funcionando la bomba de relleno
 WidgetLED led2(V11);  // esta funcionando el ventilador 
 WidgetLED led3(V12);  // esta funcionando el calentador
 WidgetLED led4(V13);  // esta funcionando lamp UV
 WidgetLED led5(V14);  // esta funcionando el aireador
 WidgetLED led6(V15);  // esta funcionando el CO2
 WidgetLED led7(V16);  // deposito agua vacio
 WidgetLED led8(V17);  // temp agua fuera de valores maximos
 
  BLYNK_WRITE(V30) //Obtenemos el estado del  aireador en HIGH si está dentro del temporizador encendido
{
  if(param.asInt() == 1) {
    Serial.println("pulsa boton a comer"); 
    a_comer();  
  }  
}

BLYNK_WRITE(V31) {  // Asignamos a Peristaltica 1 hora de incio y fin
  TimeInputParam t(param);
  peris1STHour = t.getStartHour();
  peris1STMin = t.getStartMinute();
  peris1STSec = t.getStartSecond();
  peris1FNSec = t.getStopSecond();

  Serial.println(String("Start peris 1: ") + t.getStartHour() + ":" + t.getStartMinute() + ":" + t.getStartSecond()); 
  Serial.println(String("End peris 1: ") + t.getStopHour() + ":" + t.getStopMinute() + ":" + t.getStopSecond());

  int dayadjustment = -1;
  if (weekday() == 1) {
    dayadjustment = 6;
  }
    
  if (t.isWeekdaySelected((weekday() + dayadjustment))) {
    //Schedule is ACTIVE today
      //led1.on();  // turn on virtual LED
      peris1_today = true;
      Serial.println("peris1 today = true :)");
    }
    else {
     // led1.off();  // turn on virtual LED
      peris1_today = false;
      Serial.println("peris1 today = false :(");
  }
}

BLYNK_WRITE(V32) {  // Asignamos a Peristaltica 2 hora de incio y fin
  TimeInputParam t(param);
  peris2STHour = t.getStartHour();
  peris2STMin = t.getStartMinute();
  peris2STSec = t.getStartSecond();
  peris2FNSec = t.getStopSecond();

  Serial.println(String("Start peris 2: ") + t.getStartHour() + ":" + t.getStartMinute() + ":" + t.getStartSecond()); 
  Serial.println(String("End peris 2: ") + t.getStopHour() + ":" + t.getStopMinute() + ":" + t.getStopSecond());

  int dayadjustment = -1;
  if (weekday() == 1) {
    dayadjustment = 6;
  }
    
  if (t.isWeekdaySelected((weekday() + dayadjustment))) {
    //Schedule is ACTIVE today
      //led1.on();  // turn on virtual LED
      peris2_today = true;
      Serial.println("peris2 today = true :)");
    }
    else {
     // led1.off();  // turn on virtual LED
      peris2_today = false;
      Serial.println("peris2 today = false :(");
  }
}

  BLYNK_WRITE(V40) //Obtenemos el estado del  aireador en HIGH si está dentro del temporizador encendido
{
  int temp_ai_blynk = param.asInt(); 
  Serial.println("V40 modo_TEMP_ai value is: "+String(temp_ai_blynk));
  temp_ai=temp_ai_blynk;
  
}

  BLYNK_WRITE(V41) //Obtenemos el estado de la lamp uv en HIGH si está dentro del temporizador encendido
{
  int temp_uv_blynk = param.asInt(); 
  Serial.println("V41 modo_TEMP uv value is: "+String(temp_uv_blynk));
  temp_uv=temp_uv_blynk;
  
}

BLYNK_WRITE(V43) {  // Asignamos al TIME INPUT WIDGET 1 el comedero
  TimeInputParam t(param);
 
  Serial.println(String("Start Comedero: ") + t.getStartHour() + ":" + t.getStartMinute() + ":" + t.getStartSecond());

  SThour = t.getStartHour();
  STmin = t.getStartMinute();
  int dayadjustment = -1;
  if (weekday() == 1) {
    dayadjustment = 6;
  }
    
  if (t.isWeekdaySelected((weekday() + dayadjustment))) {
    //Schedule is ACTIVE today
      //led1.on();  // turn on virtual LED
      feed_today = true;
      Serial.println("feed today = true :)");
    }
    else {
     // led1.off();  // turn on virtual LED
      feed_today = false;
      Serial.println("feed today = false :(");
  }
}


////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//Establecemos los PIN de los sensores de temperatura
///////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////


OneWire OneWireBus(sensores_temp);      //Sensores de temperatura conectados al pin 22.
DallasTemperature sensors(&OneWireBus);
DeviceAddress sensor_agua, sensor_habitacion;
//DeviceAddress sensor_agua= {0x28, 0x10, 0x32, 0x2B, 0x04, 0x00, 0x00, 0x38 }; // Es necesario cambiar este valor acorde con nuestro sensor.
//DeviceAddress sensor_disipador = {0x28, 0x99, 0x47, 0x2B, 0x04, 0x00, 0x00, 0xFB }; // Es necesario cambiar este valor acorde con nuestro sensor.
//DeviceAddress sensor_habitacion = {0x28, 0x6D, 0x70, 0x2B, 0x04, 0x00, 0x00, 0x80 }; // Es necesario cambiar este valor acorde con nuestro sensor.


////////////////////////////////////////////////////////////////
//  servo
////////////////////////////////////////////////////////////////
Servo servo1;

////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////
//  pantalla
//
// Constructor especifico para el display utilizado
// =================================================

U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

// enlace donde aparecen todas las fuentes https://github.com/olikraus/u8glib/wiki/fontsize

/*
/////////////////////////////////////////////////////////////////
// Variables de la sonda de PH
/////////////////////////////////////////////////////////////////
#define SensorPin A0            //pH meter Analog output to Arduino Analog Input 0
#define Offset 0.00            //deviation compensate
#define LED 13
#define samplingInterval 20
#define printInterval 800
#define ArrayLenth  40    //times of collection
int pHArray[ArrayLenth];   //Store the average value of the sensor feedback
int pHArrayIndex=0;    
static float pHValue;
*/
