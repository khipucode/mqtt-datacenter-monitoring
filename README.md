# 🛡️ Sistema de Monitoramento Inteligente para Data Centers (IoT)

## 📖 Sobre o Projeto

Este projeto consiste em um Sistema de Monitoramento Inteligente para Data Centers baseado em IoT. O objetivo é garantir a segurança física e térmica de racks de servidores críticos.

Utilizando um microcontrolador **ESP32**, o sistema monitora temperatura e umidade em tempo real (via sensor **DHT22**) e detecta invasões físicas no local (via sensor **PIR**). As informações são exibidas localmente em um **Display LCD** e enviadas via protocolo **MQTT com criptografia SSL/TLS** para um broker na nuvem (EMQX).

Além do monitoramento, o sistema possui um atuador de resfriamento de emergência (simulado por LED), que pode ser acionado remotamente por comandos via dashboard ou cliente MQTT. O código foi desenvolvido para ser resiliente, com reconexão automática e tratamento flexível de mensagens (JSON ou texto puro).

---

## 📂 Estrutura de Arquivos

Abaixo está a organização das pastas e arquivos deste repositório:

```text
NOME-DO-PROJETO/
│
├── README.md                 # Documentação principal do projeto
├── diagram.json              # Arquivo de configuração de hardware do Wokwi
├── .gitignore                # Arquivos ignorados pelo Git (ex: builds locais)
│
├── src/                      # Código fonte do projeto
│   └── sketch.ino            # Código principal C++ (Arduino Framework)
│
└── img/                      # Imagens para documentação
    ├── arquitetura.png       # Infográfico da arquitetura do sistema
    └── circuito_wokwi.png    # Screenshot da simulação funcionando
```

#📡 Monitoramento Inteligente de Data Center (IoT)

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
| `fiap/datacenter/rack01/cooler/comando` | Controle do Cooler | `ON` ou `OFF` |

> **Nota:** O sistema aceita comandos tanto em texto puro (`ON`) quanto em JSON (`{"msg": "ON"}`).

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
<img width="834" height="517" alt="image" src="https://github.com/user-attachments/assets/26dcba5d-8f1e-4119-8586-52b7f44478ef" />
<img width="834" height="517" alt="image" src="https://github.com/user-attachments/assets/8d3bab7c-49ae-4e2e-a9e7-691093ab74ef" />
<img width="834" height="517" alt="image" src="https://github.com/user-attachments/assets/9f42f193-2dda-42cb-ada6-2031a4f11e28" />
<img width="1835" height="931" alt="image" src="https://github.com/user-attachments/assets/43b833c3-cc2c-42a6-85e5-547665ae58bf" />


**Link do projeto no wokwi: https://wokwi.com/projects/452697865103979521

---
**Desenvolvido por:** [Leonid HM]
