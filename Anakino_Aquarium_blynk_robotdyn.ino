

///////////////////////////////////////////////////////////////
//
//
//
//
//     CONTROLADOR DE ACUARIO CON LA APP BLYNK 
//     
//     V1.0 
//     PLACA RobotDyn Mega + wifi
//     
//     TO DO: 1) Añadir opcion de luces auto, man on o man off y controladas por el arduino
//            2) Añadir comedero
//            3) Añadir los pines para los reles. segun ya tengo conectado
//            4) Añadir led verde o rojo segun si está online o no
///////////////////////////////////////////////////////////////
// Para subir Código Switch:
//  
// 3- ON 
// 4- ON
// RXD0 x TXD0
//
///////////////////////////////////////////////////////////////
// Para ejecutar código en la placa:
// 
// 1- ON
// 2- ON 
// 3- ON 
// 4- ON
// RXD3 x TXD3
//
///////////////////////////////////////////////////////////////
//
//
///////////////////////////////////////////////////////////////
//Listado de PINs utilizados
///////////////////////////////////////////////////////////////


//        Ventilador agua  2   (PWM) Refrigerador agua
//        Ventilador pant  3   (PWM) Ventilador pantalla
//        Leds blancos     4   (PWM) led blancos
//        Leds Azules      5   (PWM) led azules        
//        Sondas temp.     22   
//        Boya nivel agua  23  
//                             
//        Bomba  relleno   24  (Salida 12v)
//        Calentador       25  (Rele)
//        Aireador         26  (Rele)
//        Lampara UV       27  (Rele)
//        CO2              28  (Rele)
//        rele  1          29  (Rele)
//        rele  2          30  (Rele)

//        Peristaltica 1   31
//        Sensor Ph        35 
//        Servo comedero   36  (Servo)
//        Humedad y tempH  37  (DHT22)
//        Pin Libre        35

/////// PUERTOS VIRTUALES BLYNK /////
//                            
//        V1       Modo Airador
//        V2       Modo lamp UV
//        V10      Aviso rellenador funcionando
//        V11      Aviso calentador funcionando
//        V12      Aviso ventilador funcionando
//        V20      temp de agua
//        V21      temp habitacion
//        V22      temp pantalla
//        V23      Asigna valor a la temp. del acuario desde blynk
//        V24      variable en el que irá la humedad
//        V25      variable temperatura habitacion por el dht22
//        V30      boton de Rellenador ON / OFF
//        V40      Disparador del temporizador del aireador (temporizadores)
//        V41      Disparador del temporizador de la Lamp UV (temporizadores)
//        
//       
///////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////
//
//

 
// 
//
////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
//Librerias necesarias
///////////////////////////////////////////////////////////////


#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>
#include <SPI.h>
#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Servo.h>
#include "ThingSpeak.h"
#include <WidgetRTC.h>
#include <DHT.h>



#define BLYNK_PRINT Serial

// Hardware Serial on Mega, Leonardo, Micro...
#define EspSerial Serial3

// Your ESP8266 baud rate:
#define ESP8266_BAUD 115200

ESP8266 wifi(&EspSerial);


////////////////////////////////////////////////////////////////////////
//VALORES QUE SE PUEDEN CAMBIAR AL GUSTO
////////////////////////////////////////////////////////////////////////

#define temperatura_margen  0.5    // Margen de actuacion del calentador

////////////////////////////////////////////////////////////////////////
//VARIABLES DE PWM
////////////////////////////////////////////////////////////////////////

int pwm_vent;  // variable que llevará el valor del pwm de 0 a 255

////////////////////////////////////////////////////////////////////////
//CONFIGURACION WIFI
////////////////////////////////////////////////////////////////////////

                                // Do not change this line
  char ssid[] = "atorcha";
  char pass[] = "X55-mCx-DVL-kF4";


////////////////////////////////////////////////////////////////////////
//DECLARACION DE VARIABLES de THINGSPEAK
////////////////////////////////////////////////////////////////////////
 unsigned long myChannelNumber = 358672;
 const char * myWriteAPIKey = "K6GT1NEIV57XGXIL";
 long previous_Millis_datos = 0;

////////////////////////////////////////////////////////////////////////
//DECLARACION DE VARIABLES Y PINES
////////////////////////////////////////////////////////////////////////

#define DHTTYPE DHT22   // DHT 22  (AM2302)


////////////////////////////////////////////////////////////////
// Definimos los pines 
////////////////////////////////////////////////////////////////

#define vent_agua   2    // PWM Ventilador agua pin 2
#define vent_pant   3    // PWM Ventilador pantalla pin 3
#define luz         4    // PWM Luz blanca
#define luz_azul    5    // PWM leds azules noche

#define nivel_acu  23   // Boya nivel agua acuario
#define bomba      24   // Pin accionara la bomba de llenado 

#define calentador 25   // Calentador             
#define aireador   26   // Aireador    
#define lamp_uv    27   // Lampara UV
#define CO2        28   // Pin que activa el CO2
#define rele1      29   // rele libre
#define rele2      30   // rele libre

#define peris1     31   // peristáltica 1
#define sensor_ph  35   // sensor de pH
#define servoPin   36   // servo comedero
#define DHTPIN     37   // Sensor dht22 Pin humedad y temp habitacion

#define led_verde  40   // pin led verde
#define led_rojo   41   // pin led de aviso rojo






