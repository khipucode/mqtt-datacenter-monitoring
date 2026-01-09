# 📡 Monitoramento Inteligente de Data Center (IoT)

> Projeto desenvolvido para a disciplina de IoT, simulando o controle ambiental e de segurança de um Server Room utilizando ESP32 e protocolo MQTT.

## 📋 Descrição
Este sistema tem como objetivo monitorar as condições críticas de um rack de servidores. Ele previne superaquecimento e acessos não autorizados, permitindo monitoramento local (LCD) e remoto (Nuvem/MQTT).

### Funcionalidades Principais
* **Monitoramento Térmico:** Leitura constante de Temperatura e Umidade.
* **Segurança Física:** Detecção de movimento/presença perto do rack.
* **Dashboard Local:** Display LCD 16x2 com status em tempo real.
* **Controle Remoto:** Atuador (Cooler/LED) acionado via comandos MQTT.
* **Conectividade Segura:** Comunicação via MQTT sobre SSL/TLS (Porta 8883).

## 🛠️ Hardware Utilizado (Simulação Wokwi)

| Componente | Função | Pino ESP32 (GPIO) |
| :--- | :--- | :--- |
| **ESP32 DevKit** | Microcontrolador | - |
| **DHT22** | Sensor de Temp/Umidade | `GPIO 15` |
| **PIR (AS312)** | Sensor de Movimento | `GPIO 13` |
| **LED Vermelho** | Simula Cooler/Atuador | `GPIO 2` |
| **LCD 16x2 (I2C)** | Interface Visual | `SDA: 21` / `SCL: 22` |

## ⚙️ Configuração e Bibliotecas

O projeto foi desenvolvido em C++ (Arduino Framework). As seguintes bibliotecas são necessárias:

1.  `PubSubClient` (Nick O'Leary) - Comunicação MQTT.
2.  `DHT sensor library` (Adafruit) - Leitura do sensor.
3.  `LiquidCrystal I2C` (Frank de Brabander) - Controle do Display.
4.  `WiFiClientSecure` - Para conexão SSL com o Broker.

## ☁️ Arquitetura MQTT

O sistema utiliza um Broker MQTT (EMQX Cloud) para troca de mensagens.

### Tópicos de Publicação (ESP32 -> Nuvem)
| Tópico | Descrição | Exemplo de Payload |
| :--- | :--- | :--- |
| `fiap/datacenter/rack01/temperatura` | Temperatura atual | `24.5` |
| `fiap/datacenter/rack01/umidade` | Umidade atual | `60.0` |
| `fiap/datacenter/rack01/alerta_presenca` | Evento de segurança | `MOVIMENTO DETECTADO` |

### Tópico de Subscrição (Nuvem -> ESP32)
| Tópico | Descrição | Comandos Aceitos |
| :--- | :--- | :--- |
| `fiap/datacenter/rack01/cooler/comando` | Controle do Cooler | `LIGAR` ou `DESLIGAR` |

> **Nota:** O sistema aceita comandos tanto em texto puro (`LIGAR`) quanto em JSON (`{"msg": "LIGAR"}`).

## 🚀 Como Executar

1.  **Montagem:** Replique o circuito conforme a tabela de hardware acima.
2.  **Código:** Carregue o arquivo `sketch.ino` no ESP32.
3.  **Credenciais:** Edite as variáveis `ssid`, `password`, `MQTT_USER` e `MQTT_PASS` no código conforme sua rede.
4.  **Teste:**
    * Conecte um Cliente MQTT (MQTTX ou HiveMQ).
    * Assine o tópico `fiap/datacenter/#`.
    * Publique `LIGAR` no tópico de comando para testar o atuador.

## 📸 Demonstração
*(Aqui você pode inserir o link do seu vídeo no YouTube ou prints do Wokwi)*

---
**Desenvolvido por:** [Seu Nome]
