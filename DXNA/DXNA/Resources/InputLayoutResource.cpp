#include "InputLayoutResource.h"
#include "ResourceManager.h"
#include <string>
#include <fstream>
#include <vector>

bool InputLayoutResource::load()
{
	ifstream file(getFilename());
	string line;

	getline(file, line);

	char filename[512];
	strcpy_s(filename, line.c_str());

	ResourceManager* manager = ResourceManager::Manager();


	//Read Shader Byte Code
	ifstream fin(manager->getFilePath(filename), std::ios::binary);
	fin.seekg(0, std::ios_base::end);
	int size = (int)fin.tellg();
	fin.seekg(0, std::ios_base::beg);
	std::vector<char> compiledShader(size);
	fin.read(&compiledShader[0], size);
	fin.close();

	file.close();

	HRESULT hr = GraphicsManager::CreateInputLayout(compiledShader, &ilayout);

	if (FAILED(hr)) return false;

	return true;
}

void InputLayoutResource::release()
{
	ilayout->Release();
	ilayout = NULL;
}