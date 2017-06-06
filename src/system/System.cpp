#include "System.h"

using namespace haz;

System::System() : width(SCREEN_WIDTH), height(SCREEN_HEIGHT), 
                   window(new sf::RenderWindow(sf::VideoMode(width, height), "System", sf::Style::Titlebar | sf::Style::Close)),
                   inputs(window)
{
    logger->CONFIG("RenderWindow created...");
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    window->setPosition( { static_cast<int>(desktop.width - width) / 2, static_cast<int>(desktop.height - height) / 2 } );
    window->setMouseCursorVisible(false);
    //window->setMouseCursorGrabbed(true); // SFML 2.4

    mode = Mode::Console;

    // Cursor
    logger->CONFIG("Load cursor image");
    if (!mouseCursorTex.loadFromFile("Image/cursor.png")) {
        logger->THROWEXCEPTION(std::runtime_error, "cursor.png doesn't exist");
    }

    mouseCursorSp.setTexture(mouseCursorTex);
    mouseCursorSp.setScale(SCALE_CURSOR, SCALE_CURSOR);

    logger->CONFIG("Load courrier new font");
    if (!courrier_new.loadFromFile("Font/cour.ttf")) {
        logger->THROWEXCEPTION(std::runtime_error, "cour.ttf doesn't exist");
    }

    start();
}

System::~System() {
    window->close();
    delete window;
}

void System::start() {
    logger->ENTERING({});
    if (!window)
        return logger->RET("void");

    while (window->isOpen()) {
        manageWindowEvents();

        window->clear(sf::Color(0, 0, 160));

        manageDraw();
        
        window->display();
    }

    logger->EXITING("void");
}

void System::manageWindowEvents () {
    inputs.update();

    sf::Event event;
    while (window->pollEvent(event)) {
        inputs.onEvent(event);

        if (event.type == sf::Event::Closed)
            close();
    }
}

void System::manageDraw() {
    //Pointer
    mouseCursorSp.setPosition(inputs.getMouseX(), inputs.getMouseY());
    window->draw(mouseCursorSp);
}

void System::close() {
    window->close();
}