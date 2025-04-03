# Arduino-Based Traffic Light System

## Description
This project is an **Arduino Mega2560-based traffic light control system** that uses infrared sensors to detect traffic density. The system adjusts the green light duration based on detected vehicle congestion. Additionally, it is connected to the **Blynk application** for real-time monitoring of sensor status and active traffic lights.

## Required Hardware
- **Arduino Mega2560**
- **4 Traffic Light Units** (Red, Yellow, Green LEDs)
- **4 Infrared Sensors** (for vehicle detection)
- **7-Segment Display** (for countdown timer)
- **16x2 LCD Display** (for system monitoring)
- **ESP8266/WiFi Module** (for Blynk connectivity)
- **Jumper Wires and Breadboard**

## Installation
1. **Download the Repository**
   ```bash
   git clone https://github.com/username/traffic-light-arduino.git
   ```
   *(Replace `username` with your GitHub username and `traffic-light-arduino` with your repository name.)*

2. **Open in Arduino IDE**
   - Launch **Arduino IDE**
   - Click `File > Open` and select the `.ino` file from the downloaded folder

3. **Select Board and Port**
   - `Tools > Board > Arduino Mega2560`
   - `Tools > Port > Select the appropriate port`

4. **Upload Code to Arduino**
   - Click the **Upload** button (right arrow icon)

## How It Works
1. Infrared sensors detect vehicles at each lane.
2. If a lane has high congestion, the system prioritizes it by extending the green light duration.
3. The **16x2 LCD Display** shows traffic light and congestion status.
4. The **7-Segment Display** provides a countdown for light transitions.
5. The **Blynk App** displays:
   - Infrared sensor status (active/inactive).
   - The currently active traffic light.
   - Possible additional features like system reset or manual control via the app.

## Contribution
If you wish to contribute, please fork this repository and create a pull request.

## License
This project is licensed under [MIT/GPL/Apache License] - see the `LICENSE` file for details.
