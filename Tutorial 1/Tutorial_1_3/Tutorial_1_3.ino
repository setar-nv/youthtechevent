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
  blink(LED1);
  blink(LED2);
  blink(LED3);

}

void blink(int led)
{
  digitalWrite(led, HIGH);
  delay(1000);
  digitalWrite(led, LOW);
  delay(1000);
}

