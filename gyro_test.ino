#include <Wire.h>

#define HMC5883L_ADDR 0x0D

void setup()
{
    Serial.begin(115200);
    Wire.begin();

    // Soft Reset
    Wire.beginTransmission(HMC5883L_ADDR);
    Wire.write(0x0B);
    Wire.write(0x01);
    Wire.endTransmission();

    delay(10);

    // Continuous mode
    // ODR = 200 Hz
    // Range = ±8 G
    // OSR = 512
    Wire.beginTransmission(HMC5883L_ADDR);
    Wire.write(0x09);
    Wire.write(0x1D);
    Wire.endTransmission();

    Serial.println("HMC5883L Compass");
}

void loop()
{
    int16_t x, y, z;

    // Read X, Y, Z registers
    Wire.beginTransmission(HMC5883L_ADDR);
    Wire.write(0x00);
    Wire.endTransmission();

    Wire.requestFrom(HMC5883L_ADDR, 6);

    if (Wire.available() == 6)
    {
        x = Wire.read() | (Wire.read() << 8);
        y = Wire.read() | (Wire.read() << 8);
        z = Wire.read() | (Wire.read() << 8);

        float heading = atan2((float)y, (float)x) * 180.0 / PI;

        if (heading < 0)
            heading += 360.0;

        Serial.print("Heading: ");
        Serial.print(heading, 1);
        Serial.println(" deg");
    }

    delay(100);
}