// DEFINICIÓN DE PINES (Restaurados al esquema original)
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

// TIEMPOS DE CONTROL (ms)
const unsigned long T_VERDE    = 5000;
const unsigned long T_AMARILLO = 3000;
const unsigned long T_DESPEJE  = 1000;

// DEFINICIONES DE DIRECCIONES Y COLORES
const int NS = 100, EO = 200;
const int GRE = 300, RED = 301, YEL = 302;

// VARIABLES DE ESTADO
unsigned long tiempoAnterior = 0; 
int faseActiva = 1;

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
    unsigned long tiempoActual = millis(); 
    unsigned long tiempoTranscurrido = tiempoActual - tiempoAnterior;
    unsigned long tiempoObjetivo = 0;

    // MÁQUINA DE ESTADOS NO BLOQUEANTE
    switch (faseActiva) {
        case 1: 
            VEH(GRE, NS);
            Peat(true, EO);
            tiempoObjetivo = T_VERDE;

            if (tiempoTranscurrido >= tiempoObjetivo) { 
                faseActiva = 2; 
                tiempoAnterior = tiempoActual; 
            }
            break;

        case 2: 
            VEH(YEL, NS);
            Peat(false, EO);
            tiempoObjetivo = T_AMARILLO; 

            if (tiempoTranscurrido >= tiempoObjetivo) { 
                faseActiva = 3; 
                tiempoAnterior = tiempoActual; 
            }
            break;

        case 3: 
            VEH(RED, NS);
            tiempoObjetivo = T_DESPEJE;

            if (tiempoTranscurrido >= tiempoObjetivo) { 
                faseActiva = 4; 
                tiempoAnterior = tiempoActual; 
            }
            break;

        case 4: 
            VEH(GRE, EO);
            Peat(true, NS);
            tiempoObjetivo = T_VERDE;

            if (tiempoTranscurrido >= tiempoObjetivo) { 
                faseActiva = 5; 
                tiempoAnterior = tiempoActual; 
            }
            break;

        case 5: 
            VEH(YEL, EO);
            Peat(false, NS); 
            tiempoObjetivo = T_AMARILLO;

            if (tiempoTranscurrido >= tiempoObjetivo) {
                faseActiva = 6;
                tiempoAnterior = tiempoActual;
            }
            break;

        case 6: 
            VEH(RED, EO); 
            tiempoObjetivo = T_DESPEJE;

            if (tiempoTranscurrido >= tiempoObjetivo) { 
                faseActiva = 1; 
                tiempoAnterior = tiempoActual; 
            }
            break;
    }
}


//para el manejo de los semaforos de los carros 
void VEH(int color, int inter) {
    int gre = LOW, red = LOW, yel = LOW;

    if (color == GRE) {
        gre = HIGH;
    } else if (color == RED) {
        red = HIGH;
    } else if (color == YEL) {
        yel = HIGH;
    }

    if(inter == NS){
        digitalWrite(VEH_NS_ROJO, red);
        digitalWrite(VEH_NS_VERDE, gre); 
        digitalWrite(VEH_NS_AMARILLO, yel);
    } else {
        digitalWrite(VEH_EO_ROJO, red);
        digitalWrite(VEH_EO_VERDE, gre); 
        digitalWrite(VEH_EO_AMARILLO, yel);
    }
}

//Simplifica el encendido/apagado invertido de los LEDs peatonales
void Peat(bool paso, int inter) {
    bool red = !paso;

    if(inter == NS){
        digitalWrite(PEAT_NS_ROJO, red);
        digitalWrite(PEAT_NS_VERDE, paso);
    } else {
        digitalWrite(PEAT_EO_ROJO, red);
        digitalWrite(PEAT_EO_VERDE, paso);
    }
}
