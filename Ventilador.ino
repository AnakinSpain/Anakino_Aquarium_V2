void check_ventilador(){
  
  int pwm_vent;  // variable que llevará el valor del pwm de 0 a 255
  const int temp_min_vent = temp_agua_des + 1; // Serial.println("Temp min vent: "+String(temp_min_vent));
  const int temp_max_vent = temp_agua_des + 4; //Serial.println("Temp max vent: "+String(temp_max_vent));

  int tempval = int(temp_agua*10);
  pwm_vent = map(tempval, (temp_min_vent*10), (temp_max_vent*10),0,255);
    
  if (pwm_vent < 0) { pwm_vent =0; }
  if (pwm_vent > 255) { pwm_vent =255; }
  
  percent_vent =map(pwm_vent,0,255,0,100);
   
  if (temp_agua > temp_min_vent)
  {
    Serial.println("Ventilador a: " + String (pwm_vent));
    led2.on();
  }
  else
  {
    led2.off();
  }
}

