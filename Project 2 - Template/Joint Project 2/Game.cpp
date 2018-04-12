// Name: Ethan Fagan
// Login:C00232277
// Date: 05/03/2018
// Approximate time taken: 
//---------------------------------------------------------------------------
// Project description Template
// ---------------------------------------------------------------------------
// Known Bugs:
// List your bugs here

//////////////////////////////////////////////////////////// 
// Headers for SFML projects
// include correct library file for release and debug versions
// include iostream for console window output
// include 
//////////////////////////////////////////////////////////// 

#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 
#pragma comment(lib,"opengl32.lib") 
#pragma comment(lib,"glu32.lib") 

#include "Game.h"   // include Game header file


int main()
{
	Game aGame;
	aGame.LoadContent();
	aGame.run();

	return 0;
}

Game::Game() : window(sf::VideoMode(416, 416), "Project 2")
// Default constructor
{
}


void Game::LoadContent()
// load the font file & set up message
{
	//sets up font
	if (!m_font.loadFromFile("ASSETS/FONTS/BebasNeue.otf"))
	{
		std::cout << "error with font file file";
	}
	//-----Sets up gravestone for use in death animation
	if (!m_gravestoneTex.loadFromFile("ASSETS/IMAGES/Death Image.png"))
	{
		std::cout << "error with image file";
	}
	m_gravestone.setTexture(m_gravestoneTex);
	//------------------------------------------------------

	m_lives = 3;// sets the players total lives
	m_currentLevel = LEVEL_ONE;
	
	// set up the message string 
	for (int i = 0; i < 2; i++)
	{
		m_message[i].setFont(m_font);  // set the font for the text
		m_message[i].setCharacterSize(24); // set the text size
		m_message[i].setFillColor(sf::Color::Yellow); // set the text colour
		m_message[i].setOutlineColor(sf::Color(255, 84, 0));
		m_message[i].setOutlineThickness(4);
	}
	m_message[0].setPosition(150, 0);  // its position on the screen
	m_message[1].setPosition(125, 385);
	m_message[2].setPosition(150, 160);
	m_message[2].setCharacterSize(20);
	m_message[2].setFillColor(sf::Color::Red);
	m_message[2].setOutlineColor(sf::Color(255, 84, 0));
	m_message[2].setOutlineThickness(4);
}


void Game::run()
{
	srand(time(nullptr)); // set the seed once
	sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	// the clock object keeps the time.
	sf::Clock clock;


	clock.restart();
	setUpMaze();
	setUpEnemies();
	
	m_message[0].setString("H O N E Y B O Y");
	m_message[1].setString("Remaining enemies : " + std::to_string(m_amountOfEnemiesLeft));

	while (window.isOpen())
	{
		// check if the close window button is clicked on
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		//get the time since last update and restart the clock
		timeSinceLastUpdate += clock.restart();

		//update every 60th of a second
		//only when the time since last update is greater than 1/60 update the world.
		if (timeSinceLastUpdate > timePerFrame)
		{

			update();
			draw();

			// reset the timeSinceLastUpdate to 0 
			timeSinceLastUpdate = sf::Time::Zero;
		}
	}  // end while loop

}



void Game::update()
// This function takes the keyboard input and updates the game world
{
	// update any game variables here ...
	for (int row = 0; row < MAX_ROWS; row++)
	{
		for (int col = 0; col < MAX_COL; col++)
		{
			walls[row][col].update();// updates each wall on screen
		}
	}
	for (int i = 0; i < MAX_ENEMIES; i++)
	{
		enemies[i].update(walls);// updates the enemies on screen
	}
	player.update(walls);// updates the player
	deaths();
	m_message[1].setString("Remaining enemies : " + std::to_string(m_amountOfEnemiesLeft));
	

}

void Game::draw()
// This function draws the game world
{
	// Clear the screen and draw your game sprites
	window.clear();
	if (m_currentLevel != GAME_OVER)
	{
		drawMaze();
		drawEnemies(window);

		window.draw(m_message[0]);  // write message to the screen
		window.draw(m_message[1]);
		player.draw(window);
		player.setPosition(sf::Vector2f(200, 200));
	}
	
	player.setPosition(sf::Vector2f(200, 200));
	window.display();
}

void Game::setUpMaze()
{
	//----SETS UP MAZE------------------------------
	if (m_currentLevel == LEVEL_ONE)
	{
		setUpLevel1();
	}
	else if (m_currentLevel == LEVEL_TWO)
	{
		setUpLevel2();
	}
	else if (m_currentLevel == LEVEL_THREE)
	{
		setUpLevel3();
	}
	for (int row = 0; row < MAX_ROWS; row++)
	{
		for (int col = 0; col < MAX_COL; col++)
		{
			walls[row][col].setPosition(sf::Vector2f(32 * row, 32 * col));
		}

	}
}

