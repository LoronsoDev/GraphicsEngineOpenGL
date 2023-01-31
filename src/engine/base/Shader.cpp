#include <engine/base/Shader.h>

Shader::Shader(std::string srcPath) : srcPath(srcPath)
{
	if (srcPath.ends_with("VTX"))
	{
		this->type = VERTEX;
	}
	else if (srcPath.ends_with("FRG"))
	{
		this->type = FRAGMENT;
	}
	else
	{
		this->type = UNKNOWN;
	}

	ParseSourceCode();
}

Shader::Shader(std::string srcPath, RenderTypes type) : srcPath(srcPath), type(type)
{
	ParseSourceCode();
}

void Shader::ParseSourceCode()
{
	std::ifstream inFile;
	if (!inFile.is_open())
	{
		std::cout << "Invalid shader file! - Can't be read.";
		this->type = UNKNOWN;
		return;
	}

	inFile.open(srcPath); //open the input file
	std::stringstream strStream;
	strStream << inFile.rdbuf(); //read the file
	std::string str = strStream.str(); //str holds the content of the file

	this->code = str;
}
