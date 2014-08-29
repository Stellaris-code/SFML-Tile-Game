#ifndef GAMEENGINE_HPP
#define GAMEENGINE_HPP

#include <SFML/Graphics.hpp>
#include "engine/imageManager.hpp"
#include "engine/gameObjects/tile.hpp"
#include "engine/camera.hpp"
#include "engine/gameObjects/level.hpp"

class GameEngine
{
public:
    GameEngine(unsigned int stageWidth, unsigned int stageHeight, unsigned int tileSize)
        : m_stageWidth(stageWidth), m_stageHeight(stageHeight), m_tileSize(tileSize)
    {}

    ~GameEngine() = default;

    void run();

private:
    bool init();
    void mainLoop();
    void render();
    void processInput();
    void update();
    bool loadImages();
    void loadLevel();

private:
    sf::RenderWindow m_sfmlWindow;


    ImageManager m_imageManager;

    Camera & m_camera;
    sf::IntRect m_cameraConstraints;

    Level & m_currentLevel;

    bool m_appRunning;
    unsigned int m_stageWidth;
    unsigned int m_stageHeight;
    unsigned int m_tileSize;

    bool m_mouseDown;

    sf::Clock m_clock;
    sf::Time m_elapsedTime;

    sf::Text m_fpsCounter;
    sf::Text m_screenPrint;
};

#endif // GAMEENGINE_HPP
