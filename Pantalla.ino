void draw(void) {

 u8g.setFont(u8g_font_unifont);
 u8g.drawStr( 5, 15, "Temp:"); // 
 u8g.setPrintPos(45, 15);
 u8g.print(tempdht); 
 u8g.drawStr( 90, 15, "ºC");

 u8g.drawLine(0, 18, 127, 18); // linea separacion

 u8g.drawStr( 5, 33, "Calentador: ");
 u8g.setPrintPos(45, 15);
 u8g.print(tempdht);
 
u8g.drawLine(0, 36, 127, 36); // linea separacion
 
 u8g.drawStr( 5, 53, "Funcionando "); 
 u8g.setPrintPos(45, 15);
 u8g.print(tempdht);

 u8g.drawLine(0, 56, 127, 56); // linea separacion
 
 u8g.setFont(u8g_font_5x7);
// u8g.setFont(u8g_font_9x15);
 u8g.drawStr( 25, 62, "www.atorcha.es"); 
}

void p_error(void) {

 u8g.setFont(u8g_font_unifont);
/*
 u8g.drawStr( 5, 15, "Temp:"); // 
 u8g.setPrintPos(45, 15);
 u8g.print(tempdht); 
 u8g.drawStr( 90, 15, "ºC");

 u8g.drawLine(0, 18, 127, 18); // linea separacion

 u8g.drawStr( 5, 33, "Calentador: ");
 u8g.setPrintPos(45, 15);
 u8g.print(tempdht);
 
u8g.drawLine(0, 36, 127, 36); // linea separacion
 */
 u8g.drawStr( 5, 40, "Desconectado "); 
 
 u8g.setFont(u8g_font_5x7);
// u8g.setFont(u8g_font_9x15);
 u8g.drawStr( 25, 62, "www.atorcha.es"); 
}
