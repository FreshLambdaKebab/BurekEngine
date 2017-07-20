#ifndef _GAME_H
#define _GAME_H

#include <vector>

#include <burek\Window.h>
#include <burek\Sprite.h>
#include <burek\Shader.h>
#include <burek\Texture.h>
#include <burek\Camera2D.h>

using namespace burek;

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
	void CalculateFPS();

	Window m_window;
	int m_screenWidth, m_screenHeight;
	GameState m_gameState;

	//game objects
	std::vector<Sprite*>m_sprites;
	Shader m_colorShader;
	Camera2D m_camera;
	
	float m_fps;
	float m_frameTime;
	float m_maxFPS;
	float m_time;

};

#endif //_GAME_H
