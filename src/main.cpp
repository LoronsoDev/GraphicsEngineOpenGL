#define GLAD_ONLY_HEADERS

#include <engine/base/Kernel.h>

#include <scene/Camera.h>
#include <scene/primitives/PrimitiveObjects.h>
#include <scene/Light.h>
#include <scene/OrbitalLight.h>
#include <pugixml.cpp>

int main(int chargc, char** argv)
{
	SELECT_RENDERER(OPENGL4);

	Kernel::Init();

	//CubeTex object;

	Billboard object;
	object.name = "Bunny";
	object.LoadDataFromFile("assets/bunny.msh");
	object.SetRot({ 3.14 * 0.5,0,0,1.f });
	object.SetScale({ 5,5,5,1 });

	Object3D spotLightVisualizer;
	spotLightVisualizer.name = "Spot Light vis";
	spotLightVisualizer.isVisualizer = true;
	spotLightVisualizer.LoadDataFromFile("assets/cube.msh");
	spotLightVisualizer.SetScale(glm::vec4(0.1));

	Object3D orbitalLightVisualizer;
	orbitalLightVisualizer.name = "Orbital Light vis";
	orbitalLightVisualizer.isVisualizer = true;
	orbitalLightVisualizer.LoadDataFromFile("assets/cube.msh");
	orbitalLightVisualizer.SetScale(glm::vec4(0.1));

	CameraKeyboard camera(
		Camera::ProjectionType::PERSPECTIVE,
		{ 0,1.f,3.f },
		{ 0,1.f,0 },
		object.GetPos(),
		Kernel::s_InputManager,
		1.0f,
		0.5f);

	Light dirLight(Light::LightType::DIRECTIONAL);
	dirLight.name = "Directional Light";
	dirLight.direction = { 0.f, -1.f, 0.f };

	Light pointLight(Light::LightType::POINT);
	pointLight.name = "Point Light";
	pointLight.sceneVisualizer = &spotLightVisualizer;
	pointLight.specularColor = { 1, 0, 0 };
	pointLight.color = { 1, 0, 0 };
	pointLight.position = { 3,0,0 };
	pointLight.linearAttenuation = 0.7f;
	pointLight.quadraticAttenuation = 1.8f;

	OrbitalLight orbitalLight(Light::LightType::POINT, 1.f, {1.f, 0, 0});
	orbitalLight.name = "Orbital Light";
	orbitalLight.sceneVisualizer = &orbitalLightVisualizer;
	orbitalLight.color = glm::vec3(0,1,0);
	orbitalLight.specularColor = glm::vec3(1);
	orbitalLight.intensity = 1.f;


	Kernel::AddLight(&dirLight);
	Kernel::AddLight(&pointLight);
	Kernel::AddLight(&orbitalLight);

	Kernel::AddObject(reinterpret_cast<Object3D*>(&object));
	Kernel::AddObject(reinterpret_cast<Object3D*>(&spotLightVisualizer));
	Kernel::AddObject(reinterpret_cast<Object3D*>(&orbitalLightVisualizer));

	Kernel::AddCamera(&camera);

	Kernel::Execute();
	Kernel::Exit();
}