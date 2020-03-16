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
	GenerarBaraja();
	for (int i = 0; i < PlayersArr[0].NumCartas; i++)
	{
		Miscartas.push_back(Baraja.top());
		Baraja.pop();
	}
	
	while (_window.isOpen())
	{
		sf::Event event;
		bool playerMoved = false;
		std::cout << "You can move " << MoveLeft << " time" << std::endl;
		std::cout << "You have " << PlayersArr[0].NumCartas << " cards" << std::endl;
		std::cout << "Your cards are:" << std::endl;
		for (int i = 0; i < PlayersArr[0].NumCartas; i++)
		{
			std::cout << i+1 <<" " << Miscartas[i].N << " " << Miscartas[i].T<< std::endl;
		}
		
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
				if (event.key.code == sf::Keyboard::Left && MoveLeft!=0 && MovL)
				{
					if (PlayersArr[0].position.x > 0)
					{
						PlayersArr[0].position.x--;
						MoveLeft--;
						
					
					}
				}
				else if (event.key.code == sf::Keyboard::Up && MoveLeft != 0 && MovU)
				{
					
					if (PlayersArr[0].position.y > 0)
					{
						PlayersArr[0].position.y--;
						MoveLeft--;
						system("CLS");
						
					}
				}
				else if (event.key.code == sf::Keyboard::Right && MoveLeft != 0 && MovR)
				{
					
					if (PlayersArr[0].position.x < W_WINDOW_TITLE-1)
					{
						PlayersArr[0].position.x++;
						MoveLeft--;
						system("CLS");
						
					}
				}
				else if (event.key.code == sf::Keyboard::Down && MoveLeft != 0 && MovD)
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
		ColisionconSala();
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
			if (!Baraja.empty())
			{
				Miscartas.push_back(Baraja.top());
				Baraja.pop();
			}
		}
		MoveLeft += dado;
	}
}

