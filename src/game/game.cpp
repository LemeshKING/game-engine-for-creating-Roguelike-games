#include "game.h"


Game::Game()
{

}

void Game::TestingProceduralGeneration(sf::RenderWindow& window)
{	
	mp::Map location2;
	location2.setHeight(70);
	location2.setWidth(250);
	location2.setSeed(9928);
	location2.setPersistence(3);
	location2.setCountNoiseFunction(10);
	location2.GenerateMap();
	sf::Font font; 
	font.loadFromFile("../src/arial/ttt.otf");
	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(210);
	text.setFillColor(sf::Color::Black);
	text.setString("seed this location: " + std::to_string(location.getSeed()));
	text.setPosition(0,0);
	sf::Text text2;
	text2.setFont(font);
	text2.setCharacterSize(210);
	text2.setFillColor(sf::Color::Black);
	text2.setString("seed this location: " + std::to_string(location2.getSeed()));
	text2.setPosition(0,2200);
	for(int i = 0; i < location2.getHeight(); i++)
		for (int j = 0; j < location2.getWidth(); j++)
			location2.TileMap[i][j].setY(i * 32 + 70 * 32);
		
	sf::View view;
	view.reset(sf::FloatRect(0, 0, 8010, 4400));
	std::cout << location.getSeed() << std::endl;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			window.close();
	
		for(int i = 0; i < location.getHeight(); i++)
			for(int j = 0; j < location.getWidth(); j++)
				window.draw(location.TileMap[i][j].getSprite());
		for (int i = 0; i < location.getHeight(); i++)
			for (int j = 0; j < location.getWidth(); j++)
				window.draw(location2.TileMap[i][j].getSprite());
		window.draw(text);
		window.draw(text2);
		window.display();

		window.setView(view);
		
		window.clear(sf::Color::White);
	}
	
}

void Game::TestingPlayerMove(sf::RenderWindow& window)
{
	sf::Clock clock;
	sf::Clock clock2;
	sf::View view;
	view.reset(sf::FloatRect(0, 600, 960, 540));

	window.setView(view);
	clock.restart();
	while (window.isOpen())
	{	
		float time = clock.getElapsedTime().asSeconds();
		float timer = clock2.getElapsedTime().asMicroseconds();
		timer /= 2000;
		clock2.restart();
		
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

		}
		healthBar.setX(pl.getRect().left);
		healthBar.setY(pl.getRect().top);
		if (healthBar.getFullHealthBar().getSize().x > pl.getRect().left)
			healthBar.setX(healthBar.getFullHealthBar().getSize().x);
		else if (pl.getRect().left > (location.getWidth() - 17) * 32)
			healthBar.setX((location.getWidth() - 17) * 32);
		healthBar.update(pl.getHealth().getHealthPoints());
		pl.update(timer, location.TypeOfTiles);
		if(time < 3);
		else if(time < 5)
			pl.key["R"] = true;
		else if(time < 8)
		{
			pl.key["Up"] = true;
			pl.key["R"] = true;
		}
		else if(time < 10)
		{
			pl.key["Attack"] = true;
		}
		else if(time < 13)
		{
			pl.key["Attack"] = false;
			pl.key["Dash"] = true;
				
		}
		else if(time < 17)
			pl.key["L"] = true;
		else if(time < 20)
			clock.restart();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			window.close();

		for (int i = 0; i < location.getHeight(); i++)
			for (int j = 0; j < location.getWidth(); j++)
				window.draw(location.TileMap[i][j].getSprite());
		if(pl.key["Attack"] && pl.animation.getAnimation().getFrame() >= 2)
			window.draw(pl.getWeapon()->getSprite());
		window.draw(pl.animation.getAnimation().getSprite());
		window.draw(healthBar.getFullHealthBar());
		window.draw(healthBar.getCurrentHealthBar());
		window.draw(healthBar.getText());
		window.display();
		
		window.clear(sf::Color::White);
	}
}

