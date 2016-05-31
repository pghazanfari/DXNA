#include "PixelShaderResource.h"
#include <string>
#include <fstream>
#include <vector>

bool PixelShaderResource::load()
{
	ifstream fin(getFilename(), std::ios::binary);
	fin.seekg(0, std::ios_base::end);
	int size = (int)fin.tellg();
	fin.seekg(0, std::ios_base::beg);
	std::vector<char> compiledShader(size);
	fin.read(&compiledShader[0], size);
	fin.close();
	HRESULT hr = GraphicsManager::currentDevice()->CreatePixelShader(&compiledShader[0], size, 0, &ps);

	if (FAILED(hr)) return false;

	return true;
}

void PixelShaderResource::release()
{
	ps->Release();
	ps = NULL;
}