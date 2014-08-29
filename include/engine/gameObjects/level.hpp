#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <vector>
#include <iostream>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>

#include "engine/gameObjects/tile.hpp"
#include "engine/imageManager.hpp"

class Level
{

public:
    Level(unsigned int w, unsigned int h) { setDimensions(w, h); }
    Level() = default;
    ~Level() = default;
    void setTile(unsigned int x, unsigned int y, Tile& tile);
    Tile getTile(unsigned int x, unsigned int y);
    void loadLevel(std::string filename, ImageManager& imageManager);
    int width();
    int height();
private:
    //A 2D array of Tile pointers
    std::vector<std::vector<Tile>> m_map;
    //Width and height of level (in tiles)
    unsigned int m_w;
    unsigned int m_h;
    void setDimensions(unsigned int w, unsigned int h);

};

#endif // LEVEL_HPP
