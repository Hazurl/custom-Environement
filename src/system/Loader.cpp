#include "Loader.h"

using namespace haz;

Loader::Loader() {
    logger->setLevel(Level::DEBUG);
}

Loader::~Loader() {}

sf::Font& Loader::getFont (std::string const& name) {
    logger->ENTERING({ name });
    logger->EXITING("sf::Font&");
    return fontsTable.at(name);
}

sf::Font& Loader::getFont (std::string const& path, std::string const& name) {
    logger->ENTERING({ path, name });
    loadFont(path, name);
    logger->EXITING("sf::Font&");
    return fontsTable[name];
}

void Loader::loadFont (std::string const& path, std::string const& name) {
    logger->ENTERING({ path, name });
    if (fontsTable.find(name) == fontsTable.end()) {
        logger->CONFIG("Load " + path);
        sf::Font font;
        if (!font.loadFromFile(path))
            logger->THROWEXCEPTION(std::runtime_error, "Cannot load font at " + path);
        fontsTable[name] = font;
    }
    logger->EXITING("void");
}

sf::Texture& Loader::getTexture (std::string const& name) {
    logger->ENTERING({ name });
    logger->EXITING("sf::Texture&");
    return texturesTable.at(name);
}

sf::Texture& Loader::getTexture (std::string const& path, std::string const& name) {
    logger->ENTERING({ path, name });
    loadTexture(path, name);
    logger->EXITING("sf::Texture&");
    return texturesTable[name];
}

void Loader::loadTexture (std::string const& path, std::string const& name) {
    logger->ENTERING({ path, name });
    if (texturesTable.find(name) == texturesTable.end()) {
        logger->CONFIG("Load " + path);
        sf::Texture tex;
        if (!tex.loadFromFile(path))
            logger->THROWEXCEPTION(std::runtime_error, "Cannot load texture at " + path);
        texturesTable[name] = tex;
    }
    logger->EXITING("void");
}