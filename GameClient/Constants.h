#include <SFML/Graphics.hpp>
#pragma once

#define IP "127.0.0.1"
#define PORT 52000

#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 540

enum Protocol
{
	CLIENT_SERVER,
	PEER2PEER,
	CREATE_SERVER,
	ACK_CREATED_SERVER,
	JOIN_SERVER,
	ACK_JOINED_SERVER,
	ALIAS,
	START_GAME,
	CHAT,
	MOVING,
	GAME_OVER,
	INFO,//P2P
};


struct Button
{
	sf::Sprite sprite;
	sf::Texture texture;
};
