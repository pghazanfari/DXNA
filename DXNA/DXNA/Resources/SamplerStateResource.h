#include "GraphicsManager.h"
#include "Resource.h"

#pragma once

class SamplerStateResource : public Resource
{
private:
	ID3D11SamplerState* sampler;

protected:
	bool load();
	void release();

public:
	inline SamplerStateResource(const char* file) : Resource(file) {}
	inline void* getResource() { return sampler; }
};