#include "Camera.h"


/*
 * // calculate the new Front vector
        glm::vec3 front;
        front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        front.y = sin(glm::radians(Pitch));
        front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        Front = glm::normalize(front);
        // also re-calculate the Right and Up vector
        Right = glm::normalize(glm::cross(Front, WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        Up = glm::normalize(glm::cross(Right, Front));
 */

void CameraKeyboard::Step(float timestep)
{
	glm::vec4 currentPos = GetPos();
	glm::vec4 vel = { 0,0,0,0 };

	if(Kernel::s_InputManager->GetKeyState(GLFW_KEY_W))
	{
		vel.z = 1;
	}
	if (Kernel::s_InputManager->GetKeyState(GLFW_KEY_S))
	{
		vel.z = -1;
	}
	if (Kernel::s_InputManager->GetKeyState(GLFW_KEY_D))
	{
		vel.x = 1;
	}
	if (Kernel::s_InputManager->GetKeyState(GLFW_KEY_A))
	{
		vel.x = -1;
	}

	vel *= velocity * timestep;

	SetPos(currentPos + vel);

	
}
