#include "System.h"

using namespace haz;

System::System() : width(1600), height(900) 
{
    logger->CONFIG("RenderWindows creation...");
    window = new sf::RenderWindow(sf::VideoMode(width, height), "System", sf::Style::Titlebar | sf::Style::Close);

    start();
}

System::~System() {}

void System::start() {
    logger->ENTERING({});
    if (!window)
        return logger->RET("void");

    while (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window->close();
        }

        window->clear(sf::Color::Black);
        inputs.update();
        
        window->display();
    }

    logger->EXITING("void");
}