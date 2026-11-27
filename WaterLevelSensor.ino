#include <Wire.h>

#define THRESHOLD           100
#define ATTINY1_HIGH_ADDR   0x78
#define ATTINY2_LOW_ADDR    0x77

unsigned char low_data[8] = {0};
unsigned char high_data[12] = {0};

bool getHigh12SectionValue(void) {
  memset(high_data, 0, sizeof(high_data));
  uint8_t count = Wire.requestFrom(ATTINY1_HIGH_ADDR, 12);
  if (count != 12) {
    return false;
  }
  for (int i = 0; i < 12; i++) {
    high_data[i] = Wire.read();
  }
  return true;
}

bool getLow8SectionValue(void) {
  memset(low_data, 0, sizeof(low_data));
  uint8_t count = Wire.requestFrom(ATTINY2_LOW_ADDR, 8);
  if (count != 8) {
    return false;
  }
  for (int i = 0; i < 8; i++) {
    low_data[i] = Wire.read();
  }
  return true;
}

void setupWaterLevelSensor() {
  Wire.begin(); // SDA = GPIO 21, SCL = GPIO 22 on ESP32
}

String getWaterLevel() {
  if (!getLow8SectionValue() || !getHigh12SectionValue()) {
    Serial.println("Error: Failed to read from Water Level sensor!");
    return "Error (Check Sensor)";
  }

  uint32_t touch_val = 0;
  uint8_t trig_section = 0;

  for (int i = 0; i < 8; i++) {
    if (low_data[i] > THRESHOLD) {
      touch_val |= (1 << i);
    }
  }
  for (int i = 0; i < 12; i++) {
    if (high_data[i] > THRESHOLD) {
      touch_val |= ((uint32_t)1 << (8 + i));
    }
  }

  while (touch_val & 0x01) {
    trig_section++;
    touch_val >>= 1;
  }

  int levelPercent = trig_section * 5;
  Serial.print("Water level = ");
  Serial.print(levelPercent);
  Serial.println("%");

  return String(levelPercent);
}
