import board
import time
import busio
import digitalio
import adafruit_bus_device.i2c_device as i2c_device
import adafruit_bus_device.i2c_device as i2c_slave
from adafruit_bus_device.i2c_device import I2CDevice



# REGISTER VALUES
BLANK = 0x00;
CFG_REG = 0xA7;
INT_REG = 0x00;
EVT_REG = 0x00;
KEY_CMD = None  # Define the value of KEY_CMD


# Configure A0 as output
pin_a0 = digitalio.DigitalInOut(board.A0)
pin_a0.direction = digitalio.Direction.OUTPUT

# Define the I2C slave address
SLAVE_ADDRESS = 0x34

# Create an I2C bus object
i2c = busio.I2C(board.SCL, board.SDA)

# Create an I2C device object for the slave device
device = I2CDevice(i2c, SLAVE_ADDRESS)


while not i2c.try_lock():
    pass

# Define a function to handle I2C read requests
def handle_read_request():
 # Your logic here
    # This function will be called when a read request is received from the master device
    global KEY_CMD

    # Update KEY_CMD to 0x8C
    KEY_CMD = 0x8C
    
    # Wait for 20ms
    time.sleep(0.02)
    
    # Update KEY_CMD to 0x0C
    KEY_CMD = 0x0C
    
    # Set A0 pin high for 5ms
    pin_a0.value = True
    time.sleep(0.005)
    pin_a0.value = False

    # Send data to the master device
    data = bytearray([
        CFG_REG,  # Send CFG_REG
        INT_REG,  # Send INT_REG
        EVT_REG,  # Send EVT_REG
        KEY_CMD,  # Send KEY_CMD
        BLANK,    # Send BLANK
        BLANK,    # Send BLANK
        BLANK,    # Send BLANK
        BLANK,    # Send BLANK
        BLANK,    # Send BLANK
        BLANK,    # Send BLANK
        BLANK,    # Send BLANK
        BLANK     # Send BLANK
    ])
    
    response = bytearray(13)  # Create a buffer to store the response from the slave device
    i2c.writeto_then_readfrom(SLAVE_ADDRESS, data, response)  # Write data and read response using I2C
    #i2c.send(response)  # Send the response to the master device


# Define callback function to handle requests from the master
def on_request(data):
    data[0] = 0x8C
    data[1] = 0x0C
    
    INT_REG = 0x01;
    EVT_REG = 0x01; 
    
# Define function to handle I2C write requests
def handle_write_request(data):
    # Your logic here
    # This function will be called when a write request is received from the master device
    # You can implement the logic to handle the data sent by the master device

    data_to_write = bytearray([data])
    i2c.writeto(SLAVE_ADDRESS, data_to_write)  # Write data using I2C

# Main loop for listening to I2C requests
while True:
    try:
        # Wait for an I2C request from the master device
        # The slave address and data type (read or write) will be passed as arguments
        # to the handle_read_request() and handle_write_request() functions respectively
        data = bytearray(1)
        i2c.readfrom_into(SLAVE_ADDRESS, data)
        if data[0] == 1:  # Read request
            handle_read_request()
        elif data[0] == 2:  # Write request
            data = bytearray(1)
            i2c.readfrom_into(SLAVE_ADDRESS, data)
            handle_write_request(data[0])
    except KeyboardInterrupt:
        # Exit the loop on keyboard interrupt (e.g. Ctrl+C)
        break





# Unlock the I2C bus when finished.  Ideally put this in a try-finally!
i2c.unlock()