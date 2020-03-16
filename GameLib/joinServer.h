#pragma once
#include <SFML/Graphics.hpp>


class JoinServer
{
public:
	JoinServer();
	JoinServer(int i);
	~JoinServer();

	std::vector<std::string> serversList;
	std::vector<sf::Text*> serversTextList;
};

