// SENDER

#include <VirtualWire.h>

#define x A0
#define y A1
#define z A2

int x_val;
int y_val;
int z_val;

int x_val2;
int y_val2;
int z_val2;

void setup(){
    vw_set_tx_pin(12);
    vw_setup(2000);
    pinMode(x, INPUT);
    pinMode(y, INPUT);
    pinMode(z, INPUT);
    Serial.begin(9600);
    x_val2 = analogRead(x);
    y_val2 = analogRead(y);
    z_val2 = analogRead(z);
    delay(1000);
}

void loop(){
    x_val = analogRead(x);
    y_val = analogRead(y);
    z_val = analogRead(z);

    int x_axis = x_val - x_val2;
    int y_axis = y_val - y_val2;
    int z_axis = z_val - z_val2;
    Serial.println("--------------------------------");
    Serial.println(x_val);
    Serial.println(y_val);
    Serial.println(z_val);
    Serial.println("---------------------------------");
    // delay(1000);
    if (y_axis >= 30){
        constexpr const char *data = "f";
        vw_send((uint8_t *)data, strlen(data));
        // vw_send(1);
        vw_wait_tx();
        // delay(500);
        Serial.println("Forward");
    }
    else if (y_axis <= -30){
        constexpr const char *data = "b";
        // vw_send(2);
        vw_send((uint8_t *)data, strlen(data));
        vw_wait_tx();
        // delay(500);
        Serial.println("Backward");
    }
    else if (x_axis >= 30){
        constexpr const char *data = "r";
        vw_send((uint8_t *)data, strlen(data));
        // vw_send(3);
        vw_wait_tx();
        // delay(500);
        Serial.println("Right");
    }
    else if (x_axis <= -30){
        constexpr const char *data = "l";
        vw_send((uint8_t *)data, strlen(data));
        // vw_send(4);
        vw_wait_tx();
        // delay(500);
        Serial.println("Left");
    }
    else{
        constexpr const char *data = "s";
        vw_send((uint8_t *)data, strlen(data));
        // vw_send(0);
        vw_wait_tx();
        // delay(500);
        Serial.println("Stop");
    }
}