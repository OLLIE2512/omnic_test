## Omnic_test contents

The project **Omnic_test** contains one main component source file in C language [message_box_main.c](main/message_box_main.c). The file is located in folder [main](main).

Main task create two tasks:

* Publisher: Increment counter value every 5 seconds, and put it in queue
* Consumer:  Receive value from queue and log it with timestamp between messages

Components for customer and publisher tasks located in [components](components) folder. Each component have own folder: [publisher](components/publisher) folder include sources for Publisher task, [consumer](components/consumer) folder include sources for Consumer task.

Omnic_test project based on ESP-IDF SDK v5.12.

ESP-IDF projects are built using CMake. The project build configuration is contained in `CMakeLists.txt` files that provide a set of directives and instructions describing the project's source files and targets (executable, library, or both).

Below is a short explanation of remaining files in the project folder.

```
├── CMakeLists.txt
├── main
│   ├── include
│   │   └── message_box_types  This file contains global types defenition
│   ├── CMakeLists.txt
│   └── message_box_main.c     contains main task
│
├── components
│   ├── consumer
│   │   ├── include
│   │   │    └── consumer.h    header file for consumer component
│   │   ├── CMakeLists.txt
│   │   └── consumer.c         consuner conponent source file
│   │ 
│   └── publisher
│       ├── include
│       │    └── publisher.h   header file for publisher component
│       ├── CMakeLists.txt
│       └── publisher.c        publisher conponent source file
│
└── README.md                  This is the file you are currently reading
```

For more information on structure and contents of ESP-IDF projects, please refer to Section [Build System](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-guides/build-system.html) of the ESP-IDF Programming Guide.

## Build and flash
* Please check vendor get started guide: [ESP-IDF Get Started](https://docs.espressif.com/projects/esp-idf/en/v5.1.2/esp32/get-started)

* Download and install ESP IDF v5.12. Follow vendor get started guide to configure and install ESP-IDF for your system.

* Clone Omnic or download omnic test project.

* Navigate to project folder and set target(ESP32 DEVKIT V1 by default):
    ```
    cd omnic_test
    idf.py set-target esp32
    ```

* Build the project by running:
    ```
    idf.py build
    ```

* Flash project by running:
    ```
    idf.py -p PORT flash
    ```
Replace PORT with your ESP32 board’s USB port name. After flashing log output will be available on PORT(speed set to 115200b/s).
