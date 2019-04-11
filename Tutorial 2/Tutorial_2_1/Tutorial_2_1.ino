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

  u8g2.begin();

  u8g2.setFont(u8g2_font_logisoso32_tf); // set the target font to calculate the pixel width
  u8g2.setFontMode(0);    // enable transparent mode, which is faster
  u8g2.firstPage(); // Clear oLed Ram
  do {
    u8g2.drawStr(0, 32, "Hi.");
  } while ( u8g2.nextPage() );
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
}
