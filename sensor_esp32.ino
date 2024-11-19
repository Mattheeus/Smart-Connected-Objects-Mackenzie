#include <WiFi.h>
#include <PubSubClient.h>

// Credenciais do Wi-Fi
const char* ssid = "Vinicius";  // Nome da rede Wi-Fi
const char* password = "Viniwifi93";  // Senha do Wi-Fi

// Defina o servidor MQTT (mqtt-dashboard.com) e porta não segura 1883
const char* mqttServer = "mqtt-dashboard.com";  // Broker MQTT público
const int mqttPort = 1883;  // Porta MQTT sem SSL (não segura)
const char* mqttUser = "";  // Nome de usuário (não necessário)
const char* mqttPassword = "";  // Senha (não necessária)

// Defina o nome do cliente MQTT (ID único para o dispositivo)
const char* clientID = "clientId-SPkHgfbH0t";

// Pinos do sensor ultrassônico
const int TRIG = 23;
const int ECHO = 5;

// Pinos dos LEDs e buzzer
const int ledVerde = 14;     // LED verde (indica segurança)
const int ledAmarelo = 13;   // LED amarelo (indica alerta)
const int buzzer = 25;       // Buzzer

// Variáveis de controle do sensor de proximidade
const int distancia_carro = 10;  // Distância mínima em cm para gerar o alerta

// Crie o objeto WiFi e MQTT
WiFiClient espClient;  // Usando WiFiClient para conexões sem SSL
PubSubClient client(espClient);

// Função de callback para quando uma nova mensagem for recebida
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Mensagem recebida no tópico: ");
  Serial.print(topic);
  Serial.print(" - Mensagem: ");
  
  // Exibe a mensagem recebida no Monitor Serial
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

// Função que mede a distância usando o sensor ultrassônico
int sensor_morcego(int pinotrig, int pinoecho) {
  digitalWrite(pinotrig, LOW);
  delayMicroseconds(2);
  digitalWrite(pinotrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinotrig, LOW);
  
  return pulseIn(pinoecho, HIGH) / 58;
}

void setup() {
  // Inicializa o monitor serial
  Serial.begin(115200);
  
  // Conecta ao Wi-Fi
  Serial.println("Conectando ao Wi-Fi...");
  WiFi.begin(ssid, password);
  
  // Aguarda a conexão com o Wi-Fi
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Aguardando conexão com o Wi-Fi...");
  }
  Serial.println("Conectado ao Wi-Fi!");

  // Configura o servidor MQTT e a função de callback
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);  // Função de callback para quando recebermos uma mensagem MQTT
  
  // Configura os pinos do sensor de proximidade
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  
  // Configura os pinos dos LEDs e do buzzer
  pinMode(ledVerde, OUTPUT);
  pinMode(ledAmarelo, OUTPUT);
  pinMode(buzzer, OUTPUT);
}

void loop() {
  // Se o cliente não estiver conectado ao MQTT, tenta se conectar
  if (!client.connected()) {
    Serial.println("Tentando conectar ao MQTT...");
    
    // Tenta conectar ao servidor MQTT
    if (client.connect(clientID, mqttUser, mqttPassword)) {
      Serial.println("Conectado ao MQTT!");
      
      // Inscreve-se no tópico para receber mensagens (se necessário)
      client.subscribe("esp32/status");
    } else {
      Serial.print("Falha na conexão, rc=");
      Serial.print(client.state());
      Serial.println(" Tente novamente em 5 segundos.");
      delay(5000);  // Tenta reconectar a cada 5 segundos
    }
  }

  // Medir a distância com o sensor ultrassônico
  int distancia = sensor_morcego(TRIG, ECHO);
  Serial.print("Distância medida: ");
  Serial.print(distancia);
  Serial.println(" cm");

  // Lógica dos LEDs e buzzer
  if (distancia <= distancia_carro) {
    // Se a distância for menor ou igual ao limite definido, acende o LED amarelo e o buzzer
    digitalWrite(ledVerde, LOW);  // Apaga o LED verde
    digitalWrite(ledAmarelo, HIGH);  // Acende o LED amarelo
    tone(buzzer, 1000);  // Ativa o buzzer com tom de 1000 Hz
    Serial.println("Objeto muito perto! Alerta enviado.");
    client.publish("esp32/status", "Alerta: Objeto muito perto!");
  } else {
    // Se a distância for maior, acende o LED verde e apaga o amarelo e o buzzer
    digitalWrite(ledVerde, HIGH);  // Acende o LED verde
    digitalWrite(ledAmarelo, LOW);  // Apaga o LED amarelo
    noTone(buzzer);  // Desliga o buzzer
    Serial.println("Espaço livre!");
  }

  // Chama o loop do cliente MQTT para manter a conexão ativa e processar mensagens
  client.loop();
  
  delay(1000);  // Espera um segundo antes de medir novamente
}