#ifndef RNDRR_H
#define RNDRR_H

#include <lodepng.h>

#include "gl_texture.h"

class rndrr
{
public:
    static rndrr& instance() {
        static rndrr instance;
        return instance;
    }

    void init();
    void update(float dt);
    void draw();
private:
    rndrr();

    GLuint compile_shader(GLenum type, const char* source);
    void link_program();

    gl_texture load_texture(const char* path);


    GLfloat clear_color[4];

    GLuint vertex_shader;
    GLuint fragment_shader;
    GLuint shader_program;

    GLuint vao;
    GLuint vbo;

    gl_texture dummy_texture;

    float offset;
};

#endif // RNDRR_H