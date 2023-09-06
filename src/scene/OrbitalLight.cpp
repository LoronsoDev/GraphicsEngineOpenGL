#include <scene/OrbitalLight.h>

void OrbitalLight::step(double timeStep)
{
	angle += speed * timeStep;

	glm::mat4 identity = glm::mat4(1.0f);
	glm::mat4 tr = glm::translate(identity, radius);
	glm::mat rot = glm::rotate(identity, angle, glm::vec3(0.f, 1.f, 0.f));

	position = rot * tr * glm::vec4(glm::vec3{0,0,0}, 1.0f);
}
