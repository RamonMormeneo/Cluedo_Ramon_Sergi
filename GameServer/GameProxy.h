#pragma once
#include <SFML\Network.hpp>
#include "PlayerProxy.h" 
class GameProxy
{
public:
	GameProxy(int _id, std::string _name);
	~GameProxy();
	int id;
	std::vector<PlayerProxy*> playerProxies;
	enum State
	{
		INFO,
		IN_GAME,
		GAME_OVER
	};

	State state;
	int numReady;

	int playerIdOnTurn;
	int actionsCount;

	void CheckTurn();
	void InitBoard();

private:

};

