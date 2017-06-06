#ifndef __INPUTS_H__
#define __INPUTS_H__

#include <logger.h>
#include <SFML/Graphics.hpp>

// juste for better comprehension
#define IPT_INIT(key) keysState[haz::Inputs::KeyCode::key] = keysLastState[haz::Inputs::KeyCode::key] = false
#define IPT_UPT_KB(key, sf_key) keysLastState[haz::Inputs::KeyCode::key] = keysState[haz::Inputs::KeyCode::key]; keysState[haz::Inputs::KeyCode::key] = sf::Keyboard::isKeyPressed(sf::Keyboard::sf_key)
#define IPT_UPT_M(key, sf_key) keysLastState[haz::Inputs::KeyCode::key] = keysState[haz::Inputs::KeyCode::key]; keysState[haz::Inputs::KeyCode::key] = sf::Mouse::isButtonPressed(sf::Mouse::sf_key)

namespace haz {

class Inputs {
public:
    enum class KeyCode {
        A = 0, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
        Num0, Num1, Num2, Num3, Num4, Num5, Num6, Num7, Num8, Num9,
        Numpad0, Numpad1, Numpad2, Numpad3, Numpad4, Numpad5, Numpad6, Numpad7, Numpad8, Numpad9,
        Escape, Menu, PageUp, PageDown, End, Home, Insert, Delete, Pause,
        LControl, LShift, LAlt, LSystem, RControl, RShift, RAlt, RSystem, LBracket, RBracket, 
        SemiColon, Comma, Period, Quote, Slash, BackSlash, Tilde, Equal, Dash, Space, Return, BackSpace, Tab, 
        Add, Subtract, Multiply, Divide, 
        Left, Right, Up, Down, 
        F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12, F13, F14, F15,
        LMouse, RMouse, MMouse, XMouse1, XMouse2,

        Count
    };

    Inputs(sf::Window* window);
    ~Inputs();

    void update();
    void onEvent(sf::Event const& e);
    
    bool isKeyDown (KeyCode key) const;
    bool isKeyUp (KeyCode key) const;
    bool isKeyPressed (KeyCode key) const;
    bool isKeyReleased (KeyCode key) const;
    bool AltDown() const;
    bool CtrlDown() const;
    bool ShiftDown() const;

    int getMouseX() const;
    int getMouseY() const;

    std::vector<sf::Uint32> getTextEntered () const;

private:
    Logger* logger = &Logger::get("#.Inputs");

    std::map<KeyCode, bool> keysState = {};
    std::map<KeyCode, bool> keysLastState = {};

    int mouseX = 0, mouseY = 0;

    std::vector<sf::Uint32> txtEntered;

    sf::Window* window = nullptr;
    int width, height;

};

} // namespace haz

#endif