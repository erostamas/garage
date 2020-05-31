#include "StringCommandAdapter.h"

#include "PushButtonCommand.h"

StringCommandAdapter::StringCommandAdapter() {}

CommandPtr StringCommandAdapter::convertMessage(const char* message) const {
    LOG_DEBUG << "[StringCommandAdapter] Converting message: " << message;
    if (std::string(message) == "pushbutton") {
        LOG_DEBUG << "[StringCommandAdapter] pushbutton command received";
        return std::unique_ptr<PushButtonCommand>(new PushButtonCommand());
    } else {
        LOG_DEBUG << "[StringCommandAdapter] unknown command received: " << message;
        return nullptr;
    }
    return nullptr;
}