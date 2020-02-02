////////////////////////////////////////////////////////////////
// VOID LOOP
///////////////////////////////////////////////////////////////
void loop() {
        
        timer.run();
        Blynk.run();        // Aplicacion Blynk    
         
   #ifdef CONTADOR 
   contador_1 ++;  //   Serial.print(contador_global);
   if (contador_1 == 20) {
    Serial.println("contador 20");
    check_temp();        // Comprueba valores temperatura
   }
       if (contador_1 == 40) {
    Serial.println("contador 40");    
    check_ventilador();  // Comprueba si activa ventilador
       }
       if (contador_1 == 60) {
    Serial.println("contador 60");    
    check_calentador();  // Comprueba si activa el calentador
    check_UV();          // Comprobamos horario para encender UV
    check_ai();          // Comprobamos horario para encender AIREADOR
       }
       if (contador_1 == 100) {
    Serial.println("contador 100 y 0");       
    blynk();             // Envia datos a Blynk

    // ############## Inicio "picture loop" ####### 
     u8g2.firstPage(); 
     do { 
      draw();
     } while( u8g2.nextPage() ); 
   // ############## Fin "picture loop" ########## 
  
    contador_1 = 0;  
   }
   #endif
    
  //  peris();             // comprueba peristalticas
    check_nivel_acu();   // Comprobamos el nivel del agua del acuario
    
  if (Blynk.connected() == false){
   reconnect();
   }  
}
////////////////////////////////////////////////////////////////
// FIN DEL LOOP
///////////////////////////////////////////////////////////////
