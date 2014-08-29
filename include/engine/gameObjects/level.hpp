#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <vector>
#include <functionnal>

#include "engine/gameObjects/tile.hpp"
#include "engine/imageManager.hpp"

class Level
{

public:
    Level(unsigned int w, unsigned int h) { setDimensions(w, h); }
    ~Level() = default;
    void addTile(unsigned int x, unsigned int y, Tile& tile);
    Tile& getTile(unsigned int x, unsigned int y);
    void loadLevel(std::string filename, ImageManager& imageManager);
    int width();
    int height();
private:
    //A 2D array of Tile pointers
    vector<vector<std::reference_wrapper<Tile>>> m_map;
    //Width and height of level (in tiles)
    unsigned int m_w;
    unsigned int m_h;
    void setDimensions(unsigned int w, unsigned int h);

};

#endif // LEVEL_HPP
