////////////////////////////////////////////////////////////////
// VOID SETUP
///////////////////////////////////////////////////////////////
void setup() {
  
  // Debug console
  Serial.begin(9600);
  delay(10); 
  
  // Set ESP8266 baud rate;
  EspSerial.begin(ESP8266_BAUD);
  delay(10);

  u8g2.begin();// iniciamos la pantalla
  
 pant_inicio();

   
  // Connect to Wi-Fi network with SSID and password
   Blynk.begin(auth, wifi, ssid, pass);
  // Blynk.begin(auth, wifi, ssid, pass, "192,168,1,12"); // acceso al servidor de la raspberry pi
   Blynk.notify("Conectado!"); 
   
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 8442);
  
 
    
  timer.setInterval(120000L, SendToThingspeak);  // envia dato cada 2 minuto a thingspeak
  timer.setInterval(30000L, blynk); //timer will run every 30 sec a blynk
  timer.setInterval(14000L, feeder);  // Update feeder Check every 14 seconds
 // timer.setInterval(14000L, check_1); //timer will run every 35 sec
 // timer.setInterval(6000L, check_2); //timer will run every 6 sec 


  
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
  
  pinMode(led_rojo, OUTPUT);   // LED aviso rojo
  
  servo1.attach(servoPin);


////////////////////////////////////////
////////Con esto apagamos todos los reles. 
/////////////////////////////////////////

  digitalWrite(calentador,LOW);
  digitalWrite(aireador,LOW);
  digitalWrite(lamp_uv,LOW);
  digitalWrite(luz,LOW);
 
  
////////////////////////////////////////
// LLAMAMOS A LOS SENSORES DE LA TEMPERATURA
////////////////////////////////////////

  dht.begin();  // inicia sensor dht

  sensors.begin();     //Inicia las lecturas de las sondas de temperatura.
  if (!sensors.getAddress(sensor_agua, 0)) Serial.println("Falta el sensores de temperatura del agua");
  if (!sensors.getAddress(sensor_disipador, 1)) Serial.println("Falta el sensores de temperatura de la tapa");
  if (!sensors.getAddress(sensor_habitacion, 2)) Serial.println("Falta el sensores de temperatura de la habitacion");
  
  
  sensors.setResolution(sensor_agua, 12); // Define la resolucion en 10 bits.
  sensors.setResolution(sensor_habitacion, 12); // Define la resolucion en 10 bits.
  sensors.setResolution(sensor_disipador, 12); // Define la resolucion en 10 bits.

  
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

