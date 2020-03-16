#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include "PlayerInfo.h"
#include <vector>
#include <array>
#include <stack>
#define SIZE 20.f
///TAMA�O EN PX DE LA VENTANA
#define W_WINDOW_PX 800
#define H_WINDOW_PX 600

///TAMA�O EN CELDAS DE LA VENTANA
#define W_WINDOW_TITLE 40
#define H_WINDOW_TITLE 30
#define NUM_SALAS 9
#define ORIGEN_CENTRO_X 12
#define ORIGEN_CENTRO_Y 12
#define LONGITUD_CENTRO_X 14
#define LONGITUD_CENTRO_Y 6



struct Carta
{
	std::string N;
	std::string T;
	Carta(std::string _N, std::string _T)
	{
		N = _N;
		T = _T;
	}
};

struct Sala
{
	sf::Vector2f origen;
	sf::Vector2f longitud;
	std::string texto;
	sf::Color color;
	Sala() {}
	Sala(std::string _texto, int _origenX, int _origenY, int _longitudX, int _longitudY, sf::Color _color)
	{
		texto = _texto;
		origen.x = _origenX;
		origen.y = _origenY;
		longitud.x = _longitudX;
		longitud.y = _longitudY;
		color = _color;
	}
	void Draw(sf::RenderWindow& _window)
	{
		sf::RectangleShape shape(sf::Vector2f(SIZE, SIZE));
		shape.setFillColor(color);

		for (int x = origen.x*SIZE; x < (origen.x + longitud.x)*SIZE; x = x + SIZE)
		{
			for (int y = origen.y*SIZE; y < (origen.y + longitud.y)*SIZE; y = y + SIZE)
			{
				shape.setPosition(sf::Vector2f(x, y));
				_window.draw(shape);
			}
		}

		sf::Text text;
		text.setString(texto);
		text.setCharacterSize(14);
		text.setFillColor(sf::Color::Black);
		text.setPosition(origen.x*SIZE, origen.y*SIZE);
		sf::Font font;
		font.loadFromFile("courbd.ttf");
		text.setFont(font);
		_window.draw(text);
	}
};
class Graphics
{

	std::array<Sala, NUM_SALAS> salas;
	Sala centroMensajes;
	std::vector<Carta> Miscartas;
	std::stack<Carta> Baraja;
	Carta ArmaA{ "","" };
	Carta SalaA{ "","" };
	Carta Asesino{ "","" };
	PlayerInfo PlayersArr[6];
	int MaxPlayer;
	int MoveLeft=0;
	bool MovR = true;
	bool MovL = true;
	bool MovU = true;
	bool MovD = true;
	bool reset = false;
	bool endGAme = false;
public:
	Graphics(int max);
	void DrawDungeon();
	void UpdatePlayerPos(PlayerInfo Players[6] );
	void LanzarDados();
	void GenerarBaraja();
	void ColisionconSala();
	void CreateAsesino();
	void Inclulpar(std::string salaActual);
	void ConfirmarAcussacion(std::string arma,std::string persona,std::string);
	~Graphics();
};

