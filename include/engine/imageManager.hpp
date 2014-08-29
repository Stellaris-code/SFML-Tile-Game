#ifndef IMAGEMANAGER_HPP
#define IMAGEMANAGER_HPP

#include <vector>
#include <SFML/Graphics.hpp>

class ImageManager
{

public:
    ImageManager() = default;
    ~ImageManager() = default;

    void addTexture(sf::Texture & texture);
    sf::Texture & getTexture(unsigned int index);

private:
    std::vector<sf::Texture> textureList;

};

#endif // IMAGEMANAGER_HPP
