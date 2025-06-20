#include <stdio.h>
#include <unistd.h> 
#include "accelMagGyro.h"

int main() {
    SensorData accel, magne, gyro;

    while (1) {
        // Accelerometer 데이터 읽기
        if (readAccelerometer(&accel) == 0)
            printf("Accelerometer: X=%d, Y=%d, Z=%d\n", accel.x, accel.y, accel.z);
        else
            printf("Failed to read Accelerometer data.\n");

        // Magnetometer 데이터 읽기
        if (readMagnetometer(&magne) == 0)
            printf("Magnetometer: X=%d, Y=%d, Z=%d\n", magne.x, magne.y, magne.z);
        else
            printf("Failed to read Magnetometer data.\n");

        // Gyroscope 데이터 읽기
        if (readGyroscope(&gyro) == 0)
            printf("Gyroscope: X=%d, Y=%d, Z=%d\n", gyro.x, gyro.y, gyro.z);
        else
            printf("Failed to read Gyroscope data.\n");

        printf("-----------------------------------------\n");
        sleep(1);  // 1초 간격으로 반복
    }

    return 0;
}
