#include "PlayerProxy.h"



PlayerProxy::PlayerProxy()
{
	sock = nullptr;
	state = State::FIRST_LOBBY;
}

PlayerProxy::PlayerProxy(sf::TcpSocket * _sock)
{
	sock = _sock;
	state = State::FIRST_LOBBY;
}

PlayerProxy::~PlayerProxy()
{
}
