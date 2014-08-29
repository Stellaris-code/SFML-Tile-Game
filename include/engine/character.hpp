#ifndef CHARACTER_HPP
#define CHARACTER_HPP


#include <SFML/Graphics.hpp>

[[deprecated("Need rewriting; provided for compatibility")]]
class Character
{

public:
    Character() = default;
    ~Character() = default;
    void initialize();
    float width();
    float height();
    bool jumping();
    void updateBoundingBox();
    float left() { return m_left; }
    float right() { return m_right; }
    float top() { return m_top; }
    float bottom() { return m_bottom; }
private:
    float m_left;
    float m_right;
    float m_top;
    float m_bottom;
    bool m_jumping;
    float m_height;
    float m_width;
    sf::Sprite m_sprite;

};

#endif // CHARACTER_HPP