////////////////////////////////////////////////////////////////
//*********************** Variables de control de temperatura del agua ********************
// Preparamos otras variable

DHT dht(DHTPIN, DHTTYPE);

float temp_agua;             //Temperatura del agua
float temp_agua_des;         //temperatura agua deseada
int contador_temp = 0;
int contador_med_temp = 0;
float temperatura_agua_temp; // Temperatura temporal del agua
int contador_global = 0;

float temp_agua_inst;
float temp_habit_inst;
float temp_disp_inst;
 
//float tempHB;    //Temperatura de la habitacion
float temp2_temp;  //temperatura temporal sistema

float temperatura_disipador_temp; // Temperatura temporal del disipador
float temperatura_habitacion_temp; // temperatura temporal de la habitacion
    
 float tempD = 0;     // Temperatura del disipador
 float tempHB = 0;    // Temperatura habitacion
 float humedad = 0;   // Variable humedad
 float tempdht = 0;   // temperatura del dht22

 
//////////////////////////////////////////////////////////////
//************ Variables rellenador


 int nivel_estado = 1;

/*
float PinSensor = 30; //Sensor de nivel de agua en el pin 30
int VarSensor = 0;  //Control del nivel de agua
int floatPin = 31;  //Boya de nivel del depósito de relleno
*/
/////////////////////////////////////////////////
// Preparamos  modos de funcionamiento

int modo_relleno; // Rellenador 1 -> activado // 0-> desactivado
int modo_uv;      // modo de funcionamiento uv
int modo_ai;      // modo de funcionamiento aireador

int temp_uv;    // Variable para indicar si activa o no la lamp uv desde blynk por el temporizador
int temp_ai;    // Variable para indicar si activa o no el aireador desde blynk por el temporizador


/////////////////////////////////////////////////////////////////
//Blynk
////////////////////////////////////////////////////////////////
char auth[] = "86031b9fe3584a26b84640052eced136";

BlynkTimer timer;

WidgetRTC rtc;

bool tweet_enviado = false;

bool isConnected;


  BLYNK_CONNECTED()     // This function will run every time Blynk connection is established
  {  
   Blynk.syncAll();  // Request Blynk server to re-send latest values for all pins
   rtc.begin();  // Synchronize time on connection
   }

    
  BLYNK_WRITE(V1) // Variable del modo AIREADOR (auto, manual on, off )
{
  int modo_ai_blynk = param.asInt(); 
  Serial.println("V1 modo_ai value is: "+ String(modo_ai_blynk));
  modo_ai=modo_ai_blynk;
}

  BLYNK_WRITE(V2) //  Variable del modo LAMPARA UV (auto, manual on, off )
{
  int modo_uv_blynk = param.asInt(); 
  Serial.println("V2 modo_uv value is: " + String(modo_uv_blynk));
  modo_uv=modo_uv_blynk;
}
 WidgetLED led1(V10);  // estado de la bomba de relleno
 WidgetLED led2(V11);  // estado del calentador
 WidgetLED led3(V12);  // estado del ventilador
 

  BLYNK_WRITE(V23)  // variable de la temperatura del agua deseada
{
  float temp_agua_des_blynk = param.asFloat(); // Asigna un valor a la variable temp_agua_des desde el slider de la app
  Serial.println("Temp Deseada blynk: " + String(temp_agua_des_blynk));
  temp_agua_des = (temp_agua_des_blynk);
}

  BLYNK_WRITE(V30) // Modo del rellenador On u off 
{
  int modo_relleno_blynk = param.asInt(); 
  Serial.println("V30 modo_relleno value is: "+ String(modo_relleno_blynk));
  modo_relleno=modo_relleno_blynk;
}

  BLYNK_WRITE(V40) //Obtenemos el estado del  aireador en HIGH si está dentro del temporizador encendido
{
  int temp_ai_blynk = param.asInt(); 
  Serial.println("V40 modo_ai value is: "+String(temp_ai_blynk));
  temp_ai=temp_ai_blynk;
  
}

  BLYNK_WRITE(V41) //Obtenemos el estado de la lamp uv en HIGH si está dentro del temporizador encendido
{
  int temp_uv_blynk = param.asInt(); 
  Serial.println("V41 modo_temp uv value is: "+String(temp_uv_blynk));
  temp_uv=temp_uv_blynk;
  
}
 

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//Establecemos los PIN de los sensores de temperatura
///////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////


OneWire OneWireBus(22);      //Sensores de temperatura conectados al pin 22.
DallasTemperature sensors(&OneWireBus);
DeviceAddress sensor_agua, sensor_habitacion, sensor_disipador;
//DeviceAddress sensor_agua= {0x28, 0x10, 0x32, 0x2B, 0x04, 0x00, 0x00, 0x38 }; // Es necesario cambiar este valor acorde con nuestro sensor.
//DeviceAddress sensor_disipador = {0x28, 0x99, 0x47, 0x2B, 0x04, 0x00, 0x00, 0xFB }; // Es necesario cambiar este valor acorde con nuestro sensor.
//DeviceAddress sensor_habitacion = {0x28, 0x6D, 0x70, 0x2B, 0x04, 0x00, 0x00, 0x80 }; // Es necesario cambiar este valor acorde con nuestro sensor.


////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//  servo
///////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
Servo servo1;



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

