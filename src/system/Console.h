#ifndef __CONSOLE_H__
#define __CONSOLE_H__

#include <logger.h>
#include <SFML/Graphics.hpp>
#include <array>
#include "Inputs.h"
#include "Loader.h"
#include "../utilities/Timeline.h"

#define CONSOLE_BORDER 50

#define UNICODE_ENTER 13
#define UNICODE_SUPR 127
#define UNICODE_BACKSPACE 8

namespace haz {

template<std::size_t ROWS, std::size_t COLUMNS>
class Console {
public:

    Console() : backgroundColor(sf::Color(20, 20, 20)), backgroundColor2(sf::Color(30, 30, 30)), cursorPos(0, 0), 
        anim_cursor(1000, {
            {0, 0},
            {500, 1}
        })
    {}

    ~Console() {}

    void update (Inputs const& inputs, sf::Time, long deltaticks) {
        anim_cursor.update(deltaticks);

        if (cursorPos.x > 0 && inputs.isKeyPressed(Inputs::KeyCode::Left)) {
            cursorPos.x--;
            anim_cursor.reset();
        }
        if (cursorPos.x < COLUMNS - 1 && inputs.isKeyPressed(Inputs::KeyCode::Right)) {
            cursorPos.x++;
            anim_cursor.reset();
        }
        if (cursorPos.y < ROWS - 1 && inputs.isKeyPressed(Inputs::KeyCode::Down)) {
            cursorPos.y++;
            anim_cursor.reset();
        }
        if (cursorPos.y > 0 && inputs.isKeyPressed(Inputs::KeyCode::Up)) {
            cursorPos.y--;
            anim_cursor.reset();
        }

        // TextEvent :
        auto texts = inputs.getTextEntered();
        if (!texts.empty()) {
            anim_cursor.reset();
            for (sf::Uint32& u : texts) {
                if (u < 128)
                    write(u);
                else
                    logger->WARN("Unicode above 128");
            }
        }
    }

    void draw(sf::RenderWindow* window, Loader* loader) {
        const float rowsLenght = (window->getSize().y - CONSOLE_BORDER * 2);
        const float colLenght = (window->getSize().x - CONSOLE_BORDER * 2);
        const float pixPerRow = rowsLenght / ROWS;
        const float pixPerCol = colLenght / COLUMNS;

        sf::RectangleShape background({ colLenght, rowsLenght });
        background.setPosition(CONSOLE_BORDER, CONSOLE_BORDER);
        background.setFillColor(backgroundColor2);
        window->draw(background);
        
        if (anim_cursor.onState(0)) {
            sf::RectangleShape cursor ({ pixPerCol, pixPerRow });
            cursor.setPosition( pixPerCol * cursorPos.x + CONSOLE_BORDER, pixPerRow * cursorPos.y + CONSOLE_BORDER );
            cursor.setFillColor(sf::Color::White);
            window->draw(cursor);
        }

        for (unsigned int row = 0; row < ROWS; ++row) {
            for (unsigned int col = 0; col < COLUMNS; ++col) {
                gridInfos& info = gridAt(col, row);
                if (info.c != 0) {
                    //logger->DEBUG("Draw a character at (" + stringify(col) + ", " + stringify(row) + ")");
                    sf::String letter(info.c);
                    sf::Text letterTxt(letter, loader->getFont("courrier_new"), pixPerRow - 2);
                    letterTxt.setPosition(pixPerCol * col + CONSOLE_BORDER, pixPerRow * row + CONSOLE_BORDER);
                    letterTxt.setColor(sf::Color::White);
                    window->draw(letterTxt);
                }
            }
        }
    }

    sf::Color getBackgroundColor() const {
        return backgroundColor;
    }

private:
    Logger* logger = &Logger::get("#.Console");
    sf::Color backgroundColor;
    sf::Color backgroundColor2;

    struct gridInfos {
        char c = 0;
    };

    std::array< std::array< gridInfos, ROWS>, COLUMNS> grid;
    sf::Vector2i cursorPos;

    Timeline anim_cursor;

    gridInfos& gridAt() {
        return gridAt(cursorPos.x, cursorPos.y);
    }

    gridInfos& gridAt(int col, int row) {
        return grid[col][row];
    }

    void advanceCursor (int count = 1) {
        if (count > 0) {
            for (int cur = 0; cur < count; cur++) {
                cursorPos.x ++;
                if (cursorPos.x >= COLUMNS) {
                    cursorPos.x = 0;
                    cursorPos.y++;
                    // TODO: OVERFLOW y
                    if(cursorPos.y >= ROWS)
                        cursorPos.y = 0;
                }
            } 
        } else {
            for (int cur = 0; cur > count; cur--) {
                cursorPos.x --;
                if (cursorPos.x < 0) {
                    cursorPos.x = COLUMNS - 1;
                    cursorPos.y--;
                    // TODO: OVERFLOW y
                    if(cursorPos.y < 0)
                        cursorPos.y = ROWS - 1;
                }
            } 
        }

        //logger->DEBUG("Cursor (" + stringify(cursorPos.x) + ", " + stringify(cursorPos.y) + ")");
    }

    void write (char c) {
        logger->DEBUG("Write '" + stringify(static_cast<int>(c)) + "'");
        if (c == UNICODE_ENTER) {
            enter();
        } else if (c == UNICODE_BACKSPACE) {
            backspace();
        }
        else if (c == UNICODE_SUPR) {
            supr();
        } else {
            gridAt().c = c;
            advanceCursor();
        }
    }

    void enter () {
        advanceCursor(COLUMNS - cursorPos.x);
    }

    void backspace() {
        advanceCursor(-1);
        gridAt().c = 0;
        // TODO: move all the line to the left
    }

    void supr() {
        gridAt(cursorPos.x, cursorPos.y).c = 0;
    }
};

} // namespace haz

#endif