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

	/*CameraKeyboard camera(
		Camera::ProjectionType::PERSPECTIVE,
		{ 0,1.f,3.f },
		{ 0,1.f,0 },
		{0.0, 0.0, 0.0},
		Kernel::s_InputManager,
		1.0f,
		0.5f);*/

	CameraOrbital camera(
		Camera::ProjectionType::PERSPECTIVE,
		{ 0,1.f,3.f },
		{ 0,1.f,0 },
		{ 0.0, 0.0, 0.0 },
		1.0f);
	camera.radius = { 5., 1.5, 0.0 };

	Emitter fireEmitter("assets/flame.msh", 10.f, true);
	fireEmitter.setRateRange(10.f, 15.f);
	fireEmitter.setVelocityRange({ -0.02, 0.1, -0.02 }, {0.02, 0.5, 0.02});
	fireEmitter.setSpinVelocityRange(0, 0);
	fireEmitter.setLifetimeRange(0.5, 0.5);
	fireEmitter.setScaleRange(0.6f, 1.0f);
	fireEmitter.SetPos({ 0.f, 2.f, 0.f });

	Emitter smokeEmitter("assets/smoke.msh", 5.f, true);
	smokeEmitter.setRateRange(5.f, 10.f);
	smokeEmitter.setVelocityRange({ -0.1, 0.01, -0.1 }, { 0.1, 2, 0.1 });
	smokeEmitter.setSpinVelocityRange(30, 60);
	smokeEmitter.setLifetimeRange(1.5, 5.);
	smokeEmitter.setScaleRange(0.6f, 1.0f);
	smokeEmitter.SetPos({ 0.f, 2.f, 0.f });

	Object3D object;
	object.name = "Column";
	object.LoadDataFromFile("assets/column.msh");
	object.SetScale({ 0.003,0.003,0.003,1 });

	//Light dirLight(Light::LightType::DIRECTIONAL);
	//dirLight.name = "Directional Light";
	//dirLight.direction = { 0.f, -1.f, 0.f };

	CubeTex pointLightVisualizer;
	pointLightVisualizer.name = "PL1 vis";
	pointLightVisualizer.isDynamicObject = true;
	pointLightVisualizer.LoadDataFromFile("assets/cube.msh");
	pointLightVisualizer.SetScale(glm::vec4(0.1));

	Object3D pointLightVisualizer_2;
	pointLightVisualizer_2.name = "PL2 vis";
	pointLightVisualizer_2.isDynamicObject = true;
	pointLightVisualizer_2.LoadDataFromFile("assets/cube.msh");
	pointLightVisualizer_2.SetScale(glm::vec4(0.1));

	Light pointLight(Light::LightType::POINT);
	pointLight.name = "Point Light";
	pointLight.sceneVisualizer = &pointLightVisualizer;
	pointLight.specularColor = { 1, 0, 0 };
	pointLight.color = { 1, 0, 0 };
	pointLight.position = { 1,-1 , 6 };
	pointLight.intensity = 7.5f;
	pointLight.linearAttenuation = 0.2f;
	pointLight.quadraticAttenuation = 0.3f;

	Light pointLight_2(Light::LightType::POINT);
	pointLight_2.name = "Point Light 2";
	pointLight_2.sceneVisualizer = &pointLightVisualizer_2;
	pointLight_2.specularColor = { 0, 1, 0 };
	pointLight_2.color = { 0, 1, 0 };
	pointLight_2.position = { -1,2,-1 };
	pointLight_2.intensity = 4.5f;
	pointLight_2.linearAttenuation = 0.2f;
	pointLight_2.quadraticAttenuation = 0.3f;


	//Kernel::AddLight(&dirLight);
	Kernel::AddLight(&pointLight);
	Kernel::AddLight(&pointLight_2);

	Kernel::AddEmitter(&fireEmitter);
	Kernel::AddEmitter(&smokeEmitter);

	Kernel::AddObject(reinterpret_cast<Object3D*>(&object));
	Kernel::AddObject(reinterpret_cast<Object3D*>(&pointLightVisualizer));
	Kernel::AddObject(reinterpret_cast<Object3D*>(&pointLightVisualizer_2));

	Kernel::AddCamera(&camera);

	Kernel::Execute();
	Kernel::Exit();
}