#include "Mesh.h"
#include <unordered_map>

using namespace std;

#pragma once

class Model {
	private:
		unordered_map<string, Mesh*> meshes;

	public:
		inline Model() : meshes(unordered_map<string, Mesh*>()) {}
		inline ~Model() 
		{
			for (auto it = meshes.begin(); it != meshes.end(); ++it){
				delete it->second;
			}
		}

		inline void append(string name, Mesh* m) { meshes[name] = m; }
		inline Mesh* get(string n) { return meshes[n]; }

		inline void draw()
		{
			for (auto it = meshes.begin(); it != meshes.end(); ++it){
				it->second->draw();
			}
		}
};