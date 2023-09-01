#include "game.h"
#include "globals.h"

game::game() : window(nullptr), screen_width(800), screen_height(600)
{
	init();
	run();
}

void game::init()
{
	if (!glfwInit())
	{
		exit(-1);
	}

	window = glfwCreateWindow(screen_width, screen_height, g_name.c_str(), NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		exit(-1);
	}


	glfwSetWindowAttrib(window, GLFW_RESIZABLE, GLFW_FALSE);

	int32_t monitor_width, monitor_height;
	glfwGetMonitorWorkarea(glfwGetPrimaryMonitor(), NULL, NULL, &monitor_width, &monitor_height);
	int32_t window_width, window_height;
	glfwGetWindowSize(window, &window_width, &window_height);
	glfwSetWindowPos(window, (monitor_width - window_width) / 2, (monitor_height - window_height) / 2);
}

void game::run()
{
	while (!glfwWindowShouldClose(window))
	{
		update();
		render();
	}
}

void game::update()
{
	glfwPollEvents();
}

void game::render()
{
	glfwSwapBuffers(window);
}

game::~game()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}

int main()
{
	init_globals();
	game* g = new game();
	return 0;
}