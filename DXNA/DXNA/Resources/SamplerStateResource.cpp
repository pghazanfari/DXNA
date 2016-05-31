#include "SamplerStateResource.h"
#include <fstream>

D3D11_FILTER getFilter(string name)
{

	if (name.compare("D3D11_FILTER_MIN_MAG_POINT_MIP_LINEAR") == 0)
		return D3D11_FILTER_MIN_MAG_POINT_MIP_LINEAR;

	if (name.compare("D3D11_FILTER_MIN_POINT_MAG_LINEAR_MIP_POINT") == 0)
		return D3D11_FILTER_MIN_POINT_MAG_LINEAR_MIP_POINT;

	if (name.compare("D3D11_FILTER_MIN_POINT_MAG_MIP_LINEAR") == 0)
		return D3D11_FILTER_MIN_POINT_MAG_MIP_LINEAR;

	if (name.compare("D3D11_FILTER_MIN_LINEAR_MAG_MIP_POINT") == 0)
		return D3D11_FILTER_MIN_LINEAR_MAG_MIP_POINT;

	if (name.compare("D3D11_FILTER_MIN_LINEAR_MAG_POINT_MIP_LINEAR") == 0)
		return D3D11_FILTER_MIN_LINEAR_MAG_POINT_MIP_LINEAR;

	if (name.compare("D3D11_FILTER_MIN_MAG_LINEAR_MIP_POINT") == 0)
		return D3D11_FILTER_MIN_MAG_LINEAR_MIP_POINT;

	if (name.compare("D3D11_FILTER_MIN_MAG_MIP_LINEAR") == 0)
		return D3D11_FILTER_MIN_MAG_MIP_LINEAR;

	if (name.compare("D3D11_FILTER_ANISOTROPIC") == 0)
		return D3D11_FILTER_ANISOTROPIC;

	if (name.compare("D3D11_FILTER_COMPARISON_MIN_MAG_MIP_POINT") == 0)
		return D3D11_FILTER_COMPARISON_MIN_MAG_MIP_POINT;

	if (name.compare("D3D11_FILTER_COMPARISON_MIN_MAG_POINT_MIP_LINEAR") == 0)
		return D3D11_FILTER_COMPARISON_MIN_MAG_POINT_MIP_LINEAR;

	if (name.compare("D3D11_FILTER_COMPARISON_MIN_POINT_MAG_LINEAR_MIP_POINT") == 0)
		return D3D11_FILTER_COMPARISON_MIN_POINT_MAG_LINEAR_MIP_POINT;

	if (name.compare("D3D11_FILTER_COMPARISON_MIN_POINT_MAG_MIP_LINEAR") == 0)
		return D3D11_FILTER_COMPARISON_MIN_POINT_MAG_MIP_LINEAR;

	if (name.compare("D3D11_FILTER_COMPARISON_MIN_LINEAR_MAG_MIP_POINT") == 0)
		return D3D11_FILTER_COMPARISON_MIN_LINEAR_MAG_MIP_POINT;

	if (name.compare("D3D11_FILTER_COMPARISON_MIN_LINEAR_MAG_POINT_MIP_LINEAR") == 0)
		return D3D11_FILTER_COMPARISON_MIN_LINEAR_MAG_POINT_MIP_LINEAR;

	if (name.compare("D3D11_FILTER_COMPARISON_MIN_MAG_LINEAR_MIP_POINT") == 0)
		return D3D11_FILTER_COMPARISON_MIN_MAG_LINEAR_MIP_POINT;

	if (name.compare("D3D11_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR") == 0)
		return D3D11_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR;

	if (name.compare("D3D11_FILTER_COMPARISON_ANISOTROPIC") == 0)
		return D3D11_FILTER_COMPARISON_ANISOTROPIC;

}

D3D11_TEXTURE_ADDRESS_MODE getAddresMode(string name)
{
	if (name.compare("D3D11_TEXTURE_ADDRESS_WRAP") == 0)
		return D3D11_TEXTURE_ADDRESS_WRAP;

	if (name.compare("D3D11_TEXTURE_ADDRESS_MIRROR") == 0)
		return D3D11_TEXTURE_ADDRESS_MIRROR;

	if (name.compare("D3D11_TEXTURE_ADDRESS_CLAMP") == 0)
		return D3D11_TEXTURE_ADDRESS_CLAMP;

	if (name.compare("D3D11_TEXTURE_ADDRESS_BORDER") == 0)
		return D3D11_TEXTURE_ADDRESS_BORDER;

	if (name.compare("D3D11_TEXTURE_ADDRESS_MIRROR_ONCE") == 0)
		return D3D11_TEXTURE_ADDRESS_MIRROR_ONCE;
}

D3D11_COMPARISON_FUNC getFunc(string name)
{
	if (name.compare("D3D11_COMPARISON_NEVER") == 0)
		return D3D11_COMPARISON_NEVER;

	if (name.compare("D3D11_COMPARISON_LESS") == 0)
		return D3D11_COMPARISON_LESS;

	if (name.compare("D3D11_COMPARISON_EQUAL") == 0)
		return D3D11_COMPARISON_EQUAL;

	if (name.compare("D3D11_COMPARISON_LESS_EQUAL") == 0)
		return D3D11_COMPARISON_LESS_EQUAL;

	if (name.compare("D3D11_COMPARISON_GREATER") == 0)
		return D3D11_COMPARISON_GREATER;

	if (name.compare("D3D11_COMPARISON_NOT_EQUAL") == 0)
		return D3D11_COMPARISON_NOT_EQUAL;

	if (name.compare("D3D11_COMPARISON_GREATER_EQUAL") == 0)
		return D3D11_COMPARISON_GREATER_EQUAL;

	if (name.compare("D3D11_COMPARISON_ALWAYS") == 0)
		return D3D11_COMPARISON_ALWAYS;
}


bool SamplerStateResource::load()
{
	ifstream file(getFilename());
	string line;

	D3D11_SAMPLER_DESC desc;
	
	getline(file, line);
	desc.Filter = getFilter(line);

	getline(file, line);
	desc.AddressU = getAddresMode(line);

	getline(file, line);
	desc.AddressV = getAddresMode(line);

	getline(file, line);
	desc.AddressW = getAddresMode(line);

	getline(file, line);
	sscanf_s(line.c_str(), "%f", &desc.MipLODBias);

	getline(file, line);
	sscanf_s(line.c_str(), "%d", &desc.MaxAnisotropy);

	getline(file, line);
	desc.ComparisonFunc = getFunc(line);

	getline(file, line);
	float border[4];
	sscanf_s(line.c_str(), "%f %f %f %f", &desc.BorderColor[0], &desc.BorderColor[1], &desc.BorderColor[2], &desc.BorderColor[3]);
	desc.BorderColor[0] = border[0];
	desc.BorderColor[1] = border[1];
	desc.BorderColor[2] = border[2];
	desc.BorderColor[3] = border[3];

	getline(file, line);
	sscanf_s(line.c_str(), "%f", &desc.MinLOD);

	getline(file, line);
	if (line.compare("D3D11_FLOAT32_MAX") == 0)
		desc.MaxLOD = D3D11_FLOAT32_MAX;
	else
		sscanf_s(line.c_str(), "%f", &desc.MaxLOD);
	
	file.close();

	HRESULT hr = GraphicsManager::currentDevice()->CreateSamplerState(&desc, &sampler);

	if (FAILED(hr)) return false;

	return true;
}

void SamplerStateResource::release()
{
	sampler->Release();
	sampler = NULL;
}