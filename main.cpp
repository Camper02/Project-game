#pragma once
#include <SFML/Graphics.hpp>
#include <PLAYER.hpp>
#include <MAP.hpp>


using namespace sf;



int main()
{

	const int W = 40;

	int stayflag = 0;

	RenderWindow window(VideoMode(600, 400), "Test!");

	Texture t;
	t.loadFromFile("assets/SNINJA.png");
	
	Texture tileSet;
	tileSet.loadFromFile("assets/blocks.png");
	
	float currentFrame = 0;
	PLAYER b(tileSet);
	Sprite tile(tileSet);
	PLAYER p(t);



	Clock clock;

	//RectangleShape rectangle(Vector2f(32, 32));

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();

		time = time / 700;

		if (time > 20) time = 20;

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			p.dx = -0.1;
			stayflag = 1;
			p.f = true;
			p.direction = false;
		}
		if(Keyboard::isKeyPressed(Keyboard::Right))
		{
			p.dx = 0.1;
			stayflag = 1;
			p.f = true;
			p.direction = true;
		}

		if(Keyboard::isKeyPressed(Keyboard::Up))
		{
			if (p.onGround) { p.dy = -0.35; p.onGround = false; stayflag = 1;}
		}
		if (stayflag != 1)
		{
			p.f = false;
		}

		p.update(time);

		if (p.rect.left > 300 && p.rect.left < 980) offsetX = p.rect.left - 300;
		offsetY = p.rect.top - 200;

		window.clear(Color(107, 140, 255));


		for (int i = 0; i < H; i++)
			for (int j = 0; j < W; j++)
			{
				if (TileMap[i][j] == 'Z') tile.setTextureRect((IntRect(0, 0, 32, 32)));

				if (TileMap[i][j] == 'B') tile.setTextureRect((IntRect(0, 80, 32, 32))); //rectangle.setFillColor(Color::Red);

				if (TileMap[i][j] == '0') tile.setTextureRect((IntRect(240, 80, 32, 32))); //rectangle.setFillColor(Color::Green);

				//if (TileMap[i][j] == 'S') tile.setTextureRect((IntRect(0, 0, 40, 40))); //rectangle.setFillColor(Color::Blue);

				if (TileMap[i][j] == ' ') continue;

				tile.setPosition(j * 32 - offsetX, i * 32 - offsetY);
				window.draw(tile);
			}

		window.draw(p.sprite);
		window.display();
	}

	return 0;
}
