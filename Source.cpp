/*Youssef Helal
900142332
Assignment 6
SFML
Cat and Mouse game using SFML*/

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include <stdlib.h>
using namespace std;
float const x = 35;
float const y = 35;
int const cols = 10;
int const rows = 10;
void drawIsland(sf::RectangleShape[][cols], int);
void drawBridge(sf::RectangleShape &);
void drawCats(sf::RectangleShape I[][cols],sf::Texture &, sf::Sprite&, sf::Sprite&, sf::Sprite&, sf::Sprite&);
void Catmovement(sf::RectangleShape I[][cols], sf::Sprite &, sf::Sprite &, sf::Sprite &, sf::Sprite &);
void drawMouse(sf::RectangleShape I[][cols], sf::Texture &, sf::Sprite &);
void main()
{
	int count = 100;
	bool pause = false;
	srand(time(NULL));
	sf::RenderWindow win;                                         //window
	win.create(sf::VideoMode(1024, 748), "Cat and Mouse Game");   //window size and name

	win.setMouseCursorVisible(false); //Hide mouse cursor


	sf::RectangleShape I[rows][cols];            //rectangle with 8x8 tiles to represent the island                   
	drawIsland(I,rows);                            //call function to set the size, position and color of the island

	sf::RectangleShape bridge;                     //bridge
	drawBridge(bridge);

	sf::Texture cat;                                   // making cat sprites
	sf::Sprite S_cat1;
	sf::Sprite S_cat2;
	sf::Sprite S_cat3;
	sf::Sprite S_cat4;
	drawCats(I,cat,S_cat1,S_cat2,S_cat3,S_cat4);
	
	sf::Texture mouse;            //making mouse sprite
	sf::Sprite mouse1;
	drawMouse(I, mouse, mouse1); 
	
	
	
	sf::Font MyFont;
	if (!MyFont.loadFromFile("font.ttf"))
		cout << "Error";

	sf::Text instructions("Choose your difficulty by pressing 1 for Easy, 2 for Medium or 3 for Hard (You can change it mid game). Use the Arrow Keys to move, P to pause, R to Resume and ESC to close the game",MyFont ); //instructions at the top
	instructions.setCharacterSize(15);

	
	sf::String m("Tries Left" + count);

	sf::Text PauseMessage("To Start the game press Space", MyFont);
	PauseMessage.setPosition(380, 360);

	sf::Text Lose1("You were killed by a cat", MyFont);
	Lose1.setPosition(380, 330);
	sf::Text Lose2("You have starved to death" , MyFont);
	Lose2.setPosition(380, 330);
	sf::Text Lose3("You have drowned", MyFont);
	Lose3.setPosition(380, 330);


	sf::Text Win("You have won!", MyFont);
	Win.setPosition(380, 330);

	

	sf::Music music;
	if (!music.openFromFile("music.ogg")) 
	{
		cout << "Error loading music";
	}

	
	music.play();            //music
	music.setVolume(10);   // music volume control
	music.setLoop(true);
	bool won;
	bool loss1;
	bool loss2;
	bool loss3;
	bool isRunning = false;
	sf::Clock c;
	int difficulty;
	while (win.isOpen())            //Game loop
	{
	
		sf::Event myevent;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
			difficulty = 800;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
			difficulty = 600;                                           //choose your speed. Pressing two gives the speed required in the assignment. Difficulty can change in game.
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
			difficulty = 200;

		if (pause == false && c.getElapsedTime().asMilliseconds() %difficulty==0)
			Catmovement(I, S_cat1, S_cat2, S_cat3, S_cat4);

		while (win.pollEvent(myevent))   //event handling
		{


			if (myevent.type == sf::Event::Closed)         //close game if x is clicked
				win.close();

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))           //close game if ESC keys is pressed
				win.close();

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))          //Press space to start game and to restart too (resets everything)
			{
				if (!isRunning)                                                 
				{
					isRunning = true;
					drawCats(I, cat, S_cat1, S_cat2, S_cat3, S_cat4);
					drawMouse(I, mouse, mouse1);
					count = 100;
					won = false;
					loss1 = false;
					loss2 = false;
					loss3 = false;
				}
			}

			if (isRunning)
			{
				

				
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) //pause game
				{

					pause = true;

				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) //resume game
				{

					pause = false;

				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && pause == false)                //movement for mouse using arrow keys
				{
					mouse1.move(35, 0);
					count--;
					
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && pause == false)
				{
					mouse1.move(-35, 0);
					count--;

				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && pause == false)
				{
					mouse1.move(0, -35);
					count--;

				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && pause == false)
				{

					mouse1.move(0, 35);
					count--;

				}

				if (mouse1.getGlobalBounds().intersects(S_cat1.getGlobalBounds()))             //checks collision with each cat
				{
					
					isRunning = false;                                                  //stops game
					loss1=true;                                                           //to show loss message
				}
				if (mouse1.getGlobalBounds().intersects(S_cat2.getGlobalBounds()))
				{
					
					isRunning = false;
					loss1 = true;
				}
				if (mouse1.getGlobalBounds().intersects(S_cat3.getGlobalBounds()))
				{
					
					
					isRunning = false;
					loss1 = true;
				}
				if (mouse1.getGlobalBounds().intersects(S_cat4.getGlobalBounds()))
				{
					
					
					isRunning = false;
					loss1 = true;
				}

				if (mouse1.getGlobalBounds().contains(bridge.getPosition()))             //checks to see if bridge is reached
				{
					isRunning = false;
					won = true;                                                        //To show win message
				}
				if (count == 0)                                                      //checks number of movements
				{
					isRunning = false;
					loss2 = true;         //starved message
				}
				if (mouse1.getPosition().x <= 35 || mouse1.getPosition().x >= 350 || mouse1.getPosition().y <= 35 || mouse1.getPosition().y >= 350) //checks if mouse goes in water
				{
					isRunning = false;
					loss3 = true;     //drowned message
				}
				
				
				
			}

			
		}
		
		win.clear(sf::Color::Blue);       //blue background
		if (isRunning)                              //while game is running
		{

			for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++)
			{

				win.draw(I[i][j]);
			}
			sf::Text S(m, MyFont);
			S.setPosition(0, 0);
			S.setCharacterSize(10);
			win.draw(bridge);
			win.draw(instructions);
			win.draw(S_cat1);
			win.draw(S_cat2);
			win.draw(S_cat3);
			win.draw(S_cat4);
			win.draw(mouse1);
			
			
		}
		else                                 //while game not running
		{ 
			win.draw(PauseMessage);
			if (loss1 == true)
				win.draw(Lose1);
			else if (won == true)
				win.draw(Win);
			else if (loss2 == true)
				win.draw(Lose2);
			else if (loss3 == true)
				win.draw(Lose3);
		}
		win.display();
	}

	
	
}

