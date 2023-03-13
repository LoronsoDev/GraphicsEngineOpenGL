#include "PrimitiveObjects.h"

CubeTex::CubeTex()
{
	Mesh3D* mesh = new Mesh3D;

	//Adding here materials as the provided structure says so.
	SetPos({ 0,0,0 });

	mesh->setMaterial(new GLSLMaterial);
	mat = mesh->getMaterial();
	mat->loadPrograms("Shaders/texture2D_unlit.vert", "Shaders/texture2D_unlit.frag");

	//FIRST PLANE
	{
		Vertex v0{
			.pos = { -0.5f,-0.5f, 0.0f, 1.0f},
			.textureUV = {0.0f, 0.0f} };

		Vertex v1  {
			.pos = {-0.5f, 0.5f, 0.0f, 1.0f},
			.textureUV = {0.0f, 1.0f} };

		Vertex v2  {
			.pos = { 0.5f, 0.5f, 0.0f, 1.0f},
			.textureUV = {1.0f, 1.0f} };

		Vertex v3  {
			.pos = {0.5f,-0.5f, 0.0f, 1.0f},
			.textureUV = {1.0f, 0.0f} };


		mesh->AddVertex(v0);
		mesh->AddVertex(v1);
		mesh->AddVertex(v2);
		mesh->AddVertex(v3);


		mesh->addTriangle(0, 1, 2);
		mesh->addTriangle(0, 2, 3);

		Texture* texture = RenderFactory::GetNewTexture("assets/front.png", Texture::COLOR2D);

		mat->setTexture(texture);
	}


	SetMesh(mesh);
}

void CubeTex::Step(float deltaTime)
{
}
