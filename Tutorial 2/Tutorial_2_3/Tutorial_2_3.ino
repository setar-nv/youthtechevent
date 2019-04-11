#include <U8g2lib.h> //Oliver

#define LED1 13
#define LED2 12
#define LED3 14
#define LED4 1
#define LED5 2
#define LED6 3

U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ 16, /* clock=*/ 5, /* data=*/ 4);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Say something...");

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);

  u8g2.begin();

  u8g2.setFont(u8g2_font_logisoso16_tf); // set the target font to calculate the pixel width
  u8g2.setFontMode(0);    // enable transparent mode, which is faster
}

void loop() {
  // put your main code here, to run repeatedly:
  printOnScreen("Hi");
  blink(LED1);
  printOnScreen("what is");
  blink(LED2);
  printOnScreen("your name?.");
  blink(LED3);
}

void printOnScreen(char* text)
{
  u8g2.firstPage();
  do {
    u8g2.drawStr(0, 32, text);
  } while ( u8g2.nextPage() );
  //delay(1000); //remove delay to move faster
}

void blink(int led)
{
  digitalWrite(led, HIGH);
  delay(1000);
  digitalWrite(led, LOW);
  delay(1000);
}

