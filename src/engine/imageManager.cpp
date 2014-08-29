
#include "engine/imageManager.hpp"

void ImageManager::pushTexture(sf::Texture &texture, unsigned int id)
{
    m_textureList.push_back(texture);

    m_listID[id] = m_textureList.size() - 1;
}

sf::Texture & ImageManager::textureAt(unsigned int id)
{
    return m_textureList[m_listID[id]];
}

void ImageManager::loadTileset(const std::string & filename)
{
    using boost::property_tree::ptree;

    ptree pt;

    read_xml(filename, pt);

    sf::Image tileset;
    BOOST_FOREACH(ptree::value_type& imgfile, pt.get_child("tileset"))
    {

        std::string imagePath = imgfile.second.get_value("<xmlattr>.path");
        tileset.loadFromFile(imagePath);
        BOOST_FOREACH(ptree::value_type& tile, imgfile.second)
        {
            unsigned int x = tile.second.get<unsigned int>("<xmlattr>.x");
            unsigned int y = tile.second.get<unsigned int>("<xmlattr>.y");
            unsigned int frames = tile.second.get<unsigned int>("<xmlattr>.frames");
            unsigned int id = tile.second.get<unsigned int>("<xmlattr>.id");

            sf::Image tileImage;
            tileImage.create(m_tileSize, m_tileSize);
            tileImage.copy(tileset, 0, 0, sf::IntRect(x * m_tileSize,
                                          y * m_tileSize, frames * m_tileSize,
                                                      m_tileSize), true);
            sf::Texture tileTex;
            if (!tileTex.loadFromImage(tileImage))
                throw std::runtime_error("Cannot convert tile image to texture !");

            pushTexture(tileTex, id);

        }
    }
}
