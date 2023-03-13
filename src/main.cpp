#define GLAD_ONLY_HEADERS

#include <engine/base/Kernel.h>

#include <scene/Camera.h>
#include <scene/primitives/PrimitiveObjects.h>


int main(int chargc, char** argv)
{
	SELECT_RENDERER(OPENGL4);

	Kernel::Init();

	CubeTex object;

	CameraKeyboard camera(
		Camera::ProjectionType::PERSPECTIVE,
		{ 0,1.f,3.f },
		{ 0,1.f,0 },
		object.GetPos(),
		Kernel::s_InputManager,
		0.025f,
		0.5f);


	Kernel::AddObject(reinterpret_cast<Object3D*>(&object));
	Kernel::AddCamera(&camera);

	Kernel::Execute();
	Kernel::Exit();
}