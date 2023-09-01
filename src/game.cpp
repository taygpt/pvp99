#include "game.h"
#include "globals/globals.h"

#include <lodepng.h>

#include <iostream>

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

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "failed to initialize GLAD" << std::endl;
		return;
	}

	rndrr::instance().init();
}

void game::run()
{
	last_frame_time = glfwGetTime();
	while (!glfwWindowShouldClose(window))
	{
		double current_frame_time = glfwGetTime();
		dt = current_frame_time - last_frame_time;
		last_frame_time = current_frame_time;
		update(dt);
		render();
	}
}

void game::update(float dt)
{
	rndrr::instance().update(dt);
	glfwPollEvents();
}

void game::render()
{
	rndrr::instance().draw();
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