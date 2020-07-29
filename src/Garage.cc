#define _GLIBCXX_USE_NANOSLEEP

#include <algorithm>
#include <thread>
#include <iostream>
#include <tgmath.h>
#include <fstream>
#include <iomanip>
#include <wiringPi.h>

#include "Garage.h"
#include "Utils.h"
#include "erostamas/Logging.h"
#include "StringCommandAdapter.h"
#include "erostamas/UdpMessageReceiver.h"

Garage::Garage() {
    std::unique_ptr<StringCommandAdapter> adapter(new StringCommandAdapter());
    std::unique_ptr<UdpMessageReceiver> receiver(new UdpMessageReceiver(50001));
    adapter->registerMessageReceiver(std::move(receiver));
    _commandProcessor.registerCommandAdapter(std::move(adapter));
    _commandProcessor.processCommands();
}

Garage::~Garage() {
}

void Garage::run() {
    wiringPiSetup();
    pinMode (25, OUTPUT);

    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        _commandProcessor.processCommands();
    }
    LOG_DEBUG << "Stopping garage" << std::endl;
}
