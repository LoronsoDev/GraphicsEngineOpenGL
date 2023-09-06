#include "Object3D.h"

#include "engine/render/RenderFactory.h"

template<typename T>
std::vector<T> splitString(const std::string& str, char delim) {
	std::vector<T> elems;
	if (str != "") {
		std::stringstream ss(str);
		std::string item;
		while (std::getline(ss, item, delim)) {
			T value;
			std::stringstream ss2(item);
			ss2 >> value;
			elems.push_back(value);
		}
	}
	return elems;
}

void Object3D::Step(float deltatime)
{
	
}

void Object3D::LoadDataFromFile(std::string path)
{
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(path.c_str());

	pugi::xml_node buffersNode = doc.child("mesh").child("buffers");

	if (result) std::cout << "Error reading provided file: " << path;

	for (pugi::xml_node bufferNode = buffersNode.child("buffer");
		bufferNode;
		bufferNode = bufferNode.next_sibling("buffer"))
	{
		Mesh3D* mesh = new Mesh3D;

		auto matNode = bufferNode.child("material");
		if (matNode)
		{
			auto texNode = matNode.child("texture");

			Material* mat = new GLSLMaterial();
			if (texNode)
			{
				Texture* texture = engine::RenderFactory::GetNewTexture(texNode.text().as_string(), Texture::COLOR2D);
				mat->setTexture(texture);
			}
			auto colorNode = matNode.child("color");
			if (colorNode)
			{
				std::vector<float> listcolor = splitString<float>(colorNode.text().as_string(), ',');
				RGBA mat_color;

				mat_color.r = listcolor[0];
				mat_color.g = listcolor[1];
				mat_color.b = listcolor[2];
				mat_color.a = listcolor[3];
				mat->setColor(mat_color);
			}
			auto shininess = matNode.child("shininess");
			if (shininess)
			{
				float shine = shininess.text().as_float();
				mat->setShininess(shine/sizeof(uint8_t));
			}
			else
			{
				// defaults color if there isn't one specified.
				RGBA mat_color;
				mat_color.r = 0.f;
				mat_color.g = 0.f;
				mat_color.b = 0.f;
				mat_color.a = 0.f;

				mat->setColor(mat_color);
				mat->hasColor = false;
			}

			auto vShaderNode = matNode.child("vShader");
			auto fShaderNode = matNode.child("fShader");

			if (vShaderNode && fShaderNode)
			{
				mat->loadPrograms(vShaderNode.text().as_string(), fShaderNode.text().as_string());
				mesh->setMaterial(mat);
			}
		}


		//ELEMENTS
		VertexIdBuffer* idBuffer = new VertexIdBuffer();
		*idBuffer = splitString<unsigned int>(bufferNode.child("indices").
			text().as_string(), ',');
		mesh->SetIdBufferList(idBuffer);

		//VERTEX
		std::vector<float> vertexBuffer = splitString<float>(bufferNode.child("coords").
			text().as_string(), ',');

		auto texCoordsNode = bufferNode.child("texCoords");
		std::vector<float> uvList;
		if (texCoordsNode)
		{
			uvList = splitString<float>(texCoordsNode.
				text().as_string(), ',');
		}

		auto normalsNode = bufferNode.child("normals");
		std::vector<float> nList;
		if (normalsNode)
		{
			nList = splitString<float>(normalsNode.
				text().as_string(), ',');
		}

		auto coord = vertexBuffer.begin();
		auto texCoord = uvList.begin();
		auto normal = nList.begin();

		while (coord != vertexBuffer.end())
		{
			Vertex v;
			v.pos.x = *coord++;
			v.pos.y = *coord++;
			v.pos.z = *coord++;
			v.pos.w = 1.0f;

			if (normalsNode)
			{
				v.normal.x = *normal++;
				v.normal.y = *normal++;
				v.normal.z = *normal++;
				v.normal.w = 0.0f;
				v.normal = glm::normalize(v.normal);
			}

			RGBA color = mesh->getMaterial()->getColor();
			if (mesh->getMaterial()->hasColor)
			{
				v.color = { color.r, color.g, color.b, color.a };
			}

			if (uvList.size() > 0) {
				v.textureUV.x = *texCoord++;
				v.textureUV.y = *texCoord++;
			}

			mesh->AddVertex(v);
		}

		this->AddMesh(mesh);
	}
}

inline std::string extractPath(std::string filename) {
	while (filename.find('\\') != std::string::npos)
		filename.replace(filename.find('\\'), 1, 1, '/');
	size_t pos = filename.rfind('/');
	if (pos == std::string::npos) return "";
	filename = filename.substr(0, pos);
	if (filename.size() > 0) filename += '/';
	return filename;
}


