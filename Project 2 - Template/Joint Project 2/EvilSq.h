#pragma once
#include <SFML\Graphics.hpp>
#include "Globals.h"
#include "WorldSquare.h"

class EvilSq
{
	// private data members
	int m_enemyRow = 1; //stores the row of the enemy within 2D array
	int m_enemyCol = 1; //stores the column of the enemy within 2D array
	sf::Texture m_enemyTexture; //texture for enemy
	sf::Sprite m_enemySprite; //sprite used to represent enemy
	sf::Vector2f m_enemyPosition = sf::Vector2f(-500, -500); // curreny position of the enemy
	int m_enemyDirection; //the direction the enemy is facing
	
	int enemyX = 0;// for use in animations
	int enemyY = 0;// for use in animations

	int timer = 0; // timer that controls movement and animation

	//CONDITIONS
	bool m_isEnemyAlive = false; //checks if the enemy is alive
	bool m_enemyFacingDown;
	bool m_enemyFacingLeft;
	bool m_enemyFacingRight;
	bool m_enemyFacingUp;

public:
	EvilSq();
	void update(worldSquare t_blockArray[MAX_ROWS][MAX_COL]);
	void draw(sf::RenderWindow &t_window); //if alive draw the evil square
	void setPosition(sf::Vector2f t_newPos);// allows the enemys position to be changed
	void setDirection(int t_newDirection);
	int getRow(); // returns the enemys row position
	void setRow(int t_newRow);
	int getCol(); // returns the enemy column position
	void setCol(int t_newCol);
	bool getIsAlive();
	void setIsAlive();
	void changeDirection(worldSquare t_blockArray[MAX_ROWS][MAX_COL]); //moves the evil square in the direction it is facing until it reaches a worldSquare or boundary, then change direction.Boundary checking can be done in the move function.
	void move();
	void die(worldSquare t_blockArray[MAX_ROWS][MAX_COL]); //if the enemy is hit by a worldSquare pushed by the player, the enemy will die.
	void animation();
	void respawn(); //causes the enemy to reappear on the maze at starting position


};
