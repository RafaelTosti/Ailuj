// inclui biblioteca do servomotor
#include <Servo.h> 

// define pinos dos servos
#define pinServ1 9
#define pinServ2 10
#define pinServ3 3
#define pinServ4 5

// define as portas dos potenciômetros
#define pot1 A0
#define pot2 A1
#define pot3 A2

// define os pinos dos interruptores
#define interruptor1Pin 6
#define interruptor2Pin 7

// nomeia os servos
Servo serv1, serv2, serv3, serv4;

// variáveis para os ângulos de cada motor
int motor1, motor2, motor3, motor4;

// variável para armazenar o estado dos interruptores
bool interruptor1Estado = false;
bool interruptor2Estado = false;

// Variáveis para temporização
unsigned long mostradorTimer = 0;
const unsigned long intervaloMostrador = 5000;

void setup() {
  // inicia o monitor serial
  Serial.begin(9600); 

  // atribui pinos dos servos
  serv1.attach(pinServ1);
  serv2.attach(pinServ2);
  serv3.attach(pinServ3);
  serv4.attach(pinServ4);
  
  // configura os pinos dos interruptores como entrada
  pinMode(interruptor1Pin, INPUT_PULLUP);
  pinMode(interruptor2Pin, INPUT_PULLUP);
}

void loop() {
    // Verifica se o interruptor 2 está ativado
    if (digitalRead(interruptor2Pin) == LOW) { // interruptor 2 pressionado
        // Executa outro código quando o interruptor 2 é ativado
        Serial.println("Interruptor 2 ativado! Executando outro código...");
        
        // Código alternativo em execução (exemplo)
        for (int i = 0; i < 3; i++) {
            Serial.println("Código alternativo em execução!");
            delay(500);
        }

        // Aqui, você pode definir posições específicas para os motores, se desejar
        serv1.write(90); // Posiciona o servo 1 em um ângulo específico
        serv2.write(90); // Posiciona o servo 2 em um ângulo específico
        serv3.write(90); // Posiciona o servo 3 em um ângulo específico
        serv4.write(90); // Posiciona o servo 4 em um ângulo específico

        delay(2000);
        serv1.write(180); 
        serv2.write(180); 
        serv3.write(180); 
        serv4.write(180); 

        delay(2000);
        serv1.write(10); 
        serv2.write(10); 
        serv3.write(10); 
        serv4.write(10); 

        delay(2000);

    } else {
        // Leitura dos valores dos potenciômetros e ajuste dos ângulos
        motor1 = map(analogRead(pot1), 0, 1023, 0, 180);
        motor2 = map(analogRead(pot2), 0, 1023, 0, 180);
        motor3 = map(analogRead(pot3), 0, 1023, 0, 180);

        // Controla o motor 4 baseado no estado do interruptor 1
        if (digitalRead(interruptor1Pin) == LOW) {
            motor4 = 90;
        } else {
            motor4 = 0;
        }

        // Posiciona os servos dos motores
        serv1.write(motor1);
        serv2.write(motor2);
        serv3.write(motor3);
        serv4.write(motor4);

        // Envia os dados ao monitor serial
        if (millis() - mostradorTimer >= intervaloMostrador) {
            // envio para o monitor serial do posicionamento dos motores
            Serial.println("**********************************************");
            
            Serial.print("Pot1: ");
            Serial.print(analogRead(pot1));
            Serial.print(" Angulo Motor1: ");
            Serial.println(motor1);

            Serial.print("Pot2: ");
            Serial.print(analogRead(pot2));
            Serial.print(" Angulo Motor2: ");
            Serial.println(motor2);

            Serial.print("Pot3: ");
            Serial.print(analogRead(pot3));
            Serial.print(" Angulo Motor3: ");
            Serial.println(motor3);

            Serial.print("Interruptor 1 (Motor 4): ");
            Serial.println(motor4 == 90 ? "Ativado" : "Desativado");

            Serial.print("Interruptor 2: ");
            Serial.println(digitalRead(interruptor2Pin) == LOW ? "Ativado" : "Desativado");

            mostradorTimer = millis(); // Reinicia o timer
        }
    }

    // Pequeno delay para suavizar as leituras
    delay(100);
}
