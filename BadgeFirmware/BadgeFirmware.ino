/*
  YTE ESP8266 MQTT example

  This sketch demonstrates the capabilities of the pubsub library in combination
  with the ESP8266 board/library.

  It connects to an MQTT server then:
  - send badge data every second and 10 second.

  It will reconnect to the server and wifi if the connection is lost using a non-blocking
  reconnect function.

  To install the ESP8266 board, (using Arduino 1.6.4+):
  - Add the following 3rd party board manager under "File -> Preferences -> Additional Boards Manager URLs":
       http://arduino.esp8266.com/stable/package_esp8266com_index.json
  - Open the "Tools -> Board -> Board Manager" and click install for the ESP8266"
  - Select your ESP8266 in "Tools -> Board" eg. ESP-12E Module

*/

#include <ESP8266WiFi.h>
#include <PubSubClient.h> //Nick O'Leary
#include <ArduinoJson.h> //Benoit Blanchon
#include <U8g2lib.h> //Oliver
#include <TaskScheduler.h> //Antoli

//Led Pin Config
#define LED1 13
#define LED2 12
#define LED3 14
#define LED4 1
#define LED5 2
#define LED6 3

//U8g2 Contructor
U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ 16, /* clock=*/ 5, /* data=*/ 4);
// Alternative board version. Uncomment if above doesn't work.
// U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ 4, /* clock=*/ 14, /* data=*/ 2);

String badgeName = "YouthTech"; // scroll this text from right to left, Max 11 chars

// Update these with values suitable for your network. Badge-Wifi is the event wifi
const char* ssid = "Badge-WiFi"; // wifi name/sid
const char* password = "zp5rW5R2"; //wifi password


//**************************** DO NOT EDIT BELOW UNLES YOU KNOW WHAT YOU ARE DOING ****************************

//IOT Hub details
const char* mqtt_server = "iot.miceline.com";

//Hardware info
String bmac = ""; // wifi base station id
String mac; //device mac address

//MQTT
WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
long lastMsg2 = 0;
char msg[50];

//Battery information and screensaver
boolean displayState = true;
long lastVddSample = 0;
int lowVoltageCounter = 0;

//analog voltage reading
float vdd = 0;
ADC_MODE(ADC_VCC);

//Led Array config
int ledPins[] = {LED1, LED2, LED3, LED4, LED5, LED6};
int idx = 0;

// Callback methods prototypes
void blinkLed();
void blinkLed2();
void blinkLed3();

//Tasks
Scheduler runner;
Task t1(2, 200, &blinkLed, NULL , true, NULL, &Disable1);
Task t2(2, 200, &blinkLed2, NULL , true, NULL, &Disable1);
Task t3(2, 400, &blinkLed3, NULL , true, NULL, &Disable1);

//Wifi Events
WiFiEventHandler gotIpEventHandler, disconnectedEventHandler, onConnectedEventHandler;
long lastReconnectAttempt = 0;

//Wifi non blocking variables
int reqConnect = 16 ;
int isConnected = 0 ;
const long interval = 500; //interval between wifi status check during reconnection
const long reqConnectNum = 15; // number of intervals to wait for connection
unsigned long previousMillis;
long rssi = 0;

//display variables
u8g2_uint_t offset;     // current offset for the scrolling text
u8g2_uint_t width;      // pixel width of the scrolling text (must be lesser than 128 unless U8G2_16BIT is defined
boolean fade = false;


//Shows
int blink2Count =0;
int blink2pwm = 0;
boolean blink2dir = false;

// wifi setup and config
void setup_wifi() {

  gotIpEventHandler = WiFi.onStationModeGotIP([](const WiFiEventStationModeGotIP & event)
  {
    bmac = WiFi.BSSIDstr();
    isConnected = 2;
    fade = false;
  });

  onConnectedEventHandler = WiFi.onStationModeConnected([](const WiFiEventStationModeConnected & event)
  {
    isConnected = 1;
  });

  disconnectedEventHandler = WiFi.onStationModeDisconnected([](const WiFiEventStationModeDisconnected & event)
  {
    isConnected = 0;
  });

  delay(10); // solves some issues
  randomSeed(micros());
}

