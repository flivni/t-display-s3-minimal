#include <Arduino.h>
#include "pin_config.h"
#include "TFT_eSPI.h" /* Please use the TFT library provided in the library. */

TFT_eSPI tft = TFT_eSPI();

void setup() {
    pinMode(PIN_POWER_ON, OUTPUT);
    digitalWrite(PIN_POWER_ON, HIGH);
    delay(1000);

    Serial.begin(115200);
    Serial.println("Hello T-Display-S3");

    tft.begin();

    tft.setRotation(3);
    tft.setSwapBytes(true);
    delay(2000); // magic delay is taken from example code

    // set up PWM for brightness (taken from example)
    ledcSetup(0, 2000, 8);
    ledcAttachPin(PIN_LCD_BL, 0);
    ledcWrite(0, 255);

    tft.setTextSize(1);

    tft.fillScreen(TFT_BROWN);
    tft.setTextColor(TFT_GREEN);

    tft.drawString("Hello,", 10, 10, 4);
    tft.drawString("I am", 10, 50, 4);
    tft.drawString("Volume swell pedal.", 10, 90, 4);
}

void loop() {
    delay(1000);
    Serial.println("loop");
}
