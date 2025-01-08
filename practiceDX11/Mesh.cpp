#include "stdafx.h"
#include "Mesh.h"


Mesh::Mesh(ComPtr<ID3D11Device> device)
	: Super(ResourceType::Mesh), _device(device)
{

}

Mesh::~Mesh()
{

}

void Mesh::CreateDefautRectangle()
{
	_geometry = std::make_shared<Geometry<VertexTextureData>>();
	GeometryHelper::CreateRectangle(_geometry);

	_vertexBuffer = std::make_shared<VertexBuffer>(_device);
	_vertexBuffer->Create(_geometry->GetVertices());
	_indexBuffer = std::make_shared<IndexBuffer>(_device);
	_indexBuffer->Create(_geometry->GetIndices());
}