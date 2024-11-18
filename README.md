# Empilhadeira Automatizada com ESP32

## Descrição
Este projeto implementa uma empilhadeira automatizada utilizando um ESP32, sensores ultrassônicos, buzzer, LEDs e comunicação MQTT para monitoramento remoto e alertas em tempo real.

## Funcionamento e Uso
- **Inicialização:** O ESP32 se conecta à rede Wi-Fi e ao broker MQTT.
- **Leitura de Sensores:** O sensor ultrassônico mede continuamente a distância de objetos.
- **Ação dos Atuadores:** O buzzer e o LED amarelo são acionados quando um obstáculo é detectado.
- **Comunicação:** Mensagens são enviadas ao broker MQTT para monitoramento remoto.
