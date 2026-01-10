# 🛡️ Sistema de Monitoramento Inteligente para Data Centers (IoT)

## 📖 Sobre o Projeto

Este projeto consiste em um Sistema de Monitoramento para data centers baseado em IoT-MQTT usando ESP32 no wokwi. O objetivo é garantir a segurança física e térmica de racks de servidores críticos.
O sistema monitora temperatura e umidade em tempo real (via sensor DHT22) e detecta invasões físicas no local (via sensor PIR). As informações são monstradas em um Display LCD e enviadas via protocolo MQTT com criptografia SSL/TLS para um broker na nuvem (EMQX).
Além do monitoramento, o sistema possui um atuador (alarme ou poderia ser de resfriamento de emergência) simulado por LED, que pode ser acionado remotamente por comandos via dashboard ou cliente MQTT como um celular usando o app MQTT-dashboard.

---

## 📂 Estrutura de Arquivos

Abaixo está a organização das pastas e arquivos deste repositório:

```text
NOME-DO-PROJETO/
│
├── README.md                 # Documentação principal do projeto
│
├── src/                      # Código fonte do projeto
    └── sketch.ino            # Código principal C++ (Arduino Framework)

```

#📡 Monitoramento Inteligente de Data Center (IoT)

> Projeto desenvolvido para a disciplina de IoT, simulando o controle ambiental e de segurança de um Server Room utilizando ESP32 e protocolo MQTT.

## 📋 Descrição
Este sistema tem como objetivo monitorar as condições críticas de um rack de servidores. Ele previne superaquecimento e acessos não autorizados, permitindo monitoramento local (LCD) e remoto (Nuvem/MQTT).

### Funcionalidades Principais
* **Monitoramento Térmico:** Leitura constante de Temperatura e Umidade.
* **Segurança Física:** Detecção de movimento/presença perto do rack.
* **Dashboard Local:** Display LCD 16x2 com status em tempo real.
* **Controle Remoto:** Atuador (Cooler/LED) acionado via comandos MQTT e/o app MQTT dashboard.
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

## 📸 Demonstração

<img width="834" height="517" alt="image" src="https://github.com/user-attachments/assets/26dcba5d-8f1e-4119-8586-52b7f44478ef" />
<img width="834" height="517" alt="image" src="https://github.com/user-attachments/assets/8d3bab7c-49ae-4e2e-a9e7-691093ab74ef" />
<img width="834" height="517" alt="image" src="https://github.com/user-attachments/assets/9f42f193-2dda-42cb-ada6-2031a4f11e28" />
<img width="1835" height="931" alt="image" src="https://github.com/user-attachments/assets/43b833c3-cc2c-42a6-85e5-547665ae58bf" />


**Link do projeto no wokwi:** https://wokwi.com/projects/452697865103979521

---
**Desenvolvido por:** Leonid HM
