#include <Wire.h> //INCLUSÃO DA BIBLIOTECA
#include "RTClib.h" //INCLUSÃO DA BIBLIOTECA
#include <SPI.h>
#include <SD.h>

int sensorValue;

const int chipSelect = D8;
 
RTC_DS3231 rtc; //OBJETO DO TIPO RTC_DS3231
 
//DECLARAÇÃO DOS DIAS DA SEMANA
char daysOfTheWeek[7][12] = {"Domingo", "Segunda", "Terça", "Quarta", "Quinta", "Sexta", "Sábado"};
 
void setup(){
  Serial.begin(9600); //INICIALIZA A SERIAL
  if(! rtc.begin()) { // SE O RTC NÃO FOR INICIALIZADO, FAZ
    Serial.println("DS3231 não encontrado"); //IMPRIME O TEXTO NO MONITOR SERIAL
    while(1); //SEMPRE ENTRE NO LOOP
  }
  if(rtc.lostPower()){ //SE RTC FOI LIGADO PELA PRIMEIRA VEZ / FICOU SEM ENERGIA / ESGOTOU A BATERIA, FAZ
    Serial.println("DS3231 OK!"); //IMPRIME O TEXTO NO MONITOR SERIAL
    //REMOVA O COMENTÁRIO DE UMA DAS LINHAS ABAIXO PARA INSERIR AS INFORMAÇÕES ATUALIZADAS EM SEU RTC
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); //CAPTURA A DATA E HORA EM QUE O SKETCH É COMPILADO
    //rtc.adjust(DateTime(2018, 9, 29, 15, 00, 45)); //(ANO), (MÊS), (DIA), (HORA), (MINUTOS), (SEGUNDOS)
  }
   //---------------------------------------------------------
   Serial.print("Inicializando SD card ...");

  // Verefica de o SD esta presente e pode ser inicializado
  if (!SD.begin(chipSelect)) {
    Serial.println("Falha no cartao, nao pode ser incializado");
    // Não faz mais nada
    while (1);
  }
  Serial.println("Cartao Inicializado.");
  //------------------------------------------------------------
  delay(100); //INTERVALO DE 100 MILISSEGUNDOS
}
 
void loop () {
    DateTime now = rtc.now(); //CHAMADA DE FUNÇÃO
    Serial.print("Data: "); //IMPRIME O TEXTO NO MONITOR SERIAL
    Serial.print(now.day(), DEC); //IMPRIME NO MONITOR SERIAL O DIA
    Serial.print('/'); //IMPRIME O CARACTERE NO MONITOR SERIAL
    Serial.print(now.month(), DEC); //IMPRIME NO MONITOR SERIAL O MÊS
    Serial.print('/'); //IMPRIME O CARACTERE NO MONITOR SERIAL
    Serial.print(now.year(), DEC); //IMPRIME NO MONITOR SERIAL O ANO
    Serial.print(" / Dia: "); //IMPRIME O TEXTO NA SERIAL
    Serial.print(daysOfTheWeek[now.dayOfTheWeek()]); //IMPRIME NO MONITOR SERIAL O DIA
    Serial.print(" / Horas: "); //IMPRIME O TEXTO NA SERIAL
    Serial.print(now.hour(), DEC); //IMPRIME NO MONITOR SERIAL A HORA
    Serial.print(':'); //IMPRIME O CARACTERE NO MONITOR SERIAL
    Serial.print(now.minute(), DEC); //IMPRIME NO MONITOR SERIAL OS MINUTOS
    Serial.print(':'); //IMPRIME O CARACTERE NO MONITOR SERIAL
    Serial.print(now.second(), DEC); //IMPRIME NO MONITOR SERIAL OS SEGUNDOS
    //---------------------LDR----------------------------
    sensorValue = analogRead(A0); // leitura da entrada analógica pin 0
    sensorValue = map(sensorValue, 0, 1023, 0, 100);
    Serial.print(" / Luminosidade: "); //IMPRIME O TEXTO NA SERIAL
    Serial.print(sensorValue, DEC); // Imprime os valores lidos
    Serial.println(); //QUEBRA DE LINHA NA SERIAL
    //-----------------------------------------------------
    File dataFile = SD.open("cartao.txt", FILE_WRITE);

    if (dataFile) {
    dataFile.println(sensorValue, DEC);
    dataFile.println("Data: "); //IMPRIME O TEXTO NO MONITOR SERIAL
    dataFile.println(now.day(), DEC); //IMPRIME NO MONITOR SERIAL O DIA
    dataFile.println('/'); //IMPRIME O CARACTERE NO MONITOR SERIAL
    dataFile.println(now.month(), DEC); //IMPRIME NO MONITOR SERIAL O MÊS
    dataFile.println('/'); //IMPRIME O CARACTERE NO MONITOR SERIAL
    dataFile.println(now.year(), DEC); //IMPRIME NO MONITOR SERIAL O ANO
    dataFile.println(" / Horas: "); //IMPRIME O TEXTO NA SERIAL
    dataFile.println(now.hour(), DEC); //IMPRIME NO MONITOR SERIAL A HORA
    dataFile.println(':'); //IMPRIME O CARACTERE NO MONITOR SERIAL
    dataFile.println(now.minute(), DEC); //IMPRIME NO MONITOR SERIAL OS MINUTOS
    dataFile.println(':'); //IMPRIME O CARACTERE NO MONITOR SERIAL
    dataFile.println(now.second(), DEC); //IMPRIME NO MONITOR SERIAL OS SEGUNDOS
    dataFile.println("\n"); //QUEBRA DE LINHA NO SD
    dataFile.close();
    }else {
    Serial.println("Erro ao abrir o arquivo cartao.txt");
    }
    //---------------------------------------------
    delay(1000); //INTERVALO DE 1 SEGUNDO
}
