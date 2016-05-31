#include "MaterialPresetResource.h"
#include <fstream>
#include <sstream>

bool MaterialPresetResource::load()
{
	presets = unordered_map<string, void*>();

	ifstream file(getFilename());
	string line;

	getline(file, line);
	if (line.at(0) == 't')
	{
		stringstream ls(line.c_str() + 2);
		string param;
		string val;
		ls >> param;
		ls >> val;
		presets[param] = new string(val);
	}

	//Set Float Values - Actually do this in the future.
	if (line.at(0) == 'f')
	{
		if (line.at(1) == ' ')
		{
		}

		if (line.at(1) == '2')
		{
		}

		if (line.at(1) == '3')
		{
		}

		if (line.at(1) == '4')
		{
		}
	}

	file.close();
	
	return true;
}

void MaterialPresetResource::release()
{
	for (auto it = presets.begin(); it != presets.end(); ++it)
	{
		delete it->second;
	}
}