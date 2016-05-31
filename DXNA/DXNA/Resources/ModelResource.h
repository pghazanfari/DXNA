#include "Resource.h"
#include "Model.h"
#include "Lists.h"

#pragma once

using namespace std;

class ModelResource : public Resource
{
	private:
		Model* model;
		SinglyLinkedList<string> list;
	

	protected:
		bool load();
		void release();

	public:
		inline ModelResource(const char* file) : Resource(file) { list = SinglyLinkedList<string>(); }
		inline void* getResource() { return model; }
};