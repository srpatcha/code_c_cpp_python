#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <err.h>
#include <errno.h>
#include <linux/types.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// Model name Max Length 
#define MAX_MODEL_NAME 76

// EEPROM address on SMBus
#define SMBUS_EEPROM_ADDRESS 0x54

static inline __s32 i2c_smbus_access(int file, char read_write, __u8 command, int size, union i2c_smbus_data *data)
{
          struct i2c_smbus_ioctl_data args;

	  args.read_write = read_write;
	  args.command = command;
	  args.size = size;
	  args.data = data;

        return ioctl(file,I2C_SMBUS,&args);
}

static inline __s32 i2c_smbus_read_byte_data(int file, __u8 command)
{
        union i2c_smbus_data data;
        if (i2c_smbus_access(file, I2C_SMBUS_READ, command, I2C_SMBUS_WORD_DATA,&data))
                return -1;
        else    
         {    
                return 0x0FFFF & data.word;
         }
}

void  get_model_name(char *scPartNumber, int MaxString_Size)
{
     
        char *M_BFR= new char [20];     
        uint8_t data[MAX_MODEL_NAME], reg = 0x00;
        const char *path = "/dev/i2c-6";  // SMBus always
        int file;
        if ( (file=open( path , O_RDWR)) < 0)
                err(errno, "Tried to open but not working'%s'", path);

        if ( ioctl(file, I2C_SLAVE, SMBUS_EEPROM_ADDRESS) < 0)
                err(errno, "IOCTL EEPROM Operation i2c-SMBus for model name '0x%02x'", reg);
        printf("Model_Name :");
        for (int i=0;i<MAX_MODEL_NAME;i++)
        {
            data[i] = i2c_smbus_read_byte_data(file, reg+i);
            M_BFR+i = i2c_smbus_read_byte_data(file, reg+i); 
//            printf("%s: device at address 0x%02x: date : 0x%02x, %c\n", path, reg, data[i], data[i]);
            printf("%c", data[i]);
        }

        strncpy(scPartNumber, M_BFR, MAX_MODEL_NAME); 
        printf(" am in function %s\n",data);

}

int main( void)
{

	char * scPartNumber = new char [20];     
        get_model_name(scPartNumber , MAX_MODEL_NAME );
        printf(" am after function in main result :  %s\n", scPartNumber);

    return 0;
}
