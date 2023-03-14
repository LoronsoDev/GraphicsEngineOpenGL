#pragma once
#include <string>
#include "Engine_Core.h"
class RenderProgram
{
public:
    typedef enum class renderTypes_e {
        vertex = 0, fragment = 1
    }renderTypes_e;

    /**
     * \brief map that eases access to variables set in a shader.
     */
    std::map<std::string, unsigned int> shaderProgramVars;

	virtual void setProgram(std::string programSrc, renderTypes_e type)=0;
	virtual void linkPrograms() = 0;
	virtual void use() = 0;

    virtual void readProgramVariables() = 0;

    // utility uniform functions
    // ------------------------------------------------------------------------
    virtual void setBool(const std::string& name, bool value) const = 0;
    // ------------------------------------------------------------------------
    virtual void setInt(const std::string& name, int value) const = 0;
    // ------------------------------------------------------------------------
    virtual void setFloat(const std::string& name, float value) const = 0;
    // ------------------------------------------------------------------------
    virtual void setVec2(const std::string& name, const glm::vec2& value) const = 0;
    virtual void setVec2(const std::string& name, float x, float y) const = 0;
    
    // ------------------------------------------------------------------------
    virtual void setVec3(const std::string& name, const glm::vec3& value) const = 0;
    virtual void setVec3(const std::string& name, float x, float y, float z) const = 0;
    // ------------------------------------------------------------------------
    virtual void setVec4(const std::string& name, const glm::vec4& value) const = 0;
    virtual void setVec4(const std::string& name, float x, float y, float z, float w) const = 0;
    // ------------------------------------------------------------------------
    virtual void setMat2(const std::string& name, const glm::mat2& mat) const = 0;
    // ------------------------------------------------------------------------
    virtual void setMat3(const std::string& name, const glm::mat3& mat) const = 0;
    // ------------------------------------------------------------------------
    virtual void setMat4(const std::string& name, const glm::mat4& mat) const = 0;


};
