
/////////////////////////////////////////////////////////////////
// Controlamos Sensor de agua 
// activar o desactivar bomba de relleno
////////////////////////////////////////////////////////////////

void check_nivel_acu(){
   if (digitalRead(nivel_dep) == true) {
    led7.off(); // apaga led deposito agua vacio
    if (modo_relleno == 1)
      {
     // Serial.print("modo rellenador activado");
     //  Serial.println("");
      
      if (digitalRead(nivel_acu) != 1) // Si la lectura del sensor del nivel acuario indica que esta bajo
      {
      digitalWrite(bomba, LOW);     // desactiva la bomba
      led1.off();
  //   Serial.print("desactiva bomba");
  //   Serial.println("");
      }
   else  
   {
   digitalWrite(bomba, HIGH);
   led1.on();
 //  Serial.print("activa bomba");
 //  Serial.println("");
   }
  } 
   }
else {
  digitalWrite(bomba, LOW); // paramos la bomba si no hay agua
 // bitWrite(alarma, 3,1); // indicamos que debe activarse la alarma de deposito de agua vacio.
  led7.on();  // enciende led deposito agua vacio
  alarma_activa =true;
}
} 
/////////////////////////////////////////////////////////////////
//Fin controlNivel acuario
/////////////////////////////////////////////////////////////////
