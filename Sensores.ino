
/////////////////////////////////////////////////////////////////
// Controlamos las temperaturas para 
// activar o desactivar calentador y ventiladores
/////////////////////////////////////////////////////////////////
void check_temp(){
  #ifdef DEBUG
  Serial.println("check temp");
  #endif  
  sensors.requestTemperatures();   // call sensors.requestTemperatures() to issue a global 
  // temperature request to all devices on the bus

 temp_agua_inst = (sensors.getTempC(sensor_agua));        // lee temp del agua
 temp_habit_inst = (sensors. getTempC(sensor_habitacion));// lee temp de la habitacion
 //temp_disp_inst = (sensors.getTempC(sensor_disipador));   // lee temp del disipador

 if (temp_agua_inst != -127 && temp_habit_inst != -127) 

 {
  contador_temp ++;                       // LEE LOS VALORES DE LAS TEMPERATURAS
  temperatura_agua_temp += temp_agua_inst;  
  temperatura_habitacion_temp += temp_habit_inst; 
      
  #ifdef DEBUG 
  Serial.println("temperatura instantánea= " + String(temp_agua_inst) + " Temp. acumulada= "+ String(temperatura_agua_temp));
  #endif
 }

 
  if(contador_temp == 10)
  {
    temp_agua = temperatura_agua_temp / 10; Serial.println("Temperatura media: "+ String(temp_agua));
    tempHB = temperatura_habitacion_temp / 10;
   
    contador_temp = 0;  
    temperatura_agua_temp = 0;    
    temperatura_habitacion_temp = 0;
    temp_agua_inst = 0;
    temp_habit_inst = 0;
    
  }
                                        
}                                      // ACTUA EN FUNCION DE LOS VALORES DE LA TEMPERATURA

 void check_calentador(){
  #ifdef DEBUG
  Serial.println("check calentador");
  #endif
  
    if (temp_agua > temp_agua_des + temp_margen || temp_agua< temp_agua_des - temp_margen)  {
      led8.on();
      alarma_activa =true;
      } 
      else { 
        led8.off();
        alarma_activa = false;
        }

   
    if (temp_agua != -127 && temp_agua != 85 && temp_agua != 0){
     
      if (temp_agua <= temp_agua_des-temp_margen){
        digitalWrite(calentador,HIGH); // Encendemos Calentador
        led3.on();
   //     Serial.print("Enciende calentador: "); Serial.print(temp_agua); Serial.print(" "); Serial.println(temp_agua_des-temperatura_margen); 
       }
       
      if (temp_agua >= temp_agua_des+temp_margen){
        digitalWrite(calentador,LOW); // Apagamos Calentador
        led3.off();
   //     Serial.print("Apaga calentador"+ String(temp_agua) +"Temp agua + margen= " + String(temp_agua_des+temperatura_margen));
      }
            
    }
    else
    {
      digitalWrite(calentador,LOW); // Apagamos Calentador
      led3.off();
    }
    
}


void pHytds(){
/////////////////////////////////////////////////////////////////
// Sensor pH
/////////////////////////////////////////////////////////////////
//void pHmeter (){
  
  int buf[10];                //buffer for read analog
  for(int i=0;i<10;i++)       //Get 10 sample value from the sensor for smooth the value
  { 
    buf[i]=analogRead(sensor_ph);
    delay(10);
  }
  for(int i=0;i<9;i++)        //sort the analog from small to large
  {
    for(int j=i+1;j<10;j++)
    {
      if(buf[i]>buf[j])
      {
        int temp=buf[i];
        buf[i]=buf[j];
        buf[j]=temp;
      }
    }
  }
  avgValue=0;
  for(int i=2;i<8;i++)                      //take the average value of 6 center sample
    avgValue+=buf[i];
  phValue=(float)avgValue*5.0/1024/6; //convert the analog into millivolt
  phValue=3.5*phValue+Offset;                      //convert the millivolt into pH value
  #ifdef DEBUG
  Serial.print("pH: ");  
  Serial.print(phValue,2);
  Serial.println(" "); 
  #endif
//}

/////////////////////////////////////////////////////////////////
// Sensor TDS
/////////////////////////////////////////////////////////////////

//void TDSmeter(){
  
    temperature = (sensors.getTempC(sensor_agua));  //add your temperature sensor and read it
    gravityTds.setTemperature(temperature);  // set the temperature and execute temperature compensation
    gravityTds.update();  //sample and calculate 
    tdsValue = gravityTds.getTdsValue();  // then get the value
    #ifdef DEBUG
    Serial.print("ppm: ");
    Serial.println(tdsValue,0);
    #endif
//}
}
