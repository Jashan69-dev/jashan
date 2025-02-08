import pandas as pd
import matplotlib.pyplot as plt
# Load CSV file
df = pd.read_csv("sensor_data.csv")
# Convert timestamp to datetime format
df["Timestamp"] = pd.to_datetime(df["Timestamp"], format="%Y%m%d%H%M%S")
# Plot temperature and humidity
plt.figure(figsize=(10, 5))
plt.plot(df["Timestamp"], df["Temperature (°C)"], label="Temperature (°C)", color="red")
plt.plot(df["Timestamp"], df["Humidity (%)"], label="Humidity (%)", color="blue")

plt.xlabel("Time")
plt.ylabel("Value")
plt.title("Temperature & Humidity Over Time")
plt.legend()
plt.grid()
plt.xticks(rotation=45)

plt.show()