#include "Resource.h"
#include "GraphicsManager.h"

#pragma once

class VertexShaderResource : public Resource
{
private:
	ID3D11VertexShader* vs;

protected:
	bool load();
	void release();

public:
	inline VertexShaderResource(const char* file) : Resource(file) {}
	inline void* getResource() { return vs; }
};