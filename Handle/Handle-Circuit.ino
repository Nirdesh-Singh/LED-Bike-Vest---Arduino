#include<Wire.h>

const int MPU_addr = 0x68;
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;

int minVal = 265;
int maxVal = 402;

double x;
double y;
double z;

bool bool_caliberate = false;
int response_time = 400;

bool offset_pos = false;

void setup() {

  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true); Wire.begin();
  Serial.begin(9600);
  delay(1000);

}

void loop() {

  MPU_debug();
  GetMpuValue1(MPU_addr);

  if (offset_pos == false) {
    if ( GyZ > 15000) {
      Serial.println("L");
      offset_pos = true;
      delay(response_time);
    }
  }

  if (offset_pos == true) {
    if ( GyZ > 15000) {
      Serial.println("L");
      offset_pos = false;
      delay(response_time);
    }
  }

  if (offset_pos == true) {
    if ( GyZ < -15000) {
      Serial.println("R");
      delay(response_time);
      offset_pos = false;

    }
  }

  if (offset_pos == false) {
    if ( GyZ < -15000) {
      Serial.println("R");
      delay(response_time);
      offset_pos = true;

    }
  }

}

void GetMpuValue1(const int MPU) {

  Wire.beginTransmission(MPU);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 14, true); 

  AcX = Wire.read() << 8 | Wire.read();
  AcY = Wire.read() << 8 |  Wire.read(); 
  AcZ = Wire.read() << 8 | Wire.read();

  Tmp = Wire.read() << 8 | Wire.read();

  int xAng = map(AcX, minVal, maxVal, -90, 90);
  int yAng = map(AcY, minVal, maxVal, -90, 90);
  int zAng = map(AcZ, minVal, maxVal, -90, 90);

  GyX = Wire.read() << 8 | Wire.read(); 
  GyY = Wire.read() << 8 | Wire.read(); 
  GyZ = Wire.read() << 8 | Wire.read();
  x = RAD_TO_DEG * (atan2(-yAng, -zAng) + PI) + 4;
  y = RAD_TO_DEG * (atan2(-xAng, -zAng) + PI);
  z = RAD_TO_DEG * (atan2(-yAng, -xAng) + PI);

}

void MPU_debug() {

}