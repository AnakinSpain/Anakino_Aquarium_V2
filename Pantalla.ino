void pant_inicio(){
      // ############## PANTALLA DE ARRANQUE ####### 
 u8g2.firstPage();  
 do {
  u8g2.setFont(u8g_font_courR14); 
  u8g2.drawStr( 5, 33, "Iniciando...");
  u8g2.setFont(u8g2_font_nine_by_five_nbp_tr);
  u8g2.drawStr( 5, 50, "anakino_aquarium_v2");
    
  } 
  while( u8g2.nextPage() ); 
   // ############## Fin "picture loop" ########## 
}


void draw(void) {

 u8g2.setFont(u8g_font_8x13);
 u8g2.drawStr( 5, 15, "Temp:"); // 
 u8g2.setCursor(48, 15);
 u8g2.print(tempdht); 
 u8g2.drawStr( 93, 15, "C");

 u8g2.drawLine(0, 18, 127, 18); // linea separacion

 
// u8g2.drawLine(0, 36, 127, 36); // linea separacion

 u8g2.drawLine(0, 50, 127, 50); // linea separacion

 
 u8g2.drawStr( 1, 63, "Estado:");
 
  if (alarma_activa = false) {
   u8g2.drawStr( 58, 63, "OK");
   digitalWrite(led_rojo, LOW);
 }
else
{
   u8g2.drawStr( 58, 63, "Alarma"); 
   digitalWrite(led_rojo, HIGH);  
 }

 u8g2.drawLine(120, 50, 120, 64); // linea separacion
 u8g2.setCursor(122, 62);
 u8g2.print(ver);

}

/////////////////////////////////////////////////////////////////

void p_error(void) {

 u8g2.setFont(u8g_font_unifont);
 u8g2.drawStr( 5, 40, "Desconectado "); 
}
