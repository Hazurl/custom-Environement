#ifndef __SYSTEM_H__
#define __SYSTEM_H__

#include "../bash/Interpreter.h"
#include <logger.h>

namespace haz {

class System {
public:
    System ();
    ~System ();

    bash::Interpreter& getCmd();

private:
    Logger* logger = &Logger::get("#.System");
    bash::Interpreter cmd;

};

} // namespace system

#endif