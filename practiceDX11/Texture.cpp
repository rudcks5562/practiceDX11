#include "stdafx.h"
#include "Texture.h"

Texture::Texture(ComPtr<ID3D11Device> device)
	:Super(ResourceType::Texture),_device(device)
{
}

Texture::~Texture()
{
}

void Texture::Create(const std::wstring& path)
{
	DirectX::TexMetadata md;
	DirectX::ScratchImage img;
	HRESULT hr = ::LoadFromWICFile(path.c_str(), WIC_FLAGS_NONE, &md, img);// img load
	assert(SUCCEEDED(hr));

	hr = ::CreateShaderResourceView(_device.Get(), img.GetImages(), img.GetImageCount(), md, _shaderResourceView.GetAddressOf());
	assert(SUCCEEDED(hr));
	


}
