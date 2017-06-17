#ifndef __CONSOLE_H__
#define __CONSOLE_H__

#include <logger.h>
#include <SFML/Graphics.hpp>
#include <array>
#include <algorithm>
#include <vector>
#include <functional>

#include "Inputs.h"
#include "Loader.h"
#include "../utilities/Timeline.h"
#include "../bash/Context.h"
#include "../bash/Interpreter.h"

#define CONSOLE_BORDER 50
#define CHAR_OFFSET_Y 3

namespace haz {

template<int ROWS, int COLUMNS>
class Console {
public:

    Console() : backgroundColor(sf::Color(20, 20, 20)), backgroundColor2(sf::Color(30, 30, 30)), cursorX(0), cursorY(0), 
        anim_cursor(1000, {
            {0, 0},
            {500, 1}
        }),
        context(interpreter.createContext("SYSTEM"))
    {}

    ~Console() {}

    void initialize() {
        bash::Context::printer_t new_printer = [this] (std::string str) {
            logger->DEBUG("About to print : \"" + str + "\"");
            for (char& c : str)
                writeUnicode(c);
        };

        context.setPrinter(new_printer);
        startCmdLine();
    }

    void update (Inputs const& inputs, sf::Time, long deltaticks) {
        anim_cursor.update(deltaticks);
/*
        if (cursorX > 0 && inputs.isKeyPressed(Inputs::KeyCode::Left)) {
            cursorX--;
            anim_cursor.reset();
        }
        if (cursorX < COLUMNS - 1 && inputs.isKeyPressed(Inputs::KeyCode::Right)) {
            cursorX++;
            anim_cursor.reset();
        }
        if (cursorY < ROWS - 1 && inputs.isKeyPressed(Inputs::KeyCode::Down)) {
            cursorY++;
            anim_cursor.reset();
        }
        if (cursorY > 0 && inputs.isKeyPressed(Inputs::KeyCode::Up)) {
            cursorY--;
            anim_cursor.reset();
        }
*/
        // TextEvent :
        auto texts = inputs.getTextEntered();
        if (!texts.empty()) {
            anim_cursor.reset();
            for (sf::Uint32& u : texts) {
                if (u < 128)
                    writeUnicode(u);
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
            cursor.setPosition( pixPerCol * cursorX + CONSOLE_BORDER, pixPerRow * cursorY + CONSOLE_BORDER );
            cursor.setFillColor(sf::Color::White);
            window->draw(cursor);
        }

        for (int row = 0; row < ROWS; ++row) {
            for (int col = 0; col < COLUMNS; ++col) {
                gridInfos& info = gridAt(col, row);
                if (info.c != 0) {
                    //logger->DEBUG("Draw a character at (" + stringify(col) + ", " + stringify(row) + ")");
                    sf::String letter(info.c);
                    sf::Text letterTxt(letter, loader->getFont("courrier_new"), pixPerRow - 2);
                    letterTxt.setPosition(pixPerCol * col + CONSOLE_BORDER, pixPerRow * row + CONSOLE_BORDER - CHAR_OFFSET_Y);
                    if (anim_cursor.onState(0) && cursorX == col && cursorY == row)
                        letterTxt.setColor(backgroundColor2);
                    else
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

// ======================================== CONSOLE CONFIGURATION ========================================
//                          Colors
    sf::Color backgroundColor;
    sf::Color backgroundColor2;

// ======================================== GRID ========================================
    struct gridInfos {
        char c = 0;
    };

    struct grid_iterator_t {
        Console* C = nullptr;
        int col = 0, row = 0;
        gridInfos* info = &C->gridAt(0, 0);

        grid_iterator_t& next () {
            col ++;
            if (col >= COLUMNS) {
                col = 0;
                row++;
                if(row >= ROWS) {
                    col = row = 0;
                    info = nullptr;
                    return *this;
                }
            }
            info = &C->gridAt(col, row);
            return *this;
        }

        grid_iterator_t& prev () {
            col --;
            if (col < 0) {
                col = COLUMNS - 1;
                row--;
                if(row < 0) {
                    col = COLUMNS - 1;
                    row = ROWS - 1;
                    info = nullptr;
                    return *this;
                }
            }
            info = &C->gridAt(col, row);
            return *this;
        }

        bool out_of_bound() {
            return info == nullptr;
        }

        grid_iterator_t at (int col, int row) const {
            return grid_iterator_t{C, col, row, &C->gridAt(col, row)};
        }

        grid_iterator_t begin () const {
            return grid_iterator_t{C, 0, 0, &C->gridAt(0, 0)};
        }

        grid_iterator_t end () const {
            return grid_iterator_t{C, 0, 0, nullptr};
        }

        grid_iterator_t rbegin () const {
            return grid_iterator_t{C, COLUMNS - 1, ROWS - 1, &C->gridAt(COLUMNS - 1, ROWS - 1)};
        }

        grid_iterator_t rend () const {
            return grid_iterator_t{C, COLUMNS - 1, ROWS - 1, nullptr};
        }
    };

    const grid_iterator_t grid_iterator{this, 0, 0, &gridAt(0, 0)};

    enum class Unicode {
        NUL                         = 0,
        StartOfHeader               = 1,
        StartOfText                 = 2,
        EndOfText                   = 3,
        EndOfTransmission           = 4,
        Enquiry                     = 5,
        Acknowledge                 = 6,
        Bell                        = 7,
        Backspace                   = 8,
        HorizontalTabulation        = 9,
        NewLine                     = 10,
        VerticalTabulation          = 11,
        FormFeed                    = 12,
        Carriagereturn              = 13,
        ShiftOut                    = 14,
        ShiftIn                     = 15,
        DataLinkEscape              = 16,
        DevControl1                 = 17,
        DevControl2                 = 18,
        DevControl3                 = 19,
        DevControl4                 = 20,
        NegAcknowledge              = 21,
        SynchronousIdle             = 22,
        EndOfTransmissionBlock      = 23,
        Cancel                      = 24,
        EndOfMedium                 = 25,
        Substitute                  = 26,
        Escape                      = 27,
        FileSeparator               = 28,
        GroupSeparator              = 29,
        RecordSeparator             = 30,
        UnitSeparator               = 31,
        Delete                      = 127
    };

    std::array< std::array< gridInfos, ROWS>, COLUMNS> grid;

//                          Helper functions

    gridInfos& gridAt() {
        return gridAt(cursorX, cursorY);
    }

    gridInfos& gridAt(int col, int row) {
        return grid[col][row];
    }


// ======================================== CURSOR ========================================
//                          Position
    int cursorX, cursorY;

//                          Animation Helper
    Timeline anim_cursor;

// ======================================== INTERPRETER ========================================
//                          Line Header
    std::vector<char> lineHeader = {'U', 's', 'e', 'r', ' ', '>', '>', ' '};
    bash::Interpreter interpreter;
    bash::Context context;

//                          Recording
    int recordX, recordY;

    void startRecording () {
        recordX = cursorX;
        recordY = cursorY;
    }

    std::string stopRecording () {
        std::string records = {};
        
        grid_iterator_t cur = grid_iterator.at(cursorX, cursorY);
        records.push_back(cur.info->c);
        while(!cur.out_of_bound() && (cur.row != recordY || cur.col != recordX)) {
            cur.prev();
            records.push_back(cur.info->c);
        }

        std::reverse(records.begin(), records.end());
        return records;
    }

    void startCmdLine () {
        writeUnicodes(lineHeader);
        startRecording();
    }

    void stopCmdLine (bool auto_new_line = true) {
        std::string cmd = stopRecording();
        //logger->DEBUG("Command enter : \"" +  cmd + "\"");
        if (auto_new_line) {
            cursorX = 0;
            cursorY++;
        }

        interpreter.run(cmd, context);

    }

// ======================================== OTHER ========================================
//                          Helper functions
    void advanceCursor (int count = 1) {
        if (count > 0) {
            for (int cur = 0; cur < count; cur++) {
                cursorX ++;
                if (cursorX >= COLUMNS) {
                    cursorX = 0;
                    cursorY++;
                    // TODO: OVERFLOW y
                    if(cursorY >= ROWS)
                        cursorY = 0;
                }
            } 
        } else {
            for (int cur = 0; cur > count; cur--) {
                cursorX --;
                if (cursorX < 0) {
                    cursorX = COLUMNS - 1;
                    cursorY--;
                    // TODO: OVERFLOW y
                    if(cursorY < 0)
                        cursorY = ROWS - 1;
                }
            } 
        }

        //logger->DEBUG("Cursor (" + stringify(cursorX) + ", " + stringify(cursorY) + ")");
    }

    bool writable (char c) {
        return c >= 32 && c < 127;
    }

    void writeUnicodes (std::vector<char> cs) {
        for (auto c : cs)
            writeUnicode(c);
    }

    void writeUnicode (char c) {
        if (writable(c))
            return write (c);

        Unicode u = static_cast<Unicode>(c);

        if (u == Unicode::Carriagereturn)
            return enter();
        if (u == Unicode::Backspace)
            return backspace();
        if (u == Unicode::Delete)
            return supr();

        logger->WARN("Unicode has not been porcessed (" + stringify(static_cast<int>(c)) + ")");
    }

    void deleteChar (int col, int row) {
        grid_iterator_t it = grid_iterator.at(col, row);
        if (it.out_of_bound())
            return logger->WARN("Trying to delete a non-existing character");

        do {
            gridInfos* prev = it.info;
            it.next();
            if (it.out_of_bound())
                return;
            *prev = *it.info;
        } while(it.info->c != 0);
    }

    void write (char c) {
        //logger->DEBUG("Write '" + stringify(static_cast<int>(c)) + "'");
        gridAt().c = c;
        advanceCursor();
    }

    void enter () {
        /*
        grid_iterator_t cursor_it = grid_iterator.at(cursorX, cursorY);
        if (cursorY + 1 == ROWS) {
            // TODO : move all console lines upward
            return logger->ERROR("Row overflow");
        }
        grid_iterator_t line_it = grid_iterator.at(0, cursorY + 1);

        // copy cursor_it to line_it
        // until cursor_it is pointing on a zero gridInfo, then stop the process and place the cursor
        while (!cursor_it.out_of_bound() && cursor_it.info->c != 0) {
            *line_it.info = *cursor_it.info;
            *cursor_it.info = gridInfos{0};

            line_it.next();
            cursor_it.next();
        }
        cursorX = 0;
        cursorY = line_it.row;*/
        stopCmdLine();
        cursorX = 0;
        cursorY++;
        startCmdLine();
    }

    void backspace() {
        advanceCursor(-1);
        deleteChar(cursorX, cursorY);
    }

    void supr() {
        deleteChar(cursorX, cursorY);
    }
};

} // namespace haz

#endif