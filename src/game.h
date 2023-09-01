#ifndef GAME_H
#define GAME_H

#include <Windows.h>
#include <glfw/glfw3.h>

class game
{
public:
	game();
	~game();

private:
	void init();
	void run();

	void update();
	void render();

	GLFWwindow* window;

	uint16_t screen_width;
	uint16_t screen_height;

};
#endif // GAME_H