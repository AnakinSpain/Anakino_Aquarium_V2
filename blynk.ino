////////////////////////////////////////////////////////////////
// Funcion variable blynk
////////////////////////////////////////////////////////////////
void blynk(){
  Blynk.virtualWrite(V20, temp_agua); // envia la temp al widget agua
  Blynk.virtualWrite(V21, tempHB); // envia la temp al widget habitacion
  Blynk.virtualWrite(V22, tempD); // envia la temp al widget 
  Blynk.virtualWrite(V24, humedad);
  Blynk.virtualWrite(V25, tempdht);
  Serial.println("Envia datos a blynk." + String(hour()) + ":" + String(minute()) + ":" + String(second()));
}




