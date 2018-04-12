// Game class declaration
#pragma once

#include "SFML/Graphics.hpp" 
#include <iostream>
#include <cstdlib>  // include support for randomizing
#include <ctime>   // supports ctime function
#include <SFML\Graphics.hpp>

#include "AwesomeSq.h"   // include AwesomeSq header file
#include "EvilSq.h"   // include EvilSq header file
#include "WorldSquare.h"
#include "Globals.h"

enum class gameMode
{
	startScreen,
	level,
	gameOver
};

class Game
{
	// private data members
	// put your game objects here eg AwesomeSq object and 1D array of EvilSq objects etc.

	sf::RenderWindow window;
	

	worldSquare walls[MAX_ROWS][MAX_COL];

	AwesomeSq  player;

	EvilSq enemies[6];

public:
	sf::Font m_font;  // font for writing text
	sf::Text m_message[3];  // text to write on the screen

	sf::Sprite m_gravestone;
	sf::Texture m_gravestoneTex;

	int m_amountOfEnemiesLeft = 0;
	int m_currentLevel;
	int m_lives;

public:	  // declaration of member functions	
	Game();  // default constructor
	void	LoadContent();
	void	run();
	void	update();
	void	draw();
	void	setUpMaze();
	void    setUpLevel1();
	void    setUpLevel2();
	void    setUpLevel3();
	void    setUpEnemies();
	void	drawMaze();
	void    deaths();
	void    changeLevel(int t_newLevel);
	void    levelComplete();
	void    gameOver();
	void    countBees();
	void    drawEnemies(sf::RenderWindow &t_window);
};

