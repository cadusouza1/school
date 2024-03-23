#include <TM1637Display.h>

// Pino do LED azul
#define LED1 3

// Pino do LED verde
#define LED2 12

// Pino do potenciômetro
#define POT A1

// Pino do clock para o display de 7 segmentos
#define CLK 7

// Pino de dados para o display de 7 segmentos
#define DIO 4

// Tempo máximo para o piscar do LED azul (em milissegundos)
#define TEMPO_MAX 2500

// Tempo mínimo para o piscar do LED azul (em milissegundos)
#define TEMPO_MIN 100

// Variável para armazenar o tempo anterior do LED azul
unsigned long int tempo_anterior_azul = 0;

// Variável para armazenar o tempo anterior do LED verde
unsigned long int tempo_anterior_verde = 0;

// Variável para controlar o estado do LED azul (ligado/desligado)
bool estado_led_azul = false;

// Variável para controlar o estado do LED verde (ligado/desligado)
bool estado_led_verde = false;

// Variável para armazenar o valor lido do potenciômetro
int valor_analogico = 0;

TM1637Display display(CLK, DIO);

void setup() {
    pinMode(POT, INPUT);
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    DDRB = 0b00100000; // Configura o pino 5 (LED verde) como saída

    display.setBrightness(0x0F); // Configura o brilho do display de 7 segmentos
}

void loop() {
    atualiza_led_azul();
    atualiza_led_vermelho();
    atualiza_led_verde();
    display.showNumberDecEx(le_voltagem() * 100, DDRB, true);
}

void atualiza_led_azul() {
    if (millis() - tempo_anterior_azul >=
        map(analogRead(POT), 0, 1023, TEMPO_MIN, TEMPO_MAX)) {
        tempo_anterior_azul = millis();
        estado_led_azul = !estado_led_azul;
        digitalWrite(LED2, estado_led_azul);
    }
}

void atualiza_led_vermelho() {
    valor_analogico = analogRead(POT);
    analogWrite(LED1, map(valor_analogico, 0, 1023, 0, 255));
}

void atualiza_led_verde() {
    if (millis() - tempo_anterior_verde >= 500) {
        tempo_anterior_verde = millis();
        estado_led_verde = !estado_led_verde;
        if (estado_led_verde)
            PORTB = 0b00100000; // Acende o LED verde
        else
            PORTB = 0b00000000; // Apaga o LED verde
    }
}

float le_voltagem() { return analogRead(POT) * (5.0 / 1023.0); }
