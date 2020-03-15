#include "Graphics.h"
#include <iostream>


Graphics::Graphics(int max)
{
	Sala invernadero("Invernadero", 0, 0, 8, 10, sf::Color::Yellow);
	Sala salaBillar("Sala de billar", 12, 0, 6, 10, sf::Color::Red);
	Sala biblioteca("Biblioteca", 22, 0, 6, 10, sf::Color::Cyan);
	Sala estudio("Estudio", 32, 0, 8, 10, sf::Color::Magenta);
	Sala salaBaile("Sala de baile", 0, 12, 8, 6, sf::Color::Blue);
	Sala vestibulo("vestibulo", 30, 12, 10, 8, sf::Color::White);
	Sala cocina("cocina", 0, 20, 10, 10, sf::Color::Green);
	Sala comedor("comedor", 13, 20, 13, 10, sf::Color(150,0,150));
	Sala salon("salon", 30, 22, 10, 8, sf::Color(0,150,150));
	salas[0] = invernadero;
	salas[1] = salaBillar;
	salas[2] = biblioteca;
	salas[3] = estudio;
	salas[4] = salaBaile;
	salas[5] = vestibulo;
	salas[6] = cocina;
	salas[7] = comedor;
	salas[8] = salon;

	centroMensajes.color = sf::Color(150,150,150);
	centroMensajes.origen.x = 12;
	centroMensajes.origen.y = 12;
	centroMensajes.longitud.x = 14;
	centroMensajes.longitud.y = 6;
	MaxPlayer = max;
}

void Graphics::DrawDungeon( )
{
	sf::RenderWindow _window(sf::VideoMode(800, 600), "Ventanita");
	sf::RectangleShape shape(sf::Vector2f(SIZE, SIZE));
	shape.setOutlineColor(sf::Color::Black);
	shape.setOutlineThickness(2.f);
	
	while (_window.isOpen())
	{
		sf::Event event;
		bool playerMoved = false;
		std::cout << "You can move " << MoveLeft << " time" << std::endl;
		std::cout << "You have " << PlayersArr[0].NumCartas << " cards" << std::endl;
		if (MoveLeft == 0)
		{
			LanzarDados();
		}
		while (_window.pollEvent(event))
		{
			
			switch (event.type)
			{
			case sf::Event::Closed:
				_window.close();
				break;
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Escape)
				{
					_window.close();
				}
				if (event.key.code == sf::Keyboard::Left && MoveLeft!=0)
				{
					if (PlayersArr[0].position.x > 0)
					{
						PlayersArr[0].position.x--;
						MoveLeft--;
						
					
					}
				}
				else if (event.key.code == sf::Keyboard::Up && MoveLeft != 0)
				{
					
					if (PlayersArr[0].position.y > 0)
					{
						PlayersArr[0].position.y--;
						MoveLeft--;
						system("CLS");
						
					}
				}
				else if (event.key.code == sf::Keyboard::Right && MoveLeft != 0)
				{
					
					if (PlayersArr[0].position.x < W_WINDOW_TITLE-1)
					{
						PlayersArr[0].position.x++;
						MoveLeft--;
						system("CLS");
						
					}
				}
				else if (event.key.code == sf::Keyboard::Down && MoveLeft != 0)
				{
					
					if (PlayersArr[0].position.y < H_WINDOW_TITLE-1)
					{
						PlayersArr[0].position.y++;
						MoveLeft--;
						system("CLS");
						
					}
				}
				
				break;
			}
		}
		_window.clear();
		for (int i = 0; i < W_WINDOW_TITLE; i++)
		{
			for (int j = 0; j < H_WINDOW_TITLE; j++)
			{

				shape.setFillColor(sf::Color(90, 90, 90, 255));


				shape.setPosition(sf::Vector2f(i*SIZE, j*SIZE));
				_window.draw(shape);
			}
		}

		for (size_t i = 0; i < salas.size(); i++)
		{
			salas[i].Draw(_window);
			
		}
		centroMensajes.Draw(_window);
		//Dibujo PJ
		for (int i = 0; i < MaxPlayer; i++)
		{
			sf::Vector2f position = (sf::Vector2f)PlayersArr[i].position;
			switch (i)
			{
			case 0:
				shape.setFillColor(sf::Color::Blue);
				break;
			case 1:
				shape.setFillColor(sf::Color::Yellow);
				break;
			case 2:
				shape.setFillColor(sf::Color::Red);
				break;
			case 3:
				shape.setFillColor(sf::Color::Magenta);
				break;
			case 4:
				shape.setFillColor(sf::Color::Green);
				break;
			case 5:
				shape.setFillColor(sf::Color::White);
				break;
			default:
				break;
			}
			
			shape.setFillColor(sf::Color(0, 0, 255, 255));
			shape.setPosition(sf::Vector2f(position.x*SIZE, position.y*SIZE));
			_window.draw(shape);
		}
		

		
		system("CLS");
		_window.display();
	}
}

void Graphics::UpdatePlayerPos(PlayerInfo Players[6])
{
	for (int i = 0; i < 6; i++)
	{
		PlayersArr[i] = Players[i];
	}
	
}

void Graphics::LanzarDados()
{
	for (int i = 0; i < 2; i++)
	{
		int dado = rand() % 7 + 1;
		if (dado == 1)
		{
			PlayersArr[0].NumCartas++;
		}
		MoveLeft += dado;
	}
}




Graphics::~Graphics()
{
}
