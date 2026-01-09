#include <WiFi.h>
#include <PubSubClient.h>
#include <WiFiClientSecure.h> // Importante para porta 8883
#include "DHT.h"
#include <LiquidCrystal_I2C.h>

// ==== CONFIGURAÇÕES WI-FI ====
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// ==== CONFIGURAÇÕES MQTT (EMQX CLOUD) ====
const char* MQTT_BROKER    = "zaf70ec79.ala.eu-central-1.emqxsl.com";
const int   MQTT_PORT      = z8883; // Porta Segura
const char* MQTT_CLIENT_ID = "zESP32_Wokwi_Secure";
const char* MQTT_USER      = "zleonidmqtt";
const char* MQTT_PASS      = "z123456";

WiFiClientSecure espClient; // Cliente Seguro
PubSubClient client(espClient);

// ==== HARDWARE ====
#define DHTPIN 15
#define DHTTYPE DHT22
#define PIR_PIN 13
#define LED_COOLER 2

// Endereço I2C do LCD (Wokwi usa padrão 0x27)
LiquidCrystal_I2C lcd(0x27, 16, 2);
DHT dht(DHTPIN, DHTTYPE);

// ==== TÓPICOS ====
const char* topicTemp = "fiap/datacenter/rack01/temperatura";
const char* topicHum  = "fiap/datacenter/rack01/umidade";
const char* topicMov  = "fiap/datacenter/rack01/alerta_presenca";
const char* topicCmd  = "fiap/datacenter/rack01/cooler/comando";

unsigned long lastMsg = 0;

// Função auxiliar para escrever no LCD
void showLCD(String linha0, String linha1) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(linha0);
  lcd.setCursor(0, 1);
  lcd.print(linha1);
}

void setup_wifi() {
  delay(100);
  showLCD("PROJETO FIAP-CPQD", "LEONID HM");
  delay(3000);
  Serial.print("Conectando WiFi");
  showLCD("Conectando WiFi", "Aguarde...");
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Conectado!");
  showLCD("WiFi OK!", "IP Obtido");
  delay(1000);
}

void callback(char* topic, byte* payload, unsigned int length) {
  String msg;
  for (int i = 0; i < length; i++) msg += (char)payload[i];
  
  Serial.print("MSG Recebida: ");
  Serial.println(msg);

  showLCD("CMD Recebido:", "Processando...");

  // Verifica se o tópico é o de comando
  if (String(topic) == topicCmd) {
    
    // USAMOS indexOf EM VEZ DE ==
    // Isso procura a palavra "LIGAR" em qualquer lugar da mensagem
    if (msg.indexOf("ON") >= 0) {
      digitalWrite(LED_COOLER, HIGH);
      Serial.println(">> ATUADOR: LIGADO");
      showLCD("STATUS:", "COOLER ON");
    } 
    else if (msg.indexOf("OFF") >= 0) {
      digitalWrite(LED_COOLER, LOW);
      Serial.println(">> ATUADOR: DESLIGADO");
      showLCD("STATUS:", "COOLER OFF");
    }
  }
  delay(2000); 
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Conectando MQTT (SSL)...");
    showLCD("Conectando", "MQTT Broker...");
    
    // Tenta conectar (ID, User, Pass)
    if (client.connect(MQTT_CLIENT_ID, MQTT_USER, MQTT_PASS)) {
      Serial.println("Conectado!");
      showLCD("MQTT Online!", "Aguardando...");
      client.subscribe(topicCmd);
      delay(1000);
    } else {
      Serial.print("Falha rc=");
      Serial.print(client.state());
      showLCD("Falha MQTT", "Retentando...");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  
  pinMode(LED_COOLER, OUTPUT);
  pinMode(PIR_PIN, INPUT);
  dht.begin();
  lcd.init();
  lcd.backlight();

  setup_wifi();

  // COMANDO MÁGICO PARA O WOKWI ACEITAR O EMQX
  espClient.setInsecure(); 

  client.setServer(MQTT_BROKER, MQTT_PORT);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) reconnect();
  client.loop();

  unsigned long now = millis();
  
  if (now - lastMsg > 4000) {
    lastMsg = now;
    
    float t = dht.readTemperature();
    float h = dht.readHumidity();
    int movimento = digitalRead(PIR_PIN);

    if (!isnan(t) && !isnan(h)) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.printf("T:%.1fC H:%.0f%%", t, h);
      
      lcd.setCursor(0, 1);
      if (movimento) lcd.print("MOVIMENTO!    ");
      else           lcd.print("Ambiente OK   ");

      client.publish(topicTemp, String(t).c_str());
      client.publish(topicHum, String(h).c_str());
      
      Serial.printf("Enviado MQTT -> T: %.1f, H: %.1f\n", t, h);
      
      lcd.setCursor(15, 0); 
      lcd.print("*"); 
      delay(200);
      lcd.setCursor(15, 0); 
      lcd.print(" ");

      if (movimento == HIGH) {
        client.publish(topicMov, "MOVIMENTO DETECTADO");
        Serial.println(">> ALERTA DE SEGURANÇA ENVIADO");
        showLCD("ALERTA CRITICO", "INVASAO DETECT.");
        delay(1500); 
      }
    }
  }
}
