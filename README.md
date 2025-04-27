How to setup OTA in Platformio.

1. In platformio.ini add:

[env:esp32dev]
platform = espressif32
board = esp32dev
framework = arduino

upload_protocol = espota
upload_port = NAZWA_LUB_IP_TWOJEGO_ESP32

See main.cpp for the rest of the code.
