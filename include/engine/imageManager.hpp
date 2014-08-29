#ifndef IMAGEMANAGER_HPP
#define IMAGEMANAGER_HPP

#include <vector>
#include <map>
#include <string>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>

#include <SFML/Graphics.hpp>

class ImageManager
{

public:
    ImageManager() = default;
    ~ImageManager() = default;

    void pushTexture(sf::Texture & texture, unsigned int id);
    sf::Texture & textureAt(unsigned int index);

    void setTileSize(unsigned int size) { m_tileSize = size; }

    void loadTileset(const std::string & filename);


private:
    std::vector<sf::Texture> m_textureList;
    std::map<unsigned int, unsigned int> m_listID;
    unsigned int m_tileSize { 64 };

};

#endif // IMAGEMANAGER_HPP
