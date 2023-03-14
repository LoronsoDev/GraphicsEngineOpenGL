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
	//back
	{
		Vertex v4{
			.pos = { -0.5f,-0.5f, -1.0f, 1.0f},
			.textureUV = {0.0f, 0.0f} };

		Vertex v5{
			.pos = {-0.5f, 0.5f, -1.0f, 1.0f},
			.textureUV = {0.0f, 1.0f} };

		Vertex v6{
			.pos = { 0.5f, 0.5f, -1.0f, 1.0f},
			.textureUV = {1.0f, 1.0f} };

		Vertex v7{
			.pos = {0.5f,-0.5f, -1.0f, 1.0f},
			.textureUV = {1.0f, 0.0f} };

		mesh->AddVertex(v4);
		mesh->AddVertex(v5);
		mesh->AddVertex(v6);
		mesh->AddVertex(v7);

		mesh->addTriangle(4, 5, 6);
		mesh->addTriangle(4, 6, 7);
	}
	//left
	{
		Vertex v8{//0
			.pos = { -0.5f,-0.5f, 0.0f, 1.0f},
			.textureUV = {0.0f, 0.0f} };

		Vertex v9{//1
			.pos = {-0.5f, 0.5f, 0.0f, 1.0f},
			.textureUV = {0.0f, 1.0f} };

		Vertex v10{//5
			.pos = {-0.5f, 0.5f, -1.0f, 1.0f},
			.textureUV = {1.0f, 1.0f} };
		
		Vertex v11{//4
			.pos = { -0.5f,-0.5f, -1.0f, 1.0f},
			.textureUV = {1.0f, 0.0f} };
		
		mesh->AddVertex(v8);
		mesh->AddVertex(v9);
		mesh->AddVertex(v10);
		mesh->AddVertex(v11);

		mesh->addTriangle(8, 9, 10);
		mesh->addTriangle(8, 10, 11);
	}
	//right
	{
		Vertex v12{//3
			.pos = {0.5f,-0.5f, 0.0f, 1.0f},
			.textureUV = {0.0f, 0.0f} };

		Vertex v13{//2
			.pos = { 0.5f, 0.5f, 0.0f, 1.0f},
			.textureUV = {0.0f, 1.0f} };

		Vertex v14{//6
			.pos = { 0.5f, 0.5f, -1.0f, 1.0f},
			.textureUV = {1.0f, 1.0f} };

		Vertex v15{//7
			.pos = {0.5f,-0.5f, -1.0f, 1.0f},
			.textureUV = {1.0f, 0.0f} };

		mesh->AddVertex(v12);
		mesh->AddVertex(v13);
		mesh->AddVertex(v14);
		mesh->AddVertex(v15);

		mesh->addTriangle(12, 13, 14);
		mesh->addTriangle(12, 14, 15);
	}

	Mesh3D * topBottomMesh = new Mesh3D();
	topBottomMesh->setMaterial(new GLSLMaterial);
	Material * mat2 = topBottomMesh->getMaterial();
	mat2->loadPrograms("Shaders/texture2D_unlit.vert", "Shaders/texture2D_unlit.frag");

	//top
	{
		Vertex v0{
			.pos = {-0.5f, 0.5f, 0.0f, 1.0f},
			.textureUV = {0.0f, 0.0f} };

		Vertex v1{
			.pos = { 0.5f, 0.5f, 0.0f, 1.0f},
			.textureUV = {1.0f, 0.0f} };

		Vertex v2{
			.pos = {-0.5f, 0.5f, -1.0f, 1.0f},
			.textureUV = {0.0f, 1.0f} };

		Vertex v3{
			.pos = { 0.5f, 0.5f, -1.0f, 1.0f},
			.textureUV = {1.0f, 1.0f} };

		topBottomMesh->AddVertex(v0);
		topBottomMesh->AddVertex(v1);
		topBottomMesh->AddVertex(v2);
		topBottomMesh->AddVertex(v3);

		topBottomMesh->addTriangle(0, 1, 2);
		topBottomMesh->addTriangle(2, 1, 3);

		Texture* texture2 = RenderFactory::GetNewTexture("assets/top.png", Texture::COLOR2D);
		mat2->setTexture(texture2);
	}
	//bottom
	{
		Vertex v0{
			.pos = {-0.5f, -0.5f, 0.0f, 1.0f},
			.textureUV = {0.0f, 0.0f} };

		Vertex v1{
			.pos = { 0.5f, -0.5f, 0.0f, 1.0f},
			.textureUV = {1.0f, 0.0f} };

		Vertex v2{
			.pos = {-0.5f, -0.5f, -1.0f, 1.0f},
			.textureUV = {0.0f, 1.0f} };

		Vertex v3{
			.pos = { 0.5f, -0.5f, -1.0f, 1.0f},
			.textureUV = {1.0f, 1.0f} };

		topBottomMesh->AddVertex(v0);
		topBottomMesh->AddVertex(v1);
		topBottomMesh->AddVertex(v2);
		topBottomMesh->AddVertex(v3);

		topBottomMesh->addTriangle(4, 5, 6);
		topBottomMesh->addTriangle(6, 5, 7);
	}

	AddMesh(mesh);
	AddMesh(topBottomMesh);
}

void CubeTex::Step(float deltaTime)
{
}
