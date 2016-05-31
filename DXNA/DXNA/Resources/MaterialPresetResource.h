#include "Resource.h"
#include "GraphicsManager.h"
#include <unordered_map>

using namespace std;

#pragma once

class MaterialPresetResource : public Resource
{
private:
	unordered_map<string, void*> presets;

protected:
	bool load();
	void release();

public:
	inline MaterialPresetResource(const char* file) : Resource(file){}
	inline void* getResource() { return &presets; }
};