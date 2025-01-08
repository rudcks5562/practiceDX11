#pragma once
#include "ResourceBase.h"

class Mesh : public ResourceBase
{
	using Super = ResourceBase;

public:
	Mesh(ComPtr<ID3D11Device> device);
	virtual ~Mesh();

	void CreateDefautRectangle();

	std::shared_ptr<VertexBuffer> GetVertexBuffer() { return _vertexBuffer; }
	std::shared_ptr<IndexBuffer> GetIndexBuffer() { return _indexBuffer; }

private:
	ComPtr<ID3D11Device> _device;

	// Mesh
	std::shared_ptr<Geometry<VertexTextureData>> _geometry;
	std::shared_ptr<VertexBuffer> _vertexBuffer;
	std::shared_ptr<IndexBuffer> _indexBuffer;
};

