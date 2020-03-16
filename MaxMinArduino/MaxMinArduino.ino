#include <EnableInterrupt.h>
float PulsoPotenciaMax, PulsoPotenciaMin, PulsoPitchMax, PulsoPitchMin, PulsoRollMax, PulsoYawMin, PulsoYawMax, PulsoRollMin;

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
  Serial.begin(115200);

  pinMode(7, INPUT_PULLUP);                  // YAW
  enableInterrupt(7, INTyaw, CHANGE);
  pinMode(8, INPUT_PULLUP);                  // POTENCIA
  enableInterrupt(8, INTpotencia, CHANGE);
  pinMode(12, INPUT_PULLUP);                 // PITCH
  enableInterrupt(12, INTpitch, CHANGE);
  pinMode(9, INPUT_PULLUP);                  // ROLL
  enableInterrupt(9, INTroll, CHANGE);

  digitalWrite(13, HIGH); 
  Serial.print("Encender mando RC");
  // Hasta no encender el mando no salimos de este bucle
  while (PulsoPotencia > 2500 || PulsoPotencia < 500) {
    delay(100);
  }
  digitalWrite(13, LOW);
  PulsoRollMin = 2100;
  PulsoPotenciaMin = 2100;
  PulsoPitchMin = 2100;
  PulsoYawMin = 2100;
}

void loop() {

  if (PulsoPotencia > PulsoPotenciaMax)PulsoPotenciaMax = PulsoPotencia;
  if (PulsoPotencia < PulsoPotenciaMin)PulsoPotenciaMin = PulsoPotencia;

  if (PulsoPitch > PulsoPitchMax)PulsoPitchMax = PulsoPitch;
  if (PulsoPitch < PulsoPitchMin)PulsoPitchMin = PulsoPitch;

  if (PulsoRoll > PulsoRollMax)PulsoRollMax = PulsoRoll;
  if (PulsoRoll < PulsoRollMin)PulsoRollMin = PulsoRoll;

  if (PulsoYaw > PulsoYawMax)PulsoYawMax = PulsoYaw;
  if (PulsoYaw < PulsoYawMin)PulsoYawMin = PulsoYaw;

  Serial.print("Pmax: ");
  Serial.print(PulsoPitchMax / 1000);
  Serial.print("\t");
  Serial.print("Pmin: ");
  Serial.print(PulsoPitchMin / 1000 );
  Serial.print("\t");
  Serial.print("Tmax: ");
  Serial.print(PulsoPotenciaMax / 1000 );
  Serial.print("\t");
  Serial.print("Tmin: ");
  Serial.print(PulsoPotenciaMin / 1000);
  Serial.print("\t");
  Serial.print("Ymax: ");
  Serial.print(PulsoYawMax / 1000);
  Serial.print("\t");
  Serial.print("Ymin: ");
  Serial.print(PulsoYawMin / 1000);
  Serial.print("\t");
  Serial.print("Rmax: ");
  Serial.print(PulsoRollMax / 1000);
  Serial.print("\t");
  Serial.print("Rmin: ");
  Serial.println(PulsoRollMin / 1000);
}
