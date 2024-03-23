#include <IRremote.h>
#include <Servo.h>

#define RIGHT 0xA55AFF00
#define LEFT 0xF708FF00
#define DOWN 0xAD52FF00
#define UP 0xE718FF00
#define OK 0xE31CFF00
#define NUM2 0xB946FF00
#define NUM5 0xBF40FF00

#define pino_receptor 5
#define servo_pin_horizontal 4
#define servo_pin_vertical 6
#define servo_pin_frente_tras 7
#define servo_pin_garra 8

Servo servo_horizontal;
Servo servo_vertical;
Servo servo_garra;
Servo servo_frente_tras;

int servo_position_horizontal = 0;
int servo_step_horizontal = 15;
int servo_position_vertical = 90;
int servo_step_vertical = 20;
int servo_position_garra = 0;
int servo_step_garra = 70;
int servo_position_frente_tras = 100;
int servo_step_frente_tras = 5;

unsigned long debounce_delay = 200;
unsigned long last_debounce_time = 0;

void setup_servo_horizontal() {
    servo_horizontal.attach(servo_pin_horizontal);
    servo_horizontal.write(servo_position_horizontal);
}

void setup_servo_vertical() {
    servo_vertical.attach(servo_pin_vertical);
    servo_vertical.write(servo_position_vertical);
}

void setup_servo_garra() {
    servo_garra.attach(servo_pin_garra);
    servo_garra.write(servo_position_garra);
}

void setup_servo_frente_tras() {
    servo_frente_tras.attach(servo_pin_frente_tras);
    servo_frente_tras.write(servo_position_frente_tras);
}

void setup() {
    Serial.begin(9600);
    setup_servo_vertical();
    setup_servo_horizontal();
    setup_servo_garra();
    setup_servo_frente_tras();
    IrReceiver.begin(pino_receptor, ENABLE_LED_FEEDBACK);
}

void loop() { handle_ir_command(); }

void move_servo_horizontal(int step) {
    if (servo_position_horizontal + step >= 0 &&
        servo_position_horizontal + step <= 180) {
        servo_position_horizontal += step;
        servo_horizontal.write(servo_position_horizontal);
    }
}

void move_servo_vertical(int step) {
    if (servo_position_vertical + step >= 0 &&
        servo_position_vertical + step <= 120) {
        servo_position_vertical += step;
        servo_vertical.write(servo_position_vertical);
    }
}

void move_servo_garra(int step) {
    servo_position_garra += step;

    if (servo_position_garra >= 70 || servo_position_garra <= 0) {
        servo_step_garra *= -1;
    }

    servo_garra.write(servo_position_garra);
}

void move_servo_frente_tras(int step) {
    if (servo_position_frente_tras + step >= 80 &&
        servo_position_frente_tras + step <= 110) {
        servo_position_frente_tras += step;
        servo_frente_tras.write(servo_position_frente_tras);
        Serial.println(servo_position_frente_tras);
        Serial.println(servo_step_frente_tras);
    }
}

void handle_ir_command() {
    if (IrReceiver.decode()) {
        Serial.print(" ");
        Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);
        switch (IrReceiver.decodedIRData.decodedRawData) {
        case RIGHT:
            move_servo_horizontal(servo_step_horizontal);
            break;
        case LEFT:
            move_servo_horizontal(-servo_step_horizontal);
            break;
        case OK:
            move_servo_garra(servo_step_garra);
            break;
        case DOWN:
            move_servo_vertical(-servo_step_vertical);
            break;
        case UP:
            move_servo_vertical(servo_step_vertical);
            break;
        case NUM2:
            move_servo_frente_tras(servo_step_frente_tras);
            break;
        case NUM5:
            move_servo_frente_tras(-servo_step_frente_tras);
            break;
        }
        IrReceiver.resume();
    }
}
