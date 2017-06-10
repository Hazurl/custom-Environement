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
    console = new Console_t ();

    // Cursor
    logger->CONFIG("Load cursor image");
    mouseCursorSp.setTexture(
        loader.getTexture(PATH_TEXTURE("cursor.png"), "cursor")
    );
    mouseCursorSp.setScale(SCALE_CURSOR, SCALE_CURSOR);

    loader.loadFont(PATH_FONT("cour.ttf"), "courrier_new");
    loader.loadFont(PATH_FONT("cour.ttf"), "courrier_new");

    start();
}

System::~System() {
    window->close();
    delete window;
}

sf::Time System::getDeltaTime () {
    return time;
}

long System::getTicks () {
    return ticks;
}

void System::start() {
    logger->ENTERING({});
    if (!window)
        return logger->RET("void");

    while (window->isOpen()) {
        time = clock.restart();
        ticks = ( ticks + time.asMilliseconds() ) % 1000000000;

        manageWindowEvents();

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

    if (mode == Mode::Console)
        console->update(inputs, getDeltaTime(), getTicks());
}

void System::manageDraw() {
    if (mode == Mode::Desktop) {
        window->clear(sf::Color(0, 0, 160));
        //Pointer
        mouseCursorSp.setPosition(inputs.getMouseX(), inputs.getMouseY());
        window->draw(mouseCursorSp);
    } else if (mode == Mode::Console) {
        window->clear(console->getBackgroundColor());
        console->draw(window);
    } else 
        logger->WARN("System mode doesn't found");
}

void System::close() {
    window->close();
}