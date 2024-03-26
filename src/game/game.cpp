#include "game.h"


Game::Game()
{

}

void Game::Run(sf::RenderWindow &window)
{
	sf::View view;
	view.reset(sf::FloatRect(0, 0, 1920, 1080));
	int w = 1920;
	int h = 1080;
	int mouseX = w / 2 + 64;
	int mouseY = h / 2;
	srand(time(NULL));
	int seed = 1 + std::rand() % 1000;

	sf::RectangleShape rectangle(sf::Vector2f(32, 32));


	window.setFramerateLimit(60);

	
	sf::Clock clock;
	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		time /= 800;
		clock.restart();
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			pl.dx = 5;
			if(pl.camera.getCenterX() >= (location.getWidth() - 32) * 32)
				pl.camera.setCenterX((location.getWidth() - 32) * 32);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			pl.dx = -1;

		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			if (pl.onGround)
				pl.dy = -0.75;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			if (pl.camera.getCenterX() < (location.getWidth() - 32) * 32)
				pl.camera.setCenterX(pl.camera.getCenterX() + 64);
			pl.camera.setCenter();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			if (pl.camera.getCenterX() > 32 * 32)
				pl.camera.setCenterX(pl.camera.getCenterX() - 64);
			pl.camera.setCenter();

		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			mouseY -= 64;
			view.setCenter(mouseX, mouseY);

		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			mouseY += 64;
			view.setCenter(mouseX, mouseY);

		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			window.close();
		for (int i = 0; i < location.getHeight(); i++)
			for (int j = pl.camera.getCenterX() / 32 - 30; j < pl.camera.getCenterX() / 32 + 32; j++)
			{
				if (location.TileMap[i][j] == 1)
					rectangle.setFillColor(sf::Color::Black);
				if (location.TileMap[i][j] == 0)
					rectangle.setFillColor(sf::Color::White);
				rectangle.setPosition(j * 32, i * 32);
				window.draw(rectangle);
			}
		pl.update(5,location.TileMap);
		window.draw(pl.rectangle);
		window.display();
		window.setView(pl.camera.getView());
		window.clear(sf::Color::White);
	}
}

void Game::Pause()
{
}

void Game::Menu()
{
}

void Game::Initialization()
{
   location.setHeight(70);
   location.setWidth(100);
   location.setPersistence(5);
   location.setCountNoiseFunction(8);
   location.GenerateMap();
	pl.Initialization(10 * 32,0);
	sf::RenderWindow window(sf::VideoMode(w, h), "Ray tracing", sf::Style::Fullscreen);
	Camera camera;
	sf::View view;
	view.reset(sf::FloatRect(w/2,h/2,w,h));
	camera.setView(view);
	camera.setCenterX(w/2 + 64);
	camera.setCenterY(h/2);
	camera.setWindowHeight(h);
	camera.setWindowWidth(w);
	pl.camera = camera;
	Run(window);

}
