// RECEIVER 3 and 4

#include <VirtualWire.h>
#include <AFMotor.h>

AF_DCMotor motor3(3);
AF_DCMotor motor4(4);
static int packet = 0;
void setup(){
    vw_set_rx_pin(11);
    vw_setup(2000);
    vw_rx_start();
    motor3.setSpeed(250);
    motor4.setSpeed(250);
    Serial.begin(9600);
}

void loop(){

    uint8_t buf[VW_MAX_MESSAGE_LEN];
    uint8_t buflen = VW_MAX_MESSAGE_LEN;
    // vw_get_message(buf, &buflen);
    // delay(100);
    // buf[0]=0;

    // Serial.println(buf[0]);

    if (vw_get_message(buf, &buflen)){
        packet = 0;
        Serial.println(buf[0]);
        if (buf[0] == 'f'){
            motor3.run(FORWARD);
            motor4.run(FORWARD);

            // delay(200);
            // Serial.println("Forward");
        }
        else if (buf[0] == 'b'){
            motor3.run(BACKWARD);
            motor4.run(BACKWARD);
            // delay(200);
            // Serial.println("Backward");
        }
        else if (buf[0] == 'l'){
            motor3.run(FORWARD);
            motor4.run(RELEASE);
            // delay(200);
            // Serial.println("Left");
        }
        else if (buf[0] == 'r'){
            motor3.run(RELEASE);
            motor4.run(FORWARD);
            // delay(100);
            // Serial.println("Right");
        }
        else if (buf[0] == 's'){
            motor3.run(RELEASE);
            motor4.run(RELEASE);
            // delay(200);
            // Serial.println("Stop");
        }
    }
    else{
        if (packet >= 200){
            motor3.run(RELEASE);
            motor4.run(RELEASE);
            // Serial.println("Nothing reviced\n");
        }
        else{
            packet++;
        }
        Serial.println(packet);
    }
}