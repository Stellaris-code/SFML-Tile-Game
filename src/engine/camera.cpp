
#include "engine/camera.hpp"
#include <SFML/Graphics.hpp>
#include <cmath>

void Camera::initialize(unsigned int w, unsigned int h, float speed)
{
    m_size.x = w;
    m_size.y = h;

    if(speed < 0.0)
        m_speed = 0.0;
    else if(speed > 1.0)
        m_speed = 1.0;
    else
        m_speed = speed;

    m_target.x = 0;
    m_target.y = 0;
    m_position.x = 0;
    m_position.y = 0;
}

void Camera::setPanConstraints(sf::IntRect & panConstraints)
{
    m_panConstraints = panConstraints;
    setPosition(m_position, m_position.x, m_position.y);
    m_target.x = m_position.x;
    m_target.y = m_position.y;
}
void Camera::setPosition(sf::Vector2f & coordinatesToConstrain,
                         unsigned int targetX, unsigned int targetY)
{
    unsigned int newX = targetX;
    unsigned int newY = targetY;
        std::clog << "Pan Constraints : " << std::to_string(m_panConstraints.left) <<
                     ", " << std::to_string(m_panConstraints.top) << ", " <<
                     std::to_string(m_panConstraints.width) << ", " <<
                     std::to_string(m_panConstraints.height) << "\n";
        if (newX < m_panConstraints.left)
        {
            newX = m_panConstraints.left;
        }
        else if (newX + m_size.x > m_panConstraints.left + m_panConstraints.width)
        {
            newX = m_panConstraints.left + m_panConstraints.width - m_size.x;
        }
        if (newY < m_panConstraints.top)
        {
            newY = m_panConstraints.top;
        }
        else if (newY + m_size.y > m_panConstraints.top + m_panConstraints.height)
        {
            newY = m_panConstraints.top + m_panConstraints.height - m_size.y;
        }
    coordinatesToConstrain.x = static_cast<float>(newX);
    coordinatesToConstrain.y = static_cast<float>(newY);
}
void Camera::pan(unsigned int offsetX, unsigned int offsetY)
{
    setPosition(m_position, m_position.x + offsetX, m_position.y + offsetY);
    m_target.x = m_position.x;
    m_target.y = m_position.y;
}

void Camera::move(unsigned int x, unsigned int y)
{
    setPosition(m_position, x, y);
    m_target.x = m_position.x;
    m_target.y = m_position.y;
}

void Camera::moveCenter(unsigned int x, unsigned int y)
{
    x = x - (m_size.x / 2);
    y = y - (m_size.y / 2);
    setPosition(m_position, x, y);
    m_target.x = m_position.x;
    m_target.y = m_position.y;
}

void Camera::goTo(unsigned int x, unsigned int y)
{
    setPosition(m_target, x, y);
}

void Camera::goToCenter(unsigned int x, unsigned int y)
{
    x = x - (m_size.x / 2);
    y = y - (m_size.y / 2);
    setPosition(m_target, x, y);
}

//This function allows us to do a cool camera
//scrolling effect by moving towards a target
//position over time.

void Camera::update()
{
    if (m_position.x != m_target.x || m_position.y != m_target.y)
    {
        //X distance to target, Y distance to target, and Euclidean distance

        //Find x and y
        float x = static_cast<float>(m_target.x - m_position.x);
        float y = static_cast<float>(m_target.y - m_position.y);
        //If we're within 1 pixel of the target already, just snap
        //to target and stay there. Otherwise, continue
        if((x*x + y*y) <= 1)
        {
            setPosition(m_position, m_target.x, m_target.y);
        }
        else
        {
            //Distance formula
            float d = sqrt((x*x + y*y));
            //We set our velocity to move 1/60th of the distance to
            //the target. 60 is arbitrary, I picked it because I intend
            //to run this function once every 60th of a second. We also
            //allow the user to change the camera speed via the speed member
            float v = (d * m_speed)/60;
            //Keep v above 1 pixel per update, otherwise it may never get to
            //the target. v is an absolute value thanks to the squaring of x
            //and y earlier
            if(v < 1.0f)
                v = 1.0f;
            //Similar triangles to get vx and vy
            float vx = x * (v/d);
            float vy = y * (v/d);
            //Then update camera's position and we're done
            setPosition(m_position, m_position.x + vx, m_position.y + vy);
        }
    }
}
sf::IntRect Camera::tileBounds(unsigned int tileSize)
{
    unsigned int x = m_position.x / tileSize;
    unsigned int y = m_position.y / tileSize;
    //+1 in case camera size isn't divisible by tileSize
    //And +1 again because these values start at 0, and
    //we want them to start at one
    unsigned int w = m_size.x / tileSize + 2;
    unsigned int h = m_size.y / tileSize + 2;
    //And +1 again if we're offset from the tile
    if(x % tileSize != 0)
        w++;
    if(y % tileSize != 0)
        h++;
    return sf::IntRect(x, y, w, h);
}
