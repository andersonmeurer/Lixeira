/** 
  *
  * @author Anderson Kuntz Meurer
  *	@date 09/08/2018
  */
 
#ifndef Pino_h
#define Pino_h

struct Pino {
	public:
		byte pino;
		byte statusAnterior;
		byte statusPinoAlto;
		byte statusPinoBaixo;
		unsigned long tempoPermanecerAcionado;
		unsigned long tempoAcionado;
		unsigned long tempoDesacionado;
		unsigned long bounceOnUp;
		unsigned long bounceOnDown;
		boolean isPinoEntrada;
		boolean statusAtual;
};
#endif