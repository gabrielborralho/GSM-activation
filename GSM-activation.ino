/** ##############################################################
**
**  Filename  : GSM-activation.ino
**  Project   : GSM Activation
**  Processor : ATMega328/P
**  Version   : 1.0
**  Compiler  : Arduino IDE
**  Date/Time : 06/09/2015
**  Aluno     : Gabriel Borralho
**  Last Mod  : 10/09/2015
**
** ##############################################################*/

#include "SIM900.h"
#include <SoftwareSerial.h>
#include "sms.h"

SMSGSM sms;

boolean started = false;
char smsbuffer[160];
char n[20];

String msg_esperada("Liga");

void setup()
{
  //Inicializa a serial
  Serial.begin(9600);
  //Define a porta 13 como saida
  pinMode(6, OUTPUT);
  digitalWrite(6, LOW);
  Serial.print("Ligando shield GSM SIM900. ");
  liga_desliga_GSMShield();
  Serial.println("Testando GSM shield...");
  //Comunicacao com o Shield GSM a 2400 bauds
  if (gsm.begin(2400))
  {
    Serial.println("nstatus=READY");
    started = true;
  }
  else Serial.println("nstatus=IDLE");

  if(started) 
     {
       //Envia um SMS para o numero selecionado
       //Formato sms.SendSMS(<numero>,<mensagem>)
       if (sms.SendSMS("981312459", "Arduino SMS"))
       Serial.println("nSMS sent OK");
     }
}

void loop()
{
  if (started)
  {
    //Aguarda SMS
    Serial.println("Aguardando SMS...");
    if (gsm.readSMS(smsbuffer, 160, n, 20))
    {
      String msg_recebida(smsbuffer);
      msg_recebida.trim();
      msg_esperada.trim();
      if (msg_recebida == msg_esperada)
      {
        Serial.println("SMS Recebido! Alterando estado da porta 13....");
        digitalWrite(6, HIGH);
      }
      else
      {
        digitalWrite(6, LOW);
      }
      delay(5000);
    }
  }
}

void liga_desliga_GSMShield()
{
  Serial.print(F("Aguarde..."));
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  delay(1000);
  digitalWrite(13, HIGH);
  delay(1000);
  Serial.println(F("OK!"));
  digitalWrite(13, LOW);
  delay(500);
}
