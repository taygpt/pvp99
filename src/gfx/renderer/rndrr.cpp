#include "rndrr.h"

#include <iostream>


rndrr::rndrr()
{
	//set clear_color to muted light blue

	clear_color[0] = 0.03f;
	clear_color[1] = 0.04f;
	clear_color[2] = 0.1f;
	clear_color[3] = 1.0f;
}

void rndrr::init()
{

	const char* vertex_shader_source = R"(
		#version 330 core
		layout (location = 0) in vec3 aPos;
		void main()
		{
			gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
		}
	)";

	const char* fragment_shader_source = R"(
		#version 330 core
		out vec4 FragColor;

		uniform vec4 time_color;
		void main()
		{
			FragColor = time_color;
		}
	)";

	vertex_shader = compile_shader(GL_VERTEX_SHADER, vertex_shader_source);
	fragment_shader = compile_shader(GL_FRAGMENT_SHADER, fragment_shader_source);

	link_program();

	GLfloat vertices[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//unbind buffers
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glClearColor(clear_color[0], clear_color[1], clear_color[2], clear_color[3]);

}

void rndrr::update(float dt)
{
	offset += dt;
	glUseProgram(shader_program);

	// update the uniform color
	
	//decide the color based off some sin wave fluctuation and dt

	float red_value = (sin(offset) + 1.0f) / 2.0f;
	float green_value = (sin(offset + 2.0f) + 1.0f) / 2.0f;
	float blue_value = (sin(offset + 4.0f) + 1.0f) / 2.0f;


	int vertex_color_location = glGetUniformLocation(shader_program, "time_color");
	glUniform4f(vertex_color_location, red_value, green_value, blue_value, 1.0f);

	glUseProgram(0);
}

GLuint rndrr::compile_shader(GLenum type, const char* source)
{
	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);
	return shader;
}

void rndrr::link_program()
{
	shader_program = glCreateProgram();
	glAttachShader(shader_program, vertex_shader);
	glAttachShader(shader_program, fragment_shader);
	glLinkProgram(shader_program);
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
}

gl_texture rndrr::load_texture(const char* path)
{
	gl_texture texture = {};
	std::vector<unsigned char> image;
	unsigned width, height;

	unsigned error = lodepng::decode(image, width, height, path);

	if (error != 0)
	{
		std::cout << "rndrr::error: " << error << ": " << lodepng_error_text(error) << std::endl;
	}
	else
	{
		std::cout << "rndrr::created image with data size: " << image.size() << std::endl;
	}

	glGenTextures(1, &texture.id);

	glBindTexture(GL_TEXTURE_2D, texture.id);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.data());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

	texture.width = width;
	texture.height = height;

	return texture;
}

void rndrr::draw()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(shader_program);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glBindVertexArray(0);
	glUseProgram(0);
}