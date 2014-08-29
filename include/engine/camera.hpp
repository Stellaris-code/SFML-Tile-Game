#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <iostream>

#include <SFML/Graphics.hpp>

#include "engine/gameObjects/tile.hpp"

class Camera
{

public:
    Camera() = default;
    ~Camera() = default;

    void initialize(unsigned int w, unsigned int h, float speed);

    void setPanConstraints(sf::IntRect& panConstraints);
    void pan(unsigned int offsetX, unsigned int offsetY);

    void move(unsigned int x, unsigned int y);
    void moveCenter(unsigned int x, unsigned int y);

    void goTo(unsigned int x, unsigned int y);
    void goToCenter(unsigned int x, unsigned int y);

    void update();

    sf::Vector2i position()
    {
        return sf::Vector2i((int)m_position.x, (int)m_position.y);
    }

    sf::Vector2i tileOffset(unsigned int tileSize)
    {
        return sf::Vector2i((int)(m_position.x)
                            % tileSize, (int)(m_position.y) % tileSize);
    }

    sf::IntRect tileBounds(unsigned int tileSize);
private:
    void setPosition(sf::Vector2f & coordinatesToConstrain,
                     unsigned int targetX, unsigned int targetY);
private:

    sf::Vector2f m_position;

    sf::Vector2f m_target;

    sf::Vector2i m_size;

    float m_speed;

    sf::IntRect m_panConstraints;

};

#endif // CAMERA_HPP
