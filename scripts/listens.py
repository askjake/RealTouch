# SPDX-License-Identifier: MIT
# CircuitPython I2C Device Address Scan with Interrupt
# Listens to I2C address 0x32 when pin A0 is triggered

import time
import board
import busio
import digitalio

# Configure A0 as input with pull-up
pin_a0 = digitalio.DigitalInOut(board.A0)
pin_a0.direction = digitalio.Direction.INPUT
pin_a0.pull = digitalio.Pull.UP

# Initialize I2C bus
i2c = busio.I2C(board.SCL, board.SDA)

# Scan for I2C devices and print their addresses
while True:
    locked = i2c.try_lock()
    if locked:
        try:
            devices = i2c.scan()
            if len(devices) > 0:
                print("I2C addresses found:", [hex(device) for device in devices])
            else:
                print("No I2C devices found.")

            # Check for trigger on pin A0
            if not pin_a0.value:
                print("A0 triggered, listening to I2C address 0x32")
                device = 0x32
                try:
                    while True:
                        data = bytearray(32)
                        i2c.readfrom_into(device, data)
                        print("I2C data received:", [hex(i) for i in data])
                        time.sleep(0.1)
                except ValueError:
                    pass
                except OSError:
                    pass
        finally:
            i2c.unlock()
    else:
        print("I2C bus is busy.")

    time.sleep(0.1)
