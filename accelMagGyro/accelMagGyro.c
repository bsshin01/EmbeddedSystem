#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "accelMagGyro.h"

static int readSensor(const char *basePath, SensorData *data) {
    char path[100];
    int fd;
    FILE *fp;

    // Enable 센서
    snprintf(path, sizeof(path), "%senable", basePath);
    fd = open(path, O_WRONLY);
    if (fd < 0) return -1;
    dprintf(fd, "1");
    close(fd);

    // Data 읽기
    snprintf(path, sizeof(path), "%sdata", basePath);
    fp = fopen(path, "rt");
    if (fp == NULL) return -1;
    fscanf(fp, "%d, %d, %d", &data->x, &data->y, &data->z);
    fclose(fp);

    return 0;
}

int readAccelerometer(SensorData *data) {
    return readSensor(ACCEL_PATH, data);
}

int readMagnetometer(SensorData *data) {
    return readSensor(MAGNE_PATH, data);
}

int readGyroscope(SensorData *data) {
    return readSensor(GYRO_PATH, data);
}
