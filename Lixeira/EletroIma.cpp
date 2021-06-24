/** 
  *
  * @author Anderson Kuntz Meurer
  *	@date 09/08/2018
  */

#include "Arduino.h"
#include "EletroIma.h"
  
EletroIma::EletroIma(byte pPino) {
	pino.pino = pPino;
	pino.statusPinoAlto = HIGH;
	pino.statusPinoBaixo = (!pino.statusPinoAlto);
	pino.tempoPermanecerAcionado = TEMPO_CURTO;
	pino.isPinoEntrada = false;

	pinMode(pino.pino, OUTPUT);
	acionarPinoSaida(&pino);
	this->abrirPorta = false;
}
	
void EletroIma::loop() {
	if (abrirPorta) {
		//Serial.print("EletroIma abrirPorta ");
		//Serial.print(pino.tempoAcionado);
		//Serial.print(" - ");
		//Serial.print((millis() - pino.tempoAcionado));
		//Serial.print(" - ");
		//Serial.println(pino.tempoPermanecerAcionado);

		if (pino.tempoAcionado == 0) {
			acionarPinoSaida(&pino);
		} else if ((millis() - pino.tempoAcionado) >= pino.tempoPermanecerAcionado) {
			abrirPorta = false;
			Serial.print("EletroIma 1 ");
			Serial.println("EletroIma abrirPorta acionarPinoSaida");
			desacionarPinoSaida(&pino);
		}

	} else {
		desacionarPinoSaida(&pino);
	}
}

void EletroIma::setAbrirPorta() {
	this->abrirPorta = true;
	pino.tempoPermanecerAcionado = TEMPO_CURTO;
}

void EletroIma::isAbrirPortaAutomaticamente() {
	this->abrirPorta = true;
	pino.tempoPermanecerAcionado = TEMPO_LONGO;
}

void EletroIma::acionarPinoSaida(Pino *pinoSaida) {
	//if (digitalRead((*pinoSaida).pino) != (*pinoSaida).statusPinoAlto) {
		digitalWrite((*pinoSaida).pino, (*pinoSaida).statusPinoAlto);
		(*pinoSaida).tempoAcionado = millis();
		(*pinoSaida).tempoDesacionado = 0;
	//}
}

void EletroIma::desacionarPinoSaida(Pino *pinoSaida) {
	//if (digitalRead((*pinoSaida).pino) != (*pinoSaida).statusPinoBaixo) {
		digitalWrite((*pinoSaida).pino, (*pinoSaida).statusPinoBaixo);
		(*pinoSaida).tempoAcionado = 0;
		(*pinoSaida).tempoDesacionado = millis();
	//}
}