#include "GameProxy.h"




GameProxy::GameProxy(int _id, std::string _name)
{
	id = _id;
	name = _name;
	state = State::INFO;
	numReady = 0;
	actionsCount = 0;
	playerIdOnTurn = 0;
}

GameProxy::~GameProxy()
{
}
