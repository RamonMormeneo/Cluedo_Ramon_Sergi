#pragma once
#include "PlayerInfo.h"
#include <SFML\Network.hpp>


class PlayerProxy :
	public PlayerInfo
{
public:
	PlayerProxy();
	PlayerProxy(sf::TcpSocket* _sock);
	~PlayerProxy();

	sf::TcpSocket* sock;

	enum State
	{
		FIRST_LOBBY,
		CREATING_SERVER,
		ACK_CREATE_SERVER,
		ACK_CREATED_SERVER_DONE,
		JOINING_SERVER,
		ACK_JOIN_SERVER,
		ACK_JOINED_DONE,
		PLAYER_ALIAS,
		SELECTING_CHARACTERS,
		WAITING,
		ACK_START_GAME,
		PLAYING,
		ACK_GAME_OVER
	};

	State state;

	int gameID;
};

