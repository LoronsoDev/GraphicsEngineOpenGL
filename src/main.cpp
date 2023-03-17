#define GLAD_ONLY_HEADERS

#include <engine/base/Kernel.h>

#include <scene/Camera.h>
#include <scene/primitives/PrimitiveObjects.h>
#include <pugixml.cpp>



int main(int chargc, char** argv)
{
	SELECT_RENDERER(OPENGL4);

	Kernel::Init();

	//CubeTex object;

	Object3D object;

	object.LoadDataFromFile("assets/asian_town.msh");
	object.SetScale({ 5,5,5,5 });

	CameraKeyboard camera(
		Camera::ProjectionType::PERSPECTIVE,
		{ 0,1.f,3.f },
		{ 0,1.f,0 },
		object.GetPos(),
		Kernel::s_InputManager,
		1.0f,
		0.5f);


	Kernel::AddObject(reinterpret_cast<Object3D*>(&object));
	Kernel::AddCamera(&camera);

	Kernel::Execute();
	Kernel::Exit();
}