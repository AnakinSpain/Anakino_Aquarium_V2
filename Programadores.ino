
/////////////////////////////////////////////////////////////////
// control funcionamiento del aireador
/////////////////////////////////////////////////////////////////
void check_ai(){

      
      if (modo_ai == 1)     
      {       
        if (temp_ai == 1 )
        {      
     //   Serial.println(" AI Auto ON");
        digitalWrite(aireador,HIGH); //activa rele 
        led5.on();
        }
      else if (temp_ai == 0)
      {        
    //    Serial.println("AI Auto OFF");
        digitalWrite(aireador,LOW); //desactiva rele
        led5.off();
      }
    }
      
   else if (modo_ai == 2)
    {
 //   Serial.println("AI Manual ON");  
    digitalWrite(aireador,HIGH); // Encendemos  ai, 
    led5.on();
    }
    else if   
      (modo_ai == 3){
  //    Serial.println("AI Manual OFF");  
      digitalWrite(aireador,LOW); // Apagamos  ai, 
      led5.off();
      
    }    
   }

/////////////////////////////////////////////////////////////////
//LUZ_UV
/////////////////////////////////////////////////////////////////

void check_UV(){

       
      if (modo_uv == 1){       // si esta configurado el modo automatico
        
       if (temp_uv == 1 )
       {
        digitalWrite(lamp_uv,HIGH); //activa rele
        led4.on();
  //      Serial.println("UV Auto ON");
      }
      if (temp_uv == 0 )
      {
        digitalWrite(lamp_uv,LOW); //desactiva rele
        led4.off();
   //     Serial.println("UV Auto OFF");
      }
    }

      

   else if (modo_uv == 2) // Modo manual ON
    {
      
    digitalWrite(lamp_uv,HIGH); // Encendemos luz UV, 
    led4.on();
 //   Serial.println("UV Manual ON ");
    }
    else if   
      (modo_uv == 3)   // Modo manual OFF
      {  
      digitalWrite(lamp_uv,LOW); // Apagamos luz UV
      led4.off();
   //   Serial.println("UV Manual OFF ");
    }
 
   }
 
/////////////////////////////////////////////////////////////////
//   Comprueba comedero y funcion a comer
/////////////////////////////////////////////////////////////////

void feeder() {  // call with timer every 14 seconds or so
  // Get RTC time
 /* 
  sprintf(currentTime, "%02d:%02d:%02d", hour(), minute(), second());
  Serial.print("Current Time: ");
  Serial.println(currentTime);

  // Get Time Input Widget time
  sprintf(startTime, "%02d:%02d:%02d", SThour, STmin, STsec);
  Serial.print("Feed Time: ");
  Serial.println(startTime);
*/

if (feed_today == true)
{
 if (hour() == SThour)
 {
    if (minute() == STmin) 
    {   // si la hora actual y el minuto actuales igual a la elegida inicio, pasa
        if (feeded == false) 
        {           
      //   Serial.println("Llama a la funcion <a comer>");
         a_comer(); 
         feeded = true;        
         }
    }
    
 else {
    feeded = false;
  //  Serial.println("Se prepara para la proxima vez");
   }
  }
 }
}



void a_comer(){
  
  Serial.println("A comer!!");
  for(int posDegrees = 0; posDegrees <= 180; posDegrees++) {       
        servo1.write(posDegrees);      
      //  delay(200);
    }
}

/////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////

