#include "RF24.h"
#include <SPI.h>
#include <ezButton.h>
#include "esp_bt.h"
#include "esp_wifi.h"

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Change 0x27 to 0x3F if your LCD has a different I2C address

SPIClass *sp = nullptr;
SPIClass *hp = nullptr;

RF24 radio(26, 15, 16000000);   //NFR24-1 HSPI
RF24 radio1(4, 2, 16000000);    //NRF24-2 VSPI

unsigned int flag = 0;   //HSPI
unsigned int flagv = 0;  //VSPI
int ch = 45;
int ch1 = 45;

ezButton toggleSwitch(33);

void two() {
  if (flagv == 0) ch1 += 4; else ch1 -= 4;
  if (flag == 0) ch += 2; else ch -= 2;

  if ((ch1 > 79) && (flagv == 0)) flagv = 1;
  else if ((ch1 < 2) && (flagv == 1)) flagv = 0;

  if ((ch > 79) && (flag == 0)) flag = 1;
  else if ((ch < 2) && (flag == 1)) flag = 0;

  radio.setChannel(ch);
  radio1.setChannel(ch1);
}

void one() {
  radio1.setChannel(random(80));
  radio.setChannel(random(80));
  delayMicroseconds(random(60));
}

void setup() {
  Serial.begin(115200);

  // Initialize LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(1, 0);
  lcd.print("Signal  Stress");
  lcd.setCursor(3, 1);
  lcd.print("Test  Mode");
  delay(5000);

  esp_bt_controller_deinit();
  esp_wifi_stop();
  esp_wifi_deinit();
  esp_wifi_disconnect();

  toggleSwitch.setDebounceTime(50);

  initHP();
  initSP();
}

void initSP() {
  sp = new SPIClass(VSPI);
  sp->begin();
  radio1.begin(sp);   

  if (!radio1.isChipConnected()) {
    Serial.println("VSPI NRF24 not detected!");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("VSPI Fail");
  } else {
    Serial.println("VSPI Started !!!");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("VSPI ON!");

    radio1.setAutoAck(false);
    radio1.stopListening();
    radio1.setRetries(0, 0);
    radio1.setPALevel(RF24_PA_MAX, true);
    radio1.setDataRate(RF24_2MBPS);
    radio1.setCRCLength(RF24_CRC_DISABLED);
    radio1.printPrettyDetails();
    radio1.startConstCarrier(RF24_PA_MAX, ch1);
  }
}

void initHP() {
  hp = new SPIClass(HSPI);
  hp->begin();
  if (radio.begin(hp)) {
    Serial.println("HSPI Started !!!");
    lcd.setCursor(0, 1);
    lcd.print("HSPI ON!");
    radio.setAutoAck(false);
    radio.stopListening();
    radio.setRetries(0, 0);
    radio.setPALevel(RF24_PA_MAX, true);
    radio.setDataRate(RF24_2MBPS);
    radio.setCRCLength(RF24_CRC_DISABLED);
    radio.startConstCarrier(RF24_PA_MAX, ch);
  } else {
    Serial.println("HSPI couldn't start !!!");
    lcd.setCursor(0, 1);
    lcd.print("HSPI fail");
  }
}

void loop() {
  toggleSwitch.loop();
  int state = toggleSwitch.getState();

  if (state == HIGH)
    two();
  else
    one();
}