void Graphics::GenerarBaraja()
{
	
	int used[20];
	for (int i = 0; i < 21; i++)
	{
		used[i] = 22;
	}
	bool Done = false;
	int b = 0;
	while (!Done)
	{
		int a = rand() % 21;
		
		bool find = false;
		switch (a)
		{
		case 0:
			for (int i = 0; i < 21; i++)
			{
				if (used[i] == 0)
				{
					find = true;
					break;
				}
			}
			if (!find)
			{
				used[b] = a;
				Carta Card{std::string("Puñal"),std::string("Arma")};
				Baraja.push(Card);
				b++;
			}
			break;
		case 1:
			for (int i = 0; i < 21; i++)
			{
				if (used[i] == 1)
				{
					find = true;
					break;
				}
			}
			if (!find)
			{
				used[b] = a;
				Carta Card{ std::string("Cuerda"),std::string("Arma") };
				Baraja.push(Card);
				b++;
			}
			break;
		case 2:
			for (int i = 0; i < 21; i++)
			{
				if (used[i] == 2)
				{
					find = true;
					break;
				}
			}
			if (!find)
			{
				used[b] = a;
				Carta Card{ std::string("Candelabro"),std::string("Arma") };
				Baraja.push(Card);
				b++;
			}
			break;
		case 3:
			for (int i = 0; i < 21; i++)
			{
				if (used[i] == 3)
				{
					find = true;
					break;
				}
			}
			if (!find)
			{
				used[b] = a;
				Carta Card{ std::string("Tuberia"),std::string("Arma") };
				Baraja.push(Card);
				b++;
			}
			break;
		case 4:
			for (int i = 0; i < 21; i++)
			{
				if (used[i] == 4)
				{
					find = true;
					break;
				}
			}
			if (!find)
			{
				used[b] = a;
				Carta Card{ std::string("Pistola"),std::string("Arma") };
				Baraja.push(Card);
				b++;
			}
			break;
		case 5:
			for (int i = 0; i < 21; i++)
			{
				if (used[i] == 5)
				{
					find = true;
					break;
				}
			}
			if (!find)
			{
				used[b] = a;
				Carta Card{ std::string("Herramienta"),std::string("Arma") };
				Baraja.push(Card);
				b++;
			}
			break;
		case 6:
			for (int i = 0; i < 21; i++)
			{
				if (used[i] == 6)
				{
					find = true;
					break;
				}
			}
			if (!find)
			{
				used[b] = a;
				Carta Card{ std::string("Amapola"),std::string("Personaje") };
				Baraja.push(Card);
				b++;
			}
			break;
		case 7:
			for (int i = 0; i < 21; i++)
			{
				if (used[i] == 7)
				{
					find = true;
					break;
				}
			}
			if (!find)
			{
				used[b] = a;
				Carta Card{ std::string("Rubio"),std::string("Personaje") };
				Baraja.push(Card);
				b++;
			}
			break;
		case 8:
			for (int i = 0; i < 21; i++)
			{
				if (used[i] == 8)
				{
					find = true;
					break;
				}
			}
			if (!find)
			{
				used[b] = a;
				Carta Card{ std::string("Orquidea"),std::string("Personaje") };
				Baraja.push(Card);
				b++;
			}
			break;
		case 9:
			for (int i = 0; i < 21; i++)
			{
				if (used[i] == 9)
				{
					find = true;
					break;
				}
			}
			if (!find)
			{
				used[b] = a;
				Carta Card{ std::string("Prado"),std::string("Personaje") };
				Baraja.push(Card);
				b++;
			}
			break;
		case 10:
			for (int i = 0; i < 21; i++)
			{
				if (used[i] == 10)
				{
					find = true;
					break;
				}
			}
			if (!find)
			{
				used[b] = a;
				Carta Card{ std::string("Celeste"),std::string("Personaje") };
				Baraja.push(Card);
				b++;
			}
			break;
		case 11:
			for (int i = 0; i < 21; i++)
			{
				if (used[i] == 11)
				{
					find = true;
					break;
				}
			}
			if (!find)
			{
				used[b] = a;
				Carta Card{ std::string("Mora"),std::string("Personaje") };
				Baraja.push(Card);
				b++;
			}
			break;
		case 12:
			for (int i = 0; i < 21; i++)
			{
				if (used[i] == 12)
				{
					find = true;
					break;
				}
			}
			if (!find)
			{
				used[b] = a;
				Carta Card{ std::string("Invernadero"),std::string("Habitacion") };
				Baraja.push(Card);
				b++;
			}
			break;
		case 13:
			for (int i = 0; i < 21; i++)
			{
				if (used[i] == 13)
				{
					find = true;
					break;
				}
			}
			if (!find)
			{
				used[b] = a;
				Carta Card{ std::string("Billar"),std::string("Habitacion") };
				Baraja.push(Card);
				b++;
			}
			break;
		case 14:
			for (int i = 0; i < 21; i++)
			{
				if (used[i] == 14)
				{
					find = true;
					break;
				}
			}
			if (!find)
			{
				used[b] = a;
				Carta Card{ std::string("Biblioteca"),std::string("Habitacion") };
				Baraja.push(Card);
				b++;
			}
			break;
		case 15:
			for (int i = 0; i < 21; i++)
			{
				if (used[i] == 15)
				{
					find = true;
					break;
				}
			}
			if (!find)
			{
				used[b] = a;
				Carta Card{ std::string("Estudio"),std::string("Habitacion") };
				Baraja.push(Card);
				b++;
			}
			break;
		case 16:
			for (int i = 0; i < 21; i++)
			{
				if (used[i] == 16)
				{
					find = true;
					break;
				}
			}
			if (!find)
			{
				used[b] = a;
				Carta Card{ std::string("Sala Baile"),std::string("Habitacion") };
				Baraja.push(Card);
				b++;
			}
			break;
		case 17:
			for (int i = 0; i < 21; i++)
			{
				if (used[i] == 17)
				{
					find = true;
					break;
				}
			}
			if (!find)
			{
				used[b] = a;
				Carta Card{ std::string("Cocina"),std::string("Habitacion") };
				Baraja.push(Card);
				b++;
			}
			break;
		case 18:
			for (int i = 0; i < 21; i++)
			{
				if (used[i] == 18)
				{
					find = true;
					break;
				}
			}
			if (!find)
			{
				used[b] = a;
				Carta Card{ std::string("Comedor"),std::string("Habitacion") };
				Baraja.push(Card);
				b++;
			}
			break;
		case 19:
			for (int i = 0; i < 21; i++)
			{
				if (used[i] == 19)
				{
					find = true;
					break;
				}
			}
			if (!find)
			{
				used[b] = a;
				Carta Card{ std::string("Salon"),std::string("Habitacion") };
				Baraja.push(Card);
				b++;
			}
			break;
		case 20:
			for (int i = 0; i < 21; i++)
			{
				if (used[i] == 20)
				{
					find = true;
					break;
				}
			}
			if (!find)
			{
				used[b] = a;
				Carta Card{ std::string("Vestibulo"),std::string("Habitacion") };
				Baraja.push(Card);
				b++;
			}
			break;
		default:
			break;
		}
		for (int i = 0; i < 21; i++)
		{
			if (used[i] == 22)
			{
				Done = false;
				break;
			}
			else
			{
				Done = true;
			}
		}
	}
}

