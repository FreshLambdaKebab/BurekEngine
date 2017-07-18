#include "Game.h"
#include <string>
#include <iostream>

#include <burek\BurekEngine.h>
#include <burek\Debug.h>
//#include "ImageLoader.h"

Game::Game() :
	m_screenWidth(800),
	m_screenHeight(600),
	m_gameState(GameState::PLAY),
	m_time(0.0f),
	m_maxFPS(60.0f)
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
	burek::Initialize();

	//create window
	m_window.CreateWindow("The Douchebag Crackwhore Window", m_screenWidth, m_screenHeight, FULLSCREEN);
	
		
	//initialize sprite
	m_sprites.push_back(new Sprite());
	m_sprites.back()->Init(-1.0f, -1.0f, 1.0f, 1.0f, "res/textures/mario-sprite.png");

	m_sprites.push_back(new Sprite());
	m_sprites.back()->Init(0.0f, -1.0f, 1.0f, 1.0f, "res/textures/mario-sprite.png");



	//initialize and load shaders
	InitShaders();

	//load textures
	//m_texture = ImageLoader::LoadPNG();
}

void Game::InitShaders()
{
	//load the shaders
	m_colorShader.Compile("res/shaders/colorShader.vert", "res/shaders/colorShader.frag");
	//add attributes then link
	m_colorShader.AddAttribute("vertexPosition");
	m_colorShader.AddAttribute("vertexColor");
	m_colorShader.AddAttribute("vertexUV");
	m_colorShader.LinkShaders();
}

void Game::Update()
{
	//main/game loop
	while (m_gameState != GameState::EXIT)
	{
		//measure frame time
		float startTicks = SDL_GetTicks();

		ProcessInput();
		m_time += 0.01f;
		Draw();
		CalculateFPS();

		static int frameCount = 0;
		frameCount++;
		if (frameCount == 10)
		{
			std::cout << m_fps << std::endl;
			frameCount = 0;
		}

		float frameTicks = SDL_GetTicks() - startTicks;
		//limit fps to max
		if ((1000.0f / m_maxFPS) > frameTicks)
		{
			SDL_Delay((1000.0f / m_maxFPS) - frameTicks);
		}
	}
}

void Game::Draw()
{
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//begin the shader
	m_colorShader.Use();
	//set an active texture then bind it
	glActiveTexture(GL_TEXTURE0);
	GLint textureLocation = m_colorShader.GetUniformLocation("mySampler");
	glUniform1i(textureLocation, 0);


	//set uniforms
	//GLuint timeLocation = m_colorShader.GetUniformLocation("time");
	//glUniform1f(timeLocation, m_time);

	//draw shit
	for (size_t i= 0;i < m_sprites.size();i++)
	{
		m_sprites[i]->Draw();
	}

	//unbind teh texture
	glBindTexture(GL_TEXTURE_2D, 0);
	//end the shader
	m_colorShader.Unuse();

	m_window.SwapBuffers();
}

void Game::CalculateFPS()
{
	static const int NUM_SAMPLES = 10;
	static float frameTimes[NUM_SAMPLES];
	static int currentFrame = 0;

	static float prevTicks = SDL_GetTicks();
	float currentTicks = SDL_GetTicks();

	m_frameTime = currentTicks - prevTicks;
	frameTimes[currentFrame % NUM_SAMPLES] = m_frameTime;

	prevTicks = currentTicks;

	int count;

	currentFrame++;

	if (currentFrame < NUM_SAMPLES)
	{
		count = currentFrame;
	}
	else
	{
		count = NUM_SAMPLES;
	}

	float frameTimeAverage = 0;
	for (int i = 0; i < count; i++)
	{
		frameTimeAverage += frameTimes[i];
	}

	frameTimeAverage /= count;

	if (frameTimeAverage > 0)
	{
		m_fps = 1000.0f / frameTimeAverage;
	}
	else
	{
		m_fps = 60.0f;
	}

}

void Game::ProcessInput()
{
	SDL_Event windowEvent;

	//handle events
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
