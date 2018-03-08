#ifndef _SHADER_H_
#define _SHADER_H_

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

struct Shader
{
    unsigned int ID;

    Shader(const GLchar* vertex_path, const GLchar* fragment_path)
    {
        std::string vertex_code;
        std::string fragment_code;
        std::ifstream vertex_shader_file;
        std::ifstream fragment_shader_file;

        vertex_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fragment_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

        try
        {
            vertex_shader_file.open(vertex_path);
            fragment_shader_file.open(fragment_path);
            std::stringstream vert_shader_stream, frag_shader_stream;

            vert_shader_stream << vertex_shader_file.rdbuf();
            frag_shader_stream << fragment_shader_file.rdbuf();

            vertex_shader_file.close();
            fragment_shader_file.close();

            vertex_code = vert_shader_stream.str();
            fragment_code = frag_shader_stream.str();
        }
        catch (std::ifstream::failure e)
        {
            std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
        }

        const char* vert_shader_code = vertex_code.c_str();
        const char* frag_shader_code = fragment_code.c_str();

        int success;
        char info_log[512];

        unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vert_shader_code, NULL);
        glCompileShader(vertex);

        checkCompileErrors(vertex, "VERTEX");

        unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &frag_shader_code, NULL);
        glCompileShader(fragment);

        checkCompileErrors(fragment, "FRAGMENT");

        ID = glCreateProgram();
        glAttachShader(ID, vertex);
        glAttachShader(ID, fragment);
        glLinkProgram(ID);

        checkCompileErrors(ID, "PROGRAM");

        glDeleteShader(vertex);
        glDeleteShader(fragment);

    }

    void use()
    {
        glUseProgram(ID);
    }

    void setBool(const std::string& name, bool value) const
    {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), static_cast<int>(value));
    }

    void setInt(const std::string& name, int value) const
    {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
    }

    void setFloat(const std::string& name, float value) const
    {
        glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
    }

    void setVec2(const std::string &name, const glm::vec2 &value) const
    {
        glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
    }

    void setVec2(const std::string &name, float x, float y) const
    {
        glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
    }

    void setVec3(const std::string &name, const glm::vec3 &value) const
    {
        glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
    }
    void setVec3(const std::string &name, float x, float y, float z) const
    {
        glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
    }

    void setVec4(const std::string &name, const glm::vec4 &value) const
    {
        glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
    }
    void setVec4(const std::string &name, float x, float y, float z, float w) const
    {
        glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
    }

    void setMat2(const std::string &name, const glm::mat2 &mat) const
    {
        glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    void setMat3(const std::string &name, const glm::mat3 &mat) const
    {
        glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    void setMat4(const std::string &name, const glm::mat4 &mat) const
    {
        glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

private:
    void checkCompileErrors(GLuint shader, const std::string& type)
    {
        GLint success;
        GLchar info_log[512];

        if (type != "PROGRAM")
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(shader, 512, NULL, info_log);
                std::cerr << "ERROR::SHADER::" << type << "::COMPILATION_FAILED\n" <<  info_log << std::endl;
            }
        }
        else
        {
            glGetProgramiv(ID, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(shader, 512, NULL, info_log);
                std::cerr << "ERROR::SHADER::" << type << "::LINKING_FAILED\n" << info_log << std::endl;
            }
        }
    }
};

#endif // _SHADER_H_
