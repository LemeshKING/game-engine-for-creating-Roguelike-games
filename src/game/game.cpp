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
	Enemy enemy;
	enemy.Initialization(32, 0);
	sf::RectangleShape rectangle(sf::Vector2f(32, 32));


	window.setFramerateLimit(60);

	
	sf::Clock clock;
	int frames = 0;
	while (window.isOpen())
	{
		if(pl.isAlive())
		{
			sf::Time elapsedTime = clock.restart();
			if(pl.isImmunity())
				frames++;
			if(frames > 60)
			{
				pl.removeImmunity();
				frames = 0;
			}
			float time = clock.getElapsedTime().asMicroseconds();
			time /= 800;
			clock.restart();
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
	
			}
		
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				pl.setDx(1);
				pl.setDirection(1);
				if(pl.getCamera().getCenterX() >= (location.getWidth() - 15) * 32)
					pl.getCamera().setCenterX((location.getWidth() - 15) * 32);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				pl.setDx(1);
				pl.setDirection(-1);

			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				if (pl.isOnGround())
					pl.setDy(-0.75);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				window.close();
		
			for (int i = 0; i < location.getHeight(); i++)
				for (int j = pl.getCamera().getCenterX() / 32 - 15; j < pl.getCamera().getCenterX() / 32 + 17; j++)
				{
					if (location.TileMap[i][j] == 1)
						rectangle.setFillColor(sf::Color::Black);
					if (location.TileMap[i][j] == 0)
						rectangle.setFillColor(sf::Color::White);
					rectangle.setPosition(j * 32, i * 32);
					window.draw(rectangle);
				}
			pl.update(5,location.TileMap);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				window.draw(pl.getWeapon()->getRectangle());
			for (int i = 0; i < Enemys.size(); i++)
			{
				
				if(Enemys[i].getRect().left > pl.getCamera().getCenterX() - 512 && Enemys[i].getRect().left < pl.getCamera().getCenterX() + 576)
				{
					if (!pl.isImmunity())
						if(pl.getRect().intersects(Enemys[i].getRect()))
							pl.TakeDamage(Enemys[i].getDamageValue());
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
						if(pl.getWeapon()->getRect().intersects(Enemys[i].getRect()))
							std::cout << "Enemy Take Damage" << std::endl;
					Enemys[i].update(5,location.TileMap);
					window.draw(Enemys[i].getRectangle());
				}
			}
			weapon* Sword = pl.getWeapon();
			sf::RectangleShape tmp = Sword->getRectangle();

			//window.draw(pl.getWeapon()->getRectangle());
			
			window.draw(pl.getRectangle());
			window.display();
			window.setView(pl.getCamera().getView());
			window.clear(sf::Color::White);
		}
		else
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				window.close();
			window.display();
			window.setView(pl.getCamera().getView());
			window.clear(sf::Color::White);
		}
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
	hlth::Health health;
	health.setHealthPoints(100);
   location.setHeight(70);
   location.setWidth(250);
   location.setPersistence(3);
   location.setCountNoiseFunction(4);
   location.GenerateMap();
	sword Sword;

	pl.setCharacterHeight(50);
	pl.setCharacterWidth(40);
	pl.Initialization(0,location.getStartPlayerPosition() * 32);
	Sword.setRect(sf::FloatRect(pl.getRect().left + pl.getRect().width, pl.getRect().top,35,10));
	Sword.setRectangle(sf::RectangleShape(sf::Vector2f(35,10)));
	sf::RectangleShape tmp = Sword.getRectangle();
	tmp.setFillColor(sf::Color::Blue);
	tmp.setPosition(Sword.getRect().left, Sword.getRect().top);
	Sword.setRectangle(tmp);
	
	pl.setWeapon(&Sword);
	pl.setHealth(health);
	pl.getHealth().setHealthPoints(100);
	sf::RenderWindow window(sf::VideoMode(w, h), "Ray tracing", sf::Style::Fullscreen);
	Camera camera;
	sf::View view;
	
	camera.setView(view);

	camera.setWindowHeight(h);
	camera.setWindowWidth(w);
	camera.setViewMode(sf::Vector2u(w/2,h/2));
	camera.setCenterX(w / 4);
	camera.setCenterY(h / 4);
	Enemys.resize(30 + rand() % 50);
	for(int i = 0; i < Enemys.size(); i++)
	{
		int tmp = 30 + rand() % (location.getWidth() - 50 + 1);
		Enemys[i].setCharacterHeight(50);
		Enemys[i].setCharacterWidth(40);
		Enemys[i].setDamageValue(10);
		Enemys[i].Initialization(tmp * 32,(location.getHeight() - location.MapHeightValues[tmp] - 3) * 32);
	}

		
	
	pl.setCamera(camera);
	Run(window);

}
