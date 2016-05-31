#include "MeshDeclaration.h"
#include "Material.h"

#pragma once

class Mesh
{
private:
	Material* material;
	ID3D11Buffer* vbuffer;
	ID3D11Buffer* ibuffer;
	UINT vertexCount;
	UINT indexCount;
	bool indexed;

	inline Mesh() {}

public:
	Mesh(MeshVertex* vertices, UINT* indices, const UINT& count, const UINT& icount, Material* sh);
	Mesh(MeshVertex* vertices, const UINT& count, Material* sh);
	inline ~Mesh()
	{
		vbuffer->Release();
		if (indexed) ibuffer->Release();
	}

	inline Material* getMaterial() const { return material; }
	void setMaterial(Material* sh);

	void draw();
};