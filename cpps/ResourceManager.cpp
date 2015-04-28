/* 
 * File:   ResourceManager.cpp
 * Author: Alberto
 * 
 * Created on 25 de abril de 2015, 18:20
 */

#include "../headers/ResourceManager.h"
#include "../headers/rapidxml.hpp"
#include "../headers/rapidxml_utils.hpp"
#include <iostream>
using namespace std;
using namespace rapidxml;
ResourceManager::ResourceManager(){}

/***************************************************/
/*                       LOADERS
/**************************************************/
void ResourceManager::loadTexture(string path, string id,  loadType l)
{
    Texture* tex = new Texture();
    bool loaded = false;
    switch(l)
    {
        case FILE:
            loaded = tex->loadFromFile(path);
            break;
            
        default:break;
    }
    if (!loaded){
        cout<<"Error cargando la imagen '"<<path<<"'"<<endl;
        exit(0);
    }
    textures.insert( pair<string,Texture*>(id,tex) );
}

void ResourceManager::loadFont(string path, string id,  loadType l)
{
    Font* font = new Font();
    bool loaded = false;
    switch(l)
    {
        case FILE:
            loaded = font->loadFromFile(path);
            break;
            
        default:break;
    }
    if (!loaded){
        cout<<"Error cargando la fuente "<<path<<"'"<<endl;
        exit(0);
    }
    fonts.insert( pair<string,Font*>(id,font) );
}

void ResourceManager::loadSound(string path, string id,  loadType l)
{
    Sound* sound = new Sound();
    bool loaded = false;
    switch(l)
    {
        case FILE:
            loaded = sound->loadFromFile(path);
            break;
            
        default:break;
    }
    if (!loaded){
        cout<<"Error cargando la fuente "<<path<<"'"<<endl;
        exit(0);
    }
    sounds.insert( pair<string,Sound*>(id,sound) );
}

void ResourceManager::loadXML(string path)
{
    file<> xmlFile(path.c_str());
    xml_document<> doc;
    doc.parse<0>(xmlFile.data());
    xml_node<> *node = doc.first_node();
    
    //Accedo al primer tipo de recursos
    node = node->first_node();    
    int type = 0;
    string p,id;
    bool completed = false;
    while(node)
    {
        if(strcmp(node->name(),"fonts")==0)
            type=1;
        else if(strcmp(node->name(),"textures")==0)
            type=2;
        else if(strcmp(node->name(),"sounds")==0)
            type=3;
        
        node=node->first_node();
        completed = false;
        while(!completed)
        {
            p=string(node->value());
            id=string(node->first_attribute()->value());
            
            if(type==1)
                loadFont(p,id);
            else if(type==2)
                loadTexture(p,id);
            else if(type==3)
                loadSound(p,id);
            
            if(node->next_sibling())
                node=node->next_sibling();
            else
                completed = true;
        }
        node = node->parent();
        node=node->next_sibling();
    }
}
/***************************************************/
/*                       GETTERS
/**************************************************/
ResourceManager::Texture* ResourceManager::getTexture(string id){
    return textures[id];
}

ResourceManager::Font* ResourceManager::getFont(string id){
    return fonts[id];
}

ResourceManager::Sound* ResourceManager::getSound(string id){
    return sounds[id];
}

/***************************************************/
/*                     DELETERS
/**************************************************/
void ResourceManager::deleteTexture(std::string id){
    delete textures[id];
}

void ResourceManager::deleteFont(std::string id){
    delete fonts[id];
}

void ResourceManager::deleteSound(std::string id){
    delete sounds[id];
}
