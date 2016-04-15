#include "i2c_tmp102.h"

int main(int argc, char **argv)
{
    double temp;

    if(read_i2c("/dev/i2c-0", 0x48, &temp))
		return; // failed

    //read_i2c("/dev/i2c-0", 0x49, &temp);

    printf("%.1f", temp);
}
