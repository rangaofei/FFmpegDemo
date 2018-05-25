//
// Created by 冉高飞 on 2018/5/25.
//

#include "OpenGLHelper.h"


OpenGLHelper::OpenGLHelper(const std::string &dir_path) : dirPath(dir_path) {

}

OpenGLHelper::~OpenGLHelper() {

}

std::string OpenGLHelper::getShaderString(const std::string &fileName) {
    std::string filePath = getShaderFilePath(dirPath) + fileName;
    std::cout << filePath << std::endl;
    file.open(filePath);
    if (!file.is_open()) {
        std::cerr << "can't open the file :" << fileName << std::endl;
    }
    sourceStream << file.rdbuf();
    shaderString = sourceStream.str();
    file.close();
    sourceStream.clear();
    sourceStream.str("");
    return shaderString;
}

int OpenGLHelper::compileShader(GLuint &pointer, GLenum type, const std::string &shaderString) {
    pointer = glCreateShader(type);
    GLchar *shader_string = const_cast<GLchar *>(shaderString.c_str());
    glShaderSource(pointer, 1, &shader_string, NULL);
    glCompileShader(pointer);

    glGetShaderiv(pointer, GL_COMPILE_STATUS, &success);
    if (!success) {
        std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << errInfo << std::endl;
    }
    return pointer;
}

int
OpenGLHelper::getProgram(GLuint &program, const std::string &vertexShaderFile, const std::string &fragmentShaderFile) {
    std::string vertexShaderString = getShaderString(vertexShaderFile);
    std::string fragmentShaderString = getShaderString(fragmentShaderFile);
    GLuint vertexShader, fragmentShader;
    compileShader(vertexShader, GL_VERTEX_SHADER, vertexShaderString);
    compileShader(fragmentShader, GL_FRAGMENT_SHADER, fragmentShaderString);
    program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    return 1;
}


std::string OpenGLHelper::getShaderFilePath(const std::string &subDir) {
#ifdef _WIN32
    const char PATH_SEP='\\';
#else
    const char PATH_SEP = '/';
#endif

    static std::string baseRes;
    if (baseRes.empty()) {
        char basePath[MAX_SIZE];
        if (getcwd(basePath, MAX_SIZE)) {
            baseRes = basePath;
        } else {
            std::cerr << "Error getting resource path" << std::endl;
            return "";
        }
#ifdef RES_PATH_CLION
        size_t pos = baseRes.rfind("cmake-build-debug");
#else
        size_t pos = baseRes.rfind("build");
#endif
        baseRes = baseRes.substr(0, pos) + "res" + PATH_SEP;
    }
    return subDir.empty() ? baseRes : baseRes + subDir + PATH_SEP;
}