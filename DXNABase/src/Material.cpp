#include "Material.h"
#include "ResourceManager.h"

Material::Material(const char* vs, const char* ps, const char* il) : vs_name(vs), ps_name(ps), il_name(il), gs(false)
{
	ResourceManager* manager = ResourceManager::Manager();
	vertexShader = (ID3D11VertexShader*)manager->request(vs);
	pixelShader = (ID3D11PixelShader*)manager->request(ps);
	inputLayout = (ID3D11InputLayout*)manager->request(il);
}

Material::Material(const char* vs, const char* ps, const char* gs, const char* il) : vs_name(vs), ps_name(ps), il_name(il), gs_name(gs), gs(true)
{
	ResourceManager* manager = ResourceManager::Manager();
	vertexShader = (ID3D11VertexShader*)manager->request(vs);
	pixelShader = (ID3D11PixelShader*)manager->request(ps);
	geometryShader = (ID3D11GeometryShader*)manager->request(gs);
	inputLayout = (ID3D11InputLayout*)manager->request(il);
}

Material::~Material()
{
	ResourceManager* manager = ResourceManager::Manager();
	manager->release(vs_name);
	manager->release(ps_name);
	if (gs) manager->release(gs_name);
	manager->release(il_name);
}

Material* Material::Generate(string name)
{
	//if (name.compare("BasicTexturedModel") == 0) return new BasicTexturedModelMaterial();

	return NULL;
}