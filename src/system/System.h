#ifndef __SYSTEM_H__
#define __SYSTEM_H__

#include "../bash/Interpreter.h"
#include "Console.h"
#include "Inputs.h"
#include <logger.h>
#include <SFML/Graphics.hpp>

namespace haz {

class System {
public:
    System ();
    ~System ();

private:
    Logger* logger = &Logger::get("#.System");

    sf::RenderWindow* window = nullptr;
    Inputs inputs;
    unsigned int width;
    unsigned int height;

    void start ();

};

} // namespace haz

#endif