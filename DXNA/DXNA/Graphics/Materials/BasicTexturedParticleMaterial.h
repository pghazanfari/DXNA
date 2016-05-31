#include "Common.h"
#include"Material.h"
#include "ParticleDataBuffer.h"


class BasicTexturedParticleMaterial : public Material
{
private:
	ParticleDataBuffer bufferData;
	ID3D11Buffer* perObjectBuffer;

	ID3D11SamplerState* sampler;
	const char* textureName;
	ID3D11ShaderResourceView* texture;

	ID3D11BlendState* blendstate;
	ID3D11DepthStencilState* depthstencil;

public:
	BasicTexturedParticleMaterial();
	BasicTexturedParticleMaterial(const char* vs, const char* ps, const char* gs);
	~BasicTexturedParticleMaterial();

	void BasicTexturedParticleMaterial::SetTexture(const char* fn);
	void SetParameter(string name, void* value);

protected:
	void apply();
};