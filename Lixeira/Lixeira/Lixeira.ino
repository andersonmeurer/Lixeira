/** 
  *
  * @author Anderson Kuntz Meurer
  *	@date 09/08/2018
  */

#include "/Lixeira/Pino.h"

/*
  -----------------------------
  Pinos
  -----------------------------
  RTC - A4, A5

  RFID - D2, D3
  Buzzer - D4
  Reed - D5
  ReleEletroIma - D6
*/

#define TEMPO_CURTO 5000 // 5 MINUTOS
#define TEMPO_LONGO 120000 // 2 HORAS

#if defined(__AVR_ATmega2560__)
//arduino mega
#define NR_PINO_RTC_SCL_A4 SCL
#define NR_PINO_RTC_SDA_A5 SDA
#else
#define NR_PINO_RTC_SCL_A4 4
#define NR_PINO_RTC_SDA_A5 5

#endif

#define NR_PINO_BUZZER     4
#define NR_PINO_REED       5
#define NR_PINO_BOTAO      6
#define NR_PINO_ELETRO_IMA 12

//------------------------------------------------------
//---RTC
//------------------------------------------------------


//------------------------------------------------------
//---RFID - RDM630
//------------------------------------------------------
#if defined(__AVR_ATmega2560__)
//arduino mega
#define NR_PINO_RFID_RX         10
#define NR_PINO_RFID_TX         11
#else
//arduino nano
#define NR_PINO_RFID_RX         2
#define NR_PINO_RFID_TX         3
#endif

#include "/Users/Anderson/Google Drive/Villa di Italia/Arduino/LixeiraV1.2/RFID.cpp"
RFID rfid;

//------------------------------------------------------
//--- Alarme
//------------------------------------------------------
#include "/Users/Anderson/Google Drive/Villa di Italia/Arduino/LixeiraV1.2/Alarme.cpp"
Alarme alarme(NR_PINO_BUZZER); // Buzzer

//------------------------------------------------------
//--- EletroIma
//------------------------------------------------------
#include "/Users/Anderson/Google Drive/Villa di Italia/Arduino/LixeiraV1.2/EletroIma.cpp"
EletroIma eletroIma(NR_PINO_ELETRO_IMA);//rever, o rele esta derrubando a serial

Pino pinoReeed;
Pino pinoBotao;

bool isPortaAberta;
bool isAbrirPortaBotao;

void setup() {
  isPortaAberta = false;
  isAbrirPortaBotao = false;

  pinoReeed.pino = NR_PINO_REED;
  pinoReeed.statusPinoAlto = 1;
  pinoReeed.statusPinoBaixo = (!pinoReeed.statusPinoAlto);
  pinoReeed.bounceOnUp = 1000;
  pinoReeed.bounceOnDown = 1000;
  pinoReeed.isPinoEntrada = true;

  pinoBotao.pino = NR_PINO_BOTAO;
  pinoBotao.statusPinoAlto = LOW;
  pinoBotao.statusPinoBaixo = (!pinoBotao.statusPinoAlto);
  pinoBotao.bounceOnUp = 100;
  pinoBotao.bounceOnDown = 100;
  pinoBotao.isPinoEntrada = true;

  pinMode(pinoReeed.pino, INPUT_PULLUP);
  pinMode(pinoBotao.pino, INPUT_PULLUP);

  Serial.begin(9600);

  Serial.println("Iniciado 2020 06 29!");

  delay(3000); // wait for console opening
}

void loop() {
  verificaPinoEntrada(&pinoReeed);
  verificaPinoEntrada(&pinoBotao);

  alarme.setDispararAlarme(isPortaAberta);
  alarme.loop();

  if (isAbrirPortaBotao) {
    //Serial.print("isAbrirPortaBotao=");
    //Serial.println(isAbrirPortaBotao);
    isAbrirPortaBotao = false;
    eletroIma.setAbrirPorta();
    alarme.setBeepOK(); 

  } else {

    rfid.loop();
    if (rfid.isAbrirPorta()) {
      eletroIma.setAbrirPorta();
      rfid.setAbrirPorta(false);
      alarme.setBeepOK();
    }
  }

  eletroIma.loop();
}

void verificaPinoEntrada(Pino *pinoEntrada) {
  long t = millis();
  byte valorLido = digitalRead((*pinoEntrada).pino);
  if (valorLido == (*pinoEntrada).statusPinoAlto) {

    (*pinoEntrada).tempoDesacionado = 0;
    if ((*pinoEntrada).tempoAcionado == 0) {
      (*pinoEntrada).tempoAcionado = t;
    }

    if ((*pinoEntrada).statusAnterior == (*pinoEntrada).statusPinoBaixo && ((t - (*pinoEntrada).tempoAcionado) >= (*pinoEntrada).bounceOnUp)) {
      (*pinoEntrada).statusAnterior = (*pinoEntrada).statusPinoAlto;

      if ((*pinoEntrada).pino == pinoReeed.pino) {
        isPortaAberta = true;
        Serial.println("Porta aberta"); //delay(1000);
      }
    }

  } else if (valorLido == (*pinoEntrada).statusPinoBaixo) {

    (*pinoEntrada).tempoAcionado = 0;
    if ((*pinoEntrada).tempoDesacionado == 0) {
      (*pinoEntrada).tempoDesacionado = t;
    }

    if ((*pinoEntrada).statusAnterior == (*pinoEntrada).statusPinoAlto && ((t - (*pinoEntrada).tempoDesacionado) >= (*pinoEntrada).bounceOnDown)) {
      (*pinoEntrada).statusAnterior = (*pinoEntrada).statusPinoBaixo;

      if ((*pinoEntrada).pino == pinoReeed.pino) {
        isPortaAberta = false;
        Serial.println("Porta fechada"); //delay(1000);
      } else if ((*pinoEntrada).pino == pinoBotao.pino) {
        isAbrirPortaBotao = true;
      }
    }
  }
}
