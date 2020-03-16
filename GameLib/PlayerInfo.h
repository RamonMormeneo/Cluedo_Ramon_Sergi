#pragma once
#include <SFML\Graphics.hpp>

class PlayerInfo
{
	
	
public:
	int NumCartas=3;
	std::string name;
	int id;
	sf::Vector2i position;
	PlayerInfo();
	~PlayerInfo();
};