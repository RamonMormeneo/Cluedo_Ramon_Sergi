#pragma once
#include <PlayerInfo.h>
#include <SFML\Network.hpp>

#include <iostream>
#include <string>
#include <vector>
#include <fcntl.h>
#include "Graphics.h"
#include <mutex>
#include "Constants.h"
#include <PlayerProxy.h>



//Client-Server
void ClientServerMode(sf::TcpSocket* sock0);
//Peer2Peer
void Peer2PeerMode(sf::TcpSocket* sock0, sf::Packet p);


//CLIENT SOURCE
int main()
{
	sf::Socket::Status status;
	sf::Packet packet;
	sf::TcpSocket sock0;

	//server connection:
	status = sock0.connect(IP, PORT, sf::seconds(5.f));
	if (status != sf::Socket::Done)
	{
		std::cout << "Problem connecting to server" << std::endl;
		return 0;
	}

	std::cout << "Connected to server" << std::endl;

	status = sock0.receive(packet);
	if (status != sf::Socket::Done)
	{
		std::cout << "Problem receiving Server packet" << std::endl;
		return 0;
	}

	int mode;
	packet >> mode;

	if (mode == Protocol::CLIENT_SERVER)
	{
		ClientServerMode(&sock0);
	}
	else if (mode == Protocol::PEER2PEER)
	{
		Peer2PeerMode(&sock0, packet);//we send the packet because there's all the other info
	}

	return 0;
}


PlayerProxy m_player;

#pragma region ClientServerFunctions
std::mutex mtx;

void ClientServerMode(sf::TcpSocket* sock0)
{
	std::cout << "CLIENT-SERVER MODE" << std::endl;


	//MAIN THREAD (RECEIVER)
	sf::Packet pack;
	while (true)
	{
		if (sock0->receive(pack) == sf::Socket::Status::Done)
		{
			int protocol;
			pack >> protocol;

			switch (static_cast<Protocol>(protocol))
			{
			case CREATE_SERVER:
			{
				/*std::lock_guard<std::mutex>guard(mtx);
				m_player.state = PlayerProxy::State::ACK_CREATE_SERVER;*/
			}
			break;
			case ACK_CREATED_SERVER:
			{/*
				std::lock_guard<std::mutex>guard(mtx);
				m_player.state = PlayerProxy::State::ACK_CREATED_SERVER_DONE;*/
			}
			break;
			case JOIN_SERVER:
			{/*
				int numServers;
				pack >> numServers;
				std::lock_guard<std::mutex>guard(mtx);
				for (int i = 0; i < numServers; i++)
				{
					std::string serverName;
					pack >> serverName;
				}
				m_player.state = PlayerProxy::State::ACK_JOIN_SERVER;*/
			}
			break;
			case ACK_JOINED_SERVER:
			{/*
				std::cout << "received ACK JOINED\n";
				std::lock_guard<std::mutex>guard(mtx);
				m_player.state = PlayerProxy::State::ACK_JOINED_DONE;
			}*/
				break;
			case START_GAME:
			{
			}
			break;

			default:
				break;
			}
			}
		}

	}
}

#pragma endregion

#pragma region P2PFunctions

	//Global variables:
	int NUM_PLAYERS;
	std::vector< PlayerProxy*> playerProxies;
	int numReady;

	//declarations:
	void CreateChatP2P();
	void PeerGraphicsInterface();
	void SendToPlayerProxies();

	void Peer2PeerMode(sf::TcpSocket * sock0, sf::Packet packet)
	{
		sf::Socket::Status status;
		//PlayerInfo* m_playerInfo = new PlayerInfo;

#pragma region Connection

		int localPort = sock0->getLocalPort();
		sock0->disconnect();

		int numPeers;
		packet >> numPeers;
		std::cout << "Number peers: " << numPeers << std::endl;

		packet >> NUM_PLAYERS;
		std::cout << "Number players: " << NUM_PLAYERS << std::endl;

		if (numPeers == 0)
		{
			std::cout << "First Peer" << std::endl;
		}
		else
		{
			std::cout << "Extracting the other Peers..." << std::endl;
			//extract the other peers
			for (int i = 0; i < numPeers; i++)
			{
				sf::TcpSocket * socket = new sf::TcpSocket;
				std::string ip;
				unsigned short port;
				int num;
				packet >> ip >> port >> num;
				status = socket->connect(ip, port, sf::seconds(5.f));
				if (status != sf::Socket::Status::Done)
				{
					std::cout << "Problem connecting with peer " << num << std::endl;
				}
				PlayerProxy* newPlayer = new PlayerProxy(socket);
				playerProxies.push_back(newPlayer);
				std::cout << "Extracted player " << num << std::endl;
			}
		}

		std::cout << "Connecting with the new Peers..." << std::endl;

		sf::TcpListener listener;
		listener.listen(localPort);

		for (int i = numPeers + 1; i < NUM_PLAYERS; i++)
		{
			sf::TcpSocket * socket = new sf::TcpSocket;
			listener.accept(*socket);
			PlayerProxy* newPlayer = new PlayerProxy(socket);
			newPlayer->id = i;
			playerProxies.push_back(newPlayer);
			std::cout << "Connected with player" << i << std::endl;
		}

#pragma endregion

		std::cout << "All peers connected." << std::endl;


		sf::SocketSelector selector;

		for each (PlayerProxy * player in playerProxies)
		{
			if (player != &m_player)//al propi player no cal afegir-lo al selector, obvi
			{
				selector.add(*player->sock);
			}
		}

		sf::Packet pack;
		numReady = 0;

		while (true)
		{
			if (selector.wait())
			{
				for each (PlayerProxy * player in playerProxies)
				{
					if (player != &m_player)
					{
						//std::cout << "PLAYER ID :" << player->id << std::endl;
						if (selector.isReady(*player->sock))
						{
							if (player->sock->receive(pack) == sf::Socket::Status::Done)
							{
								std::cout << "received from " << player->id << std::endl;
								int a;
								pack >> a;
								switch (static_cast<Protocol>(a))
								{
								case Protocol::MOVING:
								{

								}
								break;
								

								////////////////////////////////////////////////////////////////			Estados a añadir


								default:
									break;
								}
							}
							else
							{
								//DISCONNECT?¿
								return;
							}
						}
					}
				}
			}
		}
	}

	void SendToPlayerProxies()
	{
		sf::Packet packet;
		packet << Protocol::INFO;

		for each(PlayerProxy* player in playerProxies)
		{
			if (player != &m_player)
			{
				if (player->sock->send(packet) != sf::Socket::Status::Done)
				{
					std::cout << "[INFO] Problem sending alias to peers\n";
					return;
				}
			}
		}
	}

#pragma endregion