//
// Created by 冉高飞 on 2018/5/25.
//

#ifndef FFMPEGDEMO_OPENGLHELPER_H
#define FFMPEGDEMO_OPENGLHELPER_H

#include <iostream>
#include <sstream>
#include <GLFW/glfw3.h>
#include "Config.h"
#include <string>
#include <unistd.h>
#include <fstream>

const int MAX_SIZE = 512;

class OpenGLHelper {
public:
    explicit OpenGLHelper(const std::string &dir_path);

    ~OpenGLHelper();

    std::string getShaderString(const std::string &fileName);

    int getProgram(GLuint &program,const std::string &vertexShaderFile, const std::string &fragmentShaderFile);

private:
    std::string dirPath;
    GLuint program;
    std::ifstream file;
    std::stringstream sourceStream;
    std::string shaderString;
    int success;
    char errInfo[MAX_SIZE];

    int compileShader(GLuint &pointer, GLenum type, const std::string &shaderString);


    std::string getShaderFilePath(const std::string &subDir = "");
};


#endif //FFMPEGDEMO_OPENGLHELPER_H
