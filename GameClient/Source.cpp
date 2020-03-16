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
				std::lock_guard<std::mutex>guard(mtx);
				m_player.state = PlayerProxy::State::ACK_CREATE_SERVER;
			}
			break;
			case ACK_CREATED_SERVER:
			{
				std::lock_guard<std::mutex>guard(mtx);
				m_player.state = PlayerProxy::State::ACK_CREATED_SERVER_DONE;
			}
			break;
			case JOIN_SERVER:
			{
				int numServers;
				pack >> numServers;
				std::lock_guard<std::mutex>guard(mtx);
				for (int i = 0; i < numServers; i++)
				{
					std::string serverName;
					pack >> serverName;
					joinServer.serversList.push_back(serverName);
				}
				m_player.state = PlayerProxy::State::ACK_JOIN_SERVER;
			}
			break;
			case ACK_JOINED_SERVER:
			{
				std::cout << "received ACK JOINED\n";
				std::lock_guard<std::mutex>guard(mtx);
				m_player.state = PlayerProxy::State::ACK_JOINED_DONE;
			}
			break;
			case CHAT:
			{
				std::string message;
				pack >> message;
				std::lock_guard<std::mutex>guard(mtx);
				chat.aMensajes.push_back(message);
			}
			break;
			case START_GAME:
			{
				CharacterType ch1, ch2, ch3, ch4, ch5, ch6, ch7, ch8;
				int ch;
				int myPos, myPartnerPos, rival1, rival2;

				pack >> myPos >> myPartnerPos >> rival1 >> rival2;
				m_player.id = myPos;
				if (m_player.id == 0)
				{
					board.onTurn = true;
				}

				//all characters in  order:
				pack >> ch;
				ch1 = static_cast<CharacterType>(ch);
				pack >> ch;
				ch2 = static_cast<CharacterType>(ch);
				pack >> ch;
				ch3 = static_cast<CharacterType>(ch);
				pack >> ch;
				ch4 = static_cast<CharacterType>(ch);
				pack >> ch;
				ch5 = static_cast<CharacterType>(ch);
				pack >> ch;
				ch6 = static_cast<CharacterType>(ch);
				pack >> ch;
				ch7 = static_cast<CharacterType>(ch);
				pack >> ch;
				ch8 = static_cast<CharacterType>(ch);


				std::lock_guard<std::mutex>guard(mtx);
				m_player.state = PlayerProxy::State::ACK_START_GAME;
				shouldBeOnAckStart = true; // hi ha un fallo precisament només amb el player amb id 3 que no té cap sentit. això és per fer un hardcode hack
				std::cout << "state to ACK_START_GAME " << std::endl;

				board.InitIndexs(myPos, myPartnerPos, rival1, rival2);
				board.InitSpritesTextures();
				board.InitCharacters(ch1, ch2, ch3, ch4, ch5, ch6, ch7, ch8);

				board.sock = sock0;
			}
			break;
			case Protocol::MOVING:
			{
				//std::cout << "MOVING RECEIVED\n";
				int id, cht, turnId;
				CharacterType chtype;
				int posX, posY;
				pack >> id;
				pack >> cht;
				chtype = static_cast<CharacterType>(cht);
				pack >> posX;
				pack >> posY;
				std::cout << "[CLIENT] posX: " << posX << " posY: " << posY << std::endl;

				std::lock_guard<std::mutex>guard(mtx);
				board.moveCharacter(id, chtype, posX, posY);

				pack >> turnId;
				if (turnId == m_player.id)
				{
					board.onTurn = true;
				}
				else
				{
					board.onTurn = false;
				}
			}
			break;
			case Protocol::ATTACKING:
			{
				std::cout << "ATTACKING RECEIVED\n";
				//int id, cht, turnId;
				//CharacterType chtype;

				//pack >> id;
				//pack >> cht;
				//chtype = static_cast<CharacterType>(cht);

				int posX, posY, turnId;

				pack >> posX >> posY;

				std::lock_guard<std::mutex>guard(mtx);
				board.DealingDamage(posX, posY);
				//board.dealingDamage(id, chtype);

				pack >> turnId;
				if (turnId == m_player.id)
				{
					board.onTurn = true;
				}
				else
				{
					board.onTurn = false;
				}
			}
			break;
			case Protocol::GAME_OVER:
			{
				std::cout << "GAME OVER\n";

				int win;
				pack >> win;

				if (win == 1 && (m_player.id == 0 || m_player.id == 1))
				{
					//ha guanyat
					std::cout << "YOU WON\n";
				}
				else if (win == 2 && (m_player.id == 2 || m_player.id == 3))
				{
					std::cout << "YOU WON\n";
				}
				else
				{
					std::cout << "YOU LOST\n";
				}

				m_player.state = PlayerProxy::State::ACK_GAME_OVER;
			}
			break;
			default:
				break;
			}
		}
	}

}
