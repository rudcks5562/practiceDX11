#pragma once
#include "ResourceBase.h"
class Mesh : public ResourceBase
{

	using Super = ResourceBase;

public:
	Mesh(ComPtr<ID3D11Device> device);
	virtual ~Mesh();

	void CreateDefaultRectangle();

	std::shared_ptr<VertexBuffer> GetVertexBuffer() { return _vertexBuffer; }
	std::shared_ptr<IndexBuffer> GetIndexBuffer() { return _indexBuffer; }


private:

	ComPtr<ID3D11Device> _device;
	//Mesh
// 
//Geometry 
	std::shared_ptr<Geometry<VertexTextureData>> _geometry;
	//std::shared_ptr<Geometry<VertexColorData>> _geometry;
	//std::vector<Vertex> _vertices;
	// CPU<->RAM(memory) - GPU-VRAM
	//ComPtr<ID3D11Buffer> _vertexBuffer = nullptr;
	std::shared_ptr<VertexBuffer>_vertexBuffer;
	//std::vector<uint32> _indices;
	//ComPtr<ID3D11Buffer> _indexBuffer = nullptr;
	std::shared_ptr<IndexBuffer> _indexBuffer;
	//ComPtr<ID3D11InputLayout> _inputLayout = nullptr;// 버텍스 구조 묘사자.


};

