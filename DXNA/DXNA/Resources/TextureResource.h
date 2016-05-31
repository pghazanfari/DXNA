#include "Resource.h"
#include "GraphicsManager.h"

#pragma once

//Currently Broken because this method is deprecated: D3DX11CreateShaderResourceViewFromFile

class TextureResource : public Resource
{
	private:
		ID3D11ShaderResourceView* resource;

	protected:
		inline bool load() 
		{ 
			const char* f = getFilename();
			/*
			HRESULT hr = D3DX11CreateShaderResourceViewFromFile(GraphicsManager::currentDevice(), getFilename(), NULL, NULL, &resource, NULL);
			if (FAILED(hr))
			{
				MessageBox(NULL, "Could not load resource.", getFilename(), MB_OK);
				return false;
			}
			*/

			return true;
		}
		inline void release() { resource->Release(); resource = NULL; }

	public:
		inline TextureResource(const char* file) : Resource(file) {}
		inline void* getResource() { return resource; }

};