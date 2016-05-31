#include "Resource.h"
#include "GraphicsManager.h"
#include "Common.h"
#pragma once

class GeometryShaderResource : public Resource
{
private:
	ID3D11GeometryShader* gs;

protected:
	bool load();
	void release();

public:
	inline GeometryShaderResource(const char* file) : Resource(file) {}
	inline void* getResource() { return gs; }
};