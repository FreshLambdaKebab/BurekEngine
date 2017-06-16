#include "Game.h"

Game::Game() :
	m_window(nullptr),
	m_screenWidth(800),
	m_screenHeight(600),
	m_gameState(GameState::PLAY)
{
}

Game::~Game()
{
}

void Game::Run()
{
	//init all systems
	Init();

	Update();
}

void Game::Init()
{
	//initialize sdl
	SDL_Init(SDL_INIT_EVERYTHING);

	//create an sdl window
	SDL_CreateWindow("The Douchebag Crackwhore Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_screenWidth,
		m_screenHeight, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

}

void Game::Update()
{
	//main/game loop
	while (m_gameState != GameState::EXIT)
	{
		ProcessInput();
	}
}

void Game::ProcessInput()
{
	SDL_Event windowEvent;

	while (SDL_PollEvent(&windowEvent))
	{
		switch (windowEvent.type)
		{
		case SDL_QUIT:
			m_gameState = GameState::EXIT;
			break;
		}

		//check if user has pressed escaped to exit window
		if (windowEvent.type == SDL_KEYDOWN && windowEvent.key.keysym.sym == SDLK_ESCAPE)
		{
			m_gameState = GameState::EXIT;
		}
	}
}
