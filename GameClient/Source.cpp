#pragma once
#include <PlayerInfo.h>
#include <SFML\Network.hpp>

#include <iostream>
#include <string>
#include <vector>
#include <fcntl.h>
#include "Graphics.h"





int main()
{
	PlayerInfo playerInfo;
	Graphics g;
	PlayerInfo restplayers[6];
	restplayers[1] = playerInfo;

	g.DrawDungeon(restplayers);
	return 0;
}