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

	CameraKeyboard camera(
		Camera::ProjectionType::PERSPECTIVE,
		{ 0,1.f,3.f },
		{ 0,1.f,0 },
		{0.0, 0.0, 0.0},
		Kernel::s_InputManager,
		1.0f,
		0.5f);

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

	Object3D spotLightVisualizer;
	spotLightVisualizer.name = "Spot Light vis";
	spotLightVisualizer.isDynamicObject = true;
	spotLightVisualizer.LoadDataFromFile("assets/cube.msh");
	spotLightVisualizer.SetScale(glm::vec4(0.1));

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


	Kernel::AddLight(&dirLight);
	Kernel::AddLight(&pointLight);

	Kernel::AddEmitter(&fireEmitter);
	Kernel::AddEmitter(&smokeEmitter);

	Kernel::AddObject(reinterpret_cast<Object3D*>(&object));
	Kernel::AddObject(reinterpret_cast<Object3D*>(&spotLightVisualizer));

	Kernel::AddCamera(&camera);

	Kernel::Execute();
	Kernel::Exit();
}