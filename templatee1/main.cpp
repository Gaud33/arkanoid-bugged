#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;


int main() {
	sf::RenderWindow window(sf::VideoMode(600, 600), "My Window");

	
	sf::Texture obsTexture;

	if (!obsTexture.loadFromFile("white.png")) {
		cout << "Error opening obstacle file!" << endl;
	}

	sf::Texture blockTexture;

	if (!blockTexture.loadFromFile("green.png")) {
		cout << "Error opening block file!" << endl;
	}

	
	//Board
	sf::RectangleShape board(sf::Vector2f(150, 25));
	sf::RectangleShape leftCorner(sf::Vector2f(10, 25));
	sf::RectangleShape left(sf::Vector2f(55, 25));
	sf::RectangleShape Center(sf::Vector2f(20, 25));
	sf::RectangleShape right(sf::Vector2f(55, 25));
	sf::RectangleShape rightCorner(sf::Vector2f(10, 25));

	float Xpos = 450.0f, Ypos = 500.0f;
	board.setPosition(sf::Vector2f(Xpos, Ypos));


	//Bottom
	sf::RectangleShape bottom(sf::Vector2f(600, 5));
	bottom.setPosition(sf::Vector2f(0, 595));
	bottom.setFillColor(sf::Color::Red);
	
	
	//Blocks and obstacles
	sf::RectangleShape block[6][25];
	float blockPosX = 120.0f, blockPosY = 50.0f;

	for (int i = 0 ; i < 6; i++)
	 {
		for (int j = 0; j < 25; j++)
		{
			block[i][j].setPosition(sf::Vector2f(blockPosX, blockPosY));

			// 1st and 5th row blocks and 1st column blocks are obstacles
			if (i == 0 || j == 0 || i == 4) {
				
				block[i][j].setTexture(&obsTexture);
			}
				
				
			else
			{
			
				block[i][j].setTexture(&blockTexture);
			}
				

			block[i][j].setSize(sf::Vector2f(15.0f, 15.0f));
			
			

			blockPosX += 15.0f;
			

		}
		blockPosX = 120.0f;
		blockPosY += 15.0f;
	}
	
	//Ball
	sf::CircleShape ball(5.0f);
	ball.setPosition(sf::Vector2f(320, 320));
	ball.setFillColor(sf::Color::Green);


	//Ball Speed;
	float dt = 0.0f;
	sf::Vector2f ballSpeed;
	ballSpeed.x = 400.0f;
	ballSpeed.y = 400.0f;

	sf::Clock dtclock;

	//Game loop
	while (window.isOpen()) {
		sf::Event ev;
		
		dt = dtclock.restart().asSeconds();
		

		while (window.pollEvent(ev)) {

			switch (ev.type)
			{
			case sf::Event::Closed:
				window.close();

				break;
			}
			
		}

		//Board Movement
		if (sf::Mouse::getPosition(window).x > 0 && sf::Mouse::getPosition(window).x < 450)
			board.setPosition(sf::Vector2f(sf::Mouse::getPosition(window).x, Ypos));

		leftCorner.setPosition(sf::Vector2f(board.getPosition().x, board.getPosition().y));
		left.setPosition(sf::Vector2f(leftCorner.getPosition().x + 10, board.getPosition().y));
		Center.setPosition(sf::Vector2f(left.getPosition().x + 55, leftCorner.getPosition().y));
		right.setPosition(sf::Vector2f(Center.getPosition().x + 20 , board.getPosition().y));
		rightCorner.setPosition(sf::Vector2f(right.getPosition().x + 55, Center.getPosition().y));


		//Ball Movement
		if (ball.getPosition().x < 2)
			ballSpeed.x = -ballSpeed.x;

		else if (ball.getPosition().x > 588)
			ballSpeed.x = -ballSpeed.x;

		if (ball.getPosition().y < 2)
			ballSpeed.y = -ballSpeed.y;

		else if (ball.getPosition().y > 588)
			ballSpeed.y = -ballSpeed.y;


		//Ball and board Collision
		
		if (leftCorner.getGlobalBounds().intersects(ball.getGlobalBounds()))
		{
			ballSpeed.x = -400.0f;
			ballSpeed.y = -ballSpeed.y;
		}

		else if (left.getGlobalBounds().intersects(ball.getGlobalBounds()))
		{
			ballSpeed.x = -300.0f;
			ballSpeed.y = -(ballSpeed.y);
		}

		else if (Center.getGlobalBounds().intersects(ball.getGlobalBounds()))
		{
			if (ballSpeed.x == 0)
				ballSpeed.x = 0.0f;

			else if (ballSpeed.x > 0)
				ballSpeed.x = 100.0f;

			else 
				ballSpeed.x = -100.0f;
			
			ballSpeed.y = -600.0f;
			
		}

		else if (right.getGlobalBounds().intersects(ball.getGlobalBounds()))
		{
			ballSpeed.x = 300.0f;
			ballSpeed.y = -(ballSpeed.y);
		}

		else if (rightCorner.getGlobalBounds().intersects(ball.getGlobalBounds()))
		{
			ballSpeed.x = 400.0f;
			ballSpeed.y = -ballSpeed.y;
		}

		ball.move(dt* ballSpeed.x ,dt* ballSpeed.y);

		// Ball and blocks collision

		for (int i = 0; i < 6; i++)
		{
			for (int j = 0; j < 25; j++)
			{
				if (block[i][j].getGlobalBounds().intersects(ball.getGlobalBounds()))
				{
					//Remove the collided block except for obstacles
					if (i != 0 && j != 0 && i!= 4 )
						block[i][j].setPosition(sf::Vector2f(-100, 0));
					
					//Revert the ball's direction
					ballSpeed.y = -ballSpeed.y;
				}
			}
		}

		//Ball hits bottom
		if (bottom.getGlobalBounds().intersects(ball.getGlobalBounds()))
			window.close();


		//Draw 
		window.clear();

		for (int i = 0; i < 6; i++)
		{
			for (int j = 0; j < 25; j++)
			{
				window.draw(block[i][j]);
			}
		}
		window.draw(board);
		window.draw(leftCorner);
		window.draw(left);
		window.draw(Center);
		window.draw(right);
		window.draw(rightCorner);
		window.draw(ball);
		window.draw(bottom);

		window.display();
	}
}
