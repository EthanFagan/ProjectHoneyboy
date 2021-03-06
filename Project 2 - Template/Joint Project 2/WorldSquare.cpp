#include "WorldSquare.h"
#include <SFML\Graphics.hpp>
#include <iostream>
worldSquare::worldSquare()
{

	if (!m_worldSqTexture.loadFromFile("ASSETS/IMAGES/outerfence.png"))
	{
		std::cout << "Texture not loaded" << std::endl;
	}
	if (!m_emptySqTexture.loadFromFile("ASSETS/IMAGES/emptyBlock.png"))
	{
		std::cout << "Texture not loaded" << std::endl;
	}
	if (!m_floorSqTexture.loadFromFile("ASSETS/IMAGES/block.PNG"))
	{
		std::cout << "Texture not loaded" << std::endl;
	}

	m_Worldsprite.setTexture(m_floorSqTexture);
}
void worldSquare::update()
{
	if (m_isAWall == true)
	{
		m_Worldsprite.setTexture(m_worldSqTexture);// sets wall texture
	}
	else if (m_isFloor == true)
	{
		m_Worldsprite.setTexture(m_emptySqTexture);// sets floor tex
	}
	else if (m_isEmpty == true)
	{
		m_Worldsprite.setTexture(m_floorSqTexture);// sets hole tex
	}
}
void worldSquare::draw(sf::RenderWindow &t_window)
{

	t_window.draw(m_Worldsprite);// draws blocks
	
}

bool worldSquare::isAWall()
{
	if (m_isAWall == true)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool worldSquare::isEmpty()
{
	if (m_isEmpty == true)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool worldSquare::isFloor()
{
	if (m_isFloor == true)
	{
		return true;
	}
	else
	{
		return false;
	}
	
}

void worldSquare::makeAWall()
{
	m_isAWall = true;
	m_isEmpty = false;
	m_isFloor = false;
}

void worldSquare::makeEmpty()
{
	m_isEmpty = true;
	m_isAWall = false;
	m_isFloor = false;
}

void worldSquare::makeAFloor()
{
	m_isFloor = true;
	m_isAWall = false;
	m_isEmpty = false;
}

void worldSquare::setPosition(sf::Vector2f t_newPos)
{
	m_position = t_newPos;
	m_Worldsprite.setPosition(m_position);
}


int worldSquare::getDirection()
{
	return m_blockDirection;
}
