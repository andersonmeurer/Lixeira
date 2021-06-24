/** 
  *
  * @author Anderson Kuntz Meurer
  *  @date 09/08/2018
  */

#include "/Lixeira/Alarme.cpp"

Alarme alarme(8); // Buzzer

void setup() {
  Serial.begin(9600);
  Serial.print("Iniciado 2");

}

void loop() {
  alarme.setDispararAlarme(true);
  //alarme.setBeepOK();
  alarme.loop();
}
