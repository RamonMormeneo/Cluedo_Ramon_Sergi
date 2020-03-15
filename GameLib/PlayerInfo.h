#pragma once
#include <SFML\Graphics.hpp>

class PlayerInfo
{
	
	int lives;
public:
	std::string name;
	sf::Vector2i position;
	PlayerInfo();
	~PlayerInfo();
};