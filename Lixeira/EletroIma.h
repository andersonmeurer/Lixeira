/** 
  *
  * @author Anderson Kuntz Meurer
  *	@date 09/08/2018
  */

#ifndef EletroIma_h
#define EletroIma_h

#include "Arduino.h"

class EletroIma {

	private:
		Pino pino;
		bool abrirPorta;
		
		void acionarPinoSaida(Pino *pinoSaida);
		void desacionarPinoSaida(Pino *pinoSaida);

	public:
		EletroIma(byte pPino);
		void loop();
		void setAbrirPorta();
		void isAbrirPortaAutomaticamente();
};
#endif