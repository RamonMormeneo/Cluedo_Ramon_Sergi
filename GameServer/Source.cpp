#pragma once
#include <iostream>
#include <SFML\Graphics.hpp>
#include <SFML\Network.hpp>
#include <PlayerInfo.h>
#include <JoinServer.h>
#include <mutex>
#include "PlayerProxy.h"
#include "GameProxy.h"
#include "Constants.h"

const int NUM_PLAYERS = 4;

int main()
{
	
	PlayerInfo playerInfo;
	return 0;
}

//Client-Server
void ClientServerMode();
//Peer2Peer
void Peer2PeerMode();


//SERVER SOURCE
int main()
{
	ClientServerMode();
	//Peer2PeerMode();
	return 0;
}

#pragma region ClientServerFunctions

std::mutex mtx;

//declarations:
void MessageReceiver(GameProxy* gameProxy, PlayerProxy* p, std::string message);
void MessageSender(GameProxy* gameProxy, std::string message);
void EliminateGameProxy(GameProxy* gp, std::vector<GameProxy*>* gameProxies);

void ClientServerMode()
{

	sf::Socket::Status status;
	sf::TcpListener dispatcher;
	std::vector<GameProxy*> gameProxies;

	status = dispatcher.listen(52000);
	if (status != sf::Socket::Done)
	{
		std::cout << "Couldn't link to port" << std::endl;
		return;
	}
	std::cout << "Linked to port" << std::endl;

	//MainLoop(&gameProxies);
}

void StartGameInformer(GameProxy* gp)
{
	sf::Packet pack;

	for (int i = 0; i < gp->playerProxies.size(); i++)
	{

		pack << i;

		int partnerId = -1;

		//busquem i posem els ids dels rivals
		for (int j = 0; j < gp->playerProxies.size(); j++)
		{
			if (j != i && j != partnerId)
			{
				pack << j;
			}
		}

		sf::TcpSocket* client = gp->playerProxies[i]->sock;
		if (client->send(pack) != sf::Socket::Status::Done)
		{
			std::cout << "Problem informing player that game starts\n";
			return;
		}

		std::cout << "sent START_GAME" << std::endl;
		gp->playerProxies[i]->state = PlayerProxy::State::PLAYING;

		pack.clear();
	}
}


#pragma endregion


#pragma region P2PFunctions

struct Direction
{
	//sf::IpAddress ip; //no funciona aix�, no pot convertir IpAddress
	std::string ip;
	unsigned short port;
};

//BOOTSTRAPER:
void Peer2PeerMode()
{
	sf::Socket::Status status;
	sf::TcpListener dispatcher;
	sf::SocketSelector selector;
	sf::Packet packet;
	std::vector<Direction> aDirection;

#pragma region Connection

	status = dispatcher.listen(52000);
	if (status != sf::Socket::Done)
	{
		std::cout << "Couldn't link to port" << std::endl;
		return;
	}
	std::cout << "Linked to port" << std::endl;

	//Receive players info:
	std::cout << "Waiting for players' connection and information..." << std::endl;

	selector.add(dispatcher);
	while (aDirection.size() <= NUM_PLAYERS)
	{
		if (selector.wait())
		{
			if (selector.isReady(dispatcher))
			{
				sf::TcpSocket* sock = new sf::TcpSocket;
				if (dispatcher.accept(*sock) != sf::Socket::Done)
				{
					std::cout << "Error connecting with Player " << aDirection.size() + 1 << std::endl;
					return;
				}
				std::cout << "Player " << aDirection.size() + 1 << " connected." << std::endl;

				//send the number of other peers:
				packet << (int)aDirection.size();
				//send the total number of players:
				packet << NUM_PLAYERS;
				//pass all the other peers directions:
				for (int i = 0; i < aDirection.size(); i++)
				{
					packet << aDirection[i].ip << aDirection[i].port << i;
				}

				//get and set this peers data for the next peers
				std::string ip = sock->getRemoteAddress().toString();
				unsigned short port = sock->getRemotePort();
				Direction dir = { ip, port };
				aDirection.push_back(dir);

				status = sock->send(packet);
				if (status != sf::Socket::Status::Done)
				{
					std::cout << "Problem sending packet to Player " << aDirection.size() << std::endl;
					return;
				}
				std::cout << "Packet sent to Player " << aDirection.size() << std::endl;
				packet.clear();
				sock->disconnect();
			}
		}
	}

#pragma endregion
}

#pragma endregion