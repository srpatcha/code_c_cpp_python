#include <linux/i2c-dev.h>
#include <linux/i2c.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>


#define I2C_DEV_ADDR 0x54
#define I2C_ADAPTER_NO 6
#define BYTE_COUNT 25

int main(int argc, char *argv[])
{
    int i2c_dev_file;
    char filename[20];

    snprintf(filename, 19, "/dev/i2c-%d", I2C_ADAPTER_NO);
    i2c_dev_file = open(filename, O_RDONLY);
    if (i2c_dev_file < 0) {
        fprintf(stderr, "i2c open error %s: %s\n", filename, strerror(errno));
        exit(1);
    }

    if (ioctl(i2c_dev_file, I2C_SLAVE, I2C_DEV_ADDR) < 0) {
        fprintf(stderr, "i2c error: %s\n", strerror(errno));
        exit(1);
    }

    char buf[BYTE_COUNT];
    if (read(i2c_dev_file, buf, BYTE_COUNT) != 1) {
        fprintf(stderr, "i2c transaction failed: %s\n", strerror(errno));
    } else {
        for (int i = 0; i < BYTE_COUNT; ++i) {
            fprintf(stdout, "[0x%2x]: (%c)0x%2x ", i, buf[i], buf[i]);
        }
        fprintf(stdout, "\n");
    }
}
