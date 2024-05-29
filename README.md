![GitHub top language](https://img.shields.io/github/languages/top/effectsmachine/ddsm_example) ![GitHub language count](https://img.shields.io/github/languages/count/effectsmachine/ddsm_example)
![GitHub code size in bytes](https://img.shields.io/github/languages/code-size/effectsmachine/ddsm_example)
![GitHub repo size](https://img.shields.io/github/repo-size/effectsmachine/ddsm_example) ![GitHub](https://img.shields.io/github/license/effectsmachine/ddsm_example) ![GitHub last commit](https://img.shields.io/github/last-commit/effectsmachine/ddsm_example)


# Waveshare DDSM Library for Arduino
Including examples and library for [DDSM115](https://www.waveshare.com/ddsm115.htm) and [DDSM210](https://www.waveshare.com/ddsm210.htm) Direct Drive Servo Motor.

Our provided examples can be directly uploaded and run on the `DDSM Driver HAT(A)` board. If you want to use a different driver board, simply change the corresponding serial port IO settings for the hub motor.

## About this Repository
- **ddsm_ctrl:** Library for Arduino. Copy this folder to the `...\Documents\Arduino\libraries` directory.
- **ddsm_example:** Open-source examples for JSON command interaction and web applications, which are the default programs for the `DDSM Driver HAT(A)` at the factory.
- **ddsm_example_downloader:** A tool for downloading the ddsm_example to the `DDSM Driver HAT(A)`. This tool allows you to quickly restore the driver board to its factory settings without needing to install dependencies or compile code.
- **ddsm_python**: Python examples for `DDSM Driver HAT(A)` using JSON cmds.

# How to use ddsm_example
**ddsm_example:** Open-source examples for JSON command interaction and web applications, which are the default programs for the `DDSM Driver HAT(A)` at the factory.

## Getting Started
- Prepare the DDSM Driver HAT(A) and a power supply with a DC5525 or XT60 interface.
    - The power supply should support 9 to 28V DC, but the specific voltage requirements depend on the model of the DDSM motor you are using. For example, when using the DDSM115, the power range is 12-24V; for the DDSM210, it is 9-28V. The power supply should also meet the current requirements of the motor. A higher current rating is preferable; in our tests, a 24V 6A power supply works for most scenarios.
- DDSM115 or DDSM210 motor
    - Mixing different models of DDSM motors is **not** recommended as control commands and feedback information vary. Do not connect the motor to the driver board before setting the motor ID.
- Due to the unique structure of hub motors, they cannot be placed directly on a table to rotate. It's best to secure the motor shaft. If you do not have the appropriate fixtures, you can set a heartbeat function to stop the motor automatically, which will be explained later.

## Setting Motor ID
- Before controlling the hub motor, you need to set an ID for each motor. The default ID is `1`.
- Connect the motor that needs an ID to the driver board.
   - Note: Only one motor should be connected to the driver board when setting the ID. If multiple motors are connected, they will all be set to the new ID.
- Power the driver board through the DC5525 or XT60 interface, ensuring the `Serial Control Switch` is set to the ESP32 position. The motor can then receive control commands from the ESP32. The ESP32 will automatically power on and create a hotspot for user connection.
- The default hotspot name is `ESP32-AP` with the password `12345678`. Connect to this hotspot using a phone, tablet, or PC, then open a browser and enter `192.168.4.1` to access the motor web application.
- In the web application, there's a JSON command input box. Below are sample JSON commands that you can click to auto-fill the input box. Modify the commands as needed and click `SEND` to send them to the ESP32.
- First, send a command to set your motor type. The driver board defaults to DDSM115 communication rules. If you are using a DDSM210, click `CMD_TYPE_DDSM210` and then `SEND`. This setting only needs to be done once per power cycle.
- To set the motor ID, click `CMD_DDSM_CHANGE_ID`, modify the JSON command in the input box, and change the default "id":1 to your desired ID value (1-253). The motor supports changing its ID **ONLY ONCE** per power cycle. To change it again, disconnect and reconnect the motor. The new ID will be saved even after power is off.

## Speed Loop Control
- Secure the motor shaft before controlling it. If you lack appropriate fixtures, set a heartbeat function.
    - Click `CMD_HEARTBEAT_TIME`, where time is in milliseconds. A time value of `-1` disables the heartbeat function; a time value of 2000 stops the motor if no new commands are received within 2 seconds after sending a motion command, preventing continuous rotation.
    - Set a heartbeat function with a time value of 1000 and click `SEND`. This stops the motor after one second of rotation for safety.
    - Note: In the examples, **the heartbeat function only applies to motors with IDs 1, 2, 3, and 4**. In position loop mode, disable the heartbeat function (time value -1) to prevent the motor from returning to position 0.
- To send a speed control command, click `CMD_DDSM_CTRL` with `{"T":10010,"id":1,"cmd":50,"act":3}`. `T` is the command type, `id` is the motor ID, `cmd` is the target speed, and `act` is the acceleration time per revolution (in 0.1ms). The larger the act value, the smoother the speed change.
    - In speed loop mode, the cmd value represents target speed. For DDSM115, the unit is rpm; for DDSM210, it is 0.1rpm. For example, a cmd value of 100 means 100 rpm for DDSM115 and 10 rpm for DDSM210.
    - Other control modes for cmd values are detailed in the **[Mode Switching]** section.
- The motor will start rotating. If you haven't set a heartbeat function (time value -1), the motor will keep rotating. To stop, set the cmd value to 0 or use `CMD_DDSM_STOP`.

## Mode Switching
- The hub motor supports different control modes but defaults to speed loop mode after each power cycle. Use `CMD_CHANGE_MODE` to switch modes: `{"T":10012,"id":1,"mode":2}`. The mode values are:
    - **0:** Open loop (DDSM210 only), similar to DC motor PWM control. The cmd value range is -32767 to 32767.
    - **1:** Current loop (DDSM115 only), controlling current with a cmd value range of -32767 to 32767, corresponding to -8A to 8A (max 2.7A for DDSM115).
    - **2:** Speed loop, available for both DDSM115 and DDSM210. The cmd value range depends on the motor's max speed.
    - **3:** Position loop, available for both DDSM115 and DDSM210. Switch to position loop mode when the motor is stationary. The cmd value range is 0 to 32767 (0 to 360°). The motor moves to the target position via the shortest path. For counterclockwise rotation from position 0, set a cmd value greater than 32767/2.

## Querying Motor ID
- To query the motor ID, connect only one motor to the driver board and send the `CMD_DDSM_ID_CHECK` command.

## Getting Motor Feedback
- Each `CMD_DDSM_CTRL` command returns the motor's current status.
- Use `CMD_DDSM_INFO` to get additional feedback information.

# Wired Control Using JSON Commands
The methods described above use the web application. This section explains how to control the driver board and hub motor via a wired connection. Use a Raspberry Pi, Jetson, PC, or any device with a USB interface for serial communication. Connect the device to the driver board with a USB cable(using the port labeled `ESP32-USB` on the driver board) and ensure the "Serial Control Switch" is set to the ESP32 position

Here’s how to use a simple serial terminal to control the motor (Python script control is covered later):
- Download a serial terminal tool.
- Connect the motor to the driver board, power the board, and use a USB cable to connect your device to the ESP32-USB Type-C port on the driver board.
- Edit JSON commands, adding a newline character (`\n`) at the end.
- The functionality of the JSON commands is the same as described in the web application section.

# Controlling with Python Scripts
You can control the hub motor by running Python scripts on your host device. These scripts can be used on any device that supports Python and serial communication, such as a Windows PC, Raspberry Pi, or Jetson Orin. Adjust the serial device name parameter according to your setup. Connect the `DDSM Driver HAT(A)` to your computer via USB (using the port labeled `ESP32-USB` on the driver board). For example, if the serial device name is /dev/ttyUSB0, run the Python script with the following command:

    python serial_simple_ctrl.py /dev/ttyUSB0

Then, you can enter JSON format commands in the terminal and press Enter to communicate with the DDSM Driver HAT(A). For instance, to obtain the ID of the currently connected motor (ensure only one motor is connected), you can send:

    {"T":10031}

# Quick Factory Reset
If you have uploaded other examples to the `DDSM Driver HAT(A)`, the original factory examples will be replaced. To restore the driver board to its factory settings, connect the `DDSM Driver HAT(A)` to your computer via USB (using the port labeled `ESP32-USB` on the driver board). Then, follow these steps:
- Extract the `ddsm_example_downloader.zip` file.
- Run `flash_download_tool_3.9.5.exe`.
- Select `ESP32` for `ChipType` and `Factory` for `WorkMode`, then click `OK`.
- In any of the Download Panels, select the appropriate `COM port`. Do not change any other parameters.
- After selecting the COM port, click `START`.
- Wait until the process shows `FINISH`.
- Fully power off the `DDSM Driver HAT(A)`` and then power it back on.
The `DDSM Driver HAT(A)`` will now be restored to its original factory examples.

# Important Notes
For most users, when controlling the motor via JSON commands or the web application, the ESP32 is used to generate control commands for the DDSM motor and convert feedback data into a human-readable format. Ensure that the "Serial Control Switch" is set to the `ESP32` position to maintain proper communication between the ESP32 and the DDSM motor. If you need to use USB communication in this mode, connect via the Type-C port labeled `ESP32-USB`.

For advanced users who want to develop their own motor control SDK based on the DDSM motor documentation, you can switch the "Serial Control Switch" to the `USB` position. In this mode, use the Type-C port labeled `USB` to communicate with other devices. This Type-C port communicates directly with the DDSM motor.


# License
ddsm_example for the Waveshare DDSM motors: an open source example and library for DDSM115 and DDSM210.
Copyright (C) 2024 [Waveshare](https://www.waveshare.com/)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/gpl-3.0.txt>.
