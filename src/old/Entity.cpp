#include "Entity.h"

Entity::Entity()
{
    pos = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    rot= glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    escala = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    modelMatrix = glm::mat4(1.0f);
}
glm::vec4 Entity::getPos()
{
    return pos;
}
glm::vec4 Entity::getRot()
{
    return rot;
}
glm::vec4 Entity::getScale()
{
    return escala;
}
glm::mat4 Entity::getModelMatrix()
{
    return modelMatrix;
}
void Entity::setPos(glm::vec4 position)
{
    pos = position;
}
void Entity::setRot(glm::vec4 rotation)
{
    rot = rotation;
}
void Entity::setScale(glm::vec4 scale)
{
    escala = scale;
}
void Entity::setModelMatrix(glm::mat4 matrix)
{
    modelMatrix = matrix;
}
void Entity::computeModelMatrix()
{
    glm::mat4 matrix = glm::translate(glm::mat4(1.0f), glm::vec3(pos));
    matrix = glm::rotate(matrix, rot.x, glm::vec3(1.0f, 0.0f, 0.0f));
    matrix = glm::rotate(matrix, rot.y, glm::vec3(0.0f, 1.0f, 0.0f));
    matrix = glm::rotate(matrix, rot.z, glm::vec3(0.0f, 0.0f, 1.0f));
    matrix = glm::scale(matrix, glm::vec3(escala));
    modelMatrix = matrix;
}
