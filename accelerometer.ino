// Originally created by Pedro Lima 
// and ruined by yours truly
// https://docs.arduino.cc/tutorials/nano-33-ble-rev2/imu-accelerometer/

#include <Arduino_BMI270_BMM150.h>

const int WAIT_TIME = 250;     // How often to run the code (in milliseconds)
const int MINIMUM_ANGLE = 45;

int POS;
int PREV_POS;
float x, y, z;
int angleX = 0;
int angleY = 0;
unsigned long previousMillis = 0;


void setup() {
Serial.begin(9600);
  while (!Serial);
  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }
}

void loop() {
  if (IMU.accelerationAvailable() && millis() - previousMillis >= WAIT_TIME) {
    previousMillis = millis();
    IMU.readAcceleration(x, y, z);
    // Calculate tilt angles in degrees
    angleX = atan2(x, sqrt(y * y + z * z)) * 180 / PI;
    angleY = atan2(y, sqrt(x * x + z * z)) * 180 / PI;
    // actual angles are probably completely extraneous for this use case
    // but I do not care to save an extra ten-thousandth of a second 

    PREV_POS = POS;
    if (abs(angleX) > abs(angleY)) {
      POS = 0; // Down
    } else if (angleY > MINIMUM_ANGLE) {
      POS = 1; // Right
    } else if (angleY < MINIMUM_ANGLE) {
      POS = 2;
    }
    if (POS != PREV_POS ) {
    Serial.println(POS);
    }
  }
}
