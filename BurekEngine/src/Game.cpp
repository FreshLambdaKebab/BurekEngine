#include "Game.h"
#include <string>
#include <iostream>

#include "Debug.h"
//#include "ImageLoader.h"

Game::Game() :
	m_window(nullptr),
	m_screenWidth(800),
	m_screenHeight(600),
	m_gameState(GameState::PLAY),
	m_time(0.0f)
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
	m_window = SDL_CreateWindow("The Douchebag Crackwhore Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_screenWidth,
		m_screenHeight, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

	if (m_window == nullptr)
	{
		FatalError("SDL window could not be created");
	}

	SDL_GLContext glContext = SDL_GL_CreateContext(m_window);
	if (glContext == nullptr)
	{
		FatalError("SDL_GLContext could not be created");
	}

	//initialize glew
	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		FatalError("could not initialize glew");
	}

	//set sdl/ogl attributes
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	//set background color to desired color
	glClearColor(0.2f, 0.3f, 0.9f, 1.0f);

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
		ProcessInput();
		m_time += 0.01f;
		Draw();
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

	//swap buffers
	SDL_GL_SwapWindow(m_window);
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
