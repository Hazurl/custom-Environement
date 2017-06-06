#ifndef __CONSOLE_H__
#define __CONSOLE_H__

#include <logger.h>
#include <SFML/Graphics.hpp>
#include "Inputs.h"

namespace haz {

class Console {
public:
    Console (sf::RenderWindow* window, unsigned int width, unsigned int heigth);
    ~Console ();

    void update (Inputs const& inputs, long delta);

private:
    Logger* logger = &Logger::get("#.Console");

    sf::RenderWindow* window = nullptr;
    unsigned int width;
    unsigned int height;
};

} // namespace haz

#endif