// mqtt publish data call back
void callback(char* topic, byte* payload, unsigned int length) {
  StaticJsonDocument<200> doc;
  DeserializationError error = deserializeJson(doc, payload);

  if (error) {
    // error during deserialization
  } else {

    //check for root commands
    String _badgeName = doc["badge_name"];
    int _show = doc["show"];
    JsonArray ledsArray = doc["leds"];
    
    if (_badgeName != "null") {
      badgeName = _badgeName;
      setBadgeName();

      u8g2.clear();
      offset = 0;
      u8g2.setFont(u8g2_font_logisoso16_tf); // set the target font to calculate the pixel width
      width = u8g2.getUTF8Width(badgeName.c_str());    // calculate the pixel width of the text
      u8g2.setFontMode(0);

    }
    if (!ledsArray.isNull())
    {
      int i = 0;
      for (JsonVariant v : ledsArray) {
        int state = v.as<int>();
        if(state == 1){
          int pinState = digitalRead(ledPins[i]);
          if(pinState == 1) digitalWrite(ledPins[i], LOW);
          else digitalWrite(ledPins[i], HIGH); 
        }
        //Serial.println(v.as<int>());
        i++;
      }
    }
    if (_show)
    {
      switch (_show)
      {
        case 1:
          t1.restartDelayed();
          break;
        case 2:
          t2.restartDelayed();
          break;
        case 3:
          t3.restartDelayed();
          break;
      }
    }
    return;
  }

}

// mqtt client reconnect routine non blocking
boolean reconnect() {
  String clientId = "ESP8266Client-";
  clientId += String(random(0xffff), HEX);
  if (client.connect(mac.c_str())) {
    String outTopic = "/badge/" + mac + "/out/";
    client.publish(outTopic.c_str(), "Online");
    String inTopic = "/badge/" + mac + "/in";
    client.subscribe(inTopic.c_str());
  }
  return client.connected();
}

//collect board voltage
void sampleVdd()
{
  //sample vdd every 5 seconds
  long now = millis();
  if (now - lastVddSample > 500) {
    vdd = ESP.getVcc() / 1000.0;
    if (vdd < 2.60) lowVoltageCounter ++;
    else lowVoltageCounter --;
    if (lowVoltageCounter < 0) lowVoltageCounter = 0;
    if (lowVoltageCounter > 5) lowVoltageCounter = 5;
    lastVddSample = millis();
  }
  if (lowVoltageCounter >= 5)
  {
    displayState = false;
    u8g2.setPowerSave(1);
  } else {
    displayState = true;
    u8g2.setPowerSave(0);
  }
}

//Data set 1 msg type 1
void mqttHearthBeat(int poll)
{
  long now = millis();
  if (now - lastMsg > poll) {
    lastMsg = now;
    StaticJsonDocument<300> jsonBuffer;
    jsonBuffer["badge_name"] = badgeName.c_str();
    jsonBuffer["badge_voltage"] = vdd;
    jsonBuffer["msg_type"] = 1;
    jsonBuffer["leds"] = jsonBuffer.as<JsonArray>();
    for (int i = 0; i < 6; i++) {
      jsonBuffer["leds"].add(digitalRead(ledPins[i]));
    }
    String outTopic = "/badge/" + mac + "/out";
    publishHeartBeat(jsonBuffer,outTopic);
  }
}

//Data set 2 msg type 2
void mqttHearthBeat2(int poll)
{
  long now = millis();
  if (now - lastMsg2 > poll) {
    lastMsg2 = now;
    rssi = WiFi.RSSI();
    StaticJsonDocument<300> jsonBuffer;
    jsonBuffer["msg_type"] = 2;
    jsonBuffer["badge_uptime"] = millis();
    jsonBuffer["wifi_station_mac"] = bmac.substring(9);
    jsonBuffer["wifi_rssi"] = rssi;
    String outTopic = "/badge/" + mac + "/out2";
    publishHeartBeat(jsonBuffer,outTopic);
  }
}

// Send data to iot hub
boolean publishHeartBeat(StaticJsonDocument<300> jsonBuffer, String outTopic)
{
  char JSONmessageBuffer[200];
  serializeJson(jsonBuffer, JSONmessageBuffer, 200);
  if(client.connected())
  {
    if (client.publish(outTopic.c_str(), JSONmessageBuffer) == true) return true;
    else return false;
  }else return false;
}

//Control screen
void displayText()
{
  u8g2_uint_t x;
  u8g2.firstPage();
  do {

    // draw the scrolling text at current offset
    x = offset;
    u8g2.setFont(u8g2_font_logisoso16_tf);   // set the target font
    do {                // repeated drawing of the scrolling text...
      u8g2.drawUTF8(x, 27, badgeName.c_str());     // draw the scolling text
      x += width;           // add the pixel width of the scrolling text
    } while ( x < u8g2.getDisplayWidth() );   // draw again until the complete display is filled

    //ssid display
    String ssidName;
    if (isConnected == 2) ssidName = ssid;
    else ssidName = "connecting...";
    if(!fade){
      u8g2.setFont(u8g2_font_helvR08_tf);
      u8g2_uint_t _wssid = u8g2.getUTF8Width(ssidName.c_str());
      u8g2.drawStr(116 - _wssid, 8, ssidName.c_str());

      //wifi icon
      u8g2.setFont(u8g2_font_open_iconic_all_1x_t);   // draw the current pixel width
      u8g2.drawGlyph(120, 8, 0x00f7);
    }
    //mqtt Icon
    if(client.connected())
    {
      u8g2.setFont(u8g2_font_open_iconic_all_1x_t);
      u8g2.drawGlyph(30, 8, 0x00cc);
    }
    //draw battery
    batteryDisplay();
    int now = millis();
  } while ( u8g2.nextPage() );

  offset -= 1;            // scroll by one pixel
  if ( (u8g2_uint_t)offset < (u8g2_uint_t) - width )
    offset = 0;             // start over again
}

