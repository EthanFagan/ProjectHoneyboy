#pragma once
#include <SFML\Graphics.hpp>
#include "WorldSquare.h"
#include "Globals.h"

class AwesomeSq
{
	// private data members
	int m_playerRow = 1;		  //stores the row the awesomeSquare is in within 2D array
	int m_playerCol = 1;		  //stores the column the awesomeSquare is in within 2D array
	sf::Texture m_playerTexture;	   //texture for awesomeSquare player
	sf::Sprite m_playerSprite; 	   //sprite used to represent awesomeSquare player
	sf::Vector2f m_playerPosition;
	int m_score;		  //players score
	int m_lives;		  //contains players lives
	int m_playerDirection;	  //the direction the player is facing in
	

	// USED TO NAVIGATE SPRITE SHEET
	int playerX;
	int playerY;

	int timer = 0;

	// CONDITIONS
	bool m_isPlayerAlive;		  //is the player alive
	
public:
	AwesomeSq();
	void draw(sf::RenderWindow &t_window); //if alive draw the awesomeSquare using its row & column
	void setRow(int t_newRow);
	void setCol(int t_newCol);
	int getRow(); // returns the row position of the player
	int getcol(); // returns the column position of the player
	int getDirection();
	void update(worldSquare t_blockArray[MAX_ROWS][MAX_COL]);
	void setPosition(sf::Vector2f t_newPsoition);
	void move(worldSquare t_blockArray[MAX_ROWS][MAX_COL]); //moves the player via keyboard input– changes its row or column
	void kick(worldSquare t_blockArray[MAX_ROWS][MAX_COL]); //a function that checks if the player is trying to kick a square
	void animation();
	void die();//if lives 0 game over & call respawn function else take away 1 life
	void respawn(); //causes the player to reappear on the maze at starting position

};