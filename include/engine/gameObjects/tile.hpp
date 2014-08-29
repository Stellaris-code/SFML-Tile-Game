#ifndef TILE_HPP
#define TILE_HPP

#include <SFML/Graphics.hpp>

class Tile
{

public:
    Tile() = default;
    Tile(sf::Texture & texture) { initialize(texture); }
    ~Tile() = default;
    void initialize(sf::Texture & texture);
    void draw(unsigned int x, unsigned int y, sf::RenderWindow & rw);

private:
    sf::Sprite m_baseSprite;

};

#endif // TILE_HPP
