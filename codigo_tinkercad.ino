int ledFrio = 2;
int ledNormal = 3;
int ledQuente = 4;

int aquecedor = 10;
int arCondicionado = 9;

void setup() {
  pinMode(A5, INPUT);
  pinMode(ledNormal, OUTPUT);
  pinMode(ledQuente, OUTPUT);
  pinMode(ledFrio, OUTPUT);
  pinMode(aquecedor, OUTPUT);
  pinMode(arCondicionado, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int tempSensor = analogRead(A5);
  float voltage = ((tempSensor * 5.0) / 1024);
  float milliVolt = (voltage * 1000);
  float temperatura = ((milliVolt - 500) / 10);

  Serial.println(temperatura);

  digitalWrite(ledNormal, LOW);
  digitalWrite(ledQuente, LOW);
  digitalWrite(ledFrio, LOW);
  digitalWrite(aquecedor, LOW);
  digitalWrite(arCondicionado, LOW);

  if (temperatura >= 20 && temperatura <= 26) {
    Serial.println("Temperatura normal");
    digitalWrite(ledNormal, HIGH);
  } else if (temperatura > 26) {
    Serial.println("Temperatura alta");
    digitalWrite(ledQuente, HIGH);
    digitalWrite(arCondicionado, HIGH);
  } else {
    Serial.println("Temperatura baixa");
    digitalWrite(ledFrio, HIGH);
    digitalWrite(aquecedor, HIGH);
  }

  delay(5000);
}
