//Bibliotecas do RFID
#include <SPI.h>
#include <MFRC522.h>

//Bibliotecas do display LCD
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//Biblioteca wifi socket
#include <ESP8266WiFi.h>

//Biblioteca para lidar com JSON
#include <ArduinoJson.h>


//Definições e intãncia da classe RFID
#define SS_PIN 2 //D4
#define RST_PIN 0 //D3

MFRC522 mfrc522(SS_PIN, RST_PIN);

//Instância da classa LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

//Variáveis wifi socket
//(substituir o seu ssid e senha)
const char *ssid = "";
const char *password = "";

IPAddress server(192,168,0,198);
WiFiClient client;

//Objeto JSON estático (criado na compilação)
StaticJsonDocument<38> json_profile;

void setup() {
  //Inicialização do RFID
  rfid_init();

  //Inicialização do display
  lcd_init();

  //Inicialização da serial 
  //(para depuração da conexão de rede wifi
  //e do parser json)
  Serial.begin(115200);

  //Inicialização da conexão com o gateway python via TCPSocket
  lcd_pretty_print("Conectando ao\ngateway...");
  server_connect();

  //Início
  lcd_pretty_print("Aproxime ou\npasse o cartao");
}

void loop() {
  //Verifica se algum cartão passou no leitor
  if (hasValidCard()){
    //Obtenção do ID do cartão
    String ID = getCardId();

    //Envia o ID para o gateway Python
    wifi_send(ID);
    
    //Informa, pelo LCD, que a chave está sendo verificada
    lcd_pretty_print("Autenticando...");

    //espera a resposta

    //Recebe as informações do perfil do usuário
    char* str_profile = wifi_receive2();
    
    //Convertendo o array de char em JSON via parsing
    json_parser(str_profile);

    //Preparando os textos com as informações de perfil do JSON recebido
    String text1 = "Bem vindo\n" + String(json_profile["name"]) + "!";
    String text2 = "Area:\n" + String(json_profile["job"]);

    //Printando as informações do usuário no LCD: nome e trabalho
    lcd_pretty_print(text1);
    delay(2500);
    lcd_pretty_print(text2);
    delay(2500);

    //Volta ao início
    lcd_pretty_print("Aproxime ou\npasse o cartao");
  }
  delay(500);
}
