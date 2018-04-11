#pragma once
#include <SFML\Graphics.hpp>
#include "Globals.h"
class worldSquare
{
	bool m_isAWall; //does it contain a world square or not
	bool m_isEmpty;
	bool m_isFloor;
	

	int m_blockDirection = -1;

	sf::Texture m_worldSqTexture;	   //the texture for the worldSquare
	sf::Texture m_emptySqTexture;	   //the texture for the empty square
	sf::Texture m_whiteSqTexture;

	sf::Vector2f m_position;

	sf::Sprite m_Worldsprite; 	   //sprite used to represent the square

public:
	worldSquare();
	void update();
	void draw(sf::RenderWindow &t_window); //if containsSquare is true draw the worldSqTexture  else draw emptySqTexture.
	bool isAWall();
	bool isEmpty();
	bool isFloor();
	int  getDirection();
	void makeAWall();
	void makeAFloor();
	void makeEmpty();
	void makeKicked(int t_newDirection);
	void setPosition(sf::Vector2f t_newPos);
	

};