#pragma once
#include<map>
#include<string>
#include"Texture.h"
using std::map;
using std::string;

class Assets
{
public:
	static std::map<std::string, Texture>textures;

	//Load a texture from file
	static Texture loadTexture(Renderer& renderer, const string& filename, const string& name);

	//Retrieve stored texture
	static Texture& getTexture(const string& name);

	//Properly de-allocates all loaded resources
	static void clear();

private:
	Assets() {}

	//load a single texture from file
	static Texture loadTextureFromFile(Renderer& renderer, const string& filename);
};