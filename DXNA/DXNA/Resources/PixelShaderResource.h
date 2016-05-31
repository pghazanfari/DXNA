#include "Resource.h"
#include "GraphicsManager.h"

#pragma once

class PixelShaderResource : public Resource
{
	private:
		ID3D11PixelShader* ps;

	protected:
		bool load();
		void release();

	public:
		inline PixelShaderResource(const char* file) : Resource(file) {}
		inline void* getResource() { return ps; }
};