//Battery drawing
void batteryDisplay()
{
  u8g2.setDisplayRotation(U8G2_R1);
  u8g2.setFont(u8g2_font_battery19_tn);
  if (vdd > 2.96) u8g2.drawGlyph(0, 128, 0x0035);
  else if (vdd > 2.92) u8g2.drawGlyph(0, 128, 0x0034);
  else if (vdd > 2.80) u8g2.drawGlyph(0, 128, 0x0033);
  else if (vdd > 2.70) u8g2.drawGlyph(0, 128, 0x0032);
  else if (vdd > 2.60) u8g2.drawGlyph(0, 128, 0x0031);
  // we should blink
  else u8g2.drawGlyph(0, 128, 0x0030);
  u8g2.setDisplayRotation(U8G2_R0);
}

void setBadgeName()
{
  badgeName.trim(); //remove any white space around text
  badgeName += " "; //add white space at end of text
}

void setup() {
  WiFi.disconnect() ;
  WiFi.persistent(false);
  turnOffLeds();
  setup_wifi();
  setBadgeName();

  Serial.begin(115200);
  //setup display
  u8g2.begin();

  u8g2.setFont(u8g2_font_logisoso16_tf); // set the target font to calculate the pixel width
  width = u8g2.getUTF8Width(badgeName.c_str());    // calculate the pixel width of the text
  u8g2.setFontMode(0);    // enable transparent mode, which is faster

  //mqtt setup
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  //app config information
  Serial.println();
  Serial.println("*****************CONFIG***************");
  Serial.println();
  Serial.println("Please enter the following information");
  Serial.println("into your YouthTech App.");
  Serial.println("To be able to interact with the badge.");
  Serial.print("Badge unique address: ");
  mac = WiFi.macAddress().substring(9);
  Serial.println(mac);
  Serial.println();
  Serial.println("*******************END****************");
  Serial.println();
  delay(1000);
  Serial.end();

  lastReconnectAttempt = 0;
  //After Serial out set all pins back to low once more.
  turnOffLeds();
  delay(10);
  //task management for leds
  runner.init();
  runner.addTask(t1);
  runner.addTask(t2);
  runner.addTask(t3);
  //t1.enable();
}
//callback when T1 is done
void Disable1() {
  turnOffLeds();
  blink2Count =0;
}

void turnOffLeds() {
  for (int i = 0; i < 6; i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW);
  }
}

void loop() {
  if (WiFi.status() != WL_CONNECTED && reqConnect > reqConnectNum && isConnected < 2) {
    reqConnect =  0 ;
    isConnected = 0 ;
    WiFi.disconnect() ;
    WiFi.begin(ssid, password);
  }

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    reqConnect++ ;
    if (isConnected < 2) {
      //No ip found yet
      //Serial.println("Not connected yet...");
      fade = !fade;
    }
  }
  if (isConnected == 2) {
    //perhaps the reconect routine we can convert in a task
    if (!client.connected()) {
      long now = millis();
      if (now - lastReconnectAttempt > 5000) {
        lastReconnectAttempt = now;
        // Attempt to reconnect
        if (reconnect()) {
          lastReconnectAttempt = 0;
        }
      }
    } else {
      // Client connected

      client.loop();
      //because of hardware limits we can't send more than 128kb of data.
      mqttHearthBeat(1000); // send data every 500ms
      mqttHearthBeat2(10000); // send data every 10.000 ms or 10 seconds
    }
  }

  if (displayState) displayText();

  sampleVdd();
  runner.execute();
}

void blinkLed() {
  int r1 = random(0, 6);
  int r2 = random(0, 6);
  digitalWrite(ledPins[r1], LOW);
  digitalWrite(ledPins[r2], HIGH);

}

void blinkLed2() {
  if(blink2Count > -1) digitalWrite(ledPins[blink2Count], LOW);
  digitalWrite(ledPins[blink2Count+1], HIGH);
  blink2Count++;
  if(blink2Count > 6) blink2Count =-1 ;
}

void blinkLed3() {
  //if(blink2Count > -1) digitalWrite(ledPins[blink2Count], LOW);
  if(blink2pwm > 0 ) for(int i =0; i < 6; i++) analogWrite(ledPins[i], blink2pwm);
  if(!blink2dir) blink2pwm = blink2pwm+5;
  else blink2pwm = blink2pwm-5;
  if(blink2pwm >= 255 || blink2pwm <= 0) blink2dir = !blink2dir;
}
