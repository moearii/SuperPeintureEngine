#include "shader.h"

Shader::Shader(){

}

void Shader::init(const GLchar* vertexPath, const GLchar* fragmentPath)
{
    // 1. Retrieve the vertex/fragment source code from filePath
    std::ifstream file(vertexPath);
    std::string str;
    std::string file_contents;
    while (std::getline(file, str))
    {
      file_contents += str;
      file_contents.push_back('\n');
    }

    const char *vertexShaderSource = file_contents.c_str();

    GLuint vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    std::ifstream fileShader(fragmentPath);
    std::string strShader;
    std::string file_contents_Shader;
    while (std::getline(fileShader, strShader))
    {
      file_contents_Shader += strShader;
      file_contents_Shader.push_back('\n');
    }
    const char *fragmentShaderSource = file_contents_Shader.c_str();

    GLuint fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::FRAGMENT::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    this->Program = glCreateProgram();
    glAttachShader(this->Program, vertexShader);
    glAttachShader(this->Program, fragmentShader);

    glBindAttribLocation(this->Program, 0, "position");
    glBindAttribLocation(this->Program, 1, "normal");
    glBindAttribLocation(this->Program, 2, "textCoord");

    glLinkProgram(this->Program);

    glGetProgramiv(this->Program, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(this->Program, 512, NULL, infoLog);
        std::cout << "ERROR::LINK::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // Delete the shaders as they're linked into our program now and no longer necessery
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::initComputeShader(const GLchar* computeShaderPath){

    //printWorkGroupsCapabilities();
}

void Shader::use(){
    glUseProgram(this->Program);
}


void Shader::printWorkGroupsCapabilities(){

    int workgroup_count[3];
    int workgroup_size[3];
    int workgroup_invocation;

    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 0, &workgroup_count[0]);
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 1, &workgroup_count[1]);
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 2, &workgroup_count[2]);

    std::cout << "Taille maximale des workgroups :\ntx : " << workgroup_count[0] << "\nty :" << workgroup_count[1] << "\ntz : " << workgroup_count[2] << std::endl;

    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 0, &workgroup_size[0]);
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 1, &workgroup_size[1]);
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 2, &workgroup_size[2]);

    std::cout << "Nombre maximal d'invocation locale :\ntx : " << workgroup_size[0] << "\nty :" << workgroup_size[1] << "\ntz : " << workgroup_size[2] << std::endl;

    //glGetIntegerv(GL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS, &workgroup_invocation);

    std::cout << "Nombre maximal d'invocation de workgroups : \nt : " << workgroup_invocation << std::endl;

}
