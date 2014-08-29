#include "engine/gameObjects/tile.hpp"

void Tile::initialize(sf::Texture & texture)
{
    m_baseSprite.setTexture(texture);
}
void Tile::draw(unsigned int x, unsigned int y, sf::RenderWindow & rw)
{
    m_baseSprite.setPosition(x, y);
    rw.draw(m_baseSprite);
}
