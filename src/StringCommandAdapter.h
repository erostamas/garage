#include "erostamas/ICommandAdapter.h"

class StringCommandAdapter : public ICommandAdapter {
public:
    StringCommandAdapter();

    virtual CommandPtr convertMessage(const char* message) const override;
};