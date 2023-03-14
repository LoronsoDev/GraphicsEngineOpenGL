#include "GLSLShader.h"

void GLSLShader::setProgram(std::string programSrc, renderTypes_e type)
{
    // 1. retrieve the vertex/fragment source code from filePath
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    if(type==renderTypes_e::vertex)
    {
        try
        {
            vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
            vShaderFile.open(programSrc);
            std::stringstream vShaderStream;
            vShaderStream << vShaderFile.rdbuf();
            vShaderFile.close();
            vertexCode = vShaderStream.str();
        }
        catch (std::ifstream::failure& e)
        {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
        }   
    }
    if (type == renderTypes_e::fragment)
    {
        try
        {
            fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
            fShaderFile.open(programSrc);
            std::stringstream fShaderStream;
            fShaderStream << fShaderFile.rdbuf();
            fShaderFile.close();
            fragmentCode = fShaderStream.str();
        }
        catch (std::ifstream::failure& e)
        {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
        }
    }
}

void GLSLShader::linkPrograms()
{
    ID = glCreateProgram();

    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();
    // 2. compile shaders
    unsigned int vertex, fragment;
    // vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    checkCompileErrors(vertex, "VERTEX");
    // fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    checkCompileErrors(fragment, "FRAGMENT");
    // shader Program
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    checkCompileErrors(ID, "PROGRAM");
    // delete the shaders as they're linked into our program now and no longer necessery
    glDeleteShader(vertex);
    glDeleteShader(fragment);

    readProgramVariables();
}

void GLSLShader::readProgramVariables()
{
    use();
    int count = 0;
    constexpr GLsizei buffSize = 100;
    char* name = new char[buffSize];
    GLsizei length;
    GLint size;
    GLenum type;

    glGetProgramiv(ID, GL_ACTIVE_ATTRIBUTES, &count);
    for (int i = 0; i < count; i++)
    {
        glGetActiveAttrib(ID, (GLuint)i, 100, &length, &size, &type, name);
        this->shaderProgramVars[std::string(name)] = glGetAttribLocation(ID, name);
    }
    glGetProgramiv(ID, GL_ACTIVE_UNIFORMS, &count);
    for (int i = 0; i < count; i++)
    {
        glGetActiveUniform(ID, (GLuint)i, 100, &length, &size, &type, name);
        shaderProgramVars[std::string(name)] = glGetUniformLocation(ID, name);
    }
}


void GLSLShader::use()
{
	glUseProgram(ID);
}

// utility uniform functions
// ------------------------------------------------------------------------
void GLSLShader::setBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}
// ------------------------------------------------------------------------
void GLSLShader::setInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}
// ------------------------------------------------------------------------
void GLSLShader::setFloat(const std::string& name, float value) const 
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}
// ------------------------------------------------------------------------
void GLSLShader::setVec2(const std::string& name, const glm::vec2& value) const
{
	glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}
void GLSLShader::setVec2(const std::string& name, float x, float y) const 
{
	glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
}

// ------------------------------------------------------------------------
void GLSLShader::setVec3(const std::string& name, const glm::vec3& value) const 
{
	glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}
void GLSLShader::setVec3(const std::string& name, float x, float y, float z) const 
{
	glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
}
// ------------------------------------------------------------------------
void GLSLShader::setVec4(const std::string& name, const glm::vec4& value) const 
{
	glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}
void GLSLShader::setVec4(const std::string& name, float x, float y, float z, float w) const
{
	glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
}
// ------------------------------------------------------------------------
void GLSLShader::setMat2(const std::string& name, const glm::mat2& mat) const 
{
	glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void GLSLShader::setMat3(const std::string& name, const glm::mat3& mat) const 
{
	glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void GLSLShader::setMat4(const std::string& name, const glm::mat4& mat) const
{
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
void GLSLShader::checkCompileErrors(GLuint shader, std::string type)
{
    GLint success;
    GLchar infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
}