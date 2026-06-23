#include <stdio.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/i2c.h>
#include <linux/sysfs.h>
#include <linux/kobject.h>
#include <linux/slab.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sean");
MODULE_DESCRIPTION("MPU-6050 Gyroscope Driver");



#define I2C_DEVICE "/dev/i2c - 1"
#define SLAVE_ADDRESS 0x68


//Defining the private state structure
struct mpu6050_data {
	struct regmap *regmap;
	int16_t accel_x, accel_y, accel_z;
	int16_t gyro_x, gyro_y, gyro_z;
	struct mutex lock;
};

//Register Definitions
#define MPU6050_PWR_MGMT_1 0x6B
#define

//I2C Driver Registration
static struct i2c_driver mpu_driver = {
	.driver = {
		.name = mpu_6050,
		.of_match_table = mpu_of_ids,
	},
	.probe	= mpu_probe,
	.id_table = mpu_i2c_ids,
};

int main() {
	int mpu;
	if ((mpu = open(I2C_DEVICE, O_RDWR)) < 0) {
		perror("Failed to open i2c bus");
		return 1;
	}
	if (ioctl(file, I2C_SLAVE, SLAVE_ADDRESS) < 0) {
		perror("Failed to acquire bus access and/or talk to slave");
		return 1;
	}

	unsigned char buffer[1];
	if (read(file, buffer, 1) != 1) {
		perror("failed, to read from the i2c device");
		return 1;
	}
}

