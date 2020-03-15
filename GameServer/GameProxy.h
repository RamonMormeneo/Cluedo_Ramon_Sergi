#pragma once
#include <SFML\Network.hpp>

class GameProxy
{
public:
	GameProxy(int _id, std::string _name);
	~GameProxy();
	int id;
	std::string name;
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

