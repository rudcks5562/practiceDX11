#include "stdafx.h"
#include "Mesh.h"


Mesh::Mesh(ComPtr<ID3D11Device> device):Super(ResourceType::Mesh),_device(device)
{

}

Mesh::~Mesh()
{

}

void Mesh::CreateDefaultRectangle()
{
	_geometry = std::make_shared<Geometry<VertexTextureData>>();
	//_geometry = std::make_shared<Geometry<VertexColorData>>();
	GeometryHelper::CreateRectangle(_geometry);
	//GeometryHelper::CreateRectangle(_geometry,Color{1.0f,0.f,0.f,1.0f});
	_vertexBuffer = std::make_shared<VertexBuffer>(_device);
	_vertexBuffer->Create(_geometry->GetVertices());

	_indexBuffer = std::make_shared<IndexBuffer>(_device);
	_indexBuffer->Create(_geometry->GetIndices());//idx buff





}
