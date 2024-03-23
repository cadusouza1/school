#include <LiquidCrystal.h>
#include <Servo.h>

const int button_pin = 2;
const int servo_pin = 4;

Servo servo;
int servo_position = 0;
int servo_step = 45;

const int lcd_rs = 13;
const int lcd_enable = 12;
const int lcd_d4 = 11;
const int lcd_d5 = 10;
const int lcd_d6 = 9;
const int lcd_d7 = 8;

LiquidCrystal lcd(lcd_rs, lcd_enable, lcd_d4, lcd_d5, lcd_d6, lcd_d7);

const unsigned long debounce_delay = 200;
unsigned long last_debounce_time = 0;

const int lcd_columns = 16;
const int lcd_rows = 2;

void setup() {
    setup_servo();
    setup_lcd();
    setup_button();
    Serial.begin(9600);
}

void loop() {}

void setup_servo() {
    servo.attach(servo_pin);
    servo.write(servo_position);
}

void setup_lcd() {
    lcd.begin(lcd_columns, lcd_rows);
    lcd.print("Position: ");
    lcd.setCursor(0, 1);
    lcd.print(servo_position);
}

void setup_button() {
    pinMode(button_pin, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(button_pin), button_pressed, FALLING);
}

void button_pressed() {
    if (millis() - last_debounce_time >= debounce_delay) {
        last_debounce_time = millis();

        if (digitalRead(button_pin) == LOW) {
            update_servo_position();
            update_lcd();
            log_position();
        }
    }
}

void update_servo_position() {
    servo_position += servo_step;
    const int servo_max_position = 180;
    const int servo_min_position = 0;

    if (servo_position >= servo_max_position ||
        servo_position <= servo_min_position) {
        servo_step *= -1; // Invert the direction
    }

    servo.write(servo_position);
}

void update_lcd() {
    const int lcd_position_row = 1;

    lcd.setCursor(0, lcd_position_row);
    lcd.print("    "); // Clear the previous position
    lcd.setCursor(0, lcd_position_row);
    lcd.print(servo_position);
}

void log_position() {
    Serial.print("Position: ");
    Serial.println(servo_position);
}
