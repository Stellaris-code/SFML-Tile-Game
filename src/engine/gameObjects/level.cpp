#include "engine/gameObjects/level.hpp"

int Level::height()
{
    return m_h;
}
int Level::width()
{
    return m_w;
}
void Level::setDimensions(unsigned int w, unsigned int h)
{
    m_w = w;
    m_h = h;
    //w rows
    m_map.resize(m_w);

    for(int i = 0; i < m_w; i++)
    {
        m_map[i].resize(m_h);
    }
}
void Level::setTile(unsigned int x, unsigned int y, Tile& tile)
{
    m_map[x][y] = tile;
}
Tile Level::getTile(unsigned int x, unsigned int y)
{

    return m_map[x][y]; // Let's that vector throw harmless exceptions !

}

void Level::loadLevel(std::string filename, ImageManager& imageManager)
{
    using boost::property_tree::ptree;

    ptree pt;

    read_xml(filename, pt);

    setDimensions(pt.get<unsigned int>("level.<xmlattr>.width"),
            pt.get<unsigned int>("level.<xmlattr>.height"));

    BOOST_FOREACH(ptree::value_type& node,
                  pt.get_child("level"))
    {
        if (node.second.get<std::string>("") == "tileset")
        {
            std::string path = node.second.get<std::string>("<xmlattr>.path");
            imageManager.loadTileset(path);
        }
        else if (node.second.get<std::string>("") == "tile")
        {
            unsigned int x = node.second.get<unsigned int>("<xmlattr>.x");
            unsigned int y = node.second.get<unsigned int>("<xmlattr>.y");
            unsigned int baseid = node.second.get<unsigned int>("<xmlattr>.baseid");
            bool walkable = node.second.get<bool>("<xmlattr>.walkable", true);

            Tile newTile(imageManager.textureAt(baseid));
            setTile(x, y, newTile);
        }
    }

}
