#ifndef GL_TEXTURE_H
#define GL_TEXTURE_H

#include "../gl/glad.h"


struct gl_texture
{
	GLuint id;
	int width;
	int height;
};

#endif // GL_TEXTURE_H