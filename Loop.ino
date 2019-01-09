////////////////////////////////////////////////////////////////
// VOID LOOP
///////////////////////////////////////////////////////////////
void loop() {

    isConnected = Blynk.connected();
       if (isConnected){
        
    //////////////////////////
    // PARTE DEL LOOP QUE SOLO SE EJECUTARÁ CADA 10 VECES PARA NO SATURAR
    //////////////////////////
    analogWrite(led_verde,180);
    analogWrite(led_rojo,0);
    contador_global ++;  //   Serial.print(contador_global);
 
    
    if (contador_global == 10) {
 
    blynk();             // envia valores de las variables de arduino a blynk
    check_temp();        // Comprueba valores temperatura
    check_ventilador();  // Comprueba si activa ventilador
    check_calentador();  // Comprueba si activa el calentador
    getDHT();            // lee sensor dth
    tweeter();           // envia tweet si está conectado.
    contador_global = 0;
    }
    /////////////////////////////////////////////////////

    
    check_UV();          // Comprobamos horario para encender UV
    check_ai();           // Comprobamos horario para encender AIREADOR
    check_nivel();       // Comprobamos el nivel del agua
  //  envio_datos();       // Enviamos datos a thingspeak
    Blynk.run();        // Aplicacion Blynk
    timer.run();
         
     }
     
  else{
    analogWrite(led_rojo,200);
    analogWrite(led_verde,0);
    Serial.println(" Espero 10 segundos.");
    delay(10000);
    tweet_enviado = false;
    Serial.println(" Envia wifi begin y blynk.connect");
    Serial.println("Reconectado");
 //   WiFi.begin(ssid, pass);
    Blynk.connect();  
        
  }
}
////////////////////////////////////////////////////////////////
// FIN DEL LOOP
///////////////////////////////////////////////////////////////

