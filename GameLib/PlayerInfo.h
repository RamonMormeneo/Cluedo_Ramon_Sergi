#pragma once
#include <SFML\Graphics.hpp>

class PlayerInfo
{
	
	
public:
	int NumCartas=3;
	std::string name;
	sf::Vector2i position;
	PlayerInfo();
	~PlayerInfo();
};