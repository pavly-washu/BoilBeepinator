# BoilBeepinator
A pager type device to alert individuals who are visually impaired when water is boiling. Created by Team 6 for the 2025 Assistive Technology Make-a-thon! 

Device uses 2 ESP32 using the ESP-NOW communication protocol. This github will have instructions on creating your own device.

Parts:
*2xESP32
*2x220 Ohm Resistors
*2xGreen Leds
*Buzzer
*Temperature probe
*Male to male jumper cables
*Breadboard
*2xAAA 3x1.5V Battery Holder

1. Connect the "receiver" ESP32 board to your laptop and run the "MACFinder.ino" arduino file to get the MAC address for the ESP-NOW protocol.
2. Copy the MAC address into line 8 of the "Transmitter-Thermo.ino" arduino file. Flash the "transmitter" ESP32 with the code.
3. Flash the "receiver" ESP32 board with the "Receiver.ino" code.
4. Wire both ESP32 Boards according to the wiring diagram in the repository and you're done!

