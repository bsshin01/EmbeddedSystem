#include "temperature.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>

#define SPI_SPEED 20000

static char gbuf[10];

int temperatureInit(const char *devicePath)
{
	int fd;
	__u8 mode = 0, lsb, bits;
	__u32 speed = SPI_SPEED;

	if ((fd = open(devicePath, O_RDWR)) < 0) {
		perror("Failed to open SPI device");
		return -1;
	}

	mode |= SPI_3WIRE;

	if (ioctl(fd, SPI_IOC_RD_MODE, &mode) < 0) {
		perror("SPI rd_mode");
		close(fd);
		return -1;
	}
	if (ioctl(fd, SPI_IOC_RD_LSB_FIRST, &lsb) < 0) {
		perror("SPI rd_lsb_first");
		close(fd);
		return -1;
	}
	if (ioctl(fd, SPI_IOC_RD_BITS_PER_WORD, &bits) < 0) {
		perror("SPI bits_per_word");
		close(fd);
		return -1;
	}

	return fd;
}

int readTemperature(int fd)
{
	memset(gbuf, 0, sizeof(gbuf));
	int len = read(fd, gbuf, 2);
	if (len != 2) {
		perror("SPI read error");
		return -999;  // 에러 코드
	}

	int value = ((gbuf[0] << 8) | gbuf[1]);

	// 음수 보정
	if (value & 0x8000) {
		value = ~value + 1;
	}
	value >>= 7;  // 단위 변환
	return value; // °C
}

void temperatureClose(int fd)
{
	close(fd);
}
