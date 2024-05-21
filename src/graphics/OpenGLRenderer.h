//
// Created by artem on 05.05.24.
//

#ifndef INC_2DSDL_OPENGLRENDERER_H
#define INC_2DSDL_OPENGLRENDERER_H

#include "GL/glew.h"

class OpenGLRenderer {
public:
    void init() {
        glewExperimental = GL_TRUE;
        glewInit();
    }

    void render() {
        glClearColor(90./255., 145./255., 255./255., 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }
};


#endif //INC_2DSDL_OPENGLRENDERER_H
