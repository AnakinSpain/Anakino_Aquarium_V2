////////////////////////////////////////////////////////////////
// Funcion variable blynk Escribe valores en los pines virtuales
////////////////////////////////////////////////////////////////
void blynk(){
  Blynk.virtualWrite(V20, temp_agua); // envia la temp al widget agua
  // Blynk.virtualWrite(V21, tempHB); // envia la temp al widget habitacion
  Blynk.virtualWrite(V22, tempD); // envia la temp pantalla leds al widget 
  Blynk.virtualWrite(V23, percent_vent); // envia el tanto por ciento al que están los ventiladores
//  Blynk.virtualWrite(V24, humedad);
  Blynk.virtualWrite(V25, tempdht); // envia la temperatura del dht de la habitacion
  Blynk.virtualWrite(V26, phValue,2); // envia la temperatura del dht de la habitacion
 // Serial.println("Envia datos a blynk.  " + String(hour()) + ":" + String(minute()) + ":" + String(second()));
}


/////////////////////////////////////////////////
// FUNCION PARA THINGSPEAK
////////////////////////////////////////////////

void SendToThingspeak(void){
  
  // Serial.println("Envia datos a thingspeak.");    //Test thingspeak
   Blynk.virtualWrite(V0, humedad, tempdht, temp_agua);

}


/////////////////////////////////////////////////
// FUNCION PARA TWITTER
////////////////////////////////////////////////

void tweeter(){
  if (tweet_enviado == false){
  Serial.println("Envía tweet"); 
  Blynk.tweet("Estoy online " + String(hour()) + ":" + String(minute()) + ":" + String(second()) + " " + String(day()) +"/" + String(month()) + "/" + String(year()) + " www.atorcha.es");
  tweet_enviado = true;
  }
}


/////////////////////////////////////////////////
// FUNCION PARA RECONECTAR
////////////////////////////////////////////////

void reconnect()
{
       // ############## Inicio "pantalla error" ####### 
     u8g2.firstPage(); 
     do { 
      p_error();
     } while( u8g2.nextPage() ); 
    // ############## Fin "pantalla error" ########## 
    
  //  Blynk.tweet("Pierde conexion y reconecta www.atorcha.es");
    tweet_enviado = false;  
  //  Serial.println(isConnected);
   
 
    // Timed Lambda Function - 
     timer.setTimeout(10000L, []() {  // Run every 10 seconds
      
     Serial.println("Envia blynk.connect... ");
     Blynk.connect();
      });
}
/////////////////////////////////////////////////
// FUNCION PARA sincronizar
////////////////////////////////////////////////


void BlynkSyncAllHack() {  // Slow but stable SyncAll hack
  for (Vcount = 0; Vcount <= 127; Vcount++) {  // Count from 0 to 127
    Blynk.syncVirtual(Vcount);  // Generate a vPin sync for each count
    delay(5);  // Small delay to allow "spacing" between each vPin sync
    Blynk.run();  // Just keeps Blynk running
  }
}
