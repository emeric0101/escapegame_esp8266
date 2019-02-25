# escapegame_esp8266
App for managing Input, output, LCD, ... for Escape Game with esp8266 with MCP23017

Use with ArduinoIDE

# Usage

1. Set all your input/output in Hardware.cpp (to be config by file later)

2. Register your inputs into Hardware::DigitalRead (channel into json -> hardware)

3. Register your outputs Hardware::DigitalWrite (same)

4. Use Hardware::deviceAdress to set your i2c MCP23017)

5. Compile and flash the ESP8266

6. Use the LCD instruction to flash your JSON (see example) with the scene

Enjoy