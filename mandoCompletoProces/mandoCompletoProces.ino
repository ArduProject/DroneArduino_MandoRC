#include <EnableInterrupt.h>

long loop_timer, tiempo_ejecucion;
float wPitch, wRoll, wYaw, pulsoPotencia;

// MANDO POTENCIA
const int PulsoMaxPotencia = 2000;
const int PulsoMinPotencia = 1000;
const float tMaxPotencia = 1.83;  // <-- Si teneis la entrada Throttle invertida sustituid este valor
const float tMinPotencia = 1.12;  // <-- por este y viceversa

const float tMax = 2;
const float tMin = 1;

// MANDO PITCH
const int wMaxPitch = -30; // <-- Si teneis la entrada Pitch invertida sustituid este valor
const int wMinPitch = 30;  // <-- por este y viceversa

// MANDO ROLL
const int wMaxRoll = 30;  // <-- Si teneis la entrada Roll invertida sustituid este valor
const int wMinRoll = -30; // <-- por este y viceversa

// MANDO YAW
const int wMaxYaw = 30;  // <-- Si teneis la entrada Yaw invertida sustituid este valor
const int wMinYaw = -30; // <-- por este y viceversa

volatile long contPotenciaInit; // LEER MANDO RC --> POTENCIA
volatile int PulsoPotencia;
void INTpotencia() {
  if (digitalRead(8) == HIGH) contPotenciaInit = micros();
  if (digitalRead(8) == LOW)PulsoPotencia = micros() - contPotenciaInit;
}

volatile long contPitchInit; // LEER MANDO RC --> PITCH
volatile int PulsoPitch;
void INTpitch() {
  if (digitalRead(12) == HIGH) contPitchInit = micros();
  if (digitalRead(12) == LOW) PulsoPitch = micros() - contPitchInit;
}

volatile long contRollInit; // LEER MANDO RC --> ROLL
volatile int PulsoRoll;
void INTroll() {
  if (digitalRead(9) == HIGH) contRollInit = micros();
  if (digitalRead(9) == LOW) PulsoRoll = micros() - contRollInit;
}

volatile long contYawInit; // LEER MANDO RC --> YAW
volatile int PulsoYaw;
void INTyaw() {
  if (digitalRead(7) == HIGH) contYawInit = micros();
  if (digitalRead(7) == LOW) PulsoYaw = micros() - contYawInit;
}

void setup() {
  pinMode(13, OUTPUT);

  pinMode(7, INPUT_PULLUP);                  // YAW
  enableInterrupt(7, INTyaw, CHANGE);
  pinMode(8, INPUT_PULLUP);                  // POTENCIA
  enableInterrupt(8, INTpotencia, CHANGE);
  pinMode(12, INPUT_PULLUP);                 // PITCH
  enableInterrupt(12, INTpitch, CHANGE);
  pinMode(9, INPUT_PULLUP);                  // ROLL
  enableInterrupt(9, INTroll, CHANGE);

  Serial.begin(115200);
  delay(200);
}

void loop() {
  while (micros() - loop_timer < 10000);
  tiempo_ejecucion = (micros() - loop_timer) / 1000;
  loop_timer = micros();

  // =============== Ecuaciones de procesamiento
  wPitch =   ((wMinPitch - wMaxPitch) / (tMax - tMin)) * ((PulsoPitch ) / 1000.00 - tMin) + wMaxPitch;
  wRoll =   ((wMaxRoll - wMinRoll) / (tMax - tMin)) * ((PulsoRoll) / 1000.00 - tMin) + wMinRoll;
  wYaw =  ((wMinYaw - wMaxYaw) / (tMax - tMin)) * ((PulsoYaw) / 1000.00 - tMin) + wMaxYaw;
  pulsoPotencia =  ((PulsoMaxPotencia - PulsoMinPotencia) / (tMinPotencia)) * ((PulsoPotencia) / 1000.00 - tMaxPotencia) + PulsoMinPotencia;
  // =============== Ecuaciones de procesamiento

  Serial.print(pulsoPotencia);
  Serial.print("\t");
  Serial.print(wPitch);
  Serial.print("\t");
  Serial.print(wRoll);
  Serial.print("\t");
  Serial.println(wYaw);
}
