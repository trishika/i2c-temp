#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

#include "i2c_tmp102.h"

int read_i2c(char* filename, int address, double* temp)
{
    unsigned char msb, lsb;
    int fd;

    // Buffer for data being read/ written on the i2c bus
    unsigned char buf[10];

    // Open port for reading and writing
    if ((fd = open(filename, O_RDWR)) < 0)
    {
            fprintf(stderr,"Failed to open i2c port\n");
            return 1;
    }

    // Set the port options and set the address of the device we wish to speak to
    if (ioctl(fd, I2C_SLAVE, address) < 0)
    {
            fprintf(stderr,"Unable to get bus access to talk to slave\n");
            return 1;
    }


    // This is the register we wish to read from
    buf[0] = 0;

    // Send register to read from
    if ((write(fd, buf, 1)) != 1)
    {
            fprintf(stderr, "Error writing to i2c slave, %s\n", strerror(errno));
            return 1;
    }

    // Read back data into buf[]
    if ((read(fd, buf, 1)) != 1)
    {
            fprintf(stderr, "Unable to read from slave, %s\n", strerror(errno));
            return 1;
    }
    else
    {
            msb = buf[0];
            //printf("0x%02X ", msb);

            // Read back data into buf[]
            if (read(fd, buf, 1) != 1)
            {
                    fprintf(stderr, "Unable to read from slave, %s\n", strerror(errno));
                    return 1;
            }
            else
            {
                    int res;
                    lsb = buf[0];

                    res = (msb<<8) | lsb;
                    res >>= 4; //The TMP102 temperature registers are left justified, correctly right justify them

					//The tmp102 does twos compliment but has the negative bit in the wrong spot, so test for it and correct if needed
					if(res & (1<<11))
						res |= 0xF800; //Set bits 11 to 15 to 1s to get this reading into real twos compliment
                    *temp = res*0.0625; // to celsius, /16
                    //printf("The temperature given at i2c addr %x is: %f \n",address, res*0.0625);
            }
    }

    return 0;
}
