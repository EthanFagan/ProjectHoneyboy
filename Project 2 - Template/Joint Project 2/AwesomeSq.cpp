// AwesomeSq function definitions here
#include <SFML\Graphics.hpp>
#include "AwesomeSq.h"
#include <iostream>
#include "Globals.h"

AwesomeSq::AwesomeSq()
{
	if (!m_playerTexture.loadFromFile("ASSETS/IMAGES/player.png"))
	{
		std::cout << "texture not loaded" << std::endl;
	}
	playerX = 0;
	playerY = 64;
	//----------------
	m_playerSprite.setTexture(m_playerTexture);
	m_playerSprite.setTextureRect(sf::IntRect(playerX, playerY, 32, 32));
	setPosition(sf::Vector2f(m_playerRow * 32, m_playerCol * 32));
	m_playerSprite.setPosition(m_playerPosition);
	//----------------
	m_playerDirection = SOUTH;
}

void AwesomeSq::draw(sf::RenderWindow &t_window)
{
	t_window.draw(m_playerSprite);
}

void AwesomeSq::setRow(int t_newRow)
{
	m_playerRow = t_newRow;
}

void AwesomeSq::setCol(int t_newCol)
{
	m_playerCol = t_newCol;
}

int AwesomeSq::getRow()
{
	return m_playerRow;
}

int AwesomeSq::getcol()
{
	return m_playerCol;
}

int AwesomeSq::getDirection()
{
	return m_playerDirection;
}

void AwesomeSq::update(worldSquare t_blockArray[MAX_ROWS][MAX_COL])
{
	timer++;
	kick(t_blockArray); // checks if player is kicking a block
	animation();// animates player sprite
	//---------------------------------------------------------
	move(t_blockArray); // moves player if player is pressing movement keys
}

void AwesomeSq::setPosition(sf::Vector2f t_newPosition)
{
	m_playerPosition = t_newPosition;
}

void AwesomeSq::move(worldSquare t_blockArray[MAX_ROWS][MAX_COL])
{
	//----MOVES PLAYER UP---------
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && timer % 10 == 0)
	{
		if (t_blockArray[m_playerRow][m_playerCol -1].isAWall() == false && t_blockArray[m_playerRow][m_playerCol -1].isEmpty() == false)
		{
			m_playerCol -= 1;
		}
		m_playerDirection = NORTH;
	}
	//----MOVES PLAYER DOWN--------
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && timer % 10 == 0)
	{
		if (t_blockArray[m_playerRow][m_playerCol +1].isAWall() == false && t_blockArray[m_playerRow][m_playerCol +1].isEmpty() == false)
		{
			m_playerCol += 1;
		}
		m_playerDirection = SOUTH;
	}
	//----MOVES PLAYER LEFT-------
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && timer % 10 == 0)
	{
		if (t_blockArray[m_playerRow -1][m_playerCol].isAWall() == false && t_blockArray[m_playerRow -1][m_playerCol].isEmpty() == false)
		{
			m_playerRow -= 1;
		}
		m_playerDirection = WEST;
	}
	//----MOVES PLAYER RIGHT------
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && timer % 10 == 0)
	{
		if (t_blockArray[m_playerRow +1][m_playerCol].isAWall() == false && t_blockArray[m_playerRow +1][m_playerCol].isEmpty() == false)
		{
			m_playerRow += 1;
		}
		m_playerDirection = EAST;
	}
	//SETS PLAYERS CHANGED POSITION
	setPosition(sf::Vector2f(m_playerRow * 32, m_playerCol * 32));
	m_playerSprite.setPosition(m_playerPosition);
}

void AwesomeSq::kick(worldSquare t_blockArray[MAX_ROWS][MAX_COL])
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		// KICKS A BLOCK LEFT ONE SPACE IF BLOCK HAS ROOM TO MOVE
		if (m_playerDirection == WEST && t_blockArray[m_playerRow - 1][m_playerCol].isAWall() == true)
		{
			if (t_blockArray[m_playerRow - 2][m_playerCol].isAWall() == false)
			{
				t_blockArray[m_playerRow - 1][m_playerCol].makeAFloor();
				if (t_blockArray[m_playerRow - 2][m_playerCol].isEmpty() == true)
				{
					t_blockArray[m_playerRow - 2][m_playerCol].makeAFloor();
				}
				else
				{
					t_blockArray[m_playerRow - 2][m_playerCol].makeAWall();
				}
			}
		}
		// KICKS A BLOCK RIGHT ONE SPACE IF BLOCK HAS ROOM TO MOVE
		else if (m_playerDirection == EAST && t_blockArray[m_playerRow + 1][m_playerCol].isAWall() == true)
		{
			if (t_blockArray[m_playerRow + 2][m_playerCol].isAWall() == false)
			{
				t_blockArray[m_playerRow + 1][m_playerCol].makeAFloor();
				if (t_blockArray[m_playerRow + 2][m_playerCol].isEmpty() == true)
				{
					t_blockArray[m_playerRow + 2][m_playerCol].makeAFloor();
				}
				else
				{
					t_blockArray[m_playerRow + 2][m_playerCol].makeAWall();
				}
			}
			
		}
		// KICKS A BLOCK DOWN ONE SPACE IF BLOCK HAS ROOM TO MOVE
		else if (m_playerDirection == SOUTH && t_blockArray[m_playerRow][m_playerCol + 1].isAWall() == true)
		{
			if (t_blockArray[m_playerRow][m_playerCol + 2].isAWall() == false)
			{
				t_blockArray[m_playerRow][m_playerCol + 1].makeAFloor();
				if (t_blockArray[m_playerRow][m_playerCol + 2].isEmpty() == true)
				{
					t_blockArray[m_playerRow][m_playerCol + 2].makeAFloor();
				}
				else
				{
					t_blockArray[m_playerRow][m_playerCol + 2].makeAWall();
				}
			}
		}
		// KICKS A BLOCK UP ONE SPACE IF BLOCK HAS ROOM TO MOVE
		else if (m_playerDirection == NORTH && t_blockArray[m_playerRow ][m_playerCol - 1].isAWall() == true)
		{
			if (t_blockArray[m_playerRow][m_playerCol - 2].isAWall() == false)
			{
				t_blockArray[m_playerRow][m_playerCol - 1].makeAFloor();
				if (t_blockArray[m_playerRow][m_playerCol - 2].isEmpty() == true)
				{
					t_blockArray[m_playerRow][m_playerCol - 2].makeAFloor();
				}
				else
				{
					t_blockArray[m_playerRow][m_playerCol - 2].makeAWall();
				}
			}
		}
	}
}

void AwesomeSq::animation()
{
	if (timer % 10 == 0)
	{
		playerX += SPRITE_WIDTH; // moves to the next frame of sprite sheet 6 times per second
	}

	if (timer >= MAX_TIMER)
	{
		timer = 0;// resets timer every second
	}

	if (playerX >= PLAYER_SPRITE_SHEET_WIDTH)
	{
		playerX = 0;// restarts animation if animation is finished
	}

	m_playerSprite.setTextureRect(sf::IntRect(playerX, playerY, 32, 32));
	//----------------------------------------------
	//----CHANGES VISIBLE DIRECTION THE PLAYER IS FACING--
	if (m_playerDirection == SOUTH)
	{
		playerY = 64;
	}
	if (m_playerDirection == NORTH)
	{
		playerY = 0;
	}
	if (m_playerDirection == WEST)
	{
		playerY = 32;
	}
	if (m_playerDirection == EAST)
	{
		playerY = 96;
	}
}

sf::Sprite AwesomeSq::getBody()
{
	return m_playerSprite;
}
