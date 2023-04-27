### 👉 [English Readme](README-ENGLISH.md) | [中文说明](README.md) 👈

# CrazyCube Application System


## Noun

* CrazyCube: The code name for this project
* AppOS: The main framework for developing CrazyCube firmware


## About
The `CrazyCube Application System` (code name: CrazyCube) is a firmware system developed for the `超级立方豆®`(English name CrazyCube). The majority of the project code is written in C++.

## Compilation and Configuration

1. IDE

   [VSCode + PlatformIO](https://platformio.org/install/ide?install=vscode)

2. Project configuration
   - Download third-party dependent libraries: Wait for the third-party library dependency download to complete when you first open the project (it will be downloaded to the `.pio/libdeps/CrazyCube` directory automatically).
   - Modify third-party library configuration: Copy all files under the **conf_lib** directory to the corresponding directory of the third-party library (for details, see `conf_lib/README.md`):
      * For example, copy `conf_lib/lvgl/lv_conf.h` to (overwrite the original file) `.pio/libdeps/CrazyCube/lvgl/lv_conf.h`, etc.

3. Compilation and running
   * Execute `Upload` to upload the code to the Cube Bean
   * Execute `Upload Filesystem Image` to upload file resources to the Cube Bean
   * Congratulations, all tasks are completed 🎉


## Project Structure Description

### Project Directory
Directory | Description
--------- | -----------
lib/      | dependent libraries 
.pio/     | Third-party dependent libraries
conf_lib/ | Third-party dependent library configuration files
extra/    | Extended materials (optional)
data/     | Resource files, including web pages, audio, image resources, etc.
src/      | Project source code

### Project source code under the src directory
Directory | Description
--------- | -----------
app/      | APP application
framework/| System API
keychain/ | Persistent storage
lv/       | lvgl toolkit
os/       | AppOS
outlander/| External application
tools/    | General toolkit
main.cpp  | Program entry


### Third-party dependent libraries

* `TFT_eSPI` Screen driver
* `Gesture PAJ7620` Infrared gesture driver
* `I2Cdevlib-MPU6050` Gyroscope driver
* `FastLED` LED bead driver
* `lvgl` Graphics library
* `OneButton` Button library
* `ESPAsyncWebServer-esphome` Web service
* `ESP32-audioI2S` Audio playback
* `ArduinoJson` Json parsing
* `TensorFlowLite_ESP32` TensorFlow Lite
* `NimBLE-Arduino` Bluetooth keyboard
* `ESP32 BLE Keyboard` Bluetooth keyboard



### PSRAM

This project uses PSRAM extensively, which can be found by searching for keywords such as `ps_malloc` and `ps_calloc`. If porting to other projects, replace `psram` as appropriate.



## License

<a rel="license" href="http://creativecommons.org/licenses/by-nc-nd/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-nd/4.0/88x31.png" /></a><br />This work is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by-nc-nd/4.0/">Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License</a>.

Copyright © 2023, 疯狂豆®  (CrazyLuke)

