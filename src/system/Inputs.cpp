#include "Inputs.h"

using namespace haz;

Inputs::Inputs(sf::Window* window) : window(window), width(window->getSize().x), height(window->getSize().y) {
    logger->CONFIG("Init Inputs");
    IPT_INIT( A ); IPT_INIT( B ); IPT_INIT( C ); IPT_INIT( D ); IPT_INIT( E ); IPT_INIT( F );
    IPT_INIT( G ); IPT_INIT( H ); IPT_INIT( I ); IPT_INIT( J ); IPT_INIT( K ); IPT_INIT( L );
    IPT_INIT( M ); IPT_INIT( N ); IPT_INIT( O ); IPT_INIT( P ); IPT_INIT( Q ); IPT_INIT( R );
    IPT_INIT( S ); IPT_INIT( T ); IPT_INIT( U ); IPT_INIT( V ); IPT_INIT( W ); IPT_INIT( X );
    IPT_INIT( Y ); IPT_INIT( Z );

    IPT_INIT( Num0 ); IPT_INIT( Num1 ); IPT_INIT( Num2 ); IPT_INIT( Num3 ); IPT_INIT( Num4 );
    IPT_INIT( Num5 ); IPT_INIT( Num6 ); IPT_INIT( Num7 ); IPT_INIT( Num8 ); IPT_INIT( Num9 );

    IPT_INIT( Numpad0 ); IPT_INIT( Numpad1 ); IPT_INIT( Numpad2 ); IPT_INIT( Numpad3 ); IPT_INIT( Numpad4 );
    IPT_INIT( Numpad5 ); IPT_INIT( Numpad6 ); IPT_INIT( Numpad7 ); IPT_INIT( Numpad8 ); IPT_INIT( Numpad9 );

    IPT_INIT( Escape ); IPT_INIT( Menu ); IPT_INIT( PageUp ); IPT_INIT( PageDown ); IPT_INIT( End );
    IPT_INIT( Home ); IPT_INIT( Insert ); IPT_INIT( Delete ); IPT_INIT( Pause ); 

    IPT_INIT( LControl ); IPT_INIT( LShift ); IPT_INIT( RControl ); IPT_INIT( RShift ); IPT_INIT( RBracket );
    IPT_INIT( LAlt ); IPT_INIT( LSystem ); IPT_INIT( RAlt ); IPT_INIT( RSystem ); IPT_INIT( LBracket );

    IPT_INIT( SemiColon ); IPT_INIT( Comma ); IPT_INIT( Period ); IPT_INIT( Quote ); IPT_INIT( Slash ); IPT_INIT( BackSlash );
    IPT_INIT( Tilde ); IPT_INIT( Equal ); IPT_INIT( Dash ); IPT_INIT( Space ); IPT_INIT( Return ); IPT_INIT( BackSpace ); IPT_INIT( Tab );
    
    IPT_INIT( Add ); IPT_INIT( Subtract ); IPT_INIT( Multiply );

    IPT_INIT( Divide ); IPT_INIT( Left ); IPT_INIT( Right ); IPT_INIT( Up ); IPT_INIT( Down );

    IPT_INIT( F1 ); IPT_INIT( F2 ); IPT_INIT( F3 ); IPT_INIT( F4 ); IPT_INIT( F5 );
    IPT_INIT( F6 ); IPT_INIT( F7 ); IPT_INIT( F8 ); IPT_INIT( F9 ); IPT_INIT( F10 );
    IPT_INIT( F11 ); IPT_INIT( F12 ); IPT_INIT( F13 ); IPT_INIT( F14 ); IPT_INIT( F15 );

    IPT_INIT( LMouse ); IPT_INIT( RMouse ); IPT_INIT( MMouse ); IPT_INIT( XMouse1 ); IPT_INIT( XMouse2 );

    sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
    mouseX = (mousePos.x < 0 ? 0 : (mousePos.x > width ? width : mousePos.x));
    mouseY = (mousePos.y < 0 ? 0 : (mousePos.y > height ? height : mousePos.y));

    txtEntered = {};
}

Inputs::~Inputs() {}

