#ifndef __SYSTEM_H__
#define __SYSTEM_H__

#include "../bash/Interpreter.h"

namespace haz {

class System {
public:
    System ();
    ~System ();

    bash::Interpreter& getCmd();

private:
    bash::Interpreter cmd;

};

} // namespace system

#endif