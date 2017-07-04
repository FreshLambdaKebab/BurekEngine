#ifndef _GAME_H
#define _GAME_H

#include <SDL\SDL.h>
#include <GL\glew.h>
#include <vector>

#include "Sprite.h"
#include "Shader.h"
#include "Texture.h"

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
	//Sprite m_sprite;
	std::vector<Sprite*>m_sprites;
	Shader m_colorShader;
	
	float m_time;
};

#endif //_GAME_H