#ifndef INC_2DSDL_SHADER_H
#define INC_2DSDL_SHADER_H

#include <string_view>

#include <GLES3/gl3.h>
#include <glm/gtc/type_ptr.hpp>

#include "IResource.h"

class Shader : public IResource {
public:
    Shader(std::string_view, std::string_view);

    GLuint getProgram();

    void setUniform(const std::string &name, const glm::mat4 &matrix);

    void setUniform(const std::string &name, const glm::vec4 &vec4);

    void setUniform(const std::string &name, const glm::vec2 &vec2);

    void setUniform(const std::string &name, float_t value);

    void setActive();

private:
    void checkShaderCompileErrors(GLuint shader, std::string type);

    GLuint shaderProgram;

};


#endif //INC_2DSDL_SHADER_H
