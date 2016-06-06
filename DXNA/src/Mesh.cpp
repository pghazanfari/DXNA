#include "Mesh.h"
#include "GraphicsManager.h"



Mesh::Mesh(MeshVertex* vertices, UINT* indices, const UINT& count, const UINT& icount, Material* sh) : material(sh), vertexCount(count), indexCount(icount), indexed(true)
{
	HRESULT hr;

	//Vertex Buffer
	D3D11_BUFFER_DESC vbd;
	vbd.Usage = D3D11_USAGE_IMMUTABLE;
	vbd.ByteWidth = sizeof(MeshVertex) * count;
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = 0;
	vbd.MiscFlags = 0;
	vbd.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA vinitData;
	vinitData.pSysMem = vertices;
	hr = GraphicsManager::currentDevice()->CreateBuffer(&vbd, &vinitData, &vbuffer);
	if (FAILED(hr))
		MessageBox(NULL, "Error Creating Vertex Buffer.", "DirectX Error", MB_OK);

	//Index Buffer
	D3D11_BUFFER_DESC ibd;
	ibd.Usage = D3D11_USAGE_IMMUTABLE;
	ibd.ByteWidth = sizeof(UINT) * icount;
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = 0;
	ibd.MiscFlags = 0;
	ibd.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA iinitData;
	iinitData.pSysMem = indices;
	hr = GraphicsManager::currentDevice()->CreateBuffer(&ibd, &iinitData, &ibuffer);
	if (FAILED(hr))
		MessageBox(NULL, "Error Creating Index Buffer.", "DirectX Error", MB_OK);
}

Mesh::Mesh(MeshVertex* vertices, const UINT& count, Material* sh) : material(sh), vertexCount(count), indexed(false)
{
	HRESULT hr;

	//Vertex Buffer
	D3D11_BUFFER_DESC vbd;
	vbd.Usage = D3D11_USAGE_IMMUTABLE;
	vbd.ByteWidth = sizeof(MeshVertex) * count;
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = 0;
	vbd.MiscFlags = 0;
	vbd.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA vinitData;
	vinitData.pSysMem = vertices;
	hr = GraphicsManager::currentDevice()->CreateBuffer(&vbd, &vinitData, &vbuffer);
	if (FAILED(hr))
		MessageBox(NULL, "Error Creating Vertex Buffer.", "DirectX Error", MB_OK);
}

void Mesh::setMaterial(Material* sh)
{
	material = sh;
}

void Mesh::draw()
{
	ID3D11DeviceContext* context = GraphicsManager::currentContext();

	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	UINT stride = sizeof(MeshVertex);
	UINT offset = 0;
	context->IASetVertexBuffers(0, 1, &vbuffer, &stride, &offset);
	if (indexed)
	{
		context->IASetIndexBuffer(ibuffer, DXGI_FORMAT_R32_UINT, 0);

		//Apply Material Pass
		material->Apply();

		context->DrawIndexed(indexCount, 0, 0);

		//context->IASetIndexBuffer(NULL, DXGI_FORMAT_R32_UINT, 0);
	}
	else
	{
		//Apply Material Pass
		material->Apply();

		context->Draw(vertexCount, 0);
	}

	//context->IASetVertexBuffers(0, 1, NULL, 0, 0);

}
