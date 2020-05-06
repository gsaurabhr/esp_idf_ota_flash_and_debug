# esp_idf_ota_flash_and_debug
Component to quickly and easily add the ability to flash your ESP and view log messages over WiFi.
Get rid of the finicky serial cable!

This makes use of the project [here](https://github.com/MalteJ/embedded-esp32-component-udp_logging)
to send logging messages to the ESP. OTA flashing was inspired from the project
[here](https://github.com/yanbe/esp-idf-ota-template).  

Being tested with ESP IDF v4. This is not a working project yet (I have only just managed to use UDP
to send and receive data between my computer and the ESP as yet). Use it as an example to implement UDP for now.  

Once I have a working setup, I will add instructions to include this in your project. Stay tuned.
