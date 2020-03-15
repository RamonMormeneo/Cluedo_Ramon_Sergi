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
