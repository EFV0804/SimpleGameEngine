#include"Game.h"
#include"Actor.h"
#include"SpriteComponent.h"
#include"AnimSpriteComponent.h"
#include"BackgroundSpriteComponent.h"
#include"Timer.h"
#include"Assets.h"
#include"Astroid.h"


bool Game::initialize()
{
	bool isWindowInit = window.initialize();
	bool isRendererInit = renderer.initialize(window);

	return isWindowInit && isRendererInit;
}
void Game::loop()
{
	Timer timer;
	float dt = 0;
	while (isRunning)
	{
		float dt = timer.computeDeltaTime() / 1000.0f;
		processInput();
		update(dt);
		render();
		timer.delayTimer();
	}
}
void Game::close()
{
	renderer.close();
	window.close();
	SDL_Quit();
}
void Game::processInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			isRunning = false;
			break;
		}
	}
	//Keyboard state
	const Uint8* keyboardState = SDL_GetKeyboardState(nullptr);
	//Escape: quit game
	if (keyboardState[SDL_SCANCODE_ESCAPE])
	{
		isRunning = false;
	}
}
void Game::update(float dt)
{
	//Update Actors
	isUpdatingActors = true;
	for (auto actor : actors)
	{
		actor->update(dt);
	}
	isUpdatingActors = false;

	//move pending actors to actors
	for (auto pendingActors : pendingActors)
	{
		actors.emplace_back(pendingActors);
	}
	pendingActors.clear();

	//Delete dead actors
	vector<Actor*> deadActors;
	for (auto actor : actors)
	{
		if (actor->getState() == Actor::ActorState::Dead)
		{
			deadActors.emplace_back(actor);
		}
	}
}
void Game::render()
{
	renderer.beginDraw();
	renderer.draw();
	renderer.endDraw();
}
void Game::addActor(Actor* actor)
{
	if (isUpdatingActors)
	{
		pendingActors.emplace_back(actor);
	}
	else
	{
		actors.emplace_back(actor);
	}
}
void Game::removeActor(Actor* actor)
{
	auto iter = std::find(begin(pendingActors), end(pendingActors), actor);
	if (iter != end(pendingActors))
	{
		std::iter_swap(iter, end(pendingActors) - 1);
		pendingActors.pop_back();
	}
	iter = std::find(begin(actors), end(actors), actor);
	if (iter != end(actors))
	{
		std::iter_swap(iter, end(actors) - 1);
		actors.pop_back();
	}
}
void Game::load()
{

	Assets::loadTexture(renderer, "D:\\ARTFX\\3D3-Prog\\BLAISE_CAZALET_G\\SimpleGameEngine\\SimpleGameEngine\\Res\\Ship01.png", "ship01");
	Assets::loadTexture(renderer, "D:\\ARTFX\\3D3-Prog\\BLAISE_CAZALET_G\\SimpleGameEngine\\SimpleGameEngine\\Res\\Ship02.png", "ship02");
	Assets::loadTexture(renderer, "D:\\ARTFX\\3D3-Prog\\BLAISE_CAZALET_G\\SimpleGameEngine\\SimpleGameEngine\\Res\\Ship03.png", "ship03");
	Assets::loadTexture(renderer, "D:\\ARTFX\\3D3-Prog\\BLAISE_CAZALET_G\\SimpleGameEngine\\SimpleGameEngine\\Res\\Ship04.png", "ship04");
	Assets::loadTexture(renderer, "D:\\ARTFX\\3D3-Prog\\BLAISE_CAZALET_G\\SimpleGameEngine\\SimpleGameEngine\\Res\\Farback01.png", "Farback01");
	Assets::loadTexture(renderer, "D:\\ARTFX\\3D3-Prog\\BLAISE_CAZALET_G\\SimpleGameEngine\\SimpleGameEngine\\Res\\Farback02.png", "Farback02");
	Assets::loadTexture(renderer, "D:\\ARTFX\\3D3-Prog\\BLAISE_CAZALET_G\\SimpleGameEngine\\SimpleGameEngine\\Res\\Stars.png", "Stars");
	Assets::loadTexture(renderer, "D:\\ARTFX\\3D3-Prog\\BLAISE_CAZALET_G\\SimpleGameEngine\\SimpleGameEngine\\Res\\Astroid.png", "Astroid");

	const int astroidNumber = 20;
	for (int i = 0; i < astroidNumber; ++i)
	{
		new Astroid();
	}

	//auto actor = new Actor();
	//auto sprite = new SpriteComponent(actor, Assets::getTexture("ship01"));
	//actor->setPosition(Vector2{ 100,100 });

	vector<Texture*> animTextures{
		&Assets::getTexture("ship01"),
		&Assets::getTexture("ship02"),
		&Assets::getTexture("ship03"),
		&Assets::getTexture("ship04"),
	};
	Actor* ship = new Actor();
	AnimSpriteComponent* animatedSprite = new AnimSpriteComponent(ship, animTextures);
	ship->setPosition(Vector2{ 100,300 });

	//BACKGROUND
	//far bg
	vector<Texture*> bgTexsFar{
		&Assets::getTexture("Farback01"),
		&Assets::getTexture("Farback02")
	};
	Actor* bgFar = new Actor();
	BackgroundSpriteComponent* bgSpritesFar = new BackgroundSpriteComponent(bgFar, bgTexsFar);
	bgSpritesFar->setScrollSpeed(-100.0f);

	//create closer bg
	Actor* bgClose = new Actor();
	vector<Texture*> bgTexsClose{
		&Assets::getTexture("Stars"),
		&Assets::getTexture("Stars")
	};
	BackgroundSpriteComponent* bgSpritesClose = new BackgroundSpriteComponent(bgClose, bgTexsClose, 50);
	bgSpritesClose->setScrollSpeed(-200.0f);

}
void Game::unload()
{
	while (!actors.empty())
	{
		delete actors.back();
	}

	Assets::clear();
}