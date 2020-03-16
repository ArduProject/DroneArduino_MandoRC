#include <EnableInterrupt.h>

long loop_timer, tiempo_ejecucion;

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

  Serial.print(PulsoPotencia);
  Serial.print("\t");
  Serial.print(PulsoPitch);
  Serial.print("\t");
  Serial.print(PulsoRoll);
  Serial.print("\t");
  Serial.println(PulsoYaw);
}