void Game::TestingInterectionWithEnemy(sf::RenderWindow& window)
{
	sf::Clock clock2;
	sf::View view;
	view.reset(sf::FloatRect(0, 600, 960, 540));
	Enemy enemy;
	hlth::Health EnemyHealth;
	EnemyHealth.setHealthPoints(100);
	enemy.setHealth(EnemyHealth);
	enemy.setCharacterHeight(50);
	enemy.setCharacterWidth(40);
	enemy.Initialization(5 *32, 25 * 32);
	enemy.setDamageValue(10);
	window.setView(view);
	while (window.isOpen())
	{
		float timer = clock2.getElapsedTime().asMicroseconds();
		enemy.setPlayerPosition(pl.getRect());
		timer /= 2000;
		clock2.restart();

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			window.close();
		enemy.update(timer, location.TypeOfTiles);
		for (int i = 0; i < location.getHeight(); i++)
			for (int j = 0; j < location.getWidth(); j++)
				window.draw(location.TileMap[i][j].getSprite());
		if (pl.getRect().intersects(enemy.getRect()))
			pl.TakeDamage(enemy.getDamageValue());
		if (pl.key["Attack"] && pl.animation.getAnimation().getFrame() >= 2)
			window.draw(pl.getWeapon()->getSprite());
		window.draw(enemy.animation.getAnimation().getSprite());
		healthBar.setX(pl.getRect().left);
		healthBar.setY(pl.getRect().top);
		if (healthBar.getFullHealthBar().getSize().x > pl.getRect().left)
			healthBar.setX(healthBar.getFullHealthBar().getSize().x);
		else if (pl.getRect().left > (location.getWidth() - 17) * 32)
			healthBar.setX((location.getWidth() - 17) * 32);
		healthBar.update(pl.getHealth().getHealthPoints());
		window.draw(healthBar.getFullHealthBar());
		window.draw(healthBar.getCurrentHealthBar());
		window.draw(healthBar.getText());
		if(pl.isAlive())
		{
			pl.update(timer, location.TypeOfTiles);
			window.draw(pl.animation.getAnimation().getSprite());
		
		}
		else
		{
			enemy.SawPlayer(false);
			
		}

		
		window.display();

		window.clear(sf::Color::White);
	}
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
	bool isMouseButtonPresed = false;

	window.setFramerateLimit(144);
	int raisingWeaponsFrames = 0;

	sf::Clock clock;
	int AttackFrames = 0;
	int frames = 0;
	bool onceAttack = true;
	while (window.isOpen())
	{
		if(pl.isAlive())
		{
			if(frames > 144)
			{
				pl.removeImmunity();
				frames = 0;
			}
			float time = clock.getElapsedTime().asMicroseconds();
			time /= 1300;
			
			clock.restart();
;
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
				if(event.type == sf::Event::MouseButtonPressed)
					if (event.key.code == sf::Mouse::Left)
					{
						isMouseButtonPresed = true;
						pl.key["Attack"] = true;
					}
					
			}
			

			pl.satDown = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
			if(pl.canMove)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
				{
					pl.key["R"] = true;
					if(pl.getCamera().getCenterX() >= (location.getWidth() - 15) * 32)
						pl.getCamera().setCenterX((location.getWidth() - 15) * 32);

				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))	
					pl.key["L"] = true;
			
					
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
					pl.key["Up"] = true;
				
				if (pl.dashColdown > 77)
				{
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
						pl.key["Dash"] = true;

				}
				
			}



			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				window.close();
		
			for (int i = pl.getCamera().getCenterY() / 32 - 9; i < pl.getCamera().getCenterY() / 32 + 10; i++)
				for (int j = pl.getCamera().getCenterX() / 32 - 15; j < pl.getCamera().getCenterX() / 32 + 17; j++)
				{
					window.draw(location.TileMap[i][j].getSprite());
					if(location.TileMap[i][j].Object != nullptr)
					{
						if(pl.getRect().intersects(location.TileMap[i][j].Object->getSprite().getGlobalBounds()))
							location.TileMap[i][j].Object->PlayerInteraction(pl);
						window.draw(location.TileMap[i][j].Object->getSprite());
					}
					if(location.TileMap[i][j].Weapon != nullptr)
					{
						if (pl.getRect().intersects(location.TileMap[i][j].Weapon->getRect()))
							if(sf::Keyboard::isKeyPressed(sf::Keyboard::E) && raisingWeaponsFrames > 77)
							{
								weapon* tmp = pl.getWeapon();
								tmp->setRotation(45);
								location.TileMap[i][j].Weapon->setRotation(0);
								pl.setWeapon(location.TileMap[i][j].Weapon);
								location.TileMap[i][j].Weapon = tmp;
								raisingWeaponsFrames = 0;
							}	
						
					window.draw(location.TileMap[i][j].Weapon->getSprite());
					}
				}
			raisingWeaponsFrames++;
			pl.update(5,location.TypeOfTiles);
			healthBar.setX(pl.getRect().left);
			healthBar.setY(pl.getRect().top);
			if(healthBar.getFullHealthBar().getSize().x > pl.getRect().left)
				healthBar.setX(healthBar.getFullHealthBar().getSize().x);
			else if(pl.getRect().left > (location.getWidth() - 17) * 32)
				healthBar.setX((location.getWidth() - 17) * 32);
			healthBar.update(pl.getHealth().getHealthPoints());
			if(pl.animation.getAnimation().getFrame() >= 2 && pl.key["Attack"])
			{
				window.draw(pl.getWeapon()->getSprite());
				AttackFrames++;
			}
			
			for (int i = 0; i < Enemys.size(); i++)
			{
				if(Enemys[i]->isAlive())
				{
					if(Enemys[i]->getRect().left > pl.getCamera().getCenterX() - 512 && Enemys[i]->getRect().left < pl.getCamera().getCenterX() + 576)
					{
						Enemys[i]->setPlayerPosition(pl.getRect());
							if(pl.getRect().intersects(Enemys[i]->getRect()))
								pl.TakeDamage(Enemys[i]->getDamageValue());
						if (Enemys[i]->projectTile.isAlive())
						{
							Enemys[i]->projectTile.update(time);
							window.draw(Enemys[i]->projectTile.getSprite());
							if(pl.getRect().intersects(Enemys[i]->projectTile.getRect()))
									pl.TakeDamage(Enemys[i]->projectTile.damageValue);
						}
						if (pl.animation.getAnimation().getFrame() >= 2 && pl.key["Attack"] && !Enemys[i]->wasAttaking)
							if(pl.getWeapon()->getRect().intersects(Enemys[i]->getRect()))
							{
								Enemys[i]->TakeDamage(pl.getWeapon()->getDamageValue());
								Enemys[i]->wasAttaking = true;
							}
						Enemys[i]->update(time,location.TypeOfTiles);
						window.draw(Enemys[i]->animation.getAnimation().getSprite());

					}
				}
				else
				{
					delete Enemys[i];
					Enemys.erase(Enemys.begin() + i);
				}
			}
		
			if (pl.animation.getAnimation().getFrame() == 4 && pl.key["Attack"] == true)
			{
				AttackFrames = 0;
				onceAttack = true;
				isMouseButtonPresed = false;
				pl.key["Attack"] = false;
				pl.animation.setFrame(0);
				for(auto i : Enemys)
					i->wasAttaking = false;
			}


			window.draw(healthBar.getFullHealthBar());
			window.draw(healthBar.getCurrentHealthBar());
			window.draw(healthBar.getText());
			window.draw(pl.animation.getAnimation().getSprite());

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
	
	

	
	location.setSeed(9928);
   location.setHeight(70);
   location.setWidth(250);
   location.setPersistence(3);
   location.setCountNoiseFunction(10);
   location.GenerateMap();
	sword Sword;
	hlth::Health health(150);
	pl.setCharacterHeight(50);
	pl.setCharacterWidth(32);
	pl.Initialization(64,location.getStartPlayerPosition() * 32);
	Sword.setRect(sf::FloatRect(pl.getRect().left + pl.getRect().width, pl.getRect().top,35,10));
	Sword.setDamageValue(34);
	pl.setWeapon(&Sword);
	pl.setHealth(health);
	healthBar.Initialization(pl.getHealth().getMaxHealthPoints(), 0, location.getStartPlayerPosition() + 7);
	sf::RenderWindow window(sf::VideoMode(w, h), "My first Game", sf::Style::Fullscreen);
	Camera camera;
	sf::View view;
	
	camera.setView(view);

	camera.setWindowHeight(h);
	camera.setWindowWidth(w);
	camera.setViewMode(sf::Vector2u(w/2,h/2));
	camera.setCenterX(w / 4);
	camera.setCenterY(h / 4 + 32);
	Enemys = location.getEnemys();
	if(Enemys.size() > location.currentEnemy)
		Enemys.resize(location.currentEnemy);
	std::cout << location.tryRnd << std::endl;
	std::cout << location.countCaves << std::endl;

	pl.setCamera(camera);
	Run(window);
	//TestingProceduralGeneration(window);
	//TestingPlayerMove(window);
	//TestingInterectionWithEnemy(window);
}
