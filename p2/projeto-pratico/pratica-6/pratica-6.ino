#include <IRremote.h>
#include <Stepper.h>

#define SENSOR_PIN 12

#define RIGHT 0xA55AFF00
#define LEFT 0xF708FF00
#define OK 0xE31CFF00

#define NUM1 0xBA45FF00
#define NUM2 0xB946FF00
#define NUM3 0xB847FF00
#define NUM4 0xBB44FF00
#define NUM5 0xBF40FF00
#define NUM6 0xBC43FF00
#define NUM7 0xF807FF00
#define NUM8 0xEA15FF00
#define NUM9 0xF609FF00
#define NUM0 0xE619FF00

#define STEP 64

const float dps = 360 / STEP;

Stepper motor(STEP, 8, 10, 9, 11);

int posicao_atual = 0, sentido = 0;

bool modo_de_calibragem = true;
bool modo_de_giro = false;

int quantidade_de_teclas = 0;
int valor;

void setup() {
    IrReceiver.begin(SENSOR_PIN, ENABLE_LED_FEEDBACK);
    motor.setSpeed(200);
    Serial.begin(9600);
}

void loop() {
    if (modo_de_giro == true)
        girar_motor(sentido);

    if (IrReceiver.decode()) {
        Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);
        handle_keys(IrReceiver.decodedIRData.decodedRawData);
        IrReceiver.resume();
    }
}

void handle_keys(long unsigned int key) {
    switch (key) {
    case RIGHT:
        sentido = 1;
        modo_de_giro = true;
        modo_de_calibragem = false;
        break;

    case LEFT:
        sentido = -1;
        modo_de_giro = true;
        modo_de_calibragem = false;
        break;

    case OK:
        if (modo_de_giro == false && modo_de_calibragem == true) {
            calibrate(valor);
            valor = 0;
            posicao_atual = 0;
            quantidade_de_teclas = 0;
        }

        if (modo_de_giro == true && modo_de_calibragem == false) {
            modo_de_giro = false;
            modo_de_calibragem = true;

            int angulo = 360 - posicao_atual;
            int passo = degree_to_step(angulo);
            sentido = 1;
            motor.step(passo);

            posicao_atual = 0;
            quantidade_de_teclas = 0;
            valor = 0;
        }
        break;

    case NUM0:
    case NUM1:
    case NUM2:
    case NUM3:
    case NUM4:
    case NUM5:
    case NUM6:
    case NUM7:
    case NUM8:
    case NUM9:
        if (modo_de_calibragem == true && quantidade_de_teclas < 3) {
            quantidade_de_teclas++;

            // Extract the numeric value from the key
            valor = valor * 10 + (key & 0x0F);
        }
        break;
    }
}

void girar_motor(int sentido) {
    int passo = degree_to_step(1);

    motor.step(passo * sentido);

    int nova_posicao = posicao_atual + sentido;

    if (nova_posicao >= 360)
        nova_posicao -= 360;
    else if (nova_posicao <= 0)
        nova_posicao += 360;

    posicao_atual = nova_posicao;

    Serial.println("Posição do motor: ");

    Serial.print(posicao_atual);
}

void calibrate(int angulo) {
    motor.step(degree_to_step(angulo));
    posicao_atual = 0;
}

int degree_to_step(int degree) { return degree * dps; }
