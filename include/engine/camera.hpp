#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <SFML/Graphics.hpp>
#include "engine/gameObjects/tile.hpp"

class Camera
{

public:
    Camera();
    ~Camera();
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
    //Absolute position of camera (number of
    //pixels from origin of level map)
    sf::Vector2f m_position;
    //Target position camera is moving towards
    sf::Vector2f m_target;
    //Size of camera
    sf::Vector2i m_size;
    //Speed of camera, a value between 0.0 and 1.0
    float m_speed;
    // pan constraints
    sf::IntRect * m_panConstraints;

};

#endif // CAMERA_HPP