void Inputs::update() {
    IPT_UPT_KB( A, A ); IPT_UPT_KB( B, B ); IPT_UPT_KB( C, C ); IPT_UPT_KB( D, D ); IPT_UPT_KB( E, E ); IPT_UPT_KB( F, F );
    IPT_UPT_KB( G, G ); IPT_UPT_KB( H, H ); IPT_UPT_KB( I, I ); IPT_UPT_KB( J, J ); IPT_UPT_KB( K, K ); IPT_UPT_KB( L, L );
    IPT_UPT_KB( M, M ); IPT_UPT_KB( N, N ); IPT_UPT_KB( O, O ); IPT_UPT_KB( P, P ); IPT_UPT_KB( Q, Q ); IPT_UPT_KB( R, R );
    IPT_UPT_KB( S, S ); IPT_UPT_KB( T, T ); IPT_UPT_KB( U, U ); IPT_UPT_KB( V, V ); IPT_UPT_KB( W, W ); IPT_UPT_KB( X, X );
    IPT_UPT_KB( Y, Y ); IPT_UPT_KB( Z, Z );

    IPT_UPT_KB( Num0, Num0 ); IPT_UPT_KB( Num1, Num1 ); IPT_UPT_KB( Num2, Num2 ); IPT_UPT_KB( Num3, Num3 ); IPT_UPT_KB( Num4, Num4 );
    IPT_UPT_KB( Num5, Num5 ); IPT_UPT_KB( Num6, Num6 ); IPT_UPT_KB( Num7, Num7 ); IPT_UPT_KB( Num8, Num8 ); IPT_UPT_KB( Num9, Num9 );

    IPT_UPT_KB( Numpad0, Numpad0 ); IPT_UPT_KB( Numpad1, Numpad1 ); IPT_UPT_KB( Numpad2, Numpad2 ); IPT_UPT_KB( Numpad3, Numpad3 ); IPT_UPT_KB( Numpad4, Numpad4 );
    IPT_UPT_KB( Numpad5, Numpad5 ); IPT_UPT_KB( Numpad6, Numpad6 ); IPT_UPT_KB( Numpad7, Numpad7 ); IPT_UPT_KB( Numpad8, Numpad8 ); IPT_UPT_KB( Numpad9, Numpad9 );

    IPT_UPT_KB( Escape, Escape ); IPT_UPT_KB( Menu, Menu ); IPT_UPT_KB( PageUp, PageUp ); IPT_UPT_KB( PageDown, PageDown ); IPT_UPT_KB( End, End );
    IPT_UPT_KB( Home, Home ); IPT_UPT_KB( Insert, Insert ); IPT_UPT_KB( Delete, Delete ); IPT_UPT_KB( Pause, Pause ); 

    IPT_UPT_KB( LControl, LControl ); IPT_UPT_KB( LShift, LShift ); IPT_UPT_KB( RControl, RControl ); IPT_UPT_KB( RShift, RShift ); IPT_UPT_KB( RBracket, RBracket );
    IPT_UPT_KB( LAlt, LAlt ); IPT_UPT_KB( LSystem, LSystem ); IPT_UPT_KB( RAlt, RAlt ); IPT_UPT_KB( RSystem, RSystem ); IPT_UPT_KB( LBracket, LBracket );

    IPT_UPT_KB( SemiColon, SemiColon ); IPT_UPT_KB( Comma, Comma ); IPT_UPT_KB( Period, Period ); IPT_UPT_KB( Quote, Quote ); IPT_UPT_KB( Slash, Slash ); IPT_UPT_KB( BackSlash, BackSlash );
    IPT_UPT_KB( Tilde, Tilde ); IPT_UPT_KB( Equal, Equal ); IPT_UPT_KB( Dash, Dash ); IPT_UPT_KB( Space, Space ); IPT_UPT_KB( Return, Return ); IPT_UPT_KB( BackSpace, BackSpace ); IPT_UPT_KB( Tab, Tab );
    
    IPT_UPT_KB( Add, Add ); IPT_UPT_KB( Subtract, Subtract ); IPT_UPT_KB( Multiply, Multiply );

    IPT_UPT_KB( Divide, Divide ); IPT_UPT_KB( Left, Left ); IPT_UPT_KB( Right, Right ); IPT_UPT_KB( Up, Up ); IPT_UPT_KB( Down, Down );

    IPT_UPT_KB( F1, F1 ); IPT_UPT_KB( F2, F2 ); IPT_UPT_KB( F3, F3 ); IPT_UPT_KB( F4, F4 ); IPT_UPT_KB( F5, F5 );
    IPT_UPT_KB( F6, F6 ); IPT_UPT_KB( F7, F7 ); IPT_UPT_KB( F8, F8 ); IPT_UPT_KB( F9, F9 ); IPT_UPT_KB( F10, F10 );
    IPT_UPT_KB( F11, F11 ); IPT_UPT_KB( F12, F12 ); IPT_UPT_KB( F13, F13 ); IPT_UPT_KB( F14, F14 ); IPT_UPT_KB( F15, F15 );

    IPT_UPT_M( LMouse, Left ); IPT_UPT_M( RMouse, Right ); IPT_UPT_M( MMouse, Middle ); IPT_UPT_M( XMouse1, XButton1 ); IPT_UPT_M( XMouse2, XButton2 );

    sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
    mouseX = (mousePos.x < 0 ? 0 : (mousePos.x > width ? width : mousePos.x));
    mouseY = (mousePos.y < 0 ? 0 : (mousePos.y > height ? height : mousePos.y));

    txtEntered = {};
}

void Inputs::onEvent(sf::Event const& e) {
    if (e.type == sf::Event::TextEntered)
        txtEntered.push_back(e.text.unicode);
}

bool Inputs::isKeyDown (Inputs::KeyCode key) const {
    return keysState.at(key);
}

bool Inputs::isKeyUp (Inputs::KeyCode key) const {
    return !keysState.at(key);
}

bool Inputs::isKeyPressed (Inputs::KeyCode key) const {
    return keysState.at(key) && !keysLastState.at(key);
}

bool Inputs::isKeyReleased (Inputs::KeyCode key) const {
    return !keysState.at(key) && keysLastState.at(key);
}

int Inputs::getMouseX() const {
    return mouseX;
}

int Inputs::getMouseY() const {
    return mouseY;
}

bool Inputs::AltDown() const {
    return isKeyDown(KeyCode::LAlt) || isKeyUp(KeyCode::RAlt);
}

bool Inputs::CtrlDown() const {
    return isKeyDown(KeyCode::LControl) || isKeyUp(KeyCode::RControl);
}

bool Inputs::ShiftDown() const {
    return isKeyDown(KeyCode::LShift) || isKeyUp(KeyCode::RShift);
}

std::vector<sf::Uint32> Inputs::getTextEntered () const {
    return txtEntered;
}