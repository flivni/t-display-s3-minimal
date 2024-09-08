#include <Arduino.h>
#include "pin_config.h"
#include "TFT_eSPI.h" /* Please use the TFT library provided in the library. */

TFT_eSPI tft = TFT_eSPI();

// LED pulse constants
const int PWM_CHANNEL = 1;    // ESP32 has 16 channels which can generate 16 independent waveforms
const int PWM_FREQ = 5000;     // Set to 5 kHz for better resolution
const int PWM_RESOLUTION = 12; // ESP32 can go up to 16 bits, but max at 5 KHz is 13: https://docs.espressif.com/projects/esp-idf/en/stable/esp32s3/api-reference/peripherals/ledc.html#ledc-api-supported-range-frequency-duty-resolution

// The max duty cycle value based on PWM resolution (255 if resolution is 8 bits)
const int MAX_DUTY_CYCLE = (int)(pow(2, PWM_RESOLUTION) - 1); 

const int LED_OUTPUT_PIN = 1;

const int DELAY_MS = 1;  // Delay between fade increments

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

    tft.setTextSize(1);

    tft.fillScreen(TFT_BROWN);
    tft.setTextColor(TFT_GREEN);

    tft.drawString("Hello,", 10, 10, 4);
    tft.drawString("I am", 10, 50, 4);
    tft.drawString("Volume swell pedal.", 10, 90, 4);

    // Pulse LED

  // Sets up a channel (0-15), a PWM duty cycle frequency, and a PWM resolution (1 - 16 bits) 
  // ledcSetup(uint8_t channel, double freq, uint8_t resolution_bits);
  ledcSetup(PWM_CHANNEL, PWM_FREQ, PWM_RESOLUTION);

  // ledcAttachPin(uint8_t pin, uint8_t channel);
  ledcAttachPin(LED_OUTPUT_PIN, PWM_CHANNEL);
}

void loop() {
  // fade up PWM on given channel
  for(int dutyCycle = 0; dutyCycle <= MAX_DUTY_CYCLE; dutyCycle++){   
    ledcWrite(PWM_CHANNEL, dutyCycle);
    delay(DELAY_MS);
  }

  // fade down PWM on given channel
  for(int dutyCycle = MAX_DUTY_CYCLE; dutyCycle >= 0; dutyCycle--){
    ledcWrite(PWM_CHANNEL, dutyCycle);   
    delay(DELAY_MS);
  }
}
