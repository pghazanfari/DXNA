#include <unordered_map>
#include <Windows.h>
#include <iostream>
#include "Resource.h"

#pragma once

using namespace std;

class ResourceManager
{
	private:
		static const char* CONTENT_DIRECTORY;

		static ResourceManager* manager;
		unordered_map<string, Resource*> resources;
		unordered_map<string, string> filepaths;
		bool autorelease = false;

		inline string getFileExt(string file)
		{
			size_t indx = file.find_last_of('.');
			if (indx == string::npos)
			{
				MessageBox(NULL, "Invalid File Name.", file.c_str(), MB_OK);
				exit(0);
			}
			return file.c_str() + indx;
		}

		inline const char* getFileName(string file)
		{
			size_t indx = file.find_last_of('\\');
			if (indx == string::npos)
			{
				MessageBox(NULL, "Invalid File Name.", file.c_str(), MB_OK);
				exit(0);
			}
			return file.c_str() + indx + 1;
		}

		inline Resource* generateResource(const char* file)
		{
			string ext = getFileExt(file);

			//if (ext.compare(".dds") == 0) return new TextureResource(file);

			//if (ext.compare(".mtl") == 0) return new MaterialPresetResource(file);

			//if (ext.compare(".il") == 0) return new InputLayoutResource(file);

			//if (ext.compare(".ss") == 0) return new SamplerStateResource(file);

			//if (ext.compare(".pbam") == 0) return new ModelResource(file);

			//if (ext.compare(".cvs") == 0) return new VertexShaderResource(file);

			//if (ext.compare(".cps") == 0) return new PixelShaderResource(file);

			//if (ext.compare(".cgs") == 0) return new GeometryShaderResource(file);

			return NULL;
		}

		inline bool validFile(const char* file)
		{
			string ext = getFileExt(file);

			return
				ext.compare(".dds") == 0 ||
				ext.compare(".pbam") == 0 ||
				ext.compare(".cvs") == 0 ||
				ext.compare(".cps") == 0 ||
				ext.compare(".ss") == 0 ||
				ext.compare(".il") == 0 ||
				ext.compare(".cgs") == 0 ||
				ext.compare(".mtl") == 0;
		}

		void index(const char* path)
		{
			const char *tmpPath = path;
			string sPath(tmpPath);

			WIN32_FIND_DATA FindFileData;
			string sTmpPath = sPath;
			sTmpPath += "\\*.*";

			string currFile = "";

			HANDLE hFind = FindFirstFile(sTmpPath.c_str(), &FindFileData);
			if (hFind == INVALID_HANDLE_VALUE) {
				MessageBox(NULL, "Invalid File Handle.", "Indexing Error", MB_OK);
				return;
			}
			else
			{
				do
				{
					//check if its a directory...
					if ((FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
					{
						string filePath = FindFileData.cFileName;
						//ignore '.' and '..'
						if (strcmp(".", filePath.c_str()) && strcmp("..", filePath.c_str()))
						{
							//Dont list recycle bin content...
							if (filePath == "$RECYCLE.BIN" || filePath == "$Recycle.Bin")
								continue;
							sTmpPath = sPath + "\\" + filePath;
							index(sTmpPath.c_str());

						}
					}
					else                       //its a file...
					{
						sTmpPath = sPath + "\\";
						currFile = sTmpPath + FindFileData.cFileName;



						if (validFile(FindFileData.cFileName))
						{
							resources[FindFileData.cFileName] =  NULL;
							filepaths[FindFileData.cFileName] = currFile;
						}
					}
				} while (FindNextFile(hFind, &FindFileData) != 0);

				FindClose(hFind);

			}

			return;
		}

	public:
		inline ResourceManager() :  autorelease(false) { filepaths = unordered_map<string, string>();  resources = unordered_map<string, Resource*>(); manager = this; index(ResourceManager::CONTENT_DIRECTORY); }
		inline ~ResourceManager()
		{
			for (auto it = resources.begin(); it != resources.end(); ++it)
			{
				if (it->second != NULL && it->second->isValid())
					it->second->Release();
			}
		}

		inline const char* getFilePath(const char* file)
		{
			return filepaths[file].c_str();
		}
		
		inline void* request(const char* file)
		{
			if (resources.find(file) == resources.end())
			{
				MessageBox(NULL, "Resource has not been indexed.", file, MB_OK);
				exit(0);
			}

			if (resources[file] == NULL)
			{

				Resource* r = generateResource(filepaths[file].c_str());
				if (r == NULL)
				{
					MessageBox(NULL, "Could not create resource for specified file type.", file, MB_OK);
					exit(0);
				}

				if (!r->Load())
				{
					MessageBox(NULL, "Error Loading Resource.", file, MB_OK);
					exit(0);
				}

				resources[file] = r;
				resources[file]->counter++;
				return r->getResource();


				return NULL;

			}
			else
			{
				resources[file]->counter++;
				return resources[file]->getResource();
			}
				
		}

		inline void release(const char* file)
		{
			if (resources[file] == NULL || resources[file]->counter <= 0) return;

			if (--resources[file]->counter <= 0)// && autorelease)
			{
				resources[file]->Release();
				resources[file] = NULL;
			}
		}

		static ResourceManager* Manager()
		{
			if (manager == NULL)
				new ResourceManager();

			return manager;
		}
};