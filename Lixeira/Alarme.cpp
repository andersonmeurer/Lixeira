/** 
  *
  * @author Anderson Kuntz Meurer
  *	@date 09/08/2018
  */

#include "Arduino.h"
#include "Alarme.h"

Alarme::Alarme(byte pPinoBuzzer) {

	this->pinoBuzzer = pPinoBuzzer;
	pinMode(pPinoBuzzer, OUTPUT);

	isUpOrDown = true;
	lastTimeBeepOK = millis();
	lastTime = millis();
}
	
void Alarme::loop() {
	if (isDispararAlarme) { 
		dispararAlarme();
	} else {
		noTone(pinoBuzzer);
	}
}

void Alarme::dispararAlarme() {
	if ((millis() - lastTime) >= 150) {
		lastTime = millis();

		if (isUpOrDown) {
			tone(pinoBuzzer, 1350);
			isUpOrDown = !isUpOrDown;
		} else {
			tone(pinoBuzzer, 1050);
			isUpOrDown = !isUpOrDown;
		}
	}
}

void Alarme::setBeepOK() {
	if ((millis() - lastTimeBeepOK) > MILLIS_MINIMO_BETWEEN_BEEP_OK) {
		lastTimeBeepOK = millis();
		tone(pinoBuzzer, 3000, 100);
		delay(800);
		noTone(pinoBuzzer);
	}
}

void Alarme::setBeepErro() {
	for (byte i = 0; i < 3; i++) {
		tone(pinoBuzzer, 3000, 100);
		delay(100);
	}
}

void Alarme::setDispararAlarme(bool isDispararAlarme) {
	this->isDispararAlarme = isDispararAlarme;
}