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
#define MPU6050_REG_ACCEL_XOUT_H	0x3B
#define MPU6050_REG_TEMP_OUT_H		0x41
#define MPU6050_REG_GYRO_XOUT_H		0x43


/* Power and Identification Management */
#define MPU6050_REG_USER_CTRL	0x6A
#define MPU6050_PWR_MGMT_1 	0x6B /* rst, sleep, cycle */
#define MPU6050_PWR_MGMT_2 	0x6C /* wakectl, standby */
#define MPU6050_REG_WHO_AM_I	0x75

/* CONFIG Register Bitfields */
#define MPU6050_CONFIG_DLPF_MASK   0x07  /* Bits [2:0] */
#define MPU6050_DLPF_260HZ         0x00
#define MPU6050_DLPF_184HZ         0x01
#define MPU6050_DLPF_94HZ          0x02
#define MPU6050_DLPF_42HZ          0x03  /* 1kHz internal Fs */

/* ACCEL_CONFIG Register Bitfields */
#define MPU6050_ACCEL_FS_MASK      0x18  /* Bits [4:3] */
#define MPU6050_ACCEL_FS_SHIFT     3

#define MPU6050_ACCEL_FS_2G        (0 << MPU6050_ACCEL_FS_SHIFT)
#define MPU6050_ACCEL_FS_4G        (1 << MPU6050_ACCEL_FS_SHIFT)
#define MPU6050_ACCEL_FS_8G        (2 << MPU6050_ACCEL_FS_SHIFT)
#define MPU6050_ACCEL_FS_16G       (3 << MPU6050_ACCEL_FS_SHIFT)


/* PWR_MGMT_1 Bitfields */
#define MPU6050_PWR1_DEVICE_RESET  0x80  /* Bit 7 */
#define MPU6050_PWR1_SLEEP         0x40  /* Bit 6 */
#define MPU6050_PWR1_CLKSEL_MASK   0x07  /* Bits [2:0] */

#define MPU6050_CLKSEL_INTERNAL    0x00
#define MPU6050_CLKSEL_PLL_XGYRO   0x01
#define MPU6050_CLKSEL_PLL_YGYRO   0x02
#define MPU6050_CLKSEL_PLL_ZGYRO   0x03


/* Expected Default Values for Verification */
#define MPU6050_WHO_AM_I_MAGIC     0x68  /* Default value of Register 117 */
#define MPU6050_PWR1_RESET_VAL     0x40  /* Boots directly into Sleep Mode */

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

