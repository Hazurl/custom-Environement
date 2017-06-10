#ifndef __SYSTEM_H__
#define __SYSTEM_H__

#include "../bash/Interpreter.h"
#include "Inputs.h"
#include "Loader.h"
#include "Console.h"
#include <logger.h>
#include <SFML/Graphics.hpp>
#include <string>

namespace haz {

class System {

#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 900
#define SCALE_CURSOR 0.008

public:
    System ();
    ~System ();

    sf::Time getDeltaTime();
    long getTicks();

private:
    Logger* logger = &Logger::get("#.System");

    unsigned int width;
    unsigned int height;
    sf::RenderWindow* window = nullptr;
    Inputs inputs;
    Loader loader;

    typedef Console<(SCREEN_HEIGHT - CONSOLE_BORDER) / 20, (SCREEN_WIDTH - CONSOLE_BORDER) / 10> Console_t;
    Console_t* console;

    sf::Clock clock;
    sf::Time time;
    long ticks = 0; // 1000 ticks correspond to 1 seconds, ticks stay between 0 and 1 billion (so max is 1 million seconds)

    enum class Mode { Console, Desktop };
    Mode mode;

    void start ();
    void close ();
    void manageWindowEvents ();
    void manageDraw();

    sf::Sprite mouseCursorSp;
};

} // namespace haz

#endif