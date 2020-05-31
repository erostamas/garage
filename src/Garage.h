#pragma once

#include "erostamas/CommandProcessor.h"

class Garage {
public:
    Garage();
    ~Garage();

	void run();

protected:
    CommandProcessor _commandProcessor;
    
};