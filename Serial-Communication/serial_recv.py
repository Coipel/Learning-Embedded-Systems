import serial

connection = serial.Serial('COM3', 9600) # [NOTE] Make sure the arudino serial monitor is not open

for index in range(1): # For loop use for debugging purposes
    data_str = str(connection.readline(), 'UTF-8').rstrip('\r\n')
    
    while data_str != "Arduino Transmitting...": # A check to make sure to start reading data at correct point
        print("Waiting on Arduino Data...")
        data_str = str(connection.readline(), 'UTF-8').rstrip('\r\n')
        print(data_str)

    print("Left the check loop")
    print(data_str)

    data_str = str(connection.readline(), 'UTF-8').rstrip('\r\n')
    if data_str == "Strain Data":
        print("In strain data")
        strain_data_size = int(str(connection.readline(), 'UTF-8').rstrip('\r\n').strip('Size: '))
        print(f"size recv: {strain_data_size}")

        data_array = [0]*strain_data_size
        for index in range(strain_data_size):
            data_int = int(str(connection.readline(), 'UTF-8').rstrip('\r\n'))
            data_array[index] = data_int
        print(data_array)

        # [TODO] I need this program to send an ACK back to the Arduino so it stops resending data
  
connection.close()