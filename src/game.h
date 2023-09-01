#ifndef GAME_H
#define GAME_H

#include <Windows.h>
#include <glfw/glfw3.h>

#include "gfx/renderer/rndrr.h"

class game
{
public:
	game();
	~game();

private:
	void init();
	void run();

	void update(float dt);
	void render();

	GLFWwindow* window;

	uint16_t screen_width;
	uint16_t screen_height;

	double last_frame_time;
	float dt;
};
#endif // GAME_H