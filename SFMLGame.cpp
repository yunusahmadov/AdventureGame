#include <iostream>
#include <string>
#include <array>
#include <ctime>
#include <SFML/Graphics.hpp>

using namespace std;

enum class Cell
{
	Grass = 0, Wall = 1
};

int main()
{
	srand(time(0));

	sf::RenderWindow window(sf::VideoMode(1000, 1000), "My first game");

	sf::Texture donkey;
	donkey.loadFromFile("donkey2.jpg");

	sf::Texture grass;
	grass.loadFromFile("grass.jpg");

	sf::Texture wall;
	wall.loadFromFile("wall.jpg");

	sf::Texture beer;
	beer.loadFromFile("donkey.jpg");

	sf::RectangleShape grassRect(sf::Vector2f(100, 100));
	grassRect.setTexture(&grass);

	sf::RectangleShape wallRect(sf::Vector2f(100, 100));
	wallRect.setTexture(&wall);

	sf::RectangleShape beerRect(sf::Vector2f(100, 100));
	beerRect.setTexture(&beer);

	sf::RectangleShape player(sf::Vector2f(100, 100));
	player.setTexture(&donkey);
	/*player.setFillColor(sf::Color::Green);
	player.setOrigin(50, 50);*/

	array<array<int, 10>, 10> map =
	{
		1,1,1,1,1,1,1,1,1,1,
		1,0,0,1,0,0,0,0,0,1,
		1,0,0,1,0,0,0,0,0,1,
		1,0,0,1,1,1,1,0,0,1,
		1,0,0,0,0,0,1,0,0,1,
		1,0,1,1,0,0,0,0,0,1,
		1,0,1,0,0,0,1,0,0,1,
		1,0,1,0,0,0,1,0,0,1,
		1,0,1,0,0,0,1,0,0,1,
		1,1,1,1,1,1,1,1,1,1,
	};

	int playerX = 5, playerY = 5;
	int beerX = 4, beerY = 4;

	while (window.isOpen())
	{
		//EVENTS
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::KeyPressed)
			{
				switch (event.key.code)
				{
				case sf::Keyboard::W:
					cout << map[playerY - 1][playerX] << endl;
					if ((Cell)map[playerY - 1][playerX] != Cell::Wall)
						playerY--;
					break;
				case sf::Keyboard::S:
					cout << map[playerY + 1][playerX] << endl;
					if ((Cell)map[playerY + 1][playerX] != Cell::Wall)
						playerY++;
					break;
				case sf::Keyboard::A:
					cout << map[playerY][playerX - 1] << endl;
					if ((Cell)map[playerY][playerX - 1] != Cell::Wall)
						playerX--;
					break;
				case sf::Keyboard::D:
					cout << map[playerY][playerX + 1] << endl;
					if ((Cell)map[playerY][playerX + 1] != Cell::Wall)
						playerX++;
					break;
				}
				cout << playerX << " - " << playerY << endl;
			}
		}


		//LOGIC
		int direction = rand() % 4;
		if (direction == 0) beerX--;
		if (direction == 1) beerY--;
		if (direction == 2) beerX++;
		if (direction == 3) beerY++;


		//DRAWING
		window.clear(sf::Color::Black);
		for (int y = 0; y < 10; y++)
		{
			for (int x = 0; x < 10; x++)
			{
				if ((Cell)map[y][x] == Cell::Grass) // 0, 0
				{
					grassRect.setPosition(x * 100, y * 100);
					window.draw(grassRect);
				}
				else if ((Cell)map[y][x] == Cell::Wall) // 5, 6
				{
					wallRect.setPosition(x * 100, y * 100);
					window.draw(wallRect);
				}
			}
		}

		player.setPosition(playerX * 100, playerY * 100);
		window.draw(player);

		beerRect.setPosition(beerX * 100, beerY * 100);
		window.draw(beerRect);
		
		window.display();
	}

	return 0;
}