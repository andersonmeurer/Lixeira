/** 
  *
  * @author Anderson Kuntz Meurer
  *	@date 09/08/2018
  */

#include "Arduino.h"
#include "RFID.h"
  
RFID::RFID() {
  serialRFID.begin(9600);
  novoID = false;
  IDiniciado = false;
  modoAprenderId = false;
  idInvalido = false;
  contID = 0;
  dado = 0;
  contAux = 0;
}
	
void RFID::loop() {
if (novoID) //Conferindo se leu algum ID
  {
    //Rotina para mostrar o ID no LCD, se você não tem um LCD, retire esta parte ou mude para a porta serial
    contAux = 0;
    while (contAux < (SIZE_ARRAY - 1))
    {
      //Serial.write(id[contAux]);//Exibe o caracter recebido - ####Se você não tem um LCD, retire esta linha####
	  Serial.print(id[contAux]);//Exibe o caracter recebido - ####Se você não tem um LCD, retire esta linha####
      contAux = contAux + 1;
	  setAbrirPorta(true);
    }
    Serial.println("");
    //Fim da rotina


    if (modoAprenderId) //Testando se esta no modo de gravar uma nova ID
    {

      contAux = 0;
      while (contAux < (SIZE_ARRAY - 1))
      {
        idGravado[contAux] = id[contAux];//Passando o ID lido para o array do ID gravado, o ideal é que se grave este dado na EEPROM para que não seja perdido
        //Você poderá usar várias posições de memória para gravar vários IDs distintos

        //Rotina para mostrar o ID no LCD, se você não tem um LCD, retire esta parte ou mude para a porta serial
        //Serial.write(idGravado[contAux]);//Exibe o caracter recebido - ####Se você não tem um LCD, retire esta linha####
		//Serial.println(">1<");
		Serial.print(idGravado[contAux]);//Exibe o caracter recebido - ####Se você não tem um LCD, retire esta linha####
        contAux = contAux + 1;
      }
      //Serial.println("");
      modoAprenderId = false;//Indica que pode sair do modo de gravar o ID
    }
    else//Se não esta no modo de aprender um novo ID, chega se o ID é igual ao gravado
    {
      contAux = 0;
      idInvalido = false;
      while ((contAux < (SIZE_ARRAY - 1)) && (!idInvalido))
      {
        //Nesta parte da rotina, você poderá implementar uma forma de comparar o ID lido com vários IDs gravados na EEPROM por exemplo
        if (idGravado[contAux] != id[contAux]) //Testando se o byte atual do ID lido é diferente do byte atual do ID gravado
        {
          idInvalido = true;//Se for diferente, informa que o ID é invalido e já sai do loop no próximo loop do while()
        }

        contAux = contAux + 1;
      }
    }


    novoID = false;//Limpa o flag que indica um novo ID
  }

  /*if (digitalRead(bt)) {
    delay(100);//Um delay, isto é um debouce mau feito

    if (digitalRead(bt))
    {
      modoAprenderId = true;//Informa que esta no modo de gravar o ID
      while (digitalRead(bt)) {} //Não faz nada até o botão ser solto
      Serial.println("Liberar Botao");
      delay(1000);
    }
  }*/

  while (serialRFID.available() > 0)//Enquanto estiver recebendo dados pela porta serial(Dados recebidos do módulo bluetooth) fica em loop
  {
    dado = serialRFID.read();//Lê o dado recebido

    if (!novoID) //Só entra na rotina se não tiver ainda um ID lido, se já tiver lido um ID, ignora os outros dados até tratar o ultimo lido
    {
      switch (dado)
      {
        case 0x02://Caso seja o byte de inicio, seta o flag
          IDiniciado = true;//Informando que iniciou um novo ID
          contID = 0;
          break;

        case 0x03:
          IDiniciado = false;
          contID = 0;
          novoID = true;//Informando que o novo ID foi lido

          //Esta parte da rotina é para ler todos os dados na serial, pois quando passamos o cartão o leitor enviar o ID várias vezes
          //Se retirar esta rotina, ele vai tratar o ID mais de uma vez
          while (Serial.available() > 0)//Enquanto estiver recebendo dados pela porta serial(Dados recebidos do módulo bluetooth) fica em loop
          {
            dado = serialRFID.read();//Lê o dado recebido
          }
          //Fim da rotina
          break;

        default://Se não for um byte de inicio ou final, armazena os dados no array do ID, inclusive o checksun
          id[contID] = dado;//Gravando o dado no array do ID
          contID = contID + 1;//Incrementa o contador de posição
      }
    }
  }
}

bool RFID::isAbrirPorta() {
	return abrirPorta;
}

void RFID::setAbrirPorta(bool pAbrirPorta) {
	this->abrirPorta = pAbrirPorta;
}