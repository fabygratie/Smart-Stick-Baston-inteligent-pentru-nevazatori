#define echoPin 2
#define trigPin 4
#define motorPin 5

long duration, distance;

void setup() {
  Serial.begin(9600);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  ledcSetup(0, 5000, 8);
  ledcAttachPin(motorPin, 0);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration / 58.2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance > 0 && distance < 100) {
    int intensity = map(distance, 100, 0, 50, 255);
    intensity = constrain(intensity, 0, 255);
    ledcWrite(0, intensity);
  } else {
    ledcWrite(0, 0);
  }

  delay(100);
}
