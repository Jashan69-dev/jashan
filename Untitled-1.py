import serial
import time
import csv

# Open serial port (check your COM port in Arduino IDE)
ser = serial.Serial('COM3', 9600, timeout=1)  # Windows: 'COMx', Linux/Mac: '/dev/ttyUSBx'
time.sleep(2)  # Wait for connection

# Open CSV file to write data
filename = "sensor_data.csv"

with open(filename, 'a', newline='') as csvfile:
    csv_writer = csv.writer(csvfile)
    csv_writer.writerow(["Timestamp", "Temperature (°C)", "Humidity (%)"])  # Column headers

    try:
        while True:
            line = ser.readline().decode().strip()  # Read serial input
            if line:
                millis, temp, humid = line.split(",")  # Split values
                timestamp = time.strftime("%Y%m%d%H%M%S")  # Format timestamp
                csv_writer.writerow([timestamp, temp, humid])
                print(f"Data saved: {timestamp}, {temp}°C, {humid}%")
    except KeyboardInterrupt:
        print("Data collection stopped.")
        ser.close()