const int pingPin = 7;    // Pinul Signal al senzorului
const int motorEnable = 9; // PWM pentru viteză
const int motorIn1 = 12;    // Direcție 1
const int motorIn2 = 10;   // Direcție 2

void setup() {
  pinMode(motorEnable, OUTPUT);
  pinMode(motorIn1, OUTPUT);
  pinMode(motorIn2, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  long durata, cm;

  // Citire senzor ultrasonic (3 pini)
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);

  pinMode(pingPin, INPUT);
  durata = pulseIn(pingPin, HIGH);
  cm = durata / 29 / 2; // Convertim în centimetri

  // Logica de control PWM pentru renuleț (trenuleț)
  digitalWrite(motorIn1, HIGH); // Setează direcția înainte
  digitalWrite(motorIn2, LOW);

  int viteza = 0;

  if (cm > 100) {        // Cale liberă
    viteza = 255; 
  } else if (cm > 30) {  // Încetinește la barieră
    viteza = 100;
  } else {               // Stop la obstacol sub 30cm
    viteza = 0;
  }

  analogWrite(motorEnable, viteza); // Trimitem semnalul PWM

  Serial.print("Distanta: ");
  Serial.print(cm);
  Serial.print("cm - Viteza PWM: ");
  Serial.println(viteza);
  
  delay(100);
}
