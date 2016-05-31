#include "Resource.h"
#include "GraphicsManager.h"

#pragma once

class InputLayoutResource : public Resource
{
private:
	ID3D11InputLayout* ilayout;

protected:
	bool load();
	void release();

public:
	inline InputLayoutResource(const char* file) : Resource(file) {}
	inline void* getResource() { return ilayout; }
};