void drawIsland(sf::RectangleShape I[][cols] ,int rows)      //function to draw island
{
	
	for (int i = 0; i < rows; i++)
	for (int j = 0; j < cols; j++)
	{
		I[i][j].setSize(sf::Vector2f(x, y));
		I[i][j].setPosition((i*x + 5.0f) + 30, (j*y + 5.0f) + 30);    //position of each tile - the 30 acts to centre the whole island
		I[i][j].setFillColor(sf::Color::Yellow);
		//I[i][j].setOutlineColor(sf::Color::Red);                //testing to see if tiles exist and to help with positioning and movement
		//I[i][j].setOutlineThickness(1);
	}

	for (int i = 0; i < rows; i++)
	for (int j = 0; j < cols; j++)
	{

		I[0][j].setFillColor(sf::Color::Blue);        //water
		I[9][j].setFillColor(sf::Color::Blue);
		I[i][0].setFillColor(sf::Color::Blue);
		I[i][9].setFillColor(sf::Color::Blue);
	}
}
void drawBridge(sf::RectangleShape &bridge)
{
	bridge.setSize(sf::Vector2f(500, 30));          //size of bridge
	bridge.setPosition(350, 213);                   //position of bridge
	bridge.setFillColor(sf::Color::Red);            //color of bridge

}

