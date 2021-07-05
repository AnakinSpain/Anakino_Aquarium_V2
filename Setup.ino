////////////////////////////////////////////////////////////////
// VOID SETUP
///////////////////////////////////////////////////////////////
void setup() {
  
  // Debug console
  Serial.begin(115200);
  delay(10); 
  
  // Set ESP8266 baud rate;
  EspSerial.begin(ESP8266_BAUD);
  delay(10);

  u8g2.begin();// iniciamos la pantalla
  
 pant_inicio();

   
  // Connect to Wi-Fi network with SSID and password
   Blynk.begin(auth, wifi, ssid, pass, "atorcha.asuscomm.com", 8080);
  // Blynk.begin(auth, wifi, ssid, pass, "192,168,1,12"); // acceso al servidor de la raspberry pi
   Blynk.logEvent("Conectado!"); 
   
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 8442);
  
 
    #ifdef NOCONTADOR
 // timer.setInterval(120000L, SendToThingspeak);  // envia dato cada 2 minuto a thingspeak
 // timer.setInterval(5000L, pHytds); // lee ph y tds cada 5 minutos
  timer.setInterval(5000L, blynk);               //envia datos a Blynk
  timer.setInterval(15000L, feeder);             // Update feeder Check every 14 seconds
  timer.setInterval(20000L, check_temp);        // Comprueba valores temperatura
  timer.setInterval(25000L, check_ventilador);  // Comprueba si activa ventilador
  timer.setInterval(30000L, check_calentador);  // Comprueba si activa el calentador
  timer.setInterval(35000L, check_UV);          // Comprobamos horario para encender UV
  timer.setInterval(40000L, check_ai);          // Comprobamos horario para encender AIREADOR
  #endif

  
//Asignamos los distintos PIN

  pinMode(vent_agua, OUTPUT);  // ventilador del agua
  pinMode(vent_pant, OUTPUT);  // ventilador del agua 
  pinMode(luz, OUTPUT);
  pinMode(luz_azul, OUTPUT);
  pinMode(nivel_acu, INPUT);   // Indicamos el puerto de control de la boya del acuario
  pinMode(nivel_dep, INPUT);   // lee el nivel deposito auxiliar agua
  pinMode(bomba, OUTPUT);      // Bomba rellenador
  pinMode(calentador, OUTPUT); // Calentador     
  pinMode(aireador, OUTPUT);   // Aireador
  pinMode(lamp_uv, OUTPUT);    // Lampara UV
  pinMode(CO2, OUTPUT);        // Salida CO2      
  pinMode(TdsSensorPin,INPUT);
  pinMode(sensor_ph, INPUT);
  
  pinMode(led_rojo, OUTPUT);   // LED aviso rojo
  
  servo1.attach(servoPin);


    gravityTds.setPin(TdsSensorPin);
    gravityTds.setAref(5.0);  //reference voltage on ADC, default 5.0V on Arduino UNO
    gravityTds.setAdcRange(1024);  //1024 for 10bit ADC;4096 for 12bit ADC
    gravityTds.begin();  //initialization

////////////////////////////////////////
////////Con esto apagamos todos los reles. 
/////////////////////////////////////////

  digitalWrite(calentador,LOW);
  digitalWrite(aireador,LOW);
  digitalWrite(lamp_uv,LOW);
  digitalWrite(CO2,LOW);
 
  
////////////////////////////////////////
// LLAMAMOS A LOS SENSORES DE LA TEMPERATURA
////////////////////////////////////////


  sensors.begin();     //Inicia las lecturas de las sondas de temperatura.
  if (!sensors.getAddress(sensor_agua, 0)) Serial.println("Falta el sensor de temperatura del agua");
  if (!sensors.getAddress(sensor_habitacion, 1)) Serial.println("Falta el sensor de temperatura de la habitacion");
  
  
  sensors.setResolution(sensor_agua, 12); // Define la resolucion en 10 bits.
  sensors.setResolution(sensor_habitacion, 12); // Define la resolucion en 10 bits.
  sensors.requestTemperatures();   // call sensors.requestTemperatures() to issue a global 
  temp_agua = (sensors.getTempC(sensor_agua));        // lee temp del agua
  tempHB = (sensors. getTempC(sensor_habitacion));// lee temp de la habitacion

  
  pHytds();
  
  Serial.println("Test the serial monitor!");    //Test the serial monitor

    // ############## Inicio "picture loop" ####### 
     u8g2.firstPage(); 
     do { 
      draw();
     } while( u8g2.nextPage() ); 
   // ############## Fin "picture loop" ########## 
}

/////////////////////////////////////////////////
// FUNCION PARA RELES CHINO QUE VAN AL CONTRARIO
/////////////////////////////////////////////////
/*
void SetRele( int Pin, boolean Estado )  //Funcion que hace que el rele chino funcione bien y se puede poner LOW o HIGH segun corresponda.
{
 
 digitalWrite( Pin, Estado );

}
*/
////////////////////////////////////////////////////////////////
// FIN DEL SETUP
///////////////////////////////////////////////////////////////
