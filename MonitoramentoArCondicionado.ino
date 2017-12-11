// Controle de Ar condicionado Trifásico
// Ar condicionado trifasico(contactor)

// bibliotecas

#include <ESP8266WiFi.h>
#include <Modbus.h>
#include <ModbusIP_ESP8266.h>

// Modbus Registers Offsets (0-9999)

const int SWITCH_ISTS1 = 1;
const int SWITCH_ISTS2 = 2;
const int SWITCH_ISTS3 = 5;

const int LED_COIL3 = 3;
const int LED_COIL4 = 4;
const int LED_COIL5 = 5;

// Entradas Digitais

const int switchPin1 = 16; // pino D0
const int switchPin2 = 14; // pino D5
const int switchPin3 = 13; // pino D7

// Saídas Digitais

const int ledPin3 = 4;  // pino D2
const int ledPin4 = 5;  // pino D1
const int ledPin5 = 12; // pino D6



//ModbusIP object
ModbusIP mb;

void setup() {
    // Config Modbus IP

     mb.config("ScadaBR", "ScadaBRunp");

    // System inputs
    pinMode(switchPin1, INPUT_PULLUP);
    pinMode(switchPin2, INPUT_PULLUP);
    pinMode(switchPin3, INPUT_PULLUP);

    //system outputs
    pinMode(ledPin3, OUTPUT);
    pinMode(ledPin4, OUTPUT);
    pinMode(ledPin5, OUTPUT);

    // Add SWITCH_ISTS register - Use addIsts() for digital inputs

    mb.addIsts(SWITCH_ISTS1);
    mb.addIsts(SWITCH_ISTS2);
    mb.addIsts(SWITCH_ISTS3);


    // acionamento do contactor_k1/k2
    mb.addCoil(LED_COIL3);
    mb.addCoil(LED_COIL4);
    mb.addCoil(LED_COIL5);


} /*End Setup*/

void loop() {

   //Call once inside loop() - all magic here
   mb.task();

   //Attach switchPin to SWITCH_ISTS register

   mb.Ists(SWITCH_ISTS1, digitalRead(switchPin1));
   mb.Ists(SWITCH_ISTS2, digitalRead(switchPin2));
   mb.Ists(SWITCH_ISTS3, digitalRead(switchPin3));

   //Write LED_COIL to Coil register


    digitalWrite(ledPin3, !mb.Coil(LED_COIL3));
    digitalWrite(ledPin4, !mb.Coil(LED_COIL4));
    digitalWrite(ledPin5, !mb.Coil(LED_COIL5));
    delay(200);

} /* End loop */
