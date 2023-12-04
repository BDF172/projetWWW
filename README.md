# Projet WWW
![](https://media.discordapp.net/attachments/1044887547127541812/1174346866134102096/image.png?ex=6579b7bf&is=656742bf&hm=37d40678314143f57bf4259ea71782f15f9172bf536c3b87fa3c0b3f1b816a30&=&format=webp&quality=lossless&width=851&height=662)
# Weather Monitoring System Readme

For more details about the Weather Monitoring System -> Guide Utilisateur - Station Météo .pdf

## Technical Specifications

- **Operating Modes:**
    - STANDARD, CONFIGURATION, MAINTENANCE, ECONOMIC
- **RGB LED Backlight.**
- **2 Push Buttons.**
- **Pressure, Temperature, and Humidity History for the Day.**
- **Outdoor Pressure, Humidity, Temperature.**
- **Temperature Measurement Range: -40°C to +60°C.**
- **Temperature Display in °C.**
- **System Connection via USB Cable.**
- **Timezone Based on French Time (UTC+2).**

## Components:

- **Microcontroller: AVR ATmega328.**
- **SD Card Reader (SPI) for Sensor Data Backup.**
- **RGB LED Backlight (SPI).**
- **RTC Clock UTC+2 (I2C) for Date and Time.**

## Sensors:

- **Atmospheric Pressure (I2C).**
- **Air Temperature (I2C).**
- **Humidity (I2C).**
- **GPS (UART).**
- **Brightness (Analog).**

## Startup Procedure:

1. **Connect the system to a computer or power source using a USB cable.**
2. **Use a USB cable connected to the USB port on the left side of the case.**
3. **You have 5 seconds to choose the startup mode, "Standard" or "Configuration" (see Modes). Press the red button for "Configuration" or do nothing for "Standard".**
4. **After 5 seconds, the system is launched, and the sensors are operational.**
5. **Read the guide thoroughly to discover all the features and avoid unintentional errors that could lead to data loss.**

## Modes:

### Standard Mode:

- **Default mode for the system.**
- **Processes one value per sensor (brightness, humidity, and pressure) every 10 minutes.**
- **All values are stored on the SD card, accessible only in "Maintenance" mode.**

### Configuration Mode:

- **Allows configuring system settings.**
- **Sensor acquisition is disabled during this mode.**
- **Switches back to Standard mode after 30 minutes of user inactivity.**

### Maintenance Mode:

- **Accessible from Standard or Economic mode.**
- **Sensor data is directly accessible through a serial interface.**
- **SD card writing is disabled during Maintenance mode.**
- **System shutdown is only possible in Maintenance mode.**

#### Available commands :
| Parameter    | Value Range Definition | Default Value | Description                                              | Example Command     |
|--------------|------------------------|---------------|----------------------------------------------------------|----------------------|
| LUMIN        | {0,1}                  | 1             | Activation (1) / Deactivation (0) of the brightness sensor | LUMIN=1              |
| LUMIN_LOW    | {0-1023}               | 255           | Value below which brightness is considered "low"           | LUMIN_LOW=200        |
| LUMIN_HIGH   | {0-1023}               | 768           | Value above which brightness is considered "high"          | LUMIN_HIGH=700       |
| TEMP_AIR     | {0,1}                  | 1             | Activation (1) / Deactivation (0) of the air temperature sensor | TEMP_AIR=0           |
| MIN_TEMP_AIR | {-40-85}               | -10           | Threshold air temperature (in °C) below which the sensor will error | MIN_TEMP_AIR=-5      |
| MAX_TEMP_AIR | {-40-85}               | 60            | Threshold air temperature (in °C) above which the sensor will error | MAX_TEMP_AIR=30      |
| HYGR         | {0,1}                  | 1             | Activation (1) / Deactivation (0) of the humidity sensor   | HYGR=1               |
| HYGR_MINT    | {-40-85}               | 0             | Temperature below which humidity measurements will not be considered | HYGR_MINT=0          |
| HYGR_MAXT    | {-40-85}               | 50            | Temperature above which humidity measurements will not be considered | HYGR_MAXT=50         |
| PRESSURE     | {0,1}                  | 1             | Activation (1) / Deactivation (0) of the atmospheric pressure sensor | PRESSURE=0           |
| PRESSURE_MIN | {300-1100}             | 850           | Atmospheric pressure threshold (in HPa) below which the sensor will error | PRESSURE_MIN=450     |
| PRESSURE_MAX | {300-1100}             | 1080          | Atmospheric pressure threshold (in HPa) above which the sensor will error | PRESSURE_MAX=1030    |

### Economic Mode:

- **Accessible only from Standard mode.**
- **Disables some sensors and processes.**
- **Data capture reduced from 6 values per hour to 3 values per hour.**

## LED indicators :
| Signal Light Color and Frequency | System State                                     |
|----------------------------------|--------------------------------------------------|
| Continuous Green LED              | Standard Mode                                    |
| Continuous Yellow LED             | Configuration Mode                               |
| Continuous Blue LED               | Economic Mode                                    |
| Continuous Orange LED             | Maintenance Mode                                 |
| Intermittent Red and Blue LED     | Clock RTC Access Error                           |
| Continuous Purple LED             | Inconsistent Sensor Data - Hardware Check Required |
| Intermittent Red and White LED    | SD Card write failure - Check if full       |
