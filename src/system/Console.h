#ifndef __CONSOLE_H__
#define __CONSOLE_H__

#include <logger.h>
#include <SFML/Graphics.hpp>
#include <array>
#include "Inputs.h"

#define CONSOLE_BORDER 50

namespace haz {

template<std::size_t ROWS, std::size_t COLUMNS>
class Console {
public:

    Console() : backgroundColor(sf::Color(20, 20, 20)), cursorPos(0, 0)
    {}

    ~Console() {}

    void update (Inputs const& inputs, sf::Time, long ticks) {
        long ticks_under = ticks % anim_cursor_ticks_long;

        if (cursorPos.x > 0 && inputs.isKeyPressed(Inputs::KeyCode::Left)) {
            cursorPos.x--;
            ticks_begin_anim_cursor = ticks_under;
        }
        if (cursorPos.x < COLUMNS && inputs.isKeyPressed(Inputs::KeyCode::Right)) {
            cursorPos.x++;
            ticks_begin_anim_cursor = ticks_under;
        }
        if (cursorPos.y < ROWS && inputs.isKeyPressed(Inputs::KeyCode::Down)) {
            cursorPos.y++;
            ticks_begin_anim_cursor = ticks_under;
        }
        if (cursorPos.y > 0 && inputs.isKeyPressed(Inputs::KeyCode::Up)) {
            cursorPos.y--;
            ticks_begin_anim_cursor = ticks_under;
        }

        anim_cursor_is_white = ticks_under < (anim_cursor_ticks_white + ticks_begin_anim_cursor) 
                            && ticks_under >= ticks_begin_anim_cursor; // cursor animation
    }

    void draw(sf::RenderWindow* window) {
        const float pixPerRow = window->getSize().y / ROWS;
        const float pixPerCol = window->getSize().x / COLUMNS;
        
        if (anim_cursor_is_white) {
            sf::RectangleShape cursor ({ pixPerCol, pixPerRow });
            cursor.setPosition( pixPerCol * cursorPos.x + CONSOLE_BORDER, pixPerRow * cursorPos.y + CONSOLE_BORDER );
            cursor.setFillColor(sf::Color::White);
            window->draw(cursor);
        }
    }

    sf::Color getBackgroundColor() const {
        return backgroundColor;
    }

private:
    Logger* logger = &Logger::get("#.Console");
    sf::Color backgroundColor;

    struct gridInfos {
        sf::Uint32 c;
    };

    std::array< std::array< gridInfos, ROWS>, COLUMNS> grid;
    sf::Vector2f cursorPos;
    bool anim_cursor_is_white = true;
    long ticks_begin_anim_cursor;
    const long anim_cursor_ticks_long = 1000;
    const long anim_cursor_ticks_white = anim_cursor_ticks_long / 2;
};

} // namespace haz

#endif