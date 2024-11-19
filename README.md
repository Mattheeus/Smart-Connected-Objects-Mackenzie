# Empilhadeira Automatizada com ESP32

## Descrição
Este projeto implementa uma empilhadeira automatizada utilizando um ESP32, sensores ultrassônicos, buzzer, LEDs e comunicação MQTT para monitoramento remoto e alertas em tempo real.

## Funcionamento e Uso
- **Inicialização:** O ESP32 se conecta à rede Wi-Fi e ao broker MQTT.
- **Leitura de Sensores:** O sensor ultrassônico mede continuamente a distância de objetos.
- **Ação dos Atuadores:** O buzzer e o LED amarelo são acionados quando um obstáculo é detectado.
- **Comunicação:** Mensagens são enviadas ao broker MQTT para monitoramento remoto.

# Descrição do Hardware Utilizado

- **ESP32:** Módulo Wi-Fi para controle e comunicação.
- **Sensor Ultrassônico:** Utilizado para detectar a distância de objetos.
- **Buzzer e LEDs:** Atuadores visuais e sonoros para alertas.
- **Conexões:** Cabos e conexões adequadas para interligar o ESP32, o sensor ultrassônico, o buzzer e os LEDs.
- **Alimentação:** Via USB ou fonte externa, dependendo da montagem final.

# Software e Documentação de Código

  O código está dividido em duas:

- Monitoramento e Alerta: Realiza a leitura dos dados do sensor ultrassônico, verifica a distância dos obstáculos e aciona buzzer e LEDs para alertar. Os dados são enviados para comunicação MQTT.

- Comunicação MQTT: Utiliza a conectividade Wi-Fi do ESP32 para conectar-se a uma rede e enviar os dados coletados para um servidor MQTT. Este segmento também é responsável por receber e processar comandos e dados enviados de volta ao dispositivo.

## Estrutura do Código
Inicialização e configuração do hardware.

- Leitura contínua dos dados do sensor ultrassônico.

- Verificação da distância e acionamento dos alertas.

- Envio de dados e MQTT para processamento ou monitoramento remoto.

- Monitoramento de conexão com o servidor MQTT e reconexão automática, se necessário.

## Montagem

O sensor ultrassônico é conectado ao ESP32 para controlar a coleta e processamento dos dados. O buzzer e os LEDs indicam a presença de obstáculos. A alimentação é fornecida via USB ou fonte externa, dependendo da montagem final.

# Documentação das Interfaces, Protocolos e Módulos de Comunicação 

## Interface de Comunicação 

- **Wi-Fi:** Utilizado para conectar o ESP32 à rede local.
- **MQTT:** Protocolo de comunicação para troca de mensagens em tempo real.

## Configuração do MQTT 
- **Broker:** mqtt-dashboard.com
-  **Porta:** 1883
- **Tópicos:**
- `esp32/status`: Publicação de alertas e status do sistema.

## Módulos de Comunicação
- **WiFi.h:** Biblioteca para conexão Wi-Fi.
- **PubSubClient.h:** Biblioteca para comunicação MQTT.
