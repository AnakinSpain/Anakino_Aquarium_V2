# Anakino_Aquarium_V2
====== Proyecto ======

En esta entrada quiero hacer una pequeña relación de los materiales que hacen falta para montarlo, aunque no está completo. De momento estoy terminando de ver lo necesario para darle una larga vida al asunto.
Con el controlador Anakin_aquarium_V2  podrás controlar el acuario con una Placa Arduino Mega + ESP8266.


===== Las opciones son =====

  * Encendido y apagado de luces les noche (azul) y blanca con efecto amanecer.
  * Control más exacto de la temperatura del agua.
  * Relleno automático de agua
  * Control de temporizadores como el de CO2, lampara UV o Aireador.
  * Sensor de pH de agua y corte de CO2 si está fuera de parámetros.
  * Supervisión de valores y control mediante aplicación movil [[https://blynk.io/en/getting-started|Blynk]].
  * Aviso de alarmas en móvil cuando haya algo fuera de parámetros.
  * Control de bombas peristalticas.
  * Control de comedero.
  * Control de ventilador de refrigeración.
 

Estoy desarrollando una placa base PCB donde aparecerán todos los componentes integrados y sea solamente conectar y listo. De todos modos todavía queda un poco. Si alguien se anima a ayudar todo es bienvenido, ya que es todo código abierto para que el que quiera montarlo pueda hacerlo. Es un proyecto colaborativo.


===== Componentes =====

  * Placa Arduino Mega y ESP8266
  * L7805 (regulador de voltaje 12v -> 5v)
  * AMS1117 (Regulador de voltaje 12v -> 5V)
  * Sensor de pH
  * Sensor TDS
  * IRF540 (para dimeado de luces y ventiladores)
  * Reles
  * Pantalla oled
  * DTH22
  * Sensores de temperatura ds18b20
  * Condensadores 10uF
  * Resistencias 4k7

==== Placa Arduino MEGA con ESP8266 ====

Para eso cuento con la placa Arduino Mega a la que se le ha conectado un ESP8266 según este esquema:

{{ :anakino_aquarium_v2:arduino-mega-2560-esp8266.jpg?600 |}} 




==== IRF540 ====

Tengo pensado usarlo para poder dimmear tanto la luz, como quizás los ventiladores que refrigerará el agua.


==== Reles ====

Modulo de 4 Reles de estado sólido para Arduino. Se utilizan de 5v para controlar los diferentes componentes a 220v.

==== Pantalla oled ====

"1.3 inch IIC I2C Serial 128x64 OLED LCD Display White Screen" esta es la descripción de la pantalla oled que he comprado por Ebay.

Al ser conectada por I2C podemos ahorrar pines aunque con esta placa tenemos de sobra.

{{ :anakino_aquarium_v2:oled.jpg?400 |}}


==== DTH22 ====

Sensor de humedad y de temperatura, utilizado para conocer los parámetros de la habitación del acuario.


==== Sensores de temperatura ====

Utilizaremos dos sensores de temperatura sumergibles pensados, uno para controlar la temperatura del agua y para conocer la de la pantalla de iluminación por si fuera necesario controlar un refrigerador de la misma.


==== Reles ====
Los reles de estado solido van a controlar los 4 enchufes que servirán para manejar el calentador, el aireado, la lampara uv y el CO2

La conexión con la placa se hará por cable de red que permite poner los enchufes es un sitio cómodo y seguro.
{{ :anakino_aquarium_v2:515wgvjw3kl.jpg?300|}}

{{:anakino_aquarium_v2:rele_estado_solido.jpg?300 |}}



 
