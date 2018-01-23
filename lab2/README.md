
This project (MyUsb.c) creates a usb firmware for Atmel AT90USBKEY2 using a LUFA library and presents the usb device 
to the host system. Two endpoints (IN and OUT) of bulk data transfers with maximum transfer of eight bytes is configured.
The selection of a bulk transfer mode is preferred to enable communication with the usb device and collecting temperature and LEDs
status information when desired. The firmware, therefore, exposes both temperatureand LEDs status to the host. The host can send commands
to toggle the device LEDs, read each LEDs status, and the temperature sensor data.

A tester script (TestMyUsb.py) is also provided to test the functionality of the firmware. The script issues commands from the host to toggle LEDs, read status of each 
LED and the temperature sensor data. 
