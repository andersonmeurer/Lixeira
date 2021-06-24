/** 
  *
  * @author Anderson Kuntz Meurer
  *	@date 09/08/2018
  */

#ifndef Alarme_h
#define Alarme_h

#include "Arduino.h"

#define MILLIS_MINIMO_BETWEEN_BEEP_OK 1500

class Alarme {

	private:
		byte pinoBuzzer;
		
		long lastTimeBeepOK;
		long lastTime;
		bool iniciar;
		bool isDispararAlarme;
		bool isIniciar;
		bool isUpOrDown;

		void dispararAlarme();
		
	public:
		Alarme(byte pPinoBuzzer);
		void loop();
		void setDispararAlarme(bool isSoarAlarme);
		void setBeepOK();
		void setBeepErro();
};
#endif