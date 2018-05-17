#include <stdio.h>
//#include <stdint.h>
//#include <stdlib.h>
#include <err.h>
#include <errno.h>
#include <sys/types.h>
//#include <linux/types.h>
#include <linux/i2c.h>
//#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <sys/types.h>
//#include <sys/stat.h>
#include <fcntl.h>
//#include <cstring>
#include <unistd.h>

#define MAX_N50_3_MODEL_NAME        15     // Model name Max Length
#define SMBUS__N50_3_EEPROM_ADDRESS 0x54   // EEPROM address on SMBus

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
        int  reg = 0;
        const char *path = "/dev/i2c-6";  // SMBus device 
        int file;
        if ( (file=open( path , O_RDWR)) < 0)
                err(errno, "Failed to open SMBus for EEPROM'%s'", path);

        if ( ioctl(file, I2C_SLAVE, SMBUS__N50_3_EEPROM_ADDRESS ) < 0)
                err(errno, "Failed to open IOCTL EEPROM Register location '0x%02x'", reg);
        int i;
        for (i=0;i<MaxString_Size-1;i++)
        {
            scPartNumber[i]  = i2c_smbus_read_byte_data(file, reg+i);
            if ( scPartNumber[i] == '\0' || scPartNumber[i]== '\xff')  {  break;   }                
        }
        close(file);
        scPartNumber[i]='\0';
}

int main( void)
{
	char scPartNumber [MAX_N50_3_MODEL_NAME] ;     
        get_model_name(scPartNumber , MAX_N50_3_MODEL_NAME );
        printf(" am after function in main result :  %s\n", scPartNumber);
    return 0;
}
