#include <iostream>
#include "engine/gameEngine.hpp"



int main()
{
    GameEngine engine(800,600,64);
    engine.run("Test");
    std::cout << "Hello World!" << std::endl;
    return 0;
}

