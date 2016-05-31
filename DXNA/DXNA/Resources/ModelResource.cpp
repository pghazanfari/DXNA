#include "ModelResource.h"
#include "ResourceManager.h"
#include <sstream>
#include <fstream>
#include "Material.h"

bool ModelResource::load()
{
	ifstream file(getFilename());
	string line;

	ResourceManager* manager = ResourceManager::Manager();

	model = new Model();

	int mcount = 0;
	getline(file, line);//Read num meshes.
	sscanf_s(line.c_str(), "%d", &mcount);

	for (int n = 0; n < mcount; n++)
	{
		char mname[1024];
		MeshVertex* vertices;
		UINT* indices;
		int vcount = 0;
		int pcount = 0;

		//Get Mesh Name
		getline(file, line);
		strcpy_s(mname, line.c_str());

		//Read Vertices
		getline(file, line);
		vcount = 0;
		sscanf_s(line.c_str(), "%d", &vcount);
		vertices = new MeshVertex[vcount];
		for (int i = 0; i < vcount; i++)
		{
			double x = 0;
			double y = 0;
			double z = 0;
			getline(file, line);
			sscanf_s(line.c_str(), "%lf %lf %lf", &x, &y, &z);
			vertices[i].Position.X = (float)x;
			vertices[i].Position.Y = (float)y;
			vertices[i].Position.Z = (float)z;
		}

		//Read Polygon Data
		getline(file, line);
		pcount = 0;
		sscanf_s(line.c_str(), "%d", &pcount);
		indices = new UINT[pcount * 3];
		for (int i = 0; i < pcount; i++)
		{
			int p1 = 0;
			int p2 = 0;
			int p3 = 0;
			getline(file, line);
			sscanf_s(line.c_str(), "%d %d %d", &p1, &p2, &p3);
			indices[i * 3] = p1;
			indices[i * 3 + 1] = p2;
			indices[i * 3 + 2] = p3;

			//Read Normals
			getline(file, line);
			double n1x = 0;
			double n1y = 0;
			double n1z = 0;
			double n2x = 0;
			double n2y = 0;
			double n2z = 0;
			double n3x = 0;
			double n3y = 0;
			double n3z = 0;
			sscanf_s(line.c_str(), "%lf %lf %lf %lf %lf %lf %lf %lf %lf", &n1x, &n1y, &n1z, &n2x, &n2y, &n2z, &n3x, &n3y, &n3z);
			vertices[p1].Normal.X = (float)n1x;
			vertices[p1].Normal.Y = (float)n1y;
			vertices[p1].Normal.Z = (float)n1z;

			vertices[p1].Normal.X = (float)n2x;
			vertices[p2].Normal.Y = (float)n2y;
			vertices[p2].Normal.Z = (float)n2z;

			vertices[p3].Normal.X = (float)n3x;
			vertices[p3].Normal.Y = (float)n3y;
			vertices[p3].Normal.Z = (float)n3z;

			//Read UV
			getline(file, line);
			sscanf_s(line.c_str(), "%lf %lf %lf %lf %lf %lf", &n1x, &n1y, &n2x, &n2y, &n3x, &n3y);
			vertices[p1].TextureCoordinates.X = (float)n1x;
			vertices[p1].TextureCoordinates.Y = (float)n1y;

			vertices[p2].TextureCoordinates.X = (float)n2x;
			vertices[p2].TextureCoordinates.Y = (float)n2y;

			vertices[p3].TextureCoordinates.X = (float)n3x;
			vertices[p3].TextureCoordinates.Y = (float)n3y;

		}

		//Add Mesh to Model
		model->append(mname, new Mesh(vertices, indices, vcount, pcount * 3, NULL));
	}

	//Read Mesh to Material Mappings
	while (getline(file, line))
	{
		if (line.length() >= 3 && line.at(0) == 'm' && line.at(1) == 'p' && line.at(2) == ' ')
		{
			//Found Mapping
			line = line.c_str() + 3;
			istringstream iss(line);
			char mName[256];
			char matName[256];
			char fName[256];
			iss >> mName; //Mesh Name
			iss >> matName; //Material Name
			iss >> fName; //Material Preset Name
			Material* m = Material::Generate(matName);
			std::unordered_map<string, void*>* prs = (std::unordered_map<string, void*>*)manager->request(fName);
			m->SetPreset(prs);
			manager->release(fName);
			model->get(mName)->setMaterial(m);

			list.insertAtEnd(fName);
		}
	}

	file.close();



	return true;
}

void ModelResource::release()
{
	SingleListNode<string>* head = list.getHead();
	while (head != NULL)
	{
		ResourceManager::Manager()->release(head->getData().c_str());
		head = head->getNext();
	}

	delete model;
	model = NULL;
}