void Game::setUpLevel1()
{
	for (int row = 0; row < MAX_ROWS; row++)
	{
		for (int col = 0; col < MAX_COL; col++)
		{
			//----SETS UP BOUNDARY--------------------------
			if (row == 0 || row == MAX_ROWS - 1)
			{
				walls[row][col].makeAWall();
			}
			else if (col == 0 || col == MAX_COL - 1)
			{
				walls[row][col].makeAWall();
			}
			else if (col == 5 && row == 6)
			{
				walls[row][col].makeEmpty();
			}
			else if (col == 1 && row == 9)
			{
				walls[row][col].makeAWall();
			}
			else if (col == 2 && row > 0 && row < 6)
			{
				walls[row][col].makeAWall();
			}
			else if (col == 2 && row > 6 && row < MAX_ROWS)
			{
				walls[row][col].makeAWall();
			}
			else if (col == 4 && row > 4 && row < 8)
			{
				walls[row][col].makeAWall();
			}
			else if (row == 8 && col > 4 && col < 10)
			{
				walls[row][col].makeAWall();
			}
			else if (row == 4 && col > 4 && col < 10)
			{
				walls[row][col].makeAWall();
			}
			else if (row == 10 && col == 11 || row == 2 && col == 11)
			{
				walls[row][col].makeAWall();
			}
			else
			{
				walls[row][col].makeAFloor();
			}
		}
	}
}

void Game::setUpLevel2()
{
	for (int row = 0; row < MAX_ROWS; row++)
	{
		for (int col = 0; col < MAX_COL; col++)
		{
			//----SETS UP BOUNDARY--------------------------
			if (row == 0 || row == MAX_ROWS - 1)
			{
				walls[row][col].makeAWall();
			}
			else if (col == 0 || col == MAX_COL - 1)
			{
				walls[row][col].makeAWall();
			}
			else
			{
				walls[row][col].makeAFloor();
			}
		}
	}
}

void Game::setUpLevel3()
{
	for (int row = 0; row < MAX_ROWS; row++)
	{
		for (int col = 0; col < MAX_COL; col++)
		{
			//----SETS UP BOUNDARY--------------------------
			if (row == 0 || row == MAX_ROWS - 1)
			{
				walls[row][col].makeAWall();
			}
			else if (col == 0 || col == MAX_COL - 1)
			{
				walls[row][col].makeAWall();
			}
			else
			{
				walls[row][col].makeAFloor();
			}
		}
	}

}

void Game::setUpEnemies()
{
	for (int i = 0; i < MAX_ENEMIES; i++)
	{
			if (i == 0)
			{
				enemies[i].setCol(6);
				enemies[i].setRow(3);
				enemies[i].setDirection(SOUTH);
				enemies[i].setIsAlive();
				m_amountOfEnemiesLeft++;
			}
			if (i == 1)
			{
				enemies[i].setCol(1);
				enemies[i].setRow(11);
				enemies[i].setDirection(WEST);
				enemies[i].setIsAlive();
				m_amountOfEnemiesLeft++;
			}
			if (i == 2)
			{
				enemies[i].setCol(3);
				enemies[i].setRow(4);
				enemies[i].setDirection(EAST);
				enemies[i].setIsAlive();
				m_amountOfEnemiesLeft++;
			}
			if (i == 3)
			{
				enemies[i].setCol(11);
				enemies[i].setRow(6);
				enemies[i].setDirection(WEST);
				enemies[i].setIsAlive();
				m_amountOfEnemiesLeft++;
			}
			if (i == 4)
			{
				enemies[i].setCol(6);
				enemies[i].setRow(9);
				enemies[i].setDirection(EAST);
				enemies[i].setIsAlive();
				m_amountOfEnemiesLeft++;
			}
			if (i == 5)
			{
				enemies[i].setCol(11);
				enemies[i].setRow(4);
				enemies[i].setDirection(SOUTH);
				enemies[i].setIsAlive();
				m_amountOfEnemiesLeft++;
			}
	}
}

void Game::drawMaze()
{
	for (int row = 0; row < MAX_ROWS; row++)
	{
		for (int col = 0; col < MAX_COL; col++)
		{
			walls[row][col].draw(window);
		}
	}
}

void Game::deaths()
{
	for (int i = 0; i < MAX_ENEMIES; i++)
	{
		if ((player.getRow() == enemies[i].getRow()) && (player.getcol() == enemies[i].getCol()) && enemies[i].getIsAlive() == true)
		{
			m_amountOfEnemiesLeft = 0;
			m_currentLevel = LEVEL_TWO;
			setUpEnemies();
			setUpMaze();
			player.setRow(1);
			player.setCol(1);
		}
		if (walls[enemies[i].getRow()][enemies[i].getCol()].isAWall() == true)
		{
			if (enemies[i].getIsAlive() == true)
			{
				m_amountOfEnemiesLeft--;
				enemies[i].die();
			}
		}
	}
}

void Game::changeLevel(int t_newLevel)
{
	m_currentLevel = t_newLevel;
}

void Game::levelComplete()
{
}

void Game::gameOver()
{
}

void Game::countBees()
{
	for (int i = 0; i < MAX_ENEMIES; i++)
	{
		m_amountOfEnemiesLeft = 0;
		if (enemies[i].getIsAlive() == true)
		{
			m_amountOfEnemiesLeft++;
		}
	}
}

void Game::drawEnemies(sf::RenderWindow &t_window)
{
	for (int i = 0; i < MAX_ENEMIES; i++)
	{
		if (enemies[i].getIsAlive() == true)
		{
			enemies[i].draw(t_window);
		}
	}
}
