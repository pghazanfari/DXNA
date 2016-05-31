#include "BasicTexturedParticleMaterial.h"
#include "GraphicsManager.h"
#include "ResourceManager.h"
#include "BlendStates.h"

BasicTexturedParticleMaterial::BasicTexturedParticleMaterial() : Material("BasicTexturedParticle.cvs", "BasicTexturedParticle.cps", "BasicTexturedParticle.cgs", "particles.il")
{
	bufferData = ParticleDataBuffer();
	perObjectBuffer = GraphicsManager::CreateConstantBuffer(&bufferData, sizeof(ParticleDataBuffer));

	D3D11_BLEND_DESC desc;
	BlendStates::AlphaBlend(0, desc);
	
	HRESULT hr = GraphicsManager::currentDevice()->CreateBlendState(&desc, &blendstate);
	if (FAILED(hr))
		MessageBox(NULL, "Error Creating Blend State.", "DirectX Error", MB_OK);

	D3D11_DEPTH_STENCIL_DESC dsDesc;
	dsDesc.DepthEnable = FALSE;
	dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dsDesc.DepthFunc = D3D11_COMPARISON_LESS;
	dsDesc.StencilEnable = false;
	dsDesc.StencilReadMask = D3D11_DEFAULT_STENCIL_READ_MASK;
	dsDesc.StencilWriteMask = D3D11_DEFAULT_STENCIL_WRITE_MASK;
	dsDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
	dsDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	dsDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_REPLACE;
	dsDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	dsDesc.BackFace = dsDesc.FrontFace;

	hr = GraphicsManager::currentDevice()->CreateDepthStencilState(&dsDesc, &depthstencil);
	if (FAILED(hr))
		MessageBox(NULL, "Error Creating Depth Stencil State.", "DirectX Error", MB_OK);

	sampler = (ID3D11SamplerState*)ResourceManager::Manager()->request("default.ss");
}

BasicTexturedParticleMaterial::BasicTexturedParticleMaterial(const char* vs, const char* ps, const char* gs) : Material(vs, ps, gs, "particles.il")
{
	bufferData = ParticleDataBuffer();
	perObjectBuffer = GraphicsManager::CreateConstantBuffer(&bufferData, sizeof(ParticleDataBuffer));

	D3D11_BLEND_DESC desc;
	BlendStates::AlphaBlend(0, desc);
	BlendStates::AdditiveBlend(0, desc);
	HRESULT hr = GraphicsManager::currentDevice()->CreateBlendState(&desc, &blendstate);
	if (FAILED(hr))
		MessageBox(NULL, "Error Creating Blend State.", "DirectX Error", MB_OK);

	D3D11_DEPTH_STENCIL_DESC dsDesc;
	dsDesc.DepthEnable = FALSE;
	dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dsDesc.DepthFunc = D3D11_COMPARISON_LESS;
	dsDesc.StencilEnable = false;
	dsDesc.StencilReadMask = D3D11_DEFAULT_STENCIL_READ_MASK;
	dsDesc.StencilWriteMask = D3D11_DEFAULT_STENCIL_WRITE_MASK;
	dsDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
	dsDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	dsDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_REPLACE;
	dsDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	dsDesc.BackFace = dsDesc.FrontFace;

	hr = GraphicsManager::currentDevice()->CreateDepthStencilState(&dsDesc, &depthstencil);
	if (FAILED(hr))
		MessageBox(NULL, "Error Creating Depth Stencil State.", "DirectX Error", MB_OK);

	sampler = (ID3D11SamplerState*)ResourceManager::Manager()->request("default.ss");
}

BasicTexturedParticleMaterial::~BasicTexturedParticleMaterial()
{
	perObjectBuffer->Release();
}

void BasicTexturedParticleMaterial::SetTexture(const char* fn)
{
	if (texture != NULL)
		ResourceManager::Manager()->release(textureName);

	textureName = fn;
	texture = (ID3D11ShaderResourceView*)ResourceManager::Manager()->request(fn);
}

void BasicTexturedParticleMaterial::apply()
{
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	GraphicsManager::currentContext()->Map(perObjectBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	ParticleDataBuffer* buff = (ParticleDataBuffer*)mappedResource.pData;
	buff->alphaFinal = bufferData.alphaFinal;
	buff->alphaInitial = bufferData.alphaInitial;
	buff->rotationFinal = bufferData.rotationFinal;
	buff->rotationInitial = bufferData.rotationInitial;
	buff->scaleFinal = bufferData.scaleFinal;
	buff->scaleInitial = bufferData.scaleInitial;
	buff->NumLiveParticles = bufferData.NumLiveParticles;
	buff->ParticleStartIndex = bufferData.ParticleStartIndex;
	buff->MaxParticleCount = bufferData.MaxParticleCount;
	buff->TimeBetweenParticles = bufferData.TimeBetweenParticles;
	buff->TimeSinceFirstLiveParticle = bufferData.TimeSinceFirstLiveParticle;
	buff->Lifespan = bufferData.Lifespan;
	buff->EmitterPosition = bufferData.EmitterPosition;
	buff->Speed = bufferData.Speed;
	GraphicsManager::currentContext()->Unmap(perObjectBuffer, 0);
	GraphicsManager::currentContext()->VSSetConstantBuffers(1, 1, &perObjectBuffer);
	GraphicsManager::currentContext()->GSSetConstantBuffers(1, 1, &perObjectBuffer);
	GraphicsManager::currentContext()->PSSetConstantBuffers(1, 1, &perObjectBuffer);

	GraphicsManager::currentContext()->PSSetSamplers(0, 1, &sampler);
	GraphicsManager::currentContext()->PSSetShaderResources(0, 1, &texture);

	GraphicsManager::currentContext()->OMSetBlendState(blendstate, NULL, 0xffffffff);
	
	GraphicsManager::currentContext()->OMSetDepthStencilState(depthstencil, 0);
}

void BasicTexturedParticleMaterial::SetParameter(string name, void* value)
{
	if (name.compare("InitialAlpha") == 0)
		bufferData.alphaInitial = *((float*)value);

	if (name.compare("FinalAlpha") == 0)
		bufferData.alphaFinal = *((float*)value);

	if (name.compare("InitialRotation") == 0)
		bufferData.rotationInitial = *((float*)value);

	if (name.compare("FinalRotation") == 0)
		bufferData.rotationFinal = *((float*)value);

	if (name.compare("InitialScale") == 0)
		bufferData.scaleInitial = *((float*)value);

	if (name.compare("FinalScale") == 0)
		bufferData.scaleFinal = *((float*)value);

	if (name.compare("NumLiveParticles") == 0)
		bufferData.NumLiveParticles = *((int*)value);

	if (name.compare("ParticleStartIndex") == 0)
		bufferData.ParticleStartIndex = *((int*)value);

	if (name.compare("MaxParticleCount") == 0)
		bufferData.MaxParticleCount = *((int*)value);

	if (name.compare("TimeBetweenParticles") == 0)
		bufferData.TimeBetweenParticles = *((float*)value);

	if (name.compare("TimeSinceFirstLiveParticle") == 0)
		bufferData.TimeSinceFirstLiveParticle = *((float*)value);

	if (name.compare("Lifespan") == 0)
		bufferData.Lifespan = *((float*)value);

	if (name.compare("EmitterPosition") == 0)
		bufferData.EmitterPosition = *((Vector3*)value);

	if (name.compare("Speed") == 0)
		bufferData.Speed = *((float*)value);
}