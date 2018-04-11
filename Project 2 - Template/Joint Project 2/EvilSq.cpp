// EvilSq function definitions here
#include <SFML\Graphics.hpp>
#include "EvilSq.h"
#include <iostream>
#include "Globals.h"

EvilSq::EvilSq()
{
	if (!m_enemyTexture.loadFromFile("ASSETS/IMAGES/BEES.png"))
	{
		std::cout << "texture not loaded" << std::endl;
	}
	enemyX = 0;
	enemyY = 0;
	//----------------
	m_enemySprite.setTexture(m_enemyTexture);
	m_enemySprite.setTextureRect(sf::IntRect(enemyX, enemyY, 32, 32));
	m_enemySprite.setPosition(sf::Vector2f(m_enemyRow * 32, m_enemyCol * 32));
	m_enemySprite.setPosition(m_enemyPosition);
}

void EvilSq::update(worldSquare t_blockArray[MAX_ROWS][MAX_COL])
{
	timer++;
	if (m_isEnemyAlive == true)
	{
		changeDirection(t_blockArray);
		die(t_blockArray);
		move();
		animation();
	}
}

void EvilSq::draw(sf::RenderWindow &t_window)
{
	t_window.draw(m_enemySprite);
}

void EvilSq::setPosition(sf::Vector2f t_newPos)
{
	m_enemyPosition = t_newPos;
}

void EvilSq::setDirection(int t_newDirection)
{
	if (t_newDirection == 1)
	{
		m_enemyDirection = NORTH;
	}
	if (t_newDirection == 2)
	{
		m_enemyDirection = SOUTH;
	}
	if (t_newDirection == 3)
	{
		m_enemyDirection = EAST;
	}
	if (t_newDirection == 4)
	{
		m_enemyDirection = WEST;
	}
}

int EvilSq::getRow()
{
	return m_enemyRow;
}

void EvilSq::setRow(int t_newRow)
{
	m_enemyRow = t_newRow;
}

int EvilSq::getCol()
{
	return m_enemyCol;
}

void EvilSq::setCol(int t_newCol)
{
	m_enemyCol = t_newCol;
}

bool EvilSq::getIsAlive()
{
	return m_isEnemyAlive;
}

void EvilSq::setIsAlive()
{
	m_isEnemyAlive = true;
}

void EvilSq::move()
{
	if (timer % 15 == 0)
	{
		if (m_enemyDirection == NORTH)
		{
			m_enemyCol -= 1;
		}
		else if(m_enemyDirection == SOUTH)
		{
			m_enemyCol += 1;
		}
		else if (m_enemyDirection == EAST)
		{
			m_enemyRow += 1;
		}
		else if (m_enemyDirection = WEST)
		{
			m_enemyRow -= 1;
		}
	}
}

void EvilSq::die(worldSquare t_blockArray[MAX_ROWS][MAX_COL])
{
	if (t_blockArray[m_enemyRow][m_enemyCol].isAWall() == true)
	{
		m_isEnemyAlive = false;
	}
}

void EvilSq::changeDirection(worldSquare t_blockArray[MAX_ROWS][MAX_COL])
{
		if (m_enemyDirection == NORTH)
		{
			if (t_blockArray[m_enemyRow][m_enemyCol - 1].isAWall() == true)
			{
				m_enemyDirection = SOUTH;
			}
		}
		else if (m_enemyDirection == SOUTH)
		{
			if (t_blockArray[m_enemyRow][m_enemyCol + 1].isAWall() == true)
			{
				m_enemyDirection = NORTH;
			}
		}
		else if (m_enemyDirection == WEST)
		{
			if (t_blockArray[m_enemyRow - 1][m_enemyCol].isAWall() == true)
			{
				m_enemyDirection = EAST;
			
			}
		}
		else if (m_enemyDirection == EAST)
		{
			if (t_blockArray[m_enemyRow + 1][m_enemyCol].isAWall() == true)
			{
				m_enemyDirection = WEST;
			}
		}
		
		setPosition(sf::Vector2f(m_enemyRow * 32, m_enemyCol * 32));
		m_enemySprite.setPosition(m_enemyPosition);
}

void EvilSq::animation()
{
	if (timer % 5 == 0)
	{
		enemyX += SPRITE_WIDTH;
	}

	if (timer >= MAX_TIMER)
	{
		timer = 0;
	}

	if (enemyX >= 96)
	{
		enemyX = 0;
	}

//-----------------------------
	if (m_enemyDirection == SOUTH)
	{
		enemyY = 0;
	}
	if (m_enemyDirection == NORTH)
	{
		enemyY = 96;
	}
	if (m_enemyDirection == WEST)
	{
		enemyY = 32;
	}
	if (m_enemyDirection == EAST)
	{
		enemyY = 64;
	}

	m_enemySprite.setTextureRect(sf::IntRect(enemyX, enemyY, 32, 32));
}
