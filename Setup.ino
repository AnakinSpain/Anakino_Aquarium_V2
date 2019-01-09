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
/*  
  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 */ 
   Blynk.begin(auth, wifi, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 8442);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8442);


  Serial.println("WiFi connected ");
  Serial.print("IP address: ");
  Blynk.tweet("My Arduino project is tweeting using @blynk_app and it’s awesome!\n #arduino #IoT #blynk");
  
 // ThingSpeak.begin(client);
  
//Asignamos los distintos PIN

  pinMode(vent_agua, OUTPUT);  // ventilador del agua
  pinMode(vent_pant, OUTPUT);  // ventilador del agua 
  pinMode(luz, OUTPUT);
  pinMode(luz_azul, OUTPUT);
  pinMode(nivel_acu, INPUT);   // Indicamos el puerto de control de la boya del acuario
  pinMode(bomba, OUTPUT);      // Bomba rellenador
  pinMode(calentador, OUTPUT); // Calentador     
  pinMode(aireador, OUTPUT);   // Aireador
  pinMode(lamp_uv, OUTPUT);    // Lampara UV
  pinMode(CO2, OUTPUT);        // Salida CO2      
  pinMode(rele1, OUTPUT);      // rele 1
  pinMode(rele2, OUTPUT);      // rele2  
  
  pinMode(led_verde, OUTPUT);  // LED aviso verde 
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

  //////////////////////////////
  
  Serial.println("Test the serial monitor!");    //Test the serial monitor
}

/////////////////////////////////////////////////
// FUNCION PARA RELES CHINO QUE VAN AL CONTRARIO
/////////////////////////////////////////////////
void SetRele( int Pin, boolean Estado )  //Funcion que hace que el rele chino funcione bien y se puede poner LOW o HIGH segun corresponda.
{
 
 digitalWrite( Pin, Estado );

}

////////////////////////////////////////////////////////////////
// FIN DEL SETUP
///////////////////////////////////////////////////////////////

