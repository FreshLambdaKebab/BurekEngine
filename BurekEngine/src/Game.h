#ifndef _GAME_H
#define _GAME_H

#include <SDL\SDL.h>
#include <GL\glew.h>

#include "Sprite.h"
#include "Shader.h"

enum class GameState{PLAY,EXIT};

class Game
{
public:
	Game();
	~Game();

	void Run();

private:
	void Init();
	void InitShaders();
	void ProcessInput();
	void Update();//the main loop
	void Draw();

	SDL_Window* m_window;
	int m_screenWidth, m_screenHeight;
	GameState m_gameState;

	//game objects
	Sprite m_sprite;
	Shader m_colorShader;
};

#endif //_GAME_H