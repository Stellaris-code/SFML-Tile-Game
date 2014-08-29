#include "engine/gameEngine.hpp"

void GameEngine::run(const std::string winName)
{
    if (!init(winName))
    {
        throw std::runtime_error("ERROR : Could not init game engine !");
    }
    mainLoop();
}
bool GameEngine::init(const std::string winName)
{
    m_appRunning = true;

    sf::ContextSettings contextSettings;
    contextSettings.depthBits = 24;
    contextSettings.stencilBits = 8;
    contextSettings.antialiasingLevel = 4;
    contextSettings.majorVersion = 1;
    contextSettings.minorVersion = 0;

    m_sfmlWindow.create(sf::VideoMode(m_stageWidth, m_stageHeight), winName, sf::Style::Default, contextSettings);
    m_sfmlWindow.setVerticalSyncEnabled(true);

    m_sfmlWindow.setFramerateLimit(framerate_limit);
    m_sfmlWindow.setKeyRepeatEnabled(false); // disable OS key repeat calls

    loadLevel();

    m_camera.initialize(m_stageWidth, m_stageHeight, 1.0f);

    m_cameraConstraints.left = 0;
    m_cameraConstraints.top = 0;
    m_cameraConstraints.width = 64 * 40 - m_stageWidth;
    m_cameraConstraints.height = 64 * 40 - m_stageHeight;

    m_camera.setPanConstraints(m_cameraConstraints);

    m_fpsCounter.setCharacterSize(12);
    m_screenPrint.setCharacterSize(12);

    m_mouseDown = false;

    m_imageManager.setTileSize(m_tileSize);

    return true;
}
void GameEngine::mainLoop()
{
    while(m_appRunning)
    {
        m_elapsedTime = m_clock.restart();
        float framerate = 1.0f / m_elapsedTime.asSeconds();
        m_fpsCounter.setString("FPS : " + std::to_string(framerate));
        processInput();
        update();
        render();
    }
}
void GameEngine::render()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    sf::IntRect tileBounds = m_camera.tileBounds(m_tileSize);

    unsigned int camOffsetX = m_camera.tileOffset(m_tileSize).x;
    unsigned int camOffsetY = m_camera.tileOffset(m_tileSize).y;

    //Loop through and draw each tile
    //We're keeping track of two variables in each loop. How many tiles
    //we've drawn (x and y), and which tile on the map we're drawing (tileX
    //and tileY)

    for(size_t y {}, tileY = tileBounds.top; y < tileBounds.height;
        y++, tileY++)
    {
        for(size_t x {}, tileX = tileBounds.left; x < tileBounds.width;
            x++, tileX++)
        {
            //Get the tile we're drawing
            m_currentLevel.getTile(tileX, tileY).draw(
                                    (x * m_tileSize) - camOffsetX,
                                    (y * m_tileSize) - camOffsetY,
                                    m_sfmlWindow);
        }
    }
    m_sfmlWindow.draw(m_fpsCounter);
    m_screenPrint.setPosition(0, 12);
    m_screenPrint.setString("Offset : " + std::to_string(camOffsetX)
                            + ", " + std::to_string(camOffsetY) + "; Bounds : "
                            + std::to_string(tileBounds.left) + ", "
                            + std::to_string(tileBounds.top) + ", "
                            + std::to_string(tileBounds.width) + ", "
                            + std::to_string(tileBounds.height) + "\n");

    m_sfmlWindow.draw(m_screenPrint);

    m_screenPrint.setPosition(0, 24);
    m_screenPrint.setString("Pos : " + std::to_string(m_camera.position().x)
                            + ", " + std::to_string(m_camera.position().y) + "\n");

    m_sfmlWindow.draw(m_screenPrint);
    m_sfmlWindow.display();
}
void GameEngine::processInput()
{
    sf::Event event;
    while(m_sfmlWindow.pollEvent(event))
    {
        switch (event.type) {
        case sf::Event::Closed:
            m_appRunning = false;
            break;
        case sf::Event::Resized:

            m_stageWidth = event.size.width;
            m_stageHeight = event.size.height;
            glViewport(0, 0, m_stageWidth, m_stageHeight);
            break;
        case sf::Event::LostFocus:

            break;
        case sf::Event::GainedFocus:

            break;
        case sf::Event::TextEntered:
            if (event.text.unicode < 128)
                std::clog << "ASCII character typed : " <<
                             static_cast<char>(event.text.unicode)
                          << std::endl;
            break;
        case sf::Event::KeyPressed:
            std::clog << "Key pressed : " << event.key.code << std::endl;
            std::clog << "Ctrl :" << event.key.control << std::endl;
            std::clog << "Alt :" << event.key.alt << std::endl;
            std::clog << "Shift :" << event.key.shift << std::endl;
            std::clog << "System :" << event.key.system << std::endl;

            if (event.key.code == sf::Keyboard::Escape)
            {
                std::clog << "Escape key was pressed" << std::endl;
                m_appRunning = false;
            }
            break;
        case sf::Event::KeyReleased:
            break;
        case sf::Event::MouseWheelMoved:
            std::clog << "Wheel movement : " << event.mouseWheel.delta
                      << std::endl;
            std::clog << "Mouse x : " << event.mouseWheel.x << std::endl;
            std::clog << "Mouse y : " << event.mouseWheel.y << std::endl;
            break;
        case sf::Event::MouseButtonPressed:
            if (event.mouseButton.button == sf::Mouse::Right)
            {
                std::clog << "Right button was pressed" << std::endl;
                std::clog << "Mouse x : " << event.mouseButton.x
                          << std::endl;
                std::clog << "Mouse y : " << event.mouseButton.y
                          << std::endl;
            }
            if (!m_mouseDown)
            {
                m_camera.goToCenter(event.mouseButton.x,
                                    event.mouseButton.y);
                m_mouseDown = true;
            }
            break;
        case sf::Event::MouseButtonReleased:
            m_mouseDown = false;
            break;
        case sf::Event::MouseMoved:
            break;
        case sf::Event::MouseEntered:
            std::clog << "Mouse cursor has entered the window" << std::endl;
            break;
        case sf::Event::MouseLeft:
            std::clog << "Mouse cursor has left the window" << std::endl;
            break;
        case sf::Event::JoystickButtonPressed:
            std::clog << "Joystick button pressed" << std::endl;
            std::clog << "Joystick id : "
                      << event.joystickButton.joystickId << std::endl;
            std::clog << "Joystick button : "
                      << event.joystickButton.button << std::endl;
            break;
        case sf::Event::JoystickButtonReleased:
            break;
        case sf::Event::JoystickMoved:
            if (event.joystickMove.axis == sf::Joystick::X)
            {
                std::clog << "Joystick X axis moved" << std::endl;
                std::clog << "Joystick id : "
                          << event.joystickMove.joystickId << std::endl;
                std::clog << "Joystick new position : "
                          << event.joystickMove.position << std::endl;
            }
            break;
        case sf::Event::JoystickConnected:
            std::clog << "Joystick connected : " <<
                         event.joystickConnect.joystickId << std::endl;
            break;
        case sf::Event::JoystickDisconnected:
            std::clog << "Joystick disconnected : " <<
                         event.joystickConnect.joystickId << std::endl;
            break;
        default:
            break;
        }
    }
    // key holds
    unsigned int cameraVX {};
    unsigned int cameraVY {};

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        cameraVX = -1;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        cameraVX = 1;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        cameraVY = -1;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        cameraVY = 1;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
    {
        cameraVX *= 10;
        cameraVY *= 10;
    }

    if (cameraVX != 0 || cameraVY != 0)
    {
        m_camera.pan(cameraVX, cameraVY);
    }
}
void GameEngine::update()
{
    m_camera.update();
}
void GameEngine::loadLevel()
{
    m_currentLevel.loadLevel("misc/level1.xml", m_imageManager);
}