void Graphics::ColisionconSala()
{
	if ((PlayersArr[0].position.y == 12 || PlayersArr[0].position.y == 13 || PlayersArr[0].position.y == 14 || PlayersArr[0].position.y == 15 || PlayersArr[0].position.y == 16 || PlayersArr[0].position.y == 17 || PlayersArr[0].position.y == 18 || PlayersArr[0].position.y == 19) && (PlayersArr[0].position.x == 30 || PlayersArr[0].position.x == 31 || PlayersArr[0].position.x == 32 || PlayersArr[0].position.x == 33 || PlayersArr[0].position.x == 34 || PlayersArr[0].position.x == 35 || PlayersArr[0].position.x == 36 || PlayersArr[0].position.x == 37 || PlayersArr[0].position.x == 38 || PlayersArr[0].position.x == 39))
	{
		MovL = false;
		MovR = false;
		MovU = false;
		MovD = false;
		if (!reset)
		{
			MoveLeft = 0;
			reset = true;
		}
			std::cout << "Estoy en el vestibulo" << std::endl;
			if (PlayersArr[0].position.x == 30)
			{
				MovL = true;
				
			}
			if (PlayersArr[0].position.y == 12)
			{
				
				MovU = true;
				
			}
			if(PlayersArr[0].position.y == 19)
			{
				
				MovD = true;
			}
	}
	else if ((PlayersArr[0].position.y == 22 || PlayersArr[0].position.y == 23 || PlayersArr[0].position.y == 24 || PlayersArr[0].position.y == 25 || PlayersArr[0].position.y == 26 || PlayersArr[0].position.y == 27 || PlayersArr[0].position.y == 28 || PlayersArr[0].position.y == 29) && (PlayersArr[0].position.x == 30 || PlayersArr[0].position.x == 31 || PlayersArr[0].position.x == 32 || PlayersArr[0].position.x == 33 || PlayersArr[0].position.x == 34 || PlayersArr[0].position.x == 35 || PlayersArr[0].position.x == 36 || PlayersArr[0].position.x == 37 || PlayersArr[0].position.x == 38 || PlayersArr[0].position.x == 39))
	{
		MovL = false;
		MovR = false;
		MovU = false;
		MovD = false;
		if (!reset)
		{
			MoveLeft = 0;
			reset = true;
		}
		std::cout << "Estoy en el Salon" << std::endl;
		if (PlayersArr[0].position.x == 30)
		{
			MovL = true;

		}
		if (PlayersArr[0].position.y == 22)
		{

			MovU = true;

		}
	}
	else if ((PlayersArr[0].position.y == 9 || PlayersArr[0].position.y == 8 || PlayersArr[0].position.y == 7 || PlayersArr[0].position.y == 6 || PlayersArr[0].position.y == 5 || PlayersArr[0].position.y == 4 || PlayersArr[0].position.y == 3 || PlayersArr[0].position.y == 2 || PlayersArr[0].position.y == 1 || PlayersArr[0].position.y == 0) && (PlayersArr[0].position.x == 32 || PlayersArr[0].position.x == 33 || PlayersArr[0].position.x == 34 || PlayersArr[0].position.x == 35 || PlayersArr[0].position.x == 36 || PlayersArr[0].position.x == 37 || PlayersArr[0].position.x == 38 || PlayersArr[0].position.x == 39))
	{
		MovL = false;
		MovR = false;
		MovU = false;
		MovD = false;
		if (!reset)
		{
			MoveLeft = 0;
			reset = true;
		}
		std::cout << "Estoy en el Estudio" << std::endl;
		if (PlayersArr[0].position.x == 32)
		{
			MovL = true;

		}
		if (PlayersArr[0].position.y == 9)
		{

			MovD = true;

		}
	}
	else if ((PlayersArr[0].position.y == 9 || PlayersArr[0].position.y == 8 || PlayersArr[0].position.y == 7 || PlayersArr[0].position.y == 6 || PlayersArr[0].position.y == 5 || PlayersArr[0].position.y == 4 || PlayersArr[0].position.y == 3 || PlayersArr[0].position.y == 2 || PlayersArr[0].position.y == 1 || PlayersArr[0].position.y == 0) && (PlayersArr[0].position.x == 27 || PlayersArr[0].position.x == 26 || PlayersArr[0].position.x == 25 || PlayersArr[0].position.x == 24 || PlayersArr[0].position.x == 23 || PlayersArr[0].position.x == 22))
	{
		MovL = false;
		MovR = false;
		MovU = false;
		MovD = false;
		if (!reset)
		{
			MoveLeft = 0;
			reset = true;
		}
		std::cout << "Estoy en el Biblioteca" << std::endl;
		if (PlayersArr[0].position.x == 27)
		{
			MovR = true;

		}
		if (PlayersArr[0].position.x == 22)
		{
			MovL = true;

		}
		if (PlayersArr[0].position.y == 9)
		{

			MovD = true;

		}
	}
	else if ((PlayersArr[0].position.y == 9 || PlayersArr[0].position.y == 8 || PlayersArr[0].position.y == 7 || PlayersArr[0].position.y == 6 || PlayersArr[0].position.y == 5 || PlayersArr[0].position.y == 4 || PlayersArr[0].position.y == 3 || PlayersArr[0].position.y == 2 || PlayersArr[0].position.y == 1 || PlayersArr[0].position.y == 0) && (PlayersArr[0].position.x == 17 || PlayersArr[0].position.x == 16 || PlayersArr[0].position.x == 15 || PlayersArr[0].position.x == 14 || PlayersArr[0].position.x == 13 || PlayersArr[0].position.x == 12))
	{
	MovL = false;
	MovR = false;
	MovU = false;
	MovD = false;
	if (!reset)
	{
		MoveLeft = 0;
		reset = true;
	}
	std::cout << "Estoy en el Billar" << std::endl;
	if (PlayersArr[0].position.x == 17)
	{
		MovR = true;

	}
	if (PlayersArr[0].position.x == 12)
	{
		MovL = true;

	}
	if (PlayersArr[0].position.y == 9)
	{

		MovD = true;

	}
	}
	else if ((PlayersArr[0].position.y == 9 || PlayersArr[0].position.y == 8 || PlayersArr[0].position.y == 7 || PlayersArr[0].position.y == 6 || PlayersArr[0].position.y == 5 || PlayersArr[0].position.y == 4 || PlayersArr[0].position.y == 3 || PlayersArr[0].position.y == 2 || PlayersArr[0].position.y == 1 || PlayersArr[0].position.y == 0) && (PlayersArr[0].position.x == 7 || PlayersArr[0].position.x == 6 || PlayersArr[0].position.x == 5 || PlayersArr[0].position.x == 4 || PlayersArr[0].position.x == 3 || PlayersArr[0].position.x == 2 || PlayersArr[0].position.x == 1 || PlayersArr[0].position.x == 0))
	{
	MovL = false;
	MovR = false;
	MovU = false;
	MovD = false;
	if (!reset)
	{
		MoveLeft = 0;
		reset = true;
	}
	std::cout << "Estoy en el Invernadero" << std::endl;
	if (PlayersArr[0].position.x == 7)
	{
		MovR = true;

	}
	if (PlayersArr[0].position.y == 9)
	{

		MovD = true;

	}
	}
	else if ((PlayersArr[0].position.y == 17 || PlayersArr[0].position.y == 16 || PlayersArr[0].position.y == 15 || PlayersArr[0].position.y == 14 || PlayersArr[0].position.y == 13 || PlayersArr[0].position.y == 12 ) && (PlayersArr[0].position.x == 7 || PlayersArr[0].position.x == 6 || PlayersArr[0].position.x == 5 || PlayersArr[0].position.x == 4 || PlayersArr[0].position.x == 3 || PlayersArr[0].position.x == 2 || PlayersArr[0].position.x == 1 || PlayersArr[0].position.x == 0))
	{
	MovL = false;
	MovR = false;
	MovU = false;
	MovD = false;
	if (!reset)
	{
		MoveLeft = 0;
		reset = true;
	}
	std::cout << "Estoy en la Sala de baile" << std::endl;
	if (PlayersArr[0].position.x == 7)
	{
		MovR = true;

	}
	if (PlayersArr[0].position.y == 17)
	{

		MovD = true;

	}

	if (PlayersArr[0].position.y == 12)
	{

		MovU = true;

	}
	}
	else if ((PlayersArr[0].position.y == 29 || PlayersArr[0].position.y == 28 || PlayersArr[0].position.y == 27 || PlayersArr[0].position.y == 26 || PlayersArr[0].position.y == 25 || PlayersArr[0].position.y == 24 || PlayersArr[0].position.y == 23 || PlayersArr[0].position.y == 22 || PlayersArr[0].position.y == 21 || PlayersArr[0].position.y == 20) && (PlayersArr[0].position.x == 9 || PlayersArr[0].position.x == 8 || PlayersArr[0].position.x == 7 || PlayersArr[0].position.x == 6 || PlayersArr[0].position.x == 5 || PlayersArr[0].position.x == 4 || PlayersArr[0].position.x == 3 || PlayersArr[0].position.x == 2 || PlayersArr[0].position.x == 1 || PlayersArr[0].position.x == 0))
	{
	MovL = false;
	MovR = false;
	MovU = false;
	MovD = false;
	if (!reset)
	{
		MoveLeft = 0;
		reset = true;
	}
	std::cout << "Estoy en la cocina" << std::endl;
	if (PlayersArr[0].position.x == 9)
	{
		MovR = true;

	}
	

	if (PlayersArr[0].position.y == 20)
	{

		MovU = true;

	}
	}
	else if ((PlayersArr[0].position.y == 29 || PlayersArr[0].position.y == 28 || PlayersArr[0].position.y == 27 || PlayersArr[0].position.y == 26 || PlayersArr[0].position.y == 25 || PlayersArr[0].position.y == 24 || PlayersArr[0].position.y == 23 || PlayersArr[0].position.y == 22 || PlayersArr[0].position.y == 21 || PlayersArr[0].position.y == 20) && (PlayersArr[0].position.x == 25 || PlayersArr[0].position.x == 24 || PlayersArr[0].position.x == 23 || PlayersArr[0].position.x == 22 || PlayersArr[0].position.x ==21 || PlayersArr[0].position.x == 20 || PlayersArr[0].position.x == 19 || PlayersArr[0].position.x == 18 || PlayersArr[0].position.x == 17 || PlayersArr[0].position.x == 16 || PlayersArr[0].position.x == 15 || PlayersArr[0].position.x == 14 || PlayersArr[0].position.x == 13))
	{
	MovL = false;
	MovR = false;
	MovU = false;
	MovD = false;
	if (!reset)
	{
		MoveLeft = 0;
		reset = true;
	}
	std::cout << "Estoy en el comedor" << std::endl;
	if (PlayersArr[0].position.x == 25)
	{
		MovR = true;

	}
	if (PlayersArr[0].position.x == 13)
	{
		MovL = true;

	}

	if (PlayersArr[0].position.y == 20)
	{

		MovU = true;

	}
	}
	else if (( PlayersArr[0].position.y == 18 || PlayersArr[0].position.y == 17 || PlayersArr[0].position.y == 16 || PlayersArr[0].position.y == 15 || PlayersArr[0].position.y == 14 || PlayersArr[0].position.y == 13 || PlayersArr[0].position.y == 12 || PlayersArr[0].position.y == 11) && (PlayersArr[0].position.x == 26 || PlayersArr[0].position.x == 25 || PlayersArr[0].position.x == 24 || PlayersArr[0].position.x == 23 || PlayersArr[0].position.x == 22 || PlayersArr[0].position.x == 21 || PlayersArr[0].position.x == 20 || PlayersArr[0].position.x == 19 || PlayersArr[0].position.x == 18 || PlayersArr[0].position.x == 17 || PlayersArr[0].position.x == 16 || PlayersArr[0].position.x == 15 || PlayersArr[0].position.x == 14 || PlayersArr[0].position.x == 13 || PlayersArr[0].position.x == 12 || PlayersArr[0].position.x == 11))
	{

	if (PlayersArr[0].position.x == 26 && PlayersArr[0].position.y != 11 && PlayersArr[0].position.y != 18)
	{ 
	
		MovL = false;
		MovR = true;
		MovU = true;
		MovD = true;
	}
	else if (PlayersArr[0].position.x == 11 && PlayersArr[0].position.y != 11 && PlayersArr[0].position.y != 18)
	{
		MovL = true;
		MovR = false;
		MovU = true;
		MovD = true;
	}

	else if (PlayersArr[0].position.y == 11 && PlayersArr[0].position.x != 11 && PlayersArr[0].position.x != 26)
	{

		MovL = true;
		MovR = true;
		MovU = true;
		MovD = false;

	}
	else if (PlayersArr[0].position.y == 18 && PlayersArr[0].position.x != 11 && PlayersArr[0].position.x != 26)
	{

		MovL = true;
		MovR = true;
		MovU = false;
		MovD = true;
	}
	else
	{
		MovL = true;
		MovR = true;
		MovU = true;
		MovD = true;

	}
	}
	else
	{
		MovL = true;
		MovR = true;
		MovU = true;
		MovD = true;
		reset = false;
	}
	
}




Graphics::~Graphics()
{
}
