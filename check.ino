

void check_1(){
    Serial.println("Check_1." + String(hour()) + ":" + String(minute()) + ":" + String(second()));
    check_temp();        // Comprueba valores temperatura
    check_ventilador();  // Comprueba si activa ventilador
    check_calentador();  // Comprueba si activa el calentador
    check_UV();           // Comprobamos horario para encender UV
    check_ai();           // Comprobamos horario para encender AIREADOR
    getDHT();            // lee sensor dth
    tweeter();           // envia tweet si está conectado.

    // ############## Inicio "picture loop" ####### 
     u8g.firstPage(); 
     do { 
      draw();
     } while( u8g.nextPage() ); 
   // ############## Fin "picture loop" ########## 
  
}

void check_2(){
    Serial.println("Check_2");
    check_nivel();       // Comprobamos el nivel del agua 
}

/////////////////////////////////////////////////
// FUNCION PARA RECONECTAR
////////////////////////////////////////////////

void reconnect()
{
       // ############## Inicio "pantalla error" ####### 
     u8g.firstPage(); 
     do { 
      p_error();
     } while( u8g.nextPage() ); 
    // ############## Fin "pantalla error" ########## 
    
  //  Blynk.tweet("Pierde conexion y reconecta www.atorcha.es");
    tweet_enviado = false;  
  //  Serial.println(isConnected);
   
 
    // Timed Lambda Function - 
     timer.setTimeout(10000L, []() {  // Run every 10 seconds
      
     Serial.println("Envia blynk.connect... ");
     Blynk.connect();      
   //Blynk.begin(auth, wifi, ssid, pass);
    });
}

