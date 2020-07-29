#include "erostamas/ICommand.h"

#include <wiringPi.h>

#include "erostamas/Logging.h"

class PushButtonCommand : public ICommand {
public:
    PushButtonCommand(){}

    virtual void execute() override {
        LOG_DEBUG << "Executing pushbutton command";
        digitalWrite(25, 1);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        digitalWrite(25, 0);
    }
};