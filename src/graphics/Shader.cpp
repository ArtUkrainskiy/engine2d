//
// Created by artem on 07.04.24.
//

#include <iostream>
#include "Shader.h"

Shader::Shader(std::string_view vertexShaderSrc, std::string_view fragmentShaderSrc) {
    const char *vertexShaderSource = vertexShaderSrc.data();
    const char *fragmentShaderSource = fragmentShaderSrc.data();

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    checkShaderCompileErrors(vertexShader, "VERTEX");

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    checkShaderCompileErrors(fragmentShader, "FRAGMENT");

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    checkShaderCompileErrors(shaderProgram, "PROGRAM");

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::checkShaderCompileErrors(GLuint shader, std::string type) {
    GLint success;
    GLchar infoLog[1024];
    if (type != "PROGRAM") {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cerr << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog
                      << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    } else {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cerr << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog
                      << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
}

void Shader::setActive() {
    glUseProgram(shaderProgram);
}

GLuint Shader::getProgram() {
    return shaderProgram;
}

void Shader::setUniform(const std::string &name, const glm::mat4 &matrix) {
    this->setActive();
    GLint location = glGetUniformLocation(shaderProgram, name.c_str());
    if (location != -1) {
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
    } else {
        std::cerr << "Uniform " << name << " not found in shader program" << std::endl;
    }
}

void Shader::setUniform(const std::string &name, const glm::vec4 &vec4) {
    this->setActive();
    GLint location = glGetUniformLocation(shaderProgram, name.c_str());
    if (location != -1) {
        glUniform4fv(location, 1, glm::value_ptr(vec4));
    } else {
        std::cerr << "Uniform " << name << " not found in shader program" << std::endl;
    }
}

void Shader::setUniform(const std::string &name, const glm::vec2 &vec2) {
    this->setActive();
    GLint location = glGetUniformLocation(shaderProgram, name.c_str());
    if (location != -1) {
        glUniform2fv(location, 1, glm::value_ptr(vec2));
    } else {
        std::cerr << "Uniform " << name << " not found in shader program" << std::endl;
    }
}

void Shader::setUniform(const std::string &name, float_t value) {
    this->setActive();
    GLint location = glGetUniformLocation(shaderProgram, name.c_str());
    if (location != -1) {
        glUniform1f(location,value);
    } else {
        std::cerr << "Uniform " << name << " not found in shader program" << std::endl;
    }
}

