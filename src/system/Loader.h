#ifndef __LOADER_H__
#define __LOADER_H__

#include <logger.h>
#include <SFML/Graphics.hpp>
#include <map>

#define PATH_FONT(n) "Font/" n
#define PATH_TEXTURE(n) "Image/" n

namespace haz {

class Loader {
public:
    Loader ();
    ~Loader ();

    sf::Font& getFont (std::string const& name);
    sf::Font& getFont (std::string const& path, std::string const& name);
    void loadFont (std::string const& path, std::string const& name);

    sf::Texture& getTexture (std::string const& name);
    sf::Texture& getTexture (std::string const& path, std::string const& name);
    void loadTexture (std::string const& path, std::string const& name);

private:
    Logger* logger = &Logger::get("#.Loader");

    // nom -> Font
    std::map<std::string, sf::Font> fontsTable; 
    // nom -> Texture
    std::map<std::string, sf::Texture> texturesTable; 
};

} // namespace haz

#endif