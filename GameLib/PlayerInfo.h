#pragma once
#include <SFML\Graphics.hpp>

class PlayerInfo
{
	
	int lives;
public:
	std::string name;
	int id;
	sf::Vector2i position;
	PlayerInfo();
	~PlayerInfo();
};