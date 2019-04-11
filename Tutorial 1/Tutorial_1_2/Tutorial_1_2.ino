#define LED1 13
#define LED2 12
#define LED3 14
#define LED4 1
#define LED5 2
#define LED6 3

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Hello World");
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  
  
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED1, HIGH);
  delay(1000);
  digitalWrite(LED1, LOW);
  delay(1000);

  digitalWrite(LED2, HIGH);
  delay(1000);
  digitalWrite(LED2, LOW);
  delay(1000);

  digitalWrite(LED3, HIGH);
  delay(1000);
  digitalWrite(LED3, LOW);
  delay(1000);

}
