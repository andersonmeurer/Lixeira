/** 
  *
  * @author Anderson Kuntz Meurer
  *	@date 09/08/2018
  */

#ifndef RFID_h
#define RFID_h

#include "Arduino.h"

#include <SoftwareSerial.h>

SoftwareSerial serialRFID(NR_PINO_RFID_RX, NR_PINO_RFID_TX);
#define SIZE_ARRAY 12

//-------------------------------------------
// RDM630
//-------------------------------------------
class RFID {

	private:
		//Definição do Botão
		//int bt = 4;//Botão para ativar o modo de gravação do ID

		byte dado;//Variável para armazenar o dado recebido Pela porta serial

		byte idGravado[SIZE_ARRAY];//Armazena o ID memorizado, para um programa melhor, grave os dados na EEPROM
		byte id[SIZE_ARRAY];//Armazena o ID lido pela serial
		byte contID;//Variável para contar a posição do byte dentro do ID
		byte contAux;//Variável auxiliar para fazer contagem de posição dos byte
		short IDiniciado;//Informa que recebeu o byte de inicio do ID
		short novoID;//Informa que leu um novo ID
		short modoAprenderId;//Flag para indicar que esta no modo de gravar um ID
        short idInvalido;//Sinaliza quando lê um ID diferente do gravado

		bool abrirPorta;
	public:
		RFID();
		void loop();
		bool isAbrirPorta();
		void setAbrirPorta(bool b);
};
#endif