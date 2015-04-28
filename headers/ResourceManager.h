/* 
 * File:   ResourceManager.h
 * Author: Alberto
 *
 * Created on 25 de abril de 2015, 18:20
 */

#ifndef RESOURCEMANAGER_H
#define	RESOURCEMANAGER_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <map>
#include <string>
#include <cstring>
class ResourceManager{
public:
    
    enum loadType{FILE,MEMORY,STREAM};
    
    typedef sf::Texture Texture;
    typedef sf::Font Font;
    typedef sf::SoundBuffer Sound;
    
    static ResourceManager& get(){
        static ResourceManager *instance = new ResourceManager();
        return *instance;
    }
    
    virtual void loadTexture(std::string path, std::string id, loadType l = FILE);
    virtual void loadFont(std::string path, std::string id, loadType l = FILE);
    virtual void loadSound(std::string path, std::string id, loadType l = FILE);
    
    virtual Texture* getTexture(std::string id);
    virtual Font* getFont(std::string id);
    virtual Sound* getSound(std::string id);
    
    virtual void deleteTexture(std::string id);
    virtual void deleteFont(std::string id);
    virtual void deleteSound(std::string id);
    
    virtual void loadXML(std::string path);
private:
    std::map<std::string,Texture*> textures;
    std::map<std::string,Font*> fonts;
    std::map<std::string,Sound*> sounds;
    ResourceManager();
};
#endif	/* RESOURCEMANAGER_H */

