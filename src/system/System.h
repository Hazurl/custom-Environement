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

#define CONSOLE_ROWS (SCREEN_HEIGHT - CONSOLE_BORDER*2) / 20
#define CONSOLE_COLUMNS (SCREEN_WIDTH - CONSOLE_BORDER*2) / 10

public:
    System ();
    ~System ();

    sf::Time getDeltaTime();
    long getDeltaTicks();

private:
    Logger* logger = &Logger::get("#.System");

    unsigned int width;
    unsigned int height;
    sf::RenderWindow* window = nullptr;
    Inputs inputs;
    Loader loader;

    typedef Console<CONSOLE_ROWS, CONSOLE_COLUMNS> Console_t;
    Console_t* console;

    sf::Clock clock;
    sf::Time time;
    long deltaticks = 0;

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