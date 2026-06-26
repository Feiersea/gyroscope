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

/* MPU60X0 Register Map Offsets */
#define MPU_REG_SMPLRT_DIV	0x19  /* Sample rate register */
#define MPU6050_REG_CONFIG 	 0x1A /* General Configuration */
#define MPU6050_REG_GYRO_CONFIG	 0x1B /* Gyroscope configuration, range of outputs */
#define MPU6050_REG_ACCEL_CONFIG 0x1C /* Configure self test and range for accelerometer */
#define MPU6050_REG_FIFO_EN	 0x23 /* Enable for the various measurements to be put into the FIFO register */
#define MPU6050_REG_INT_ENABLE	 0x38 /* For interrupt generation through various methods */
	#define MPU6050_REG_INT_STATUS	 0x3A /* This shows the status of whether or not there is an interrupt */


/* Data Registers */


/* Power and Identification Management */
#define MPU6050_PWR_MGMT_1 	0x6B /* rst, sleep, cycle */
#define MPU6050_PWR_SLEEP	0x40 //defines the sleep
#define MPU_PWR_CLKSEL_MASK	0x07 //defines the clearing
#define MPU6050_CLKSEL_PLL_XGYRO	0x01 //defines the case for x gyro based reference

#define MPU6050_PWR_MGMT_2 	0x6C /* wakectl, standby */
#


//I2C Driver
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
		perror("failed, to read from the i2c device")
	}
}

