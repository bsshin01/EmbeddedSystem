#include <stdio.h>
#include <stdlib.h>
#include "temperature.h"

int main(int argc, char *argv[])
{
    const char *devicePath = "/dev/spidev1.0";

    int fd = temperatureInit(devicePath);
    if (fd < 0) {
        fprintf(stderr, "Failed to initialize SPI device\n");
        return -1;
    }

    int temp = readTemperature(fd);
    if (temp == -999) {
        fprintf(stderr, "Failed to read temperature\n");
        temperatureClose(fd);
        return -1;
    }

    printf("Current Temperature: %d°C\n", temp);

    temperatureClose(fd);
    return 0;
}
