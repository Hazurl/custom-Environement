#ifndef __SYSTEM_H__
#define __SYSTEM_H__

#include "../bash/Interpreter.h"
#include "Console.h"
#include "Inputs.h"
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

private:
    Logger* logger = &Logger::get("#.System");

    unsigned int width;
    unsigned int height;
    sf::RenderWindow* window = nullptr;
    Inputs inputs;

    enum class Mode { Console, Desktop };
    Mode mode;

    void start ();
    void close ();
    void manageWindowEvents ();
    void manageDraw();

    sf::Texture mouseCursorTex;
    sf::Sprite mouseCursorSp;

    sf::Font courrier_new;

};

} // namespace haz

#endif