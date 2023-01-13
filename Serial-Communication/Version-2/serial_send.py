# This program is to be used simultaneously with the python recv_w_tx.ino

import serial
import time
import matplotlib.pyplot as pyplot

class WaterTankData:
    def __init__(self, valve_data, strain_data):
        self.valve_data = valve_data
        self.strain_data = strain_data
    def plot_data(self):
        pyplot.scatter(self.valve_data, self.strain_data)
        pyplot.show()

ARDUINO_STARTUP_DELAY_SEC = 1 # This delay is useful to wait for the Arduino to setup (will need to increase in future)
ARDUINO_RECV_DELAY_SEC = 0.1 # This delay is important since Arduino isn't as fast to recv
ARDUINO_SEND_DELAY_SEC = 0.1 # This delay is important since Arduino isn't as fast to send

connection = serial.Serial('COM3', 9600)
time.sleep(ARDUINO_STARTUP_DELAY_SEC)
msg_state = b'A' # Represents not received 
while connection.in_waiting == 0: # Arduino sends info after sending the below data
    connection.write(msg_state)
    time.sleep(ARDUINO_RECV_DELAY_SEC) 
print("Gathering Arduino Data...")
msg_array = []
while connection.in_waiting != 0:
    msg = connection.readline().decode().rstrip('\r\n')
    msg_array.append(msg)
    time.sleep(ARDUINO_SEND_DELAY_SEC) 
print(msg_array)

#From here filtering can be done to process the obtained data and organize it
strain_data_pointer = msg_array.index('Strain Data') + 1
valve_data_pointer = msg_array.index('Valve Data') + 1

data_size = (valve_data_pointer - strain_data_pointer)-1 

strain_data = msg_array[strain_data_pointer:valve_data_pointer-1]
valve_data = msg_array[valve_data_pointer:]

water_tank_data = WaterTankData(valve_data, strain_data)
print(water_tank_data.valve_data)
print(water_tank_data.strain_data)
water_tank_data.plot_data()

#print(strain_data_pointer)
#print(valve_data_pointer)
#print(data_size)

#print(strain_data)
#print(valve_data)

connection.close()