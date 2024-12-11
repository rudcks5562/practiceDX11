#pragma once
class VertexBuffer
{

public:
	VertexBuffer();
	~VertexBuffer();

	ComPtr<ID3D11Buffer> GetComPtr() { return _vertexBuffer; };

	void Create() {



	}







private:
	ComPtr<ID3D11Device> _device;
	ComPtr<ID3D11Buffer> _vertexBuffer;

	uint32 _stride = 0;
	uint32 _offset = 0;
	uint32 _count = 0;





};

