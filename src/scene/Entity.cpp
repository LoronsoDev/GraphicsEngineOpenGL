#include "Entity.h"

Entity::Entity()
{
    m_Pos   = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    m_Rot   = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    m_Scale = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

    m_ModelMatrix = glm::mat4(1.0f);
}

void Entity::ComputeModelMatrix()
{
    glm::mat4 matrix = glm::translate(glm::mat4(1.0f), glm::vec3(m_Pos));
    matrix = glm::rotate(matrix, m_Rot.x, glm::vec3(1.0f, 0.0f, 0.0f));
    matrix = glm::rotate(matrix, m_Rot.y, glm::vec3(0.0f, 1.0f, 0.0f));
    matrix = glm::rotate(matrix, m_Rot.z, glm::vec3(0.0f, 0.0f, 1.0f));
    matrix = glm::scale(matrix, glm::vec3(m_Scale));
    m_ModelMatrix = matrix;
}
