#include "BasicTexturedModelMaterial.h"
#include "GraphicsManager.h"
#include "ResourceManager.h"

BasicTexturedModelMaterial::BasicTexturedModelMaterial() : Material("BasicTexturedModel.cvs", "BasicTexturedModel.cps","default.il")
{
	bufferData = PerObjectBuffer();
	bufferData.World = Matrix::Identity();
	perObjectBuffer = GraphicsManager::CreateConstantBuffer(&bufferData, sizeof(PerObjectBuffer));

	sampler = (ID3D11SamplerState*)ResourceManager::Manager()->request("default.ss");
}

BasicTexturedModelMaterial::~BasicTexturedModelMaterial()
{
	perObjectBuffer->Release();
	ResourceManager::Manager()->release("default.ss");
}

void BasicTexturedModelMaterial::apply() 
{
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	GraphicsManager::currentContext()->Map(perObjectBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	PerObjectBuffer* buff = (PerObjectBuffer*)mappedResource.pData;
	buff->World = bufferData.World;
	GraphicsManager::currentContext()->Unmap(perObjectBuffer, 0);
	GraphicsManager::currentContext()->VSSetConstantBuffers(1, 1, &perObjectBuffer);
	if (gs) GraphicsManager::currentContext()->GSSetConstantBuffers(1, 1, &perObjectBuffer);
	GraphicsManager::currentContext()->PSSetSamplers(0, 1, &sampler);
	GraphicsManager::currentContext()->PSSetShaderResources(0, 1, &texture);
}

void BasicTexturedModelMaterial::SetTexture(const char* fn)
{
	if (texture != NULL)
		ResourceManager::Manager()->release(textureName);

	textureName = fn;
	texture = (ID3D11ShaderResourceView*)ResourceManager::Manager()->request(fn);
}

void BasicTexturedModelMaterial::SetParameter(string name, void* value)
{
	if (name.compare("Diffuse") == 0)
	{
		string* nm = (string*)value;
		SetTexture(nm->c_str());
	}

	if (name.compare("World") == 0)
	{
		bufferData.World = *((Matrix*)value);
	}
}