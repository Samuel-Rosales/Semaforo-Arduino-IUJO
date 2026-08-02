const int VEH_NS_VERDE    = 4;
const int VEH_NS_AMARILLO = 3;
const int VEH_NS_ROJO     = 2;
const int PEAT_NS_ROJO    = 5;
const int PEAT_NS_VERDE   = 6;
const int VEH_EO_VERDE    = 11;
const int VEH_EO_AMARILLO = 10;
const int VEH_EO_ROJO     = 9;
const int PEAT_EO_VERDE   = 8;
const int PEAT_EO_ROJO    = 7;

const unsigned long T_VERDE    = 5000;
const unsigned long T_AMARILLO = 3000;
const unsigned long T_DESPEJE  = 1000;

void setup() {
    for (int pin = 2; pin <= 11; pin++) {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
        }
    digitalWrite(VEH_NS_ROJO, HIGH);
    digitalWrite(PEAT_NS_ROJO, HIGH);
    digitalWrite(VEH_EO_ROJO, HIGH);
    digitalWrite(PEAT_EO_ROJO, HIGH);
    delay(1000);
}

void loop() {
    // FASE 1
    digitalWrite(VEH_NS_ROJO, LOW);
    digitalWrite(VEH_NS_VERDE, HIGH);
    digitalWrite(PEAT_EO_ROJO, LOW);
    digitalWrite(PEAT_EO_VERDE, HIGH);
    delay(T_VERDE);

    // FASE 2
    digitalWrite(VEH_NS_VERDE, LOW);
    digitalWrite(VEH_NS_AMARILLO, HIGH);
    digitalWrite(PEAT_EO_VERDE, LOW);
    digitalWrite(PEAT_EO_ROJO, HIGH);
    delay(T_AMARILLO);

    // FASE DESPEJE 1
    digitalWrite(VEH_NS_AMARILLO, LOW);
    digitalWrite(VEH_NS_ROJO, HIGH);
    delay(T_DESPEJE);

    // FASE 3
    digitalWrite(VEH_EO_ROJO, LOW);
    digitalWrite(VEH_EO_VERDE, HIGH);
    digitalWrite(PEAT_NS_ROJO, LOW);
    digitalWrite(PEAT_NS_VERDE, HIGH);
    delay(T_VERDE);

    // FASE 4
    digitalWrite(VEH_EO_VERDE, LOW);
    digitalWrite(VEH_EO_AMARILLO, HIGH);
    digitalWrite(PEAT_NS_VERDE, LOW);
    digitalWrite(PEAT_NS_ROJO, HIGH);
    delay(T_AMARILLO);

    // FASE DESPEJE 2
    digitalWrite(VEH_EO_AMARILLO, LOW);
    digitalWrite(VEH_EO_ROJO, HIGH);
    delay(T_DESPEJE);
}