void drawCats(sf::RectangleShape I[][cols],sf::Texture &cat, sf::Sprite &S_cat1, sf::Sprite &S_cat2, sf::Sprite &S_cat3, sf::Sprite &S_cat4)     //function to make all 4 cats
{
	sf::Vector2f p1 = I[5][2].getPosition();       //starting position of cats
	sf::Vector2f p2 = I[5][3].getPosition();
	sf::Vector2f p3 = I[5][4].getPosition();
	sf::Vector2f p4 = I[5][5].getPosition();
	
	if (!cat.loadFromFile("Cat1.png"))
	{
		cout << "Error cat image not loaded";
	}
	S_cat1.setTexture(cat);   
	S_cat1.setScale(sf::Vector2f(0.38f, 0.38f));
	S_cat1.setPosition(p1);

	S_cat2.setTexture(cat);
	S_cat2.setScale(sf::Vector2f(0.38f, 0.38f));              //same texture and size, different position
	S_cat2.setPosition(p2);

	S_cat3.setTexture(cat);
	S_cat3.setScale(sf::Vector2f(0.38f, 0.38f));
	S_cat3.setPosition(p3);

	S_cat4.setTexture(cat);
	S_cat4.setScale(sf::Vector2f(0.38f, 0.38f));
	S_cat4.setPosition(p4);
}

void drawMouse(sf::RectangleShape I[][cols],sf::Texture &mouse, sf::Sprite &mouse1)
{
	sf::Vector2f p1 = I[1][4].getPosition();       //starting position of mouse
	if (!mouse.loadFromFile("Mouse1.png"))
	{
		cout << "Error mouse image not loaded";
	}
	mouse1.setTexture(mouse);                      //mouse sprite
	mouse1.setScale(sf::Vector2f(0.8f, 0.8f));
	mouse1.setPosition(I[1][4].getPosition());
}

void Catmovement(sf::RectangleShape I[][cols], sf::Sprite &S_cat1, sf::Sprite &S_cat2, sf::Sprite &S_cat3, sf::Sprite &S_cat4)
{
	int d1, d2, d3, d4;

		d1 = rand() % 4;              //random movement
		if (d1 == 0)
			S_cat1.move(0, -35);   

		if (d1 == 1)
			S_cat1.move(35, 0);
		if (d1 == 2)
			S_cat1.move(0, 35);
		if (d1 == 3)
			S_cat1.move(-35, 0);



		if (S_cat1.getPosition().x <= 35)  //stops cat from going in water
		{
			S_cat1.move(35, 0);
		}

		if (S_cat1.getPosition().x >= 350)
		{
			S_cat1.move(-35, 0);
		}
		if (S_cat1.getPosition().y <= 35)
		{
			S_cat1.move(0, 35);
		}
		if (S_cat1.getPosition().y >= 350)
		{
			S_cat1.move(0, -35);
		}



		d2 = rand() % 4;
		if (d2 == 0)
			S_cat2.move(0, -35);
		if (d2 == 1)
			S_cat2.move(35, 0);
		if (d2 == 2)
			S_cat2.move(0, 35);
		if (d2 == 3)
			S_cat2.move(-35, 0);


		if (S_cat2.getPosition().x <= 35)
		{
			S_cat2.move(35, 0);
		}

		if (S_cat2.getPosition().x >= 350)
		{
			S_cat2.move(-35, 0);
		}
		if (S_cat2.getPosition().y <= 35)
		{
			S_cat2.move(0, 35);
		}
		if (S_cat2.getPosition().y >= 350)
		{
			S_cat2.move(0, -35);
		}



		d3 = rand() % 4;
		if (d3 == 0)
			S_cat3.move(0, -35);
		if (d3 == 1)
			S_cat3.move(35, 0);
		if (d3 == 2)
			S_cat3.move(0, 35);
		if (d3 == 3)
			S_cat3.move(-35, 0);


		if (S_cat3.getPosition().x <= 35)
		{
			S_cat3.move(35, 0);
		}

		if (S_cat3.getPosition().x >= 350)
		{
			S_cat3.move(-35, 0);
		}
		if (S_cat3.getPosition().y <= 35)
		{
			S_cat3.move(0, 35);
		}
		if (S_cat3.getPosition().y >= 350)
		{
			S_cat3.move(0, -35);
		}




		d4 = rand() % 4;
		if (d4 == 0)
			S_cat4.move(0, -35);
		if (d4 == 1)
			S_cat4.move(35, 0);
		if (d4 == 2)
			S_cat4.move(0, 35);
		if (d4 == 3)
			S_cat4.move(-35, 0);


		if (S_cat4.getPosition().x <= 35)
		{
			S_cat4.move(35, 0);
		}

		if (S_cat4.getPosition().x >= 350)
		{
			S_cat4.move(-35, 0);
		}
		if (S_cat4.getPosition().y <= 35)
		{
			S_cat4.move(0, 35);
		}
		if (S_cat4.getPosition().y >= 350)
		{
			S_cat4.move(0, -35);
		}

	}

