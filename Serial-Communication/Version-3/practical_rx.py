# [NOTE] This program runs on a personal computer not on the Arduino despite some variables refering to the Arduino
# This program must be ran first before the Arduino button to send data is pushed (also have serial monitor closed in Arduino IDE)

import serial
import time
import matplotlib.pyplot as pyplot

DATA_ACUMULATION_DELAY_SEC = 0.2

over_status = False
total_strain_data = []
total_valve_data = []
total_time_data = []

connection = serial.Serial('COM3', 57600) # A decently high baudrate is needed so the Arduino doesn't take so long to trasmit data that it leaves large gaps data collection

while over_status == False:
    # The implemented method of waiting a set time for data to accumulate in the buffer before grabbing it is a little crude, 
    # may improve in the future where an "END" is send in each message bundle
    
    while connection.in_waiting == 0:
        pass

    print("Arduino Data Detected...")
    time.sleep(DATA_ACUMULATION_DELAY_SEC)
    print("Starting Data Gather...")

    msg_array = []
    while connection.in_waiting != 0:
        msg = connection.readline().decode().rstrip('\r\n')
        if msg == "OVER":
            over_status = True
            break
        msg_array.append(msg)

    # Filtering message here to receive and organize data
    print(msg_array)
    strain_data_pointer = msg_array.index('SD') + 1
    valve_data_pointer = msg_array.index('VD') + 1
    time_data_pointer = msg_array.index('TD') + 1
    strain_data = msg_array[strain_data_pointer:valve_data_pointer-1]
    valve_data = msg_array[valve_data_pointer:time_data_pointer-1]
    time_data = msg_array[time_data_pointer:]
    
    #print(f"strain_data {strain_data}")
    #print(f"valve_data {valve_data}")

    total_strain_data.extend(strain_data)
    total_valve_data.extend(valve_data)
    total_time_data.extend(time_data)

print("Data Transmission Ended")
# Below used to convert the string array into int array
total_strain_data = list(map(int, total_strain_data))
total_valve_data = list(map(int, total_valve_data))
total_time_data = list(map(int, total_time_data))

print(f"total_strain_data {total_strain_data}")
print(f"total_valve_data {total_valve_data}")
print(f"total_time_data {total_time_data}")

# [TODO] Store the above data in an instance of a class and pickle it for future use. Name the pickle based on the date and time and put it a "Data" directory

pyplot.plot(total_time_data, total_strain_data)
pyplot.grid(True)
pyplot.show()
