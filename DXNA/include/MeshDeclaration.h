#include "Types.h"
#include <d3d11.h>
#include <DirectXMath.h>

#pragma once

using namespace DirectX;

/*
struct MeshVertex
{
	Vector3 Position;
	Vector3 Color;
};
*/

struct MeshVertex
{
	Vector3 Position;
	Vector3 Normal;
	Vector2 TextureCoordinates;
};

static const D3D11_INPUT_ELEMENT_DESC MeshVertexDescription[] =
{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	//{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, sizeof(Vector3), D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, sizeof(Vector3), D3D11_INPUT_PER_VERTEX_DATA, 0 }
};

static const D3D11_INPUT_ELEMENT_DESC DefaultMeshVertexDescription[] =
{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 }
};