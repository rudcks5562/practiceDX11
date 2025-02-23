#include "stdafx.h"
#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(ComPtr<ID3D11Device> device):_device(device)
{
}

IndexBuffer::~IndexBuffer()
{
}

void IndexBuffer::Create(const std::vector<uint32>& indices)
{

	_stride = sizeof(uint32);
	_count = static_cast<uint32>(indices.size());

	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.Usage = D3D11_USAGE_IMMUTABLE; // 용도 immutable-> read only gpu!!
	desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	desc.ByteWidth = (uint32)(_stride * _count);// 정점1개크기* 구성개수

	D3D11_SUBRESOURCE_DATA data;
	ZeroMemory(&data, sizeof(data));
	data.pSysMem = indices.data();// 첫번째 시작주소 전달

	HRESULT hr = _device->CreateBuffer(&desc, &data, _indexBuffer.GetAddressOf());

	assert(SUCCEEDED(hr));
}
