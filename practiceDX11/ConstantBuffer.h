#pragma once



template<typename T>
class ConstantBuffer
{
public:

	ConstantBuffer(ComPtr<ID3D11Device> device,
		ComPtr<ID3D11DeviceContext>deviceContext)
	:_device(device),_deviceContext(deviceContext)
	{

	}
	ComPtr<ID3D11Buffer> GetComPtr() { return _constantBuffer; }

	void Create() {// 만약 버퍼의 용도를 변경하고자 한다면 이 함수의 인자로 넣어서 진행하도록 한다.


		D3D11_BUFFER_DESC desc;

		ZeroMemory(&desc, sizeof(desc));
		desc.Usage = D3D11_USAGE_DYNAMIC;//cpu wr+ gpu read
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;// 용도적시 
		desc.ByteWidth = sizeof(T);
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		HRESULT hr = _device->CreateBuffer(&desc, nullptr, _constantBuffer.GetAddressOf());
		assert(SUCCEEDED(hr));
	}
	void CopyData(const T& data) {
		D3D11_MAPPED_SUBRESOURCE subResource;
		ZeroMemory(&subResource, sizeof(subResource));


		_deviceContext->Map(_constantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);
		::memcpy(subResource.pData, &data, sizeof(data));
		_deviceContext->Unmap(_constantBuffer.Get(), 0);


	}

private:

	ComPtr<ID3D11Device> _device;
	ComPtr<ID3D11DeviceContext> _deviceContext;
	ComPtr<ID3D11Buffer> _constantBuffer;





};

