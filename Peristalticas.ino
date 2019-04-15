
void peris(){

  if (peris1_today == true) {

    if ((hour() == peris1STHour) && (minute() == peris1STMin) && (second() >= peris1STSec) && (second() <=peris1FNSec)) {

   digitalWrite(peris1, HIGH);  // activa la salida de la peristáltica 1
  }
  else {
    digitalWrite(peris1, LOW);
  }
 }

 if (peris2_today == true) {

    if ((hour() == peris2STHour) && (minute() == peris2STMin) && (second() >= peris2STSec) && (second() <=peris2FNSec)) {

   digitalWrite(peris2, HIGH);  // activa la salida de la peristáltica 2
  }
  else {
    digitalWrite(peris2, LOW);
  }
 }

 
}

