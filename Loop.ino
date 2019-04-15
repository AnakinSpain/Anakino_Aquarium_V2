////////////////////////////////////////////////////////////////
// VOID LOOP
///////////////////////////////////////////////////////////////
void loop() {
        
        timer.run();
        Blynk.run();        // Aplicacion Blynk     
    
   contador_global ++;  //   Serial.print(contador_global);
   if (contador_global == 10) {
    
    pHmeter();
    check_ventilador();  // Comprueba si activa ventilador
    check_calentador();  // Comprueba si activa el calentador
    check_UV();           // Comprobamos horario para encender UV
    check_ai();           // Comprobamos horario para encender AIREADOR
    getDHT();            // lee sensor dth    
  //  tweeter();           // envia tweet si está conectado.

    // ############## Inicio "picture loop" ####### 
     u8g2.firstPage(); 
     do { 
      draw();
     } while( u8g2.nextPage() ); 
   // ############## Fin "picture loop" ########## 
  
    contador_global = 0;  
   }
    
    peris();             // comprueba peristalticas
    check_temp();        // Comprueba valores temperatura
    check_nivel_acu();       // Comprobamos el nivel del agua del acuario
    
  if (Blynk.connected() == false){
   reconnect();
   }  
}
////////////////////////////////////////////////////////////////
// FIN DEL LOOP
///////////////////////////////////////////////